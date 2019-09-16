#ifndef __eosString__
#define	__eosString__


namespace eos {
    
    /// \brief Implementacio de cadenes de texte.
    ///
    class String {
        private:
        	unsigned length;
        	unsigned containerSize;
            char *container;

        private:
            void alloc(const char *text);

        public:
            String();
            String(const char *text);
            String(const String &text);
            String(const String &text, unsigned index, unsigned length);
            ~String();
            
            inline unsigned getLength() const { return length; }
            inline bool isEmpty() const { return length == 0; }
            
            int compare(const String& text) const;
            int compare(const char *text) const;

            String& operator = (const char *text);
            String& operator = (const String &text);

            bool operator ==(const String &text) const;
            inline bool operator !=(const String &text) const { return !operator ==(text); }

            inline operator const char*() const { return container; }
            inline char& operator[](int index) { return container[index]; }
            inline const char& operator[](int index) const { return container[index]; }
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
