/*****************************************************************
Implementa l'interfaccia video.h per OpennGL per Win32
Code by Leonardo Berti 1/1/2007
******************************************************************/

#ifndef VIDEOGLW_H_INCLUDED
#define VIDEOGLW_H_INCLUDED

#include "lwtk/libhead.h"
#include <windows.h>
#include <stdio.h>
#include "video/video_exception.h"
#include "video/video.h"
#include "video/canvas.h"
#include "logger/logger.h"
#include "lwtk/mouse.h"
#include "glcanvas.h"
#include "lwtk/keys.h"
#include <math.h>
#include <gl/gl.h>
#include <gl/glext.h>
//stl stack
#include <stack>
#include <vector>
#include <list>

#ifdef _USEVIDEONAMESPACE_
namespace video {
    #endif

    using namespace std;

    typedef struct VIDEOGLWIN32_STATE_TYP {
        COLOR color;
        COLOR fillcolor;
        COLOR transpcolor;
        COLOR text_color;

    } VIDEOGLWIN32_STATE,*VIDEOGLWIN32_STATE_PTR;

//difinizione puntatori a funzione usati per il settaggio del vsync
    typedef void (APIENTRY *PFNWGLEXTSWAPCONTROLPROC) (int);
    typedef int (*PFNWGLEXTGETSWAPINTERVALPROC) (void);


    class VideoGlWin32;


class DLL_EXPORT VideoGlWin32:public virtual Video,public virtual Canvas,public GLCanvasWin32 {

private:

        static const float m_conv; //fattore conv gradi->radianti

        //funzioni utilizzate per il vsync
        PFNWGLEXTSWAPCONTROLPROC wglSwapIntervalEXT;
        PFNWGLEXTGETSWAPINTERVALPROC wglGetSwapIntervalEXT;

        VIDEOGLWIN32_STATE m_state;

        static LRESULT CALLBACK WndProc(HWND hWnd,UINT uMsg,WPARAM wParam,LPARAM lParam);

        //stringa con tutte le estensioni supportate
        static char* m_strGLExtensions;

        static void DetectTextureTarget(bool trace); //determina se � presente l'estensione che abilita texture con lati non 2^n

        static bool texture_target_detected;//settato su 1 quando ha deteminato il texture_target

        static GLenum texture_2d_target;

        //converte da byte a float una terna di valori
        static void ByteToFloat3(GLclampf f[3],unsigned char b[3]);

        static void ByteToFloat4(GLclampf f[4],unsigned char b[4]);

        VERSION_INFO version;

        bool m_vsync_enabled;

        HFONT m_hSelFont; //font selezionato nell'hdc corrente

        int m_font_width,m_font_height; //dimensioni del font

        //inizializza OpenGL
        virtual bool initGL(void) throw (VideoException);

        //Crea la finestra principale OpenGL (anche in modalit� fullscreen)
        HRESULT CreateGLWindow(HDC& hdc,HGLRC& hglrc,HWND& hwnd,HINSTANCE& hinstance,WNDPROC WndProc,const char* title,int width,int height,int bpp,bool fullscreen,int frequency) throw (VideoException);

        //Distrugge la finestra OpenGL
        void DestroyGLWindow();

        //Ricrea e ridimensiona la finestra e pulisce lo schermo
        virtual void reshape(int w,int h);

        //memorizza i parametri di stato per il disegno
        void PushDrawState(void);
        //ripristina i parametri di stato del disegno
        void PopDrawState(void);
        //traccia il risultato di change display settings
        void TraceDispSettingsResult(LONG result);

        //inizializza il font OpenGl
        bool InitFonts(int font_height) throw(VideoException);
        //rilascia il font
        void DestroyFont(void);
        //restituisce l'istanza corrente
        static VideoGlWin32* getInstance(void);

        //Esegue le inizializzazioni prima di avviare il graphic loop
        virtual void InitGraphicLoop();

        //Esegue la deinizializzazione alla fine del graphic loop
        virtual void DeinitGraphicLoop();

        /**inizializza il vsync*/
        void InitVsync();

protected:

