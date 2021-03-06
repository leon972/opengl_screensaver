#ifndef WINDOW_H_INCLUDED
#define WINDOW_H_INCLUDED

#include <tchar.h>
#include "lwtkdefs.h"
#include "mouse.h"
#include "keys.h"
#include "container.h"
#include "action.h"
#include "paintevt.h"
#include "menu.h"
#include "panel.h"

#ifdef _USEVIDEONAMESPACE_
using namespace video;
#endif

namespace lwtk {

    /**Modalità di visualizzazione di una finestra*/
    enum WINDOW_SHOW_MODE {
        W_NONE=0x0,
        W_MODAL=0x1,
        W_QUIT_ON_CLOSE=0x2,    //termina l'applicazione alla chiusura della finestra
    };

    class Window;

    /**interfaccia gestore eventi della finestra*/
    class WindowEvents {
public:

        virtual ~WindowEvents() {}
        /**La finestra viene attivata*/
        virtual void WindowActivated(Window* src)=0;
        /**La finestra viene chiusa*/
        virtual void WindowClosed(Window* src)=0;
        /**Evento che si verifica subito prima di chiudere la finestra.
           Se restituisce true chiude la finestra , altrimenti ne impedisce la chiusura*/
        virtual bool WindowClosing(Window* src)=0;
        /**La finestra viene deattivata*/
        virtual void WindowDeactivated(Window* src)=0;
        /**La finestra viene viene ripristinata*/
        virtual void WindowDeiconified(Window* src)=0;
        /**La finestra è stata visualizzata a tutto schermo*/
        virtual void WindowMaximized(Window* src)=0;
        /**La finestra viene ridotta ad icona*/
        virtual void WindowIconified(Window* src)=0;
        /**La finestra viene aperta*/
        virtual void WindowOpened(Window* src)=0;
        /**La finestra viene ridimensionata*/
        virtual void WindowResize(Window* src,int client_width,int client_height)=0;
        /**La finestra viene spostata*/
        virtual void WindowMove(Window* src,int x,int y)=0;
    };

class Window:public Container {
public:

        virtual ~Window() {}
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
        virtual const TCHAR* GetText()=0;
        virtual void SetText(const TCHAR* text)=0;
        virtual void SetVisible(bool visible)=0;
        virtual bool IsVisible()=0;
        virtual const TCHAR* GetTitle()=0;
        virtual void SetTitle(const TCHAR* title)=0;
        virtual void Show()=0;
        virtual void Show(WINDOW_SHOW_MODE show_mode)=0;
        virtual void Close()=0;
        virtual void Iconify()=0;
        virtual void Maximize()=0;
        virtual void Activate()=0;
        virtual bool IsIconified()=0;
        virtual bool IsMaximized()=0;
        virtual MSG_BOX_RESULT MsgBox(const TCHAR* szTitle,int type,TCHAR* szFormat, ...)=0;
        /**Aggiunge un gestore degli eventi della finestra*/
        virtual WindowEvents* AddWindowEvents(WindowEvents* evt)=0;
        /**Rimuove un gestore degli eventi della finestra*/
        virtual bool RemoveWindowEvents(WindowEvents* evt)=0;
        /**Eventi ridisegno*/
        virtual PaintEvent* AddPaintEvent(PaintEvent* evt)=0;
        virtual bool RemovePaintEvent(PaintEvent* evt)=0;
        /**Eventi focus*/
        virtual FocusEvents* AddFocusEvents(FocusEvents* evt)=0;
        virtual bool RemoveFocusEvents(FocusEvents* evt)=0;
        /**Eventi tastiera*/
        virtual KeyEvents* AddKeyEvents(KeyEvents* e)=0;
        virtual bool RemoveKeyEvents(KeyEvents* e)=0;
        /**Eventi mouse*/
        virtual MouseEvents* AddMouseEvents(MouseEvents* e)=0;
        virtual bool RemoveMouseEvents(MouseEvents* e)=0;
        /**Eventi movimento del mouse*/
        virtual MouseMoveEvents* AddMouseMoveEvents(MouseMoveEvents* e)=0;
        virtual bool RemoveMouseMoveEvents(MouseMoveEvents* e)=0;

        virtual Graphics* GetGraphics()=0;
        virtual void SetPositionRelativeTo(Window* ref)=0;
        virtual void SetPositionRelativeTo(Window* ref,WIDGET_POS position)=0;
        /**Imposta la barra dei menu corrente*/
        virtual void SetMenuBar(MenuBar* menu_bar)=0;
        virtual Panel* GetContentPanel()=0;
        /**aggiorna il contenuto della finestra*/
        virtual void Refresh()=0;
        /**aggiorna una parte della finestra*/
        virtual void Refresh(int left,int top,int right,int bottom)=0;
        /**Restituisce le dimensioni in pixel di un testo su questa finestra usando il font corrente*/
        virtual int GetTextWidth(const TCHAR* text)=0;
        virtual int GetTextHeight(const TCHAR* text)=0;
    };



};

#endif // WINDOW_H_INCLUDED
