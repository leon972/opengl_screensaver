#ifndef WIDGET_H_INCLUDED
#define WIDGET_H_INCLUDED

#include <tchar.h>
#include "lwtkdefs.h"
#include "mouse.h"
#include "keys.h"
#include "control.h"
#include "action.h"
#include "focusevt.h"
#include "container.h"

#ifdef _USEVIDEONAMESPACE_
using namespace video;
#endif

namespace lwtk {

class Container;


    /**Posizione di un elemento rispetto ad un altro*/
enum WIDGET_POS {
    POS_CENTER,
    POS_UPPER_LEFT,
    POS_UPPER,
    POS_UPPER_RIGHT,
    POS_BOTTOM_LEFT,
    POS_BOTTOM,
    POS_BOTTOM_RIGHT
};

 /**Elemento astratto dell'interfaccia grafica*/
    class Widget:public virtual Control {
public:

        virtual ~Widget() {}
        virtual void SetAction(const TCHAR* action)=0;
        virtual const TCHAR* GetAction()=0;
        virtual void AddActionEvent(ActionEvent* e)=0;
        virtual bool RemoveActionEvent(ActionEvent* e)=0;
        virtual void AddMouseEvents(MouseEvents* e)=0;
        virtual void AddMouseRolloverEvents(MouseRolloverEvents* e)=0;
        virtual void RemoveMouseEvents(MouseEvents* e)=0;
        virtual void AddMouseMoveEvents(MouseMoveEvents* e)=0;
        virtual void RemoveMouseMoveEvents(MouseMoveEvents* e)=0;
        virtual void AddFocusEvents(FocusEvents* e)=0;
        virtual void RemoveFocusEvents(FocusEvents* e)=0;
        virtual void AddKeyEvents(KeyEvents* e)=0;
        virtual void RemoveKeyEvents(KeyEvents* e)=0;
        virtual void SetZOrder(ZORDER_POS pos)=0;
        virtual void SetZOrder(Widget* ins_after)=0;
        virtual void ResizeToDefault()=0;
        virtual Container* GetParent()=0;
    };

};

#endif // WIDGET_H_INCLUDED
