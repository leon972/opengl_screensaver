#ifndef FOCUSEVT_H_INCLUDED
#define FOCUSEVT_H_INCLUDED

namespace lwtk {

class Widget;

class FocusEvents
    {
        public:
        virtual ~FocusEvents() {}
        virtual void FocusLost(Widget* src)=0;
        virtual void FocusGained(Widget* src)=0;
    };

};


#endif // FOCUSEVT_H_INCLUDED
