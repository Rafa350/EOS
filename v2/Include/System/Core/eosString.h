#ifndef __eosString__
#define	__eosString__


// EOS includes
//
#include "eos.h"


namespace eos {
    
    /// \brief Implementacio de cadenes de texte.
    ///
    class String final {
    	private:
			struct StringData {
				unsigned refCount;
				unsigned length;
				char container[1];
			};

    	private:
			StringData *pData;

        private:
            void create(const char *cstr, unsigned index, unsigned length);
            void reference(const String &str);
            void release();

        public:
            String();
            String(const char *cstr);
            String(const String &str);
            String(const String &str, unsigned index, unsigned length);
            ~String();
            
            unsigned getLength() const;
            bool isEmpty() const;
            bool isNull() const;
            
            String& operator = (const char *cstr);
            String& operator = (const String &str);

            bool operator ==(const String &str) const;
            inline bool operator !=(const String &str) const { return !operator==(str); }
            bool operator <(const String &str) const;
            bool operator <=(const String &str) const;
            bool operator >(const String &str) const;
            bool operator >=(const String &str) const;

            inline operator const char*() const { return pData->container; }
            char operator[](int index) const;
    };
    
    /// \brief Constructor de cadenes de texte.
    ///
    class StringBuilder {
        private:
            char *container;
            unsigned length;
            unsigned capacity;            
        public:
            StringBuilder();
            ~StringBuilder();
            void append(char);
            void append(const char *s);
            void append(const String &s);
    };
}


#endif // __eosString__
