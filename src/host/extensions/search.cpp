#include "search.hpp"
#include <sstream>
#include <iterator>
#include <algorithm>
#include <regex>
#include <experimental/filesystem>


namespace intercept::search {

    std::string plugin_searcher::getCommandLine() {
    #if __linux__
        std::ifstream cmdline("/proc/self/cmdline");
        std::string file_contents;
        std::string line;
        while (std::getline(cmdline, line)) {
            file_contents += line;
            file_contents.push_back('\n'); //#TODO can linux even have more than one line?
        }
        std::cout << "cmdLine " << file_contents << "\n";
        return file_contents;
    #else
        return GetCommandLineA();
    #endif
    }

}

#if __linux__
#include <string.h>
#include <stdio.h>
#include <dirent.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <sys/resource.h>
intercept::search::plugin_searcher::plugin_searcher() {
    //std::experimental::filesystem::directory_iterator end_itr; // default construction yields past-the-end
    //std::error_code err;
    //std::experimental::filesystem::directory_iterator x("/proc/self", err);
    //
    //for (;
    //    x != end_itr;
    //    ++x) {
    //    if (std::experimental::filesystem::is_regular_file(x->status())) {
    //        //x->path().extension() == ".pbo";
    //        std::cout << "pbo found " << x->path() << "\n";
    //    }
    //}



    char buff[PATH_MAX];
    
    struct dirent *dp;
    DIR *dir = opendir("/proc/self/fd");
    while ((dp = readdir(dir)) != NULL) {

        ssize_t len = ::readlink((std::string("/proc/self/fd/")+ dp->d_name).c_str(), buff, sizeof(buff) - 1);
        if (len != -1) {
            buff[len] = '\0';
            std::cout << "found " << std::string(buff) << "\n";
        }
    }
    closedir(dir);
}
#else

#define NT_SUCCESS(x) ((x) >= 0)
#define STATUS_INFO_LENGTH_MISMATCH 0xc0000004

#define SystemHandleInformation 16
#define SystemHandleInformationEx 64

#define ObjectBasicInformation 0
#define ObjectNameInformation 1
#define ObjectTypeInformation 2

typedef NTSTATUS(NTAPI *_NtQuerySystemInformation)(
    ULONG SystemInformationClass,
    PVOID SystemInformation,
    ULONG SystemInformationLength,
    PULONG ReturnLength
    );
typedef NTSTATUS(NTAPI *_NtDuplicateObject)(
    HANDLE SourceProcessHandle,
    HANDLE SourceHandle,
    HANDLE TargetProcessHandle,
    PHANDLE TargetHandle,
    ACCESS_MASK DesiredAccess,
    ULONG Attributes,
    ULONG Options
    );
typedef NTSTATUS(NTAPI *_NtQueryObject)(
    HANDLE ObjectHandle,
    ULONG ObjectInformationClass,
    PVOID ObjectInformation,
    ULONG ObjectInformationLength,
    PULONG ReturnLength
    );

typedef struct _UNICODE_STRING {
    USHORT Length;
    USHORT MaximumLength;
    PWSTR Buffer;
} UNICODE_STRING, *PUNICODE_STRING;

typedef struct _SYSTEM_HANDLE {
    ULONG ProcessId;
    BYTE ObjectTypeNumber;
    BYTE Flags;
    USHORT Handle;
    PVOID Object;
    ACCESS_MASK GrantedAccess;
} SYSTEM_HANDLE, *PSYSTEM_HANDLE;

typedef struct _SYSTEM_HANDLE_EX {
    PVOID Object;
    HANDLE ProcessId;
    HANDLE Handle;
    ULONG GrantedAccess;
    USHORT CreatorBackTraceIndex;
    USHORT ObjectTypeIndex;
    ULONG HandleAttributes;
    ULONG Reserved;
} SYSTEM_HANDLE_EX, *PSYSTEM_HANDLE_EX;

typedef struct _SYSTEM_HANDLE_INFORMATION {
    ULONG HandleCount;
    SYSTEM_HANDLE Handles[1];
} SYSTEM_HANDLE_INFORMATION, *PSYSTEM_HANDLE_INFORMATION;

