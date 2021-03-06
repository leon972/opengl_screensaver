#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED

namespace lwtk
{

    #include "widget.h"

    /**Un elemento di un menu*/
    class MenuItem:public Widget
    {
        public:
        virtual ~MenuItem() {}
        virtual bool IsChecked()=0;
        virtual void SetChecked(bool checked)=0;
    };

    /**Un menu costituito da vari MenuItem*/
    class Menu {
public:
        virtual ~Menu() {}
        virtual const TCHAR* GetText()=0;
        virtual void SetText(const TCHAR* text)=0;
        virtual void SetEnabled(bool enabled)=0;
        virtual bool IsEnabled()=0;
        virtual void SetVisible(bool visible)=0;
        virtual bool IsVisible()=0;
        virtual void SetAction(const TCHAR* action)=0;
        virtual const TCHAR* GetAction()=0;
        virtual void AddActionEvent(ActionEvent* e)=0;
        virtual bool RemoveActionEvent(ActionEvent* e)=0;
        virtual void AddItem(MenuItem* m)=0;
        virtual bool RemoveItem(MenuItem* m)=0;
        virtual void AddSubMenu(Menu* m)=0;
        virtual void AddSeparator()=0;
        virtual bool RemoveSubMenu(Menu* m)=0;
    };

    /**Barra dei menu di una finestra*/
    class MenuBar {

public:
        virtual ~MenuBar() {}
        virtual void SetEnabled(bool enabled)=0;
        virtual bool IsEnabled()=0;
        virtual void SetVisible(bool visible)=0;
        virtual bool IsVisible()=0;
        virtual void AddMenu(Menu* m)=0;
        virtual bool RemoveMenu(Menu* m)=0;

        };

};

#endif // MENU_H_INCLUDED
