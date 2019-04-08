#include "shared/containers.hpp"
#include "shared/types.hpp"
#include "client/client.hpp"

#if INTERCEPT_HOST_DLL
#include "loader.hpp"
#define GET_ENGINE_ALLOCATOR intercept::loader::get().get_allocator();
#else
#define GET_ENGINE_ALLOCATOR client::host::functions.get_engine_allocator()
#endif

namespace intercept::types {

#pragma region Allocator
    class MemTableFunctions { //We don't want to expose this in the header. It's only used here
    public:
        virtual void *New(size_t size) = 0;
        virtual void *New(size_t size, const char *file, int line) = 0;
        virtual void Delete(void *mem) = 0;
        virtual void Delete(void *mem, const char *file, int line) = 0;
        virtual void *Realloc(void *mem, size_t size) = 0;
        virtual void *Realloc(void *mem, size_t size, const char *file, int line) = 0;
        virtual void *Resize(void *mem, size_t size) = 0; //This actually doesn't do anything.

        virtual void *NewPage(size_t size, size_t align) = 0;
        virtual void DeletePage(void *page, size_t size) = 0;

        virtual void *HeapAlloc(void *mem, size_t size) = 0;
        virtual void *HeapAlloc(void *mem, size_t size, const char *file, int line) = 0;//HeapAlloc

        virtual void *HeapDelete(void *mem, size_t size) = 0;
        virtual void *HeapDelete(void *mem, size_t size, const char *file, int line) = 0;//HeapFree

    #ifdef __linux__
        virtual int something1(void* mem, size_t unknown) = 0; //memalign alloc and memmove
        virtual int something2(void* mem, size_t unknown) = 0; //redirect to something1
        virtual int something3(void* mem, size_t unknown) = 0; //ret 0
    #endif

        virtual int something(void* mem, size_t unknown) = 0; //Returns HeapSize(mem) - (unknown<=4 ? 4 : unknown) -(-0 & 3) -3
                                                              //In Linux binary this calls malloc_usable_size(unknown)
                                                              //In Linux binary this allocates aligned memory and moves memory. But on linux it also takes 4 args

        virtual size_t GetPageRecommendedSize() = 0;

        virtual void *HeapBase() = 0;
        virtual size_t HeapUsed() = 0;

        virtual size_t HeapUsedByNew() = 0;
        virtual size_t HeapCommited() = 0;
        virtual int FreeBlocks() = 0;
        virtual int MemoryAllocatedBlocks() = 0;
        virtual void Report() = 0;//Does nothing on release build. Maybe on Profiling build
        virtual bool CheckIntegrity() = 0;//Does nothing on release build. Maybe on Profiling build returns true.
        virtual bool IsOutOfMemory() = 0;//If true we are so full we are already moving memory to disk.

        virtual void CleanUp() = 0;//Does nothing? I guess.
                                   //Synchronization for Multithreaded access
        virtual void Lock() = 0;
        virtual void Unlock() = 0;
        const char* arr[6]{ "tbb4malloc_bi","tbb3malloc_bi","jemalloc_bi","tcmalloc_bi","nedmalloc_bi","custommalloc_bi" };
    };

    void __internal::set_game_value_vtable(uintptr_t vtable) {
        game_value::__vptr_def = vtable;
    }

    void* __internal::rv_allocator_allocate_generic(size_t _size) {
        static auto allocatorBase = GET_ENGINE_ALLOCATOR;
    #ifdef __linux__
        MemTableFunctions* alloc = reinterpret_cast<MemTableFunctions*>(reinterpret_cast<uintptr_t>(&(allocatorBase->genericAllocBase)));
    #else
        MemTableFunctions* alloc = reinterpret_cast<MemTableFunctions*>(allocatorBase->genericAllocBase);
    #endif
        return alloc->New(_size);
    }

    void __internal::rv_allocator_deallocate_generic(void* _Ptr) {
        //#TODO assert when _ptr is not 32/64bit aligned
        // deallocate object at _Ptr
        static auto allocatorBase = GET_ENGINE_ALLOCATOR;
    #ifdef __linux__
        MemTableFunctions* alloc = reinterpret_cast<MemTableFunctions*>(reinterpret_cast<uintptr_t>(&(allocatorBase->genericAllocBase)));
    #else
        MemTableFunctions* alloc = reinterpret_cast<MemTableFunctions*>(allocatorBase->genericAllocBase);
    #endif
        alloc->Delete(_Ptr);
    }

    void* __internal::rv_allocator_reallocate_generic(void* _Ptr, size_t _size) {
        //#TODO assert when _ptr is not 32/64bit aligned
        // deallocate object at _Ptr
        static auto allocatorBase = GET_ENGINE_ALLOCATOR;
    #ifdef __linux__
        MemTableFunctions* alloc = reinterpret_cast<MemTableFunctions*>(reinterpret_cast<uintptr_t>(&(allocatorBase->genericAllocBase)));
    #else
        MemTableFunctions* alloc = reinterpret_cast<MemTableFunctions*>(allocatorBase->genericAllocBase);
    #endif
        return alloc->Realloc(_Ptr, _size);
    }

    void* rv_pool_allocator::allocate(size_t count) {
    #ifdef __linux__
        return __internal::rv_allocator_allocate_generic(count);
    #else
        static auto allocatorBase = GET_ENGINE_ALLOCATOR;
        typedef void*(__thiscall *allocFunc)(rv_pool_allocator*, size_t /*count*/);
        allocFunc alloc = reinterpret_cast<allocFunc>(allocatorBase->poolFuncAlloc);
        auto allocation = alloc(this, count);
        return allocation;
    #endif
    }

    void rv_pool_allocator::deallocate(void* data) {
    #ifdef __linux__
        __internal::rv_allocator_deallocate_generic(data);
    #else
        static auto allocatorBase = GET_ENGINE_ALLOCATOR;
        typedef void(__thiscall *deallocFunc)(rv_pool_allocator*, void* /*data*/);
        deallocFunc dealloc = reinterpret_cast<deallocFunc>(allocatorBase->poolFuncDealloc);
        dealloc(this, data);
    #endif
    }
#pragma endregion
}
