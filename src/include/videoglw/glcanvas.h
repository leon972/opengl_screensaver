#ifndef GLCANVAS_H_INCLUDED
#define GLCANVAS_H_INCLUDED

#include "lwtk/libhead.h"
#include <list>
#include "video/canvas.h"
#define WIN32_LEAN_AND_MEAN
#include "windows.h"
#include "video/video_exception.h"


#ifdef _USEVIDEONAMESPACE_
namespace video {
    #endif



    /************************************************
    Implementazione OpenGL su Win32 dell'interfaccia
    Canvas
    code by L.Berti (c) 2008
    *************************************************/


    using namespace std;
    using namespace lwtk;

/**interfaccia per gli oggetti collegati ad una finestra Win32*/
class DLL_EXPORT HWNDWin
{
    public:
    virtual ~HWNDWin() {
    }
    virtual HWND getHWND()=0;

};

/**contiene le informazioni di un generico messaggio intercettato dalla finestra*/
struct WINDOW_MESSAGE
{
    HWND hWnd;
    UINT uMsg;
    WPARAM wParam;
    LPARAM lParam;
};

/**Interfaccia callback implementata dai listeners della finestra open GL*/
class IWinMessageCallback
{
    public:
    virtual ~IWinMessageCallback() {}
    virtual void process(const WINDOW_MESSAGE& msg)=0;

};

    /**
    Implementazione per restituire i descrittori degli eventi del mouse e della tastiera*/
class DLL_EXPORT VidMouseInfo:public MouseInfo {


        friend class GLCanvasWin32;


private:
        int x,y;
        MOUSE_BUTTONS button;
public:
        VidMouseInfo() {
            x=y=0;
            button=NO_BUTTON;
        }
        VidMouseInfo(int x,int y,MOUSE_BUTTONS button)
        {
            this->x=x;
            this->y=y;
            this->button=button;
        }
        virtual ~VidMouseInfo() {}
        /**Posizione del mouse*/
        int GetX() {
            return x;
        }
        int GetY() {
            return y;
        }


        /**Restituisce quale tasto del mouse ha cambiato stato*/
        MOUSE_BUTTONS GetButton() {
            return button;
        }
    };

class DLL_EXPORT VidKeyInfo:public KeyInfo {
private:

        static const size_t str_size=32;
        TCHAR key_name[str_size];
        int key_code;
        LPARAM lParam;

public:

        VidKeyInfo() {
            key_code=0;
            memset(key_name,0,str_size);
        }


        void Set(LPARAM lParam,WPARAM wParam) {
            key_code=wParam;
            GetKeyNameText(lParam,key_name,str_size);
            this->lParam=lParam;

        }

        /**acquisisce un flag esteso del tasto*/
        int GetExtendedKeyFlag() const {
            //if (lParam & 1<<24) return 1 non funziona
            //else return 0;
            //distingue fra tasto destro e sinistro (solo per shift e ctrl)
            if (lParam==(LPARAM)0xC0360001 || lParam==(LPARAM)0x360001 || lParam==(LPARAM)0xC11D0001 || lParam==(LPARAM)0x11D0001) return 1;
            else return 0;
            }

            int GetKeyCode() const {
                    return key_code;
                }

                char GetKeyChar() const {
                    return static_cast<char>(key_code);
                }

                const TCHAR* GetKeyName() const {
                    return static_cast<const TCHAR*>(key_name);
                }
            };


    /**
    Classe astratta:le classe derivate devono implemetare StartAnimation e StopAnimation
    */

class DLL_EXPORT GLCanvasWin32:public virtual Canvas,public virtual HWNDWin {
protected:

        bool m_isActive;

        static GLCanvasWin32* cur_instance;

        static VidKeyInfo ki_up;
        static VidKeyInfo ki_down;
        static VidKeyInfo ki_pressed;

        static LRESULT CALLBACK WndProc(HWND hWnd,UINT	uMsg,WPARAM	wParam,LPARAM lParam);
        //listeners dei messaggi generici della finestra
        list<IWinMessageCallback*> msg_listeners;

        HWND m_hwnd;
        HDC m_hdc;//device context corrente
        HGLRC m_hglrc; //OpenGl rendering context
        HINSTANCE m_hinstance;

        int m_screen_width;
        int m_screen_height;
        int m_screen_bpp;
        int m_frequency; //frequenza monitor impostata

        volatile bool m_graphics_loop;

        bool m_traceon; //trace errori abilitato

