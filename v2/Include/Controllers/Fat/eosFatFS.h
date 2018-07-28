#ifndef __eosFatFS__
#define __eosFatFS__


namespace eos {

	typedef void *FileHandle;

	class FatFileSystem {
		public:
			void mount();
			void format();
			FileHandle open();
			void close(FileHandle handle);
			void read(FileHandle handle);
			void write(FileHandle handle);
	};
}


#endif // __eosFat__
