#ifndef __EOS_STRING_HPP
#define	__EOS_STRING_HPP


namespace eos {
    
    /// \brief Implementacio de cadenes de texte.
    ///
    class String {
        private:
            char *container;
            unsigned length;
        public:
            String();
            String(const char *text);
            String(char ch, unsigned repeat);
            String(const String &other);
            ~String();
            
            unsigned getLength() const { return length; }
            
            operator const char*() const { return container; }
            char operator[](int index) const { return container[index]; }
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


#endif
