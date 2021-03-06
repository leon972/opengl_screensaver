/*****************************************************************
Implementazione di un motore grafico 3D con OpenGL per Win32
Code by Leonardo Berti (c) 2007
******************************************************************/

#ifndef L3DENGINEGLW_H_INCLUDED
#define L3DENGINEGLW_H_INCLUDED

#include "lwtk/libhead.h"
#include "video/video.h"      //interfaccia video 2D
#include "video/canvas.h"
#include "videoglw/videoglw.h"
#include "cameraglw.h"
#include "mod3dglw.h"
#include "math/vectors3.h"    //vettori a 2,3 e 3 dim in coord. omogenee
#include "math/matrix2.h"     //matrici 2x2,3x3 e 3x3 in coord. omogenee
#include "math/quat2.h"       //quaternions
#include "3dengine/3dengine.h"
#include "logger/logger.h"
#include "lightglw.h"
#include "nodeglw.h"
#include <list>           //std list

//nota : queste istruzioni del preprocessore servono ad esclude i namespace
//per rendere i file compatibili con alcuni vecchi compilatori
#ifdef _USENAMESPACE_
using namespace mathengine; //namespace usato dai moduli matematici
#endif

#ifdef _USEDOUBLE_
//usa i double per le coordinate
#define GL_REAL GL_DOUBLE
#else
//usa i float
#define GL_REAL GL_FLOAT
#endif

#ifdef _USEVIDEONAMESPACE_
namespace video {
#endif

//converte la matrice in una matrice nel formato OpenGL
    void DLL_EXPORT ToGlMatrix(GLfloat* m,const CHMatrix33<real>& matrix);
    void DLL_EXPORT ToMatrix(CHMatrix33<real>* m,const GLfloat* matrix);

    //debug::Logger& operator<< (debug::Logger& fl,const float* m);
    //debug::Logger& operator<< (debug::Logger& fl,const CHMatrix33<real>& m);

    class DLL_EXPORT L3DEngineGlWin32:public L3DEngine,public virtual Canvas,public virtual Video,public virtual VideoGlWin32 {
    private:

        //default camera
        CameraGlWin32* m_pDefaultCam;

        Viewport m_DefaultVp;

        // RenderList* m_pInternalRenderList;

        bool m_b2D;

        //inizializza OpenGL (proiezione 3D)
        bool initGL(void) throw (VideoException);

        //Distrugge la finestra OpenGL
        void DestroyGLWindow(void);

        //Ricrea e ridimensiona la finestra (modalit� 3D)
        void reshape(int w,int h);

        //Esegue le inizializzazioni prima di avviare il graphic loop
        void InitGraphicLoop();

        //Esegue la deinizializzazione alla fine del graphic loop
        void DeinitGraphicLoop();

        //scene node radice
        SceneNodeGlw root_node;

    protected:



    public:

        L3DEngineGlWin32();
        ~L3DEngineGlWin32();

        //interfaccia Video -----------------------------------------

        //imposta la modalit� grafica e crea la finestra OpenGL
        bool SetGraphMode(int width,int height,int bpp,bool fullScreen) throw (VideoException,InvalidVideoState);

        bool SetGraphMode(int width,int height,int bpp,bool fullScreen,int frequency) throw (VideoException,InvalidVideoState);

        //ottiene l'altezza in pixel dell'area grafica
        int GetScreenHeight(void);

        int GetScreenWidth(void);

        int GetScreenBpp(void);

        bool IsPaletteColorMode(void);

        bool IsFullScreen();

        VideoEvents* AddVideoEvent(VideoEvents* evt);

        bool RemoveVideoEvent(VideoEvents* evt);

        void ShowSystemCursor(bool bVisible);

        bool isSystemCursorVisible();

        //shutdown
        void ShutDown(void);

        void DisplayMessageEx(int x,int y,char* formatText ...);

        bool is2DMode(void);

        //inizia la modalit� ortogonale (disegno di primitive 2D)
        bool Begin2D(void);

        //termina la modalit� 2D
        bool End2D(void);

        //output di testo alle coordinate x,y
        void WriteText(int x,int y,const TCHAR* formatText ...);

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

        //disegna un arco riempito
        void FillArc(int cx,int cy,float radiusx,float radiusy,float deg_ang_start,float deg_ang_finish);


        //larghezza linea disegno
        void SetLineWidth(int width);

        int GetLineWidth();

        /**Imposta il font corrente per la finestra*/
        void SetFont(Font* font);

        /**Ottiene il font corrente*/
        Font* GetFont();

        const char* TranslateErr(int err);

        /**aggiunge un oggetto da renderizzare alla scene node radice*/
        void Add(Renderable* r);

        /**rimuove un oggetto renderizzabile dalla scene-node radice*/
        void Remove(Renderable* r);

        /**aggiunde una scene-node alla scene-node radice*/
        void AddChildNode(SceneNode* node);

        /**rimuove una scene-node dalla scene node radice*/
        void RemoveChildNode(SceneNode* node);

        //------------------------------------------------------------

        void SetRenderingFlags(int flags);

        int GetRenderingFlags(void);

        //esegue il rendering
        void RenderScene(void);

