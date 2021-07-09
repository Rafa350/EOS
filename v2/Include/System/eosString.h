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
            StringData* _data;

        private:
            void create(const char* cstr, int index, int length);
            void reference(const String& str);
            void release();

        public:
            String();
            String(const String& str);
            String(const String& str, int index, int length);
            String(const char* cstr);
            String(const char* cstr, int index, int length);
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
            char operator [] (int) const;
    };


    /// \brief Constructor de cadenes de texte.
    ///
    class StringBuilder {

        private:
            char* _container;
            int _size;
            int _capacity;

        private:
            int calcNewCapacity(int requiredCapacity) const;
            void reserve(int size);

        public:
            StringBuilder();
            ~StringBuilder();
            void clear();
            void append(char value);
            void append(const char* value);
            void append(const char* value, int index, int length);
            void append(const String& value);
            void append(int value);
            void append(unsigned value);
            void append(bool value);

            inline operator String () const { return String(_container, 0, _size); }
    };

}


#endif // __eosString__
