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
            struct StringData;

        public:
            typedef char* Iterator;
            typedef const char* CIterator;

        private:
            StringData* pData;

        private:
            void create(const char* cstr, unsigned index, unsigned length);
            void reference(const String& str);
            void release();

        public:
            String();
            String(const String& str);
            String(const String& str, unsigned index, unsigned length);
            String(const char* cstr);
            String(const char* cstr, unsigned index, unsigned length);
            ~String();

            unsigned getLength() const;
            bool isEmpty() const;
            bool isNull() const;

            bool isEqual(const char* cstr) const;
            bool isEqual(const String& str) const;
            int compare(const char* cstr) const;
            int compare(const String& str) const;

            Iterator begin();
            CIterator begin() const;
            Iterator end();
            CIterator end() const;

            String& operator = (const char* cstr);
            String& operator = (const String& str);

            inline bool operator == (const String& str) const { return isEqual(str); }
            inline bool operator != (const String& str) const { return !isEqual(str); }
            bool operator < (const String& str) const;
            bool operator <= (const String& str) const;
            bool operator > (const String& str) const;
            bool operator >= (const String& str) const;

            operator const char* () const;
            char operator [] (unsigned) const;
    };

    /// \brief Constructor de cadenes de texte.
    ///
    class StringBuilder {

        private:
            char* container;
            unsigned size;
            unsigned capacity;

        private:
            unsigned calcNewCapacity(unsigned requiredCapacity) const;
            void reserve(unsigned size);

        public:
            StringBuilder();
            ~StringBuilder();
            void clear();
            void append(char value);
            void append(const char* value);
            void append(const char* value, unsigned index, unsigned length);
            void append(const String& value);
            void append(int value);
            void append(unsigned value);
            void append(bool value);

            inline operator String () const { return String(container, 0, size); }
    };

}


#endif // __eosString__
