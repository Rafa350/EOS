#ifndef __eosFileSystemDriver__
#define __eosFileSystemDriver__


#include "eos.h"

#include <stdint.h>


namespace eos {

	enum class FileSystemDriverStatus {
		ok,
		error,
		deviceNotPressent,
		notInitialized
	};

	class IFileSystemDriver {
		public:
			virtual ~IFileSystemDriver() {}

			virtual bool initialize() = 0;
			virtual void shutdown() = 0;
			virtual bool isBusy() = 0;
			virtual bool read(uint8_t *pData, uint32_t blockAddr, uint32_t numBlocks, uint32_t timeout) = 0;
			virtual int write() = 0;
			virtual int ioctrl() = 0;

			virtual FileSystemDriverStatus getStatus() const {

				return FileSystemDriverStatus::notInitialized;
			}
	};
}


#endif // __eosFileSystemDriver__
