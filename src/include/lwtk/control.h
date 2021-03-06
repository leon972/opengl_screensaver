#ifndef CONTROL_H_INCLUDED
#define CONTROL_H_INCLUDED

#include <tchar.h>
#include "lwtkdefs.h"

#ifdef _USEVIDEONAMESPACE_
using namespace video;
#endif

namespace lwtk {


/**è una generica area rettangolare che contiene un widget,una finestra,un pannello...*/
    class Control
    {
        public:

        virtual ~Control() {}
        virtual void SetForeground(COLOR c)=0;
        virtual COLOR GetForeground()=0;
        virtual void SetBackground(COLOR c)=0;
        virtual COLOR GetBackground()=0;
        virtual void Resize(int w,int h)=0;
        virtual void Move(int x,int y)=0;
        virtual int GetWidth()=0;
        virtual int GetHeight()=0;
        virtual int GetLeft()=0;
        virtual int GetTop()=0;
        virtual int SetWidth(int w)=0;
        virtual int SetHeight(int h)=0;
        virtual int SetLeft(int x)=0;
        virtual int SetTop(int y)=0;
        /**Imposta il font corrente per la finestra*/
        virtual void SetFont(Font* font)=0;
        /**Ottiene il font corrente*/
        virtual Font* GetFont()=0;

        virtual const TCHAR* GetText()=0;
        virtual void SetText(const TCHAR* text)=0;
        virtual void SetEnabled(bool enabled)=0;
        virtual bool IsEnabled()=0;
        virtual void SetVisible(bool visible)=0;
        virtual bool IsVisible()=0;
        virtual BORDER_TYPE GetBorder()=0;
    };


};

#endif // CONTROL_H_INCLUDED