         //il sistema di coordinate dipende dalla particolare implementazione
        int last_error;
        VAxisDir m_vaxis_dir; //direzione asse verticale
        HAxisDir m_haxis_dir; //direzione asse orizzontale
        OriginPos m_origin_pos; //posizione origine
        COLOR m_color; //colore per il disegno corrente
        COLOR m_text_color; //colore di output per il testo
        COLOR m_fill_color; //colore per il riempimento corrente
        bool m_palette_mode; //flag modalit� palette
        bool m_full_screen; //flag modalit� full screen
        bool m_show_cursor;
        COLOR m_transparent_color; //colore trasparente usato per il blitting
        int m_last_error; //id ultimo errore
        int m_exit_key; //tasto fine app. (ESC per default )
        int m_toggle_key; //tasto toggle fullscreen (F1 per default)
        PIXEL_FORMAT m_pixel_format; //descrizione del formato pixel
        clock_t last_clock;
        int fps_cnt;  //usato per il calcolo delle frame per secondo
        int clip_x,clip_y,clip_x1,clip_y1; //rettangolo di clipping corrente
        bool m_bClippingEnabled;
        double m_fps; //frame per second
        //Enumerazione modalit� grafiche disponibili
        PFN_ENUM_VIDEO_MODES m_CallbackEnumVidModes;
        //Inizializza le variabili di stato
        void init(void);

        const TCHAR* title;

        bool is_visible;

        GLubyte rgbaFillColor[4]; //componenti colore di riempimento
        GLubyte rgbaDrawColor[4];
        GLubyte rgbaTextColor[4];
        UINT m_font_display_list; //ID della display list del font caricato
        /**textmetric per il device context corrente*/
        TEXTMETRIC textmetrics;
        //list<WindowEvents*> *window_events;

        list<VideoEvents*>* video_events;

        //immette un errore nello stack degli errori
        //void PushError(int err);
        void UpdateTextMetrics();
        //Avvia il loop specificando i tasti di uscita e cambiamento modalit� video fullscreen
        bool StartGraphicsLoop(int exitKey,int toggleFullScreenKey);


public:


        static const int ERR_VSYNC=114;

        VideoGlWin32();
        virtual ~VideoGlWin32();
        
        //------------------------- interfaccia Container----------------------------------------------------



        //------------------------- interfaccia Canvas -----------------------------------------------------

        /**Avvia il loop grafico*/
        void StartAnimation();
        /**Interrompe il loop di aggiornamento grafico*/
        void StopAnimation();
        /**Avvia il loop specificando i tasti di uscita e toggle full screen*/
        void StartAnimation(int exit_key,int toggle_fullscreen_key);

        //------------------------- interfaccia Video ------------------------------------------------------

        void SetCallbackEnumVidModes(PFN_ENUM_VIDEO_MODES pfn);

        const TCHAR* GetTitle();

        virtual void SetTitle(const TCHAR* title);

        //imposta la modalit� grafica
        bool SetGraphMode(int width,int height,int bpp,bool fullScreen) throw(VideoException,InvalidVideoState) ;

        bool SetGraphMode(int width,int height,int bpp,bool fullScreen,int frequency) throw(VideoException,InvalidVideoState);

        //passa da modalit� fullscreen a windowed e viceversa
        bool SetFullScreenMode(bool fullScreen);

        //shutdown
        void ShutDown(void);

        //ottiene l'altezza in pixel dell'area grafica
        int GetScreenHeight(void);

        int GetScreenWidth(void);

        int GetScreenBpp(void);

        bool IsPaletteColorMode(void);

        bool IsFullScreen();

        /**
        Visualizza /nasconde il cursore di sitema quando � in modalit� full screen
        */
        void ShowSystemCursor(bool bVisible)
        {
            m_show_cursor=bVisible;
        }

        /**
        determina se il cursore di sistema viene visualizzato in modalit� full screen
        */
        bool isSystemCursorVisible()
        {
            return m_show_cursor;
        }

        OriginPos GetOriginPos(void);

        //restituisce la direzione dell'asse verticale
        VAxisDir GetVerticalAxisDir(void);

        //restituisce la direzione dell'asse orizzontale
        HAxisDir GetHorizontalAxisDir(void);

        PIXEL_FORMAT GetPixelFormat(void);

        bool isGraphicMode(void);

        //cancella l'area grafica
        void Cls(void);

        void Cls(COLOR color);

        void SetClearScreenColor(COLOR color);

        //imposta il colore per il disegno
        void SetDrawColor(COLOR color);

        void SetDrawColor(unsigned char red,unsigned char green,unsigned char blue);

        void SetDrawColor(unsigned char red,unsigned char green,unsigned char blue,unsigned char alpha);

        COLOR GetDrawColor(void);

        //imposta il colore di riempimento
        void SetFillColor(COLOR color);

        void SetFillColor(unsigned char red,unsigned char green,unsigned char blue);

        void SetFillColor(unsigned char red,unsigned char green,unsigned char blue,unsigned char alpha);

        COLOR GetFillColor(void);

        //imposta il colore di output per il testo
        void SetTextColor(COLOR color);

        void SetTextColor(unsigned char red,unsigned char green,unsigned char blue);

        void SetTextColor(unsigned char red,unsigned char green,unsigned char blue,unsigned char alpha);

