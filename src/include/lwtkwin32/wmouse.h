#ifndef WMOUSE_H_INCLUDED
#define WMOUSE_H_INCLUDED

namespace lwtk {

    #define WIN32_LEAN_AND_MEAN

    #include "lwtk/lwtk.h"
    #include "windows.h"

class Win32MouseInfo:public MouseInfo {


friend class Win32Widget;


private:
        int x,y;
        MOUSE_BUTTONS button;
public:
        Win32MouseInfo() {
            x=y=0;
            button=NO_BUTTON;
        }
        virtual ~Win32MouseInfo() {}
        /**Posizione del mouse*/
        int GetX() {
            return x;
        }
        int GetY() {
            return y;
        }


        /**Restituisce quale tasto del mouse ha cambiato stato*/
        MOUSE_BUTTONS GetButton() {
            return button;
        }
    };

};

#endif // WMOUSE_H_INCLUDED
