#ifndef __EOS_STRING_HPP
#define	__EOS_STRING_HPP


namespace eos {
    
    class String {
        private:
            char *buffer;
            unsigned length;
        public:
            String();
            String(const char *text);
            String(char ch, unsigned repeat);
            String(const String &other);
            ~String();
    };
    
    class StringBuilder {
        
    };
}


#endif