typedef struct _SYSTEM_HANDLE_INFORMATION_EX {
    ULONG_PTR HandleCount;
    ULONG_PTR Reserved;
    SYSTEM_HANDLE_EX Handles[1];
} SYSTEM_HANDLE_INFORMATION_EX, *PSYSTEM_HANDLE_INFORMATION_EX;

typedef enum _POOL_TYPE {
    NonPagedPool,
    PagedPool,
    NonPagedPoolMustSucceed,
    DontUseThisType,
    NonPagedPoolCacheAligned,
    PagedPoolCacheAligned,
    NonPagedPoolCacheAlignedMustS
} POOL_TYPE, *PPOOL_TYPE;

typedef struct _OBJECT_TYPE_INFORMATION {
    UNICODE_STRING Name;
    ULONG TotalNumberOfObjects;
    ULONG TotalNumberOfHandles;
    ULONG TotalPagedPoolUsage;
    ULONG TotalNonPagedPoolUsage;
    ULONG TotalNamePoolUsage;
    ULONG TotalHandleTableUsage;
    ULONG HighWaterNumberOfObjects;
    ULONG HighWaterNumberOfHandles;
    ULONG HighWaterPagedPoolUsage;
    ULONG HighWaterNonPagedPoolUsage;
    ULONG HighWaterNamePoolUsage;
    ULONG HighWaterHandleTableUsage;
    ULONG InvalidAttributes;
    GENERIC_MAPPING GenericMapping;
    ULONG ValidAccess;
    BOOLEAN SecurityRequired;
    BOOLEAN MaintainHandleCount;
    USHORT MaintainTypeList;
    POOL_TYPE PoolType;
    ULONG PagedPoolUsage;
    ULONG NonPagedPoolUsage;
} OBJECT_TYPE_INFORMATION, *POBJECT_TYPE_INFORMATION;

PVOID GetLibraryProcAddress(PSTR LibraryName, PSTR ProcName) {
    return GetProcAddress(GetModuleHandleA(LibraryName), ProcName);
}

intercept::search::plugin_searcher::plugin_searcher() {
    auto pboList = generate_pbo_list();
    for (auto& file : pboList) {
        size_t last_index = file.find_last_of("\\/");
        std::string path = file.substr(0, last_index);
        last_index = path.find_last_of("\\/");
        path = path.substr(0, last_index);
        active_mod_folder_list.push_back(path);
    }
}

