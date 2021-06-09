#pragma once

#include <memory>

    class StringV2 {
        private:
            struct Impl;
            typedef std::shared_ptr<Impl> PImpl;
        private:
            PImpl _pImpl;
        private:
            PImpl allocate(const char* cstr);
        public:
            StringV2(const char* cstr);
            StringV2(const StringV2& str);

            StringV2& operator = (const char* cstr);
            StringV2& operator = (const StringV2& str);

            unsigned getLength() const;
            bool isEmpty() const;
            bool isNull() const;

            operator const char* () const;
            char operator [] (unsigned) const;
    };

