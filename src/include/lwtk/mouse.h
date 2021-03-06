#ifndef MOUSE_H_INCLUDED
#define MOUSE_H_INCLUDED

#include <tchar.h>


namespace lwtk {

    /**Identificativi dei tasti del mouse*/
    enum MOUSE_BUTTONS {
        NO_BUTTON=0x0,
        LEFT_BUTTON=0x1,
        RIGHT_BUTTON=0x2,
        MIDDLE_BUTTON=0x4,
    };

    /**Informazioni sullo stato del mouse*/
    class MouseInfo {
public:
        virtual ~MouseInfo() {}
        /**Posizione relativa del mouse*/
        virtual int GetX()=0;
        virtual int GetY()=0;
        /**Restituisce quale tasto del mouse ha cambiato stato*/
        virtual MOUSE_BUTTONS GetButton()=0;
    };

    /**Gestisce gli eventi del mouse, click dblclick e mouse button press*/
    class MouseEvents
    {
        public:
        virtual     ~MouseEvents() {}
        virtual void MouseClicked(MouseInfo* mouse_info)=0;
        virtual void MouseDblClicked(MouseInfo* mouse_info)=0;
        virtual void MousePressed(MouseInfo* mouse_info)=0;
        virtual void MouseReleased(MouseInfo* mouse_info)=0;
    };

    class MouseMoveEvents
    {
        public:
        virtual ~MouseMoveEvents() {}
        virtual void MouseMove(int x,int y)=0;
    };

    class MouseRolloverEvents
    {
        public:
        virtual ~MouseRolloverEvents() {}
        virtual void MouseEntered(MouseInfo* mouse_info)=0;
        virtual void MouseExited(MouseInfo* mouse_info)=0;
    };

};


#endif // MOUSE_H_INCLUDED
