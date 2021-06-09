#ifndef __eosString__
#define	__eosString__


// EOS includes
//
#include "eos.h"
#ifdef USE_STD_STRINGS
    #include <string>
#endif

namespace eos {

#ifdef USE_STD_STRINGS

    class String final {
        public:
            typedef std::string::iterator Iterator;
            typedef std::string::const_iterator CIterator;

        private:
            std::string s;

        public:
            String() {}
            String(const String& str): s(str.s) {}
            String(const String& str, unsigned index, unsigned length): s(str.s, index, length) {}
            String(const char* cstr): s(cstr) {}
            String(const char* cstr, unsigned index, unsigned length): s(cstr, length) {}
            ~String() {}

            inline unsigned getLength() const { return s.size(); }
            inline bool isEmpty() const { return s.empty(); }
            inline bool isNull() const { return s.empty(); }

            inline bool isEqual(const char* cstr) const { return compare(cstr) == 0; }
            inline bool isEqual(const String& str) const { return compare(str) == 0; }
            inline int compare(const char* cstr) const { return s.compare(cstr); }
            inline int compare(const String& str) const { return s.compare(str); }

            inline Iterator begin() { return s.begin(); }
            inline CIterator begin() const { return s.cbegin(); }
            inline Iterator end() { return s.end(); }
            inline CIterator end() const { return s.cend(); }

            inline String& operator = (const char* cstr) { s = cstr; return *this; }
            inline String& operator = (const String& str) { s = str; return *this; }

            inline bool operator == (const String& str) const { return s == str.s; }
            inline bool operator != (const String& str) const { return s != str.s; }
            inline bool operator < (const String& str) const { return s < str.s; }
            inline bool operator <= (const String& str) const { return s <= str.s; }
            inline bool operator > (const String& str) const { return s > str.s; }
            inline bool operator >= (const String& str) const { return s >= str.s; }

            inline operator const char* () const { return s.c_str(); }
            inline char operator [] (unsigned pos) const { return s[pos]; }
    };

#else

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

#endif


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