        //---------------------- interfaccia Video --------------------------

        //Cambia da modalit� full screen a windowed anche dopo aver impostato la modalit� grafica
        bool SetFullScreenMode(bool fullScreen);

        //Rende true se il sistema � inizializzato in modalit� grafica
        bool isGraphicMode(void);

        //cancella l'area grafica
        void Cls(void);

        void Cls(COLOR c);

        void SetClearScreenColor(COLOR color);

        void SetTransparentBlitColor(COLOR color);

        //acquisisce il colore trasparente per il blitting
        COLOR GetTransparentBlitcolor(void);

        //imposta il colore per il disegno
        void SetDrawColor(COLOR color);

        void SetDrawColor(unsigned char red,unsigned char green,unsigned char blue);

        void SetDrawColor(unsigned char red,unsigned char green,unsigned char blue,unsigned char alpha);

        //imposta il colore di riempimento
        void SetFillColor(COLOR color);

        void SetFillColor(unsigned char red,unsigned char green,unsigned char blue);

        void SetFillColor(unsigned char red,unsigned char green,unsigned char blue,unsigned char alpha);

        //imposta il colore di output per il testo
        void SetTextColor(COLOR color);

        void SetTextColor(unsigned char red,unsigned char green,unsigned char blue);

        void SetTextColor(unsigned char red,unsigned char green,unsigned char blue,unsigned char alpha);

        //restituisce la larghezza del font corrente
        int GetFontWidth(void);

        //restituisce l'altezza del font corrente
        int GetFontHeight(void);

        //ottiene il colore per il disegno
        COLOR GetDrawColor(void);

        //ottiene il colore corrente per il riempimento
        COLOR GetFillColor(void);

        //ottiene il colore di output per il testo corrente
        COLOR GetTextColor(void);

        //ottiene il colore alle coordinare x,y
        COLOR GetPixel(int x,int y);

        /**applica un rettangolo di clipping*/
        void SetClippingArea(int x,int y,int x1,int y1);

        /**rimuove il rettangolo di clipping*/
        void RemoveClippingArea();

        //attende il retrace
        void WaitForVsync(void);

        //visualizza il back buffer
        void ShowBackBuffer(void);

        PALETTE_ENTRY GetPaletteEntry(int index);

        void GetPaletteEntry(int index,PALETTE_ENTRY_PTR entry);

        void SetPaletteEntry(int index,PALETTE_ENTRY_PTR entry);

        //Restituisce la posizione dell'origine degli assi di riferimento
        OriginPos GetOriginPos(void);

        //restituisce la direzione dell'asse verticale
        VAxisDir GetVerticalAxisDir(void);

        //restituisce la direzione dell'asse orizzontale
        HAxisDir GetHorizontalAxisDir(void);

        //restituisce la descrizione del pixel della modalit� corrente
        PIXEL_FORMAT GetPixelFormat(void);

        //Avvia il loop specificando i tasti di uscita e cambiamento modalit� video fullscreen
        //bool StartGraphicsLoop(int exitKey,int toggleFullScreenKey);

        //Enumera le modalit� disponibili
        void EnumVidModes(void);

        //Callback invocata quando si cambia la modalit� del display video
        //void SetCallbackChangeDisplaySettings(PFN_CHANGE_DISPLAY_SETTINGS pfn);

        //abilita il tracing degli errori su file log o altro output
        void TraceMode(bool enable);

        //ottiene l'ultimo errore dallo stack
        int GetLastError();

        //svuota lo stack degli errori
        void ClearErrors();

        void OutpuDebugMsg(char* msg);

        VERSION_INFO GetVersionInfo();

        //---------------- interfaccia Window -------------------------

        int GetWidth();
        int GetHeight();
        int GetLeft();
        int GetTop();

        const TCHAR* GetTitle();
        virtual void SetTitle(const TCHAR* title);
        /**Eventi ridisegno*/
        PaintEvent* AddPaintEvent(PaintEvent* evt);
        bool RemovePaintEvent(PaintEvent* evt);
        /**Eventi focus*/
        FocusEvents* AddFocusEvents(FocusEvents* evt);
        bool RemoveFocusEvents(FocusEvents* evt);
        /**Eventi tastiera*/
        KeyEvents* AddKeyEvents(KeyEvents* e);
        bool RemoveKeyEvents(KeyEvents* e);

        /**Eventi mouse*/
        MouseEvents* AddMouseEvents(MouseEvents* e);
        bool RemoveMouseEvents(MouseEvents* e);
        /**Eventi movimento del mouse*/
        MouseMoveEvents* AddMouseMoveEvents(MouseMoveEvents* e);
        bool RemoveMouseMoveEvents(MouseMoveEvents* e);

        /**Avvia il loop grafico*/
        void StartAnimation();

        void StartAnimation(int exit_key, int toggle_fullscreen_key);
        /**Interrompe il loop di aggiornamento grafico*/
        void StopAnimation();

        //metodi specifici per questa implementazione
        virtual HWND getHWND(void);
    };



#ifdef _USEVIDEONAMESPACE_
};
#endif

#endif // 3DENGINEGLW_H_INCLUDED
