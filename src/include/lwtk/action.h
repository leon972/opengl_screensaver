#ifndef ACTION_H_INCLUDED
#define ACTION_H_INCLUDED

namespace lwtk {

    class Widget;

/**Ascoltatore eventi azioni*/
    class ActionEvent
    {
        public:
        virtual ~ActionEvent() {}
        virtual void ActionPerformed(Widget* src)=0;
    };

};

#endif // ACTION_H_INCLUDED
