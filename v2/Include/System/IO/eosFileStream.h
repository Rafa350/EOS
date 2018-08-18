#ifndef __eosFileStream__
#define	__eosFileStream__


#include "eos.h"
#include "System/Core/eosString.h"
#include "System/IO/eosFile.h"
#include "System/IO/eosStream.h"


namespace eos {

    class FileStream: public Stream {
    	private:
			uint8_t fileId;
    	public:
			FileStream();
    		FileStream(const String &fileName, FileMode mode, FileAccess access);
    		~FileStream();
    		bool open(const String &fileName, FileMode mode, FileAccess access);
    		bool close();
    		uint32_t write(void *data, uint32_t size);
    		uint32_t read(void *data, uint32_t size);
    		inline bool isOpen() const { return fileId != 0xFF; }
    };

}


#endif // __eosFileStream__

