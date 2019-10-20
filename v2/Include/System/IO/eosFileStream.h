#ifndef __eosFileStream__
#define	__eosFileStream__


#include "eos.h"
#include "System/IO/eosFile.h"
#include "System/IO/eosStream.h"


namespace eos {

	class String;

    class FileStream: public Stream {
    	private:
    		void *hFile;

    	public:
            static void *operator new(size_t size);
            static void operator delete(void *p);

			FileStream();
    		FileStream(const String &fileName, FileMode mode, FileAccess access);
    		~FileStream();

    		bool open(const String &fileName, FileMode mode, FileAccess access);
    		bool close();
    		int write(void *data, int size) override;
    		int read(void *data, int size) override;
    		inline bool isOpen() const { return hFile != nullptr; }
    };

}


#endif // __eosFileStream__

