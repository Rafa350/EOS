#ifndef __eosFileSystemSDIODriver__
#define __eosFileSystemSDIODriver__


#include "eos.h"
#include "Controllers/Fat/eosFileSystemDriver.h"


#if !defined(EOS_STM32F7)
    #error Hardware no soportado
#endif


namespace eos {

	class FileSystemSDIODriver: public IFileSystemDriver {
		private:
			static IFileSystemDriver *instance;
			FileSystemDriverStatus fsStatus;

		private:
		    FileSystemSDIODriver();

		public:
		    static IFileSystemDriver *getInstance();

			bool initialize();
			void shutdown();
			bool isBusy();
			bool read(uint8_t *pData, uint32_t blockAddr, uint32_t numBlocks, uint32_t timeout);
			int write();
			int ioctrl();

			FileSystemDriverStatus getStatus() const;
	};
}


#endif // __eosFileSystemSDIODriver__
