#include "ptraccess.h"
#include <cstdio>
#include <cerrno>

#ifdef __CUSTOM_ISBADREADPTR
#include <unistd.h>
#include <fcntl.h>
#include <optional>

class TmpFd {
public:
	TmpFd(const char *path, int mode):
		_raw(open(path, mode))
	{
		if (!valid()) {
			_error = errno;
		}
	}
	~TmpFd()
	{
		close(_raw);
	}
	inline bool valid() const {
		return _raw >= 0;
	}
	inline const std::optional<int> error() const {
		return _error;
	}
	inline ssize_t fd_write(const void *buf, size_t count) {
		return write(_raw, buf, count);
	}
	inline int raw_fd() {
		return _raw;
	}
private:
	int _raw;
	std::optional<int> _error;
};

extern "C" bool IsBadReadPtr(const void *p, size_t size) {
	TmpFd fd("/dev/random", O_WRONLY);
	return (fd.fd_write(p, size) < 0);
}
#endif