        list<PaintEvent*>* paint_events;
        list<FocusEvents*>* focus_events;
        list<KeyEvents*>* key_events;
        list<MouseEvents*>* mouse_events;
        list<MouseMoveEvents*>* mouse_move_events;
        list<AnimationEvent*>* animation_events;

        //Ricrea e ridimensiona la finestra
        virtual void reshape(int w,int h);

        //output di un messaggio di debug sul file di output
        void OutputDebugMsg(const char* msg);

        void NotifyAnimationEvents();

        void NotifyListeners(HWND hWnd,UINT	uMsg,WPARAM	wParam,LPARAM lParam);

        virtual LRESULT ProcessWin32Message(HWND hWnd,UINT	uMsg,WPARAM	wParam,LPARAM lParam);

public:

        //Errori specifici di questa implementazione
        static const int ERR_FAILED_REGISTER_WINDOW=100;
        static const int ERR_FULLSCREEN_NOT_SUPPORTED=101;
        static const int ERR_WINDOW_CREATION=102;
        static const int ERR_CREATING_OGLRENDERING_CONTEXT=103;
        static const int ERR_NO_SUITABLE_PIXELFORMAT=104;
        static const int ERR_CANT_SET_PIXELFORMAT=105;
        static const int ERR_CREATING_WIN_HDC=106;
        static const int ERR_ACTIVATING_RENDERING_CONTEXT=107;
        static const int ERR_INITIALIZING_OGL=108;
        static const int ERR_RELEASE_RC_FAILED=109; //errore rilasciando il rendering context
        static const int ERR_RELEASE_DC=110; //errore rilasciando il device context
        static const int ERR_RELEASE_HWND=111;
        static const int ERR_UNREGISTER_WNDCLASS=112;
        static const int ERR_CREATE_FONT=113;

        //utility functions
        /**crea il rendering context utilizzando l'hdc della finestra (o di un altro oggetto)
         pfdType=flag PFD_TYPE_RGBA o altro tipo
         error=restituisce l'error flag
        */
        static HRESULT CreateRenderingContext(int bpp,int pfdType,HDC hdc,HGLRC& hglrc) throw (VideoException);

        /**aggiunge un listener dei messaggi*/
        virtual void AddMessageListener(IWinMessageCallback* callback);
        /** rimuove un listener*/
        void RemoveMessageListener(IWinMessageCallback* callback);

        GLCanvasWin32();
        virtual ~GLCanvasWin32();
        /**Restituisce la larghezza in pixel dell'area di disegno*/
        virtual int GetWidth();
        /**Restituisce l'altezza in pixel dell'area di disegno*/
        virtual int GetHeight();
        /**Restituisce la posizione x del vertice in alto a sinistra*/
        virtual int GetLeft();
        /**Restituisce la posizione y del vertice in alto a sinistra*/
        virtual int GetTop();

        //interfaccia HWNDWin
        virtual HWND getHWND(void);

        /**Trace debug*/
        void TraceMode(bool enable);
        bool isTraceEnabled();

        /**Eventi ridisegno (vengono invocati quanto l'area viene ridisegnata*/
        virtual PaintEvent* AddPaintEvent(PaintEvent* evt);
        virtual bool RemovePaintEvent(PaintEvent* evt);

        /**Eventi tastiera*/
        virtual KeyEvents* AddKeyEvents(KeyEvents* e);
        virtual bool RemoveKeyEvents(KeyEvents* e);
        /**Eventi mouse*/
        virtual MouseEvents* AddMouseEvents(MouseEvents* e);
        virtual bool RemoveMouseEvents(MouseEvents* e);
        /**Eventi movimento del mouse*/
        virtual MouseMoveEvents* AddMouseMoveEvents(MouseMoveEvents* e);
        virtual bool RemoveMouseMoveEvents(MouseMoveEvents* e);
        /**Eventi focus*/
        FocusEvents* AddFocusEvents(FocusEvents* evt);
        bool RemoveFocusEvents(FocusEvents* evt);
        /**Eventi di animazione*/
        virtual AnimationEvent* AddAnimationEvent(AnimationEvent* evt);
        virtual bool RemoveAnimationEvent(AnimationEvent* evt);
        /**Avvia il loop grafico*/
        virtual void StartAnimation()=0;
        /**Interrompe il loop di aggiornamento grafico*/
        virtual void StopAnimation()=0;
        /**Avvia il loop di animazione specificando i tasti di uscita e toggle full screen*/
        virtual void StartAnimation(int exit_key,int toggle_fullscreen_key)=0;


    };

    #ifdef _USEVIDEONAMESPACE_
};
#endif

#endif // GLCANVAS_H_INCLUDED
