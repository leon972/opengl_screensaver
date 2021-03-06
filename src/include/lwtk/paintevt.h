#ifndef PAINTEVT_H_INCLUDED
#define PAINTEVT_H_INCLUDED

#include "video/graphics.h"

namespace lwtk {



    /**interfaccia gestore eventi di ridisegno*/
    class PaintEvent {
public:
        virtual ~PaintEvent() {}
        /**Viene ridisegnato il contenuto dell'area client*/
        virtual void Paint(Graphics* g)=0;
    };

};

#endif // PAINTEVT_H_INCLUDED