        COLOR GetTextColor(void);

        void DisplayMessageEx(int x,int y,char* formatText ...);

        //output di testo alle coordinate x,y
        void WriteText(int x,int y,const TCHAR* formatText ...);

        //restituisce la larghezza del font corrente
        int GetFontWidth(void);
        //restituisce l'altezza del font corrente
        int GetFontHeight(void);

        //imposta un pixel dell'area grafica
        void SetPixel(int x,int y);


        //traccia una linea con il colore di disegno corrente
        void DrawLine(int x1,int y1,int x2,int y2);

        //disegna un rettangolo
        void DrawRect(int x1,int y1,int x2,int y2);

        //riempie un rettangolo
        void FillRect(int x1,int y1,int x2,int y2);

        //disegna un cerchio
        void DrawCircle(int cx,int cy,float radius);

        //disegna un arco
        void DrawArc(int cx,int cy,float radiusx,float radiusy,float deg_ang_start,float deg_ang_finish);

        //disegna un'ellisse
        void DrawEllipse(int cx,int cy,float radiusx,float radiusy);

         //rettangolo stondato
        void RoundRect(int x1,int y1,int x2,int y2,int radius,bool filled);

        //riempie un cerchio
        void FillCircle(int cx,int cy,float radius);

        //riempie un'ellisse
        void FillEllipse(int cx,int cy,float radiusx,float radiusy);

        //disegna un arco
        void FillArc(int cx,int cy,float radiusx,float radiusy,float deg_ang_start,float deg_ang_finish);

        //larghezza linea disegno
        void SetLineWidth(int width);

        int GetLineWidth();

        /**Imposta il font corrente per la finestra*/
        void SetFont(Font* font);

        /**Ottiene il font corrente*/
        Font* GetFont();

        /**applica un rettangolo di clipping*/
        void SetClippingArea(int x,int y,int x1,int y1);
        /**rimuove il rettangolo di clipping*/
        void RemoveClippingArea();

        //imposta il colore trasparente il blitting
        void SetTransparentBlitColor(COLOR color);

        COLOR GetTransparentBlitcolor(void);

        //crea un colore a partire dai canali RGBA
        COLOR GetColor(float red,float green,float blue,float alpha);

        //ottiene il colore alle coordinare x,y
        COLOR GetPixel(int x,int y);

        //visualizza il back buffer
        void ShowBackBuffer(void);

        PALETTE_ENTRY GetPaletteEntry(int index);

        void GetPaletteEntry(int index,PALETTE_ENTRY_PTR entry);

        void SetPaletteEntry(int index,PALETTE_ENTRY_PTR entry);

        void WaitForVsync(void);

        //Restituisce le frame per secondo
        double GetFPS(void);

        //Enumera le modalit� disponibili
        void EnumVidModes(void);

        //svuota lo stack degli errori
        void ClearErrors(void);

        //estrae l'ultimo errore dallo stack errori
        int GetLastError(void);

        const char* TranslateErr(int err);

        VERSION_INFO GetVersionInfo();

        VideoEvents* AddVideoEvent(VideoEvents* evt);

        bool RemoveVideoEvent(VideoEvents* evt);

        //--------------------------------------------------------------------------------------------------
        //Metodi specifici per questa implementazione

        //Crea una display list con il font specificato
        //fontName:� il nome del font
        //height=altezza in unit� logiche (em)
        //curDC=device context corrente
        //hfont=par. output restituisce l'handelr del font creato
        //la funzione restituisce l'id della display list che contiene i caratteri del font in formato bitmap
        static UINT CreateGlFont(LPCSTR fontName,int height,HDC curDC,HFONT& hSelFont);


        //restituisce true se la finestra � attiva
        bool isActive(void);
        //Restituisce true se il tasto key � premuto
        bool isKeyPress(int key);

        /**restituisce true se la sincronizzazione verticale � abilitata*/
        bool IsVsyncEnabled();
        /**Abilita/disabilita la sincronizzazione verticale*/
        bool EnableVSync(bool enabled);
        /**Restituisce informazioni sulla schda e sulla versione OpenGL*/
        const char* GetRendererInfo();
        /**Restituisce il nome del produttore dell'hardware*/
        const char* GetRendererVendorInfo();
        /**Altre informazioni*/
        const char* GetRendererExtraInfo();
        /**Determina se una estensione OpenGL � supportata*/
        static bool IsExtensionSupported(const char* ext_name);

        static void ColorToFloat4(GLclampf f[4],COLOR col);

        static GLenum GetTexture2DTarget();

    };

    #ifdef _USEVIDEONAMESPACE_
}
#endif

#endif // VIDEOGLW_H_INCLUDED
