/*****************************************************************
video.h
Interfaccia per la gestione del video full screen e windowed
con disegno di primitive 2D
Code by Leonardo Berti 1/1/2007
 ******************************************************************/

#ifndef _PORTABLEVIDEODEF_INCLUDE_
#define _PORTABLEVIDEODEF_INCLUDE_

#include <time.h>
#include "lwtk/libhead.h"
#include "videodef.h"
#include "graphics.h"
#include "canvas.h"

#define _USENAMESPACE_
#define _USEVIDEONAMESPACE_

#ifdef _USEVIDEONAMESPACE_
namespace video {
#endif

    using namespace lwtk;

    //Errori generici del sistema video
    //le varie implementazioni estendono questa tabella



    //testo usato per gli errori non definiti
#define UNDEFINED_ERROR_TEXT "UNDEFINED ERROR"

    //****** cambiare questa definizione in _USEDOUBLE_ per utilizzare double al posto di float

#define _USEFLOAT_

#ifdef _USEFLOAT_
    //cambiare questa linea se si vuol usare double
    typedef float real;
#endif

#ifdef _USEDOUBLE_
    typedef double real;
#endif

    typedef struct VERSION_INFO_STRC {
        int major;
        int minor;
        int revision;
        char info[64];
    } VERSION_INFO;

    /**Eccezioni*/
    class InvalidVideoState {
    };

    /** Funzioni callback
    Queste funzioni sono utilizzate per intercettare gli eventi della
    tastiera ed altri eventi da parte
    del programma.Possono essere impostate dall'utente
     */

    //Enumerazione modalit� video disponibili
    //w=larghezza in pixel h=altezza bpp=bitper pixel (continua l'enumerazione fino a che rende true)
    typedef bool (*PFN_ENUM_VIDEO_MODES)(int w, int h, int bpp);

    /**Eventi specifici per la classe Video*/
    class VideoEvents {
    public:

        /**Cambiamento della modalit� video*/
        virtual void ChangeDisplaySetting(int w, int h, int bpp) = 0;
        /**Inizio passaggio modalit� full-screen windowed o viceversa*/
        virtual void BeforeToggleFullScreen(bool go_full_screen) = 0;
        /**fine passaggio modalit� full-screen windowed o viceversa*/
        virtual void AfterToggleFullScreen(bool go_full_screen) = 0;

    };


    


    /**
    Interfaccia per la gestione grafica del video in modalit� full screen
    e windowed
     */

    class DLL_EXPORT Video : public virtual Graphics, public virtual Canvas {
    public:

        static const int ERR_NONE = 0;
        static const int ERR_UNSUPPORTED_MODE = 1;
        static const int ERR_UNSUPPORTED_BPP = 2;
        static const int ERR_NOT_IMPLEMETED = 3;
        static const int ERR_INVALID_STATE = 4;
        static const int ERR_UNSUPPORTED = 5;
        static const int ERR_UNKNOWN = 6;
        static const int ERR_HEART_BEAT_UNDEFINED = 7;

        static COLOR getRGBColor(unsigned char red, unsigned char green, unsigned char blue);

        static COLOR getRGBAColor(unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha);

        static COLOR getRGBColorFloat(float red,float green,float blue);

        static COLOR getRGBAColorFloat(float red,float green,float blue,float alpha);

        static void toRGBFloat(float* red,float* green,float* blue,const COLOR& color);

        static void toRGBAFloat(float* red,float* green,float* blue,float* alpha,const COLOR& color);

        static void splitColor(COLOR c, unsigned char& red, unsigned char& green, unsigned char& blue);

        static void splitColor(COLOR c, unsigned char& red, unsigned char& green, unsigned char& blue, unsigned char& alpha);
      
        virtual ~Video();

        //aggiunge un listener degli eventi video
        virtual VideoEvents* AddVideoEvent(VideoEvents* evt) = 0;
        /**
        rimuove un listener degli eventi video
         */
        virtual bool RemoveVideoEvent(VideoEvents* evt) = 0;

        /**Acquisisce il titolo della finestra*/
        virtual const TCHAR* GetTitle() = 0;

        /**Imposta il titolo della finestra quando � in modalit� windowed*/
        virtual void SetTitle(const TCHAR* title) = 0;

        //imposta la modalit� grafica
        virtual bool SetGraphMode(int width, int height, int bpp, bool fullScreen) = 0;
        //immposta la modalit� grafica specificando anche la frequenza
        virtual bool SetGraphMode(int width, int height, int bpp, bool fullScreen, int frequency) = 0;

        //Cambia da modalit� full screen a windowed anche dopo aver impostato la modalit� grafica
        virtual bool SetFullScreenMode(bool fullScreen) = 0;

        //Rende true se il sistema � inizializzato in modalit� grafica
        virtual bool isGraphicMode(void) = 0;

        //shutdown:deinizializza la modalit� grafica e termina
        virtual void ShutDown(void) = 0;

        /**
        Visualizza /nasconde il cursore di sitema quando è in modalità full screen
         */
        virtual void ShowSystemCursor(bool bVisible) = 0;

        /**
        determina se il cursore di sistema viene visualizzato in modalit� full screen
         */
        virtual bool isSystemCursorVisible() = 0;


        //attende il retrace
        virtual void WaitForVsync(void) = 0;
        //abilita/disabilita la sincronizzazione con il retrace verticale
        virtual bool EnableVSync(bool enabled) = 0;

        virtual bool IsVsyncEnabled() = 0;

        //visualizza il back buffer
        virtual void ShowBackBuffer(void) = 0;

        virtual PALETTE_ENTRY GetPaletteEntry(int index) = 0;

        virtual void GetPaletteEntry(int index, PALETTE_ENTRY_PTR entry) = 0;

        virtual void SetPaletteEntry(int index, PALETTE_ENTRY_PTR entry) = 0;

        //restituisce la descrizione del pixel della modalit� corrente
        virtual PIXEL_FORMAT GetPixelFormat(void) = 0;

        //Enumerazione modalit� grafiche disponibili
        virtual void SetCallbackEnumVidModes(PFN_ENUM_VIDEO_MODES pfn) = 0;
        //Enumera le modalit� disponibili
        virtual void EnumVidModes(void) = 0;
        //Restituisce le frame per secondo
        virtual double GetFPS(void) = 0;
        //ottiene l'ultimo errore verificatosi
        virtual int GetLastError(void) = 0;
        //svuota lo stack degli errori
        virtual void ClearErrors(void) = 0;
        //restituisce l'errore in formato stringa
        virtual const char* TranslateErr(int err) = 0;
        //restituisce informazioni sulla versione
        virtual VERSION_INFO GetVersionInfo() = 0;
        //restituisce informazioni sull'hardware
        virtual const char* GetRendererInfo() = 0;
        /**Restituisce il nome del produttore dell'hardware*/
        virtual const char* GetRendererVendorInfo() = 0;
        /**Altre informazioni*/
        virtual const char* GetRendererExtraInfo() = 0;
    };

#ifdef _USEVIDEONAMESPACE_
}
#endif

#endif
