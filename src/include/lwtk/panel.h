#ifndef PANEL_H_INCLUDED
#define PANEL_H_INCLUDED


namespace lwtk {

#include "paintevt.h"

class Panel:public Container,public Widget
    {
        public:
        virtual ~Panel() {}
        virtual PaintEvent* AddPaintEvent(PaintEvent* evt)=0;
        virtual bool RemovePaintEvent(PaintEvent* evt)=0;
        virtual void Refresh()=0;
    };

};

#endif // PANEL_H_INCLUDED