std::vector<std::string> intercept::search::plugin_searcher::generate_pbo_list() {
    std::vector<std::string> _active_pbo_list;
    NTSTATUS status;
    ULONG handleInfoSize = 0x10000;

    _NtQuerySystemInformation NtQuerySystemInformation =
        static_cast<_NtQuerySystemInformation>(GetLibraryProcAddress("ntdll.dll", "NtQuerySystemInformation"));
    _NtDuplicateObject NtDuplicateObject =
        static_cast<_NtDuplicateObject>(GetLibraryProcAddress("ntdll.dll", "NtDuplicateObject"));
    _NtQueryObject NtQueryObject =
        static_cast<_NtQueryObject>(GetLibraryProcAddress("ntdll.dll", "NtQueryObject"));

    if (!NtQuerySystemInformation || !NtDuplicateObject || !NtQueryObject)
        return _active_pbo_list;

    HANDLE pid = reinterpret_cast<HANDLE>(GetCurrentProcessId());
    HANDLE processHandle = static_cast<HANDLE>(GetCurrentProcess());

    PSYSTEM_HANDLE_INFORMATION_EX handleInfo = static_cast<PSYSTEM_HANDLE_INFORMATION_EX>(malloc(handleInfoSize));
    while ((status = NtQuerySystemInformation(
        SystemHandleInformationEx,
        handleInfo,
        handleInfoSize,
        nullptr
    )) == STATUS_INFO_LENGTH_MISMATCH)
        handleInfo = static_cast<PSYSTEM_HANDLE_INFORMATION_EX>(realloc(handleInfo, handleInfoSize *= 2));

    /* NtQuerySystemInformation stopped giving us STATUS_INFO_LENGTH_MISMATCH. */
    if (!NT_SUCCESS(status)) {
        //LOG(ERROR) << "Error opening object for pbo search";
        free(handleInfo);
        return _active_pbo_list;
    }
    //LOG(INFO) << "Handles obtained!";
    for (ULONG i = 0; i < handleInfo->HandleCount; i++) {
        SYSTEM_HANDLE_EX handle = handleInfo->Handles[i];
        HANDLE dupHandle = nullptr;
        POBJECT_TYPE_INFORMATION objectTypeInfo;
        PVOID objectNameInfo;
        ULONG returnLength;

        /* Check if this handle belongs to the PID the user specified. */
        if (handle.ProcessId != pid) {
            //LOG(INFO) << "PID MISMATCH: " << (DWORD)handle.ProcessId << " != " << (DWORD)pid;
            continue;
        }


        /* Duplicate the handle so we can query it. */
        if (!NT_SUCCESS(NtDuplicateObject(
            processHandle,
            static_cast<HANDLE>(handle.Handle),
            GetCurrentProcess(),
            &dupHandle,
            0,
            0,
            0
        ))) {
            //LOG(INFO) << "FAILED TO DUPLICATE OJBECT";
            continue;
        }

        /* Query the object type. */
        objectTypeInfo = static_cast<POBJECT_TYPE_INFORMATION>(malloc(0x1000));
        if (!NT_SUCCESS(NtQueryObject(
            dupHandle,
            ObjectTypeInformation,
            objectTypeInfo,
            0x1000,
            NULL
        ))) {
            //LOG(INFO) << "FAILED TO QUERY OJBECT";
            CloseHandle(dupHandle);
            continue;
        }

        /* Query the object name (unless it has an access of
        0x0012019f, on which NtQueryObject could hang. */
        if (handle.GrantedAccess == 0x0012019f) {
            //LOG(INFO) << "ACCESS == 0x0012019f";
            free(objectTypeInfo);
            CloseHandle(dupHandle);
            continue;
        }

        objectNameInfo = malloc(0x1000);
        if (!NT_SUCCESS(NtQueryObject(
            dupHandle,
            ObjectNameInformation,
            objectNameInfo,
            0x1000,
            &returnLength
        ))) {
            //LOG(INFO) << "THE FUCK...";
            /* Reallocate the buffer and try again. */
            objectNameInfo = realloc(objectNameInfo, returnLength);
            if (!NT_SUCCESS(NtQueryObject(
                dupHandle,
                ObjectNameInformation,
                objectNameInfo,
                returnLength,
                NULL
            ))) {
                //LOG(INFO) << "... IS THIS SHIT?";
                free(objectTypeInfo);
                free(objectNameInfo);
                CloseHandle(dupHandle);
                continue;
            }
        }

        /* Cast our buffer into an UNICODE_STRING. */
        UNICODE_STRING objectName = *static_cast<PUNICODE_STRING>(objectNameInfo);



        /* Print the information! */
        if (objectName.Length) {
            std::wstring tmp_type(objectTypeInfo->Name.Buffer);
            std::wstring tmp_name(objectName.Buffer);

            std::string object_type(tmp_type.begin(), tmp_type.end());
            std::string object_name(tmp_name.begin(), tmp_name.end());
            //LOG(INFO) << "File: " << object_name;
            if (object_type == "File" && object_name.find(".pbo") != object_name.npos) {
                char buffer[MAX_PATH];
                GetFinalPathNameByHandle(dupHandle, buffer, sizeof(buffer), VOLUME_NAME_DOS);

                //LOG(INFO) << "Pbo: " << buffer;
                _active_pbo_list.push_back(std::string(buffer));
            }
        }

        free(objectTypeInfo);
        free(objectNameInfo);
        CloseHandle(dupHandle);
    }

    free(handleInfo);

    return _active_pbo_list;
}

#endif