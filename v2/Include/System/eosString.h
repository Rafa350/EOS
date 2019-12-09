#ifndef __eosString__
#define	__eosString__


// EOS includes
//
#include "eos.h"


namespace eos {
#ifdef EOS_USE_FULL_NAMESPACE
    namespace System {
#endif

        /// \brief Implementacio de cadenes de texte.
        ///
        class String final {
            private:
                struct StringData;

            private:
                StringData *pData;

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

                int getLength() const;
                bool isEmpty() const;
                bool isNull() const;

                int isEqual(const char* cstr) const;
                inline int isEqual(const String& str) const { return isEqual((const char *) str); }

                String& operator = (const char* cstr);
                String& operator = (const String& str);

                bool operator ==(const String& str) const;
                inline bool operator !=(const String& str) const { return !operator==(str); }
                bool operator <(const String& str) const;
                bool operator <=(const String& str) const;
                bool operator >(const String& str) const;
                bool operator >=(const String& str) const;

                operator const char*() const;
                char operator[](int index) const;
        };

        /// \brief Constructor de cadenes de texte.
        ///
        class StringBuilder {
            private:
                char* container;
                int length;
                int capacity;
            public:
                StringBuilder();
                ~StringBuilder();
                void append(char);
                void append(const char* s);
                void append(const String& s);
        };

#ifdef EOS_USE_FULL_NAMESPACE
    }
#endif
}


#endif // __eosString__
