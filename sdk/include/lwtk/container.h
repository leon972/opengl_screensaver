#ifndef CONTAINER_H_INCLUDED
#define CONTAINER_H_INCLUDED

#include "widget.h"

namespace lwtk {

 class Widget;

 class Container {

public:
        virtual ~Container() {}
        virtual const Widget* Add(Widget* widget)=0;
        virtual bool Remove(Widget* widget)=0;
    };

};

#endif // CONTAINER_H_INCLUDED
