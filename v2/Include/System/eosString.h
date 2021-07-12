#ifndef __eosString__
#define	__eosString__


// EOS includes
//
#include "eos.h"
#ifdef EOS_USE_STD_STRING
	#include "System/Core/eosStdHeapAllocator.h"
    #include <string>
#endif


namespace eos {


#ifdef EOS_USE_STD_STRING

	class String final {
        public:
			typedef std::basic_string<char, std::char_traits<char>, StdHeapAllocator<char> > S;
            typedef S::iterator Iterator;
            typedef S::const_iterator CIterator;

        private:
            S _s;

        private:
            String(const S& s):
            	_s(s) {
            }

        public:
            String() {
            }

            String(const String& str):
            	_s(str._s) {
            }

            String(const String& str, int index, int length):
            	_s(str._s, index, length) {
            }

            String(const char* cstr):
            	_s(cstr) {
            }

            String(const char* cstr, int index, int length):
            	_s(&cstr[index], length) {
            }

            ~String() {
            }

            inline int getLength() const {
            	return (int) _s.size();
            }

            inline bool isEmpty() const {
            	return _s.empty();
            }

            inline bool isNull() const {
            	return _s.empty();
            }

            inline bool isEqual(const char* cstr) const {
            	return compare(cstr) == 0;
            }

            inline bool isEqual(const String& str) const {
            	return compare(str) == 0;
            }

            inline int compare(const char* cstr) const {
            	return _s.compare(cstr);
            }

            inline int compare(const String& str) const {
            	return _s.compare(str);
            }

            /// \brief Obte el iterador inicial.
            ///
            inline Iterator begin() {
            	return _s.begin();
            }

            /// \brief Obte el iterador inicial.
            ///
            inline CIterator begin() const {
            	return _s.cbegin();
            }

            /// \brief Obte el iterator final.
            ///
            inline Iterator end() {
            	return _s.end();
            }

            /// \brief Obte el iterator final.
            ///
            inline CIterator end() const {
            	return _s.cend();
            }

            inline String& operator = (const char* cstr) {
            	_s = cstr;
            	return *this;
            }

            inline String& operator = (const String& str) {
            	_s = str;
            	return *this;
            }

            inline String operator + (const String& str) const {
            	return String(_s + str._s);
            }

            inline String operator + (const char ch) const {
            	return String(_s + S(1u, ch));
            }

            inline bool operator == (const String& str) const {
            	return _s == str._s;
            }

            inline bool operator != (const String& str) const {
            	return _s != str._s;
            }

            inline bool operator < (const String& str) const {
            	return _s < str._s;
            }

            inline bool operator <= (const String& str) const {
            	return _s <= str._s;
            }

            inline bool operator > (const String& str) const {
            	return _s > str._s;
            }

            inline bool operator >= (const String& str) const {
            	return _s >= str._s;
            }

            inline operator const char* () const {
            	return _s.c_str();
            }

            inline char operator [] (int pos) const {
            	return _s[pos];
            }
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
            void create(int length);
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

            int getLength() const;
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

            String operator + (const String& str) const;
            String operator + (const char ch) const;
            inline bool operator == (const String& str) const { return isEqual(str); }
            inline bool operator != (const String& str) const { return !isEqual(str); }
            bool operator < (const String& str) const;
            bool operator <= (const String& str) const;
            bool operator > (const String& str) const;
            bool operator >= (const String& str) const;

            operator const char* () const;
            char operator [] (int) const;
    };

#endif


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
