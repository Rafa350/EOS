#ifndef __FSMCONTEXT_H
#define __FSMCONTEXT_H


class IContext {
    public:
        void clearLED1();
        void clearLED2();
        void clearLED3();
        void setLED1();
        void setLED2();
        void setLED3();
        void startTIMER1(unsigned time);
};


#endif