#ifndef KEYS_H_INCLUDED
#define KEYS_H_INCLUDED

#include <tchar.h>
namespace lwtk {

//virtual keys dei tasti (sono diversi dagli scan code fisici dei tasti)
const int K_SPACE=32;
const int K_UP=38;
const int K_DOWN=40;
const int K_LEFT=37;
const int K_RIGHT=39;
const int K_CTRL=17;
const int K_SHIFT=16;
const int K_CAPS_LOCK=20;
const int K_NUM_LOCK=144;
const int K_ALT=18;
const int K_ESC=27;
const int K_PGUP=33;
const int K_PGDOWN=34;
const int K_BACKSPACE=8;
const int K_PLUS=107;
const int K_MINUS=109;
const int K_END=35;
const int K_SCROLL_LOCK=145;
const int K_RETURN=13;
const int K_TAB=9;
const int K_DEL=46;
const int K_F1=112;
const int K_F2=113;
const int K_F3=114;
const int K_F4=115;
const int K_F5=116;
const int K_F6=117;
const int K_F7=118;
const int K_F8=119;
const int K_F9=120;
const int K_F10=121;
const int K_F11=122;
const int K_F12=123;

    class KeyInfo {
public:
        virtual ~KeyInfo() {}
        /**sacan code del tasto*/
        virtual int GetKeyCode() const=0;
        /**acquisisce un flag esteso del tasto*/
        virtual int GetExtendedKeyFlag() const=0;
        virtual char GetKeyChar()const=0;
        /**carattere ASCII corrispondente al tasto*/
        virtual const TCHAR* GetKeyName() const=0;
    };

    class KeyEvents
    {
        public:

        virtual ~KeyEvents() {}
        //nota:i metodi restituiscono il codice del tasto filtrato (gestito solo da alcuni widget)
        /**Tasto premuto*/
        virtual int KeyDown(const KeyInfo* key_info)=0;
        /**Tasto rilasciato*/
        virtual int KeyUp(const KeyInfo* key_info)=0;
        /**Tasto ASCII premuto*/
        virtual int KeyPressed(const KeyInfo* key_info)=0;
    };
};

#endif // KEYS_H_INCLUDED
