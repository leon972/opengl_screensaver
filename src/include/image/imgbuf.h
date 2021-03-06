/************************************
Generico buffer immmagine
Code by L.Berti (c) 2008
*************************************/

#ifndef IMGBUF_H_INCLUDED
#define IMGBUF_H_INCLUDED

#include "lwtk/libhead.h"
#include "video/videodef.h"
#include "geom/geomdefs.h"
#include "video/video_exception.h"
#include <stddef.h>

#ifdef _USEVIDEONAMESPACE_



namespace video {
    #endif

    //rettangolo di selezione
    typedef geom::RECT_TYP<int> SEL_RECT;
    typedef SEL_RECT* SEL_RECT_PTR;

    /**Buffer di un immagine*/
    typedef struct {

        int width,height; //larghezza e altezza in pixel
        int pitch; //pitch in bytes
        void* buffer; //buffer immagine
        PIXEL_FORMAT pf; //pixel format

    } IMAGE_BUFFER,*IMAGE_BUFFER_PTR;

    /**pixel RGBA con 8 bit per canale
    canale alpha: a=0xFF pixel completamente opaco, a=0x00 pixel completamente
    trasparente
    */

    /**Trasformazioni buffer immagini (RGBA 8888)
    NB:gestisce solo immagini con bit depth 32 formato RGBA 8888
    */

    class DLL_EXPORT ImageBufferMgr {
private:

        ImageBufferMgr();


        static bool CheckBuffer(IMAGE_BUFFER_PTR img_buff);

public:

        /**Alloca e setta il buffer*/
        static bool AllocateBuffer(IMAGE_BUFFER_PTR img_buff,int width,int height,int byte_align,const PIXEL_FORMAT_PTR pf) throw (VideoException);

        /**Dealloca e resetta il buffer*/
        static void ReleaseBuffer(IMAGE_BUFFER_PTR img_buff);
        /**Restituisce il pitch del buffer immagine in byte*/
        static int GetPitch(int width,int bpp,int byte_align);

        /**Restituisce il numero di byte di padding necessari per raggiungere l'allineamento*/
        static int GetBytePadding(int width,int bpp,int byte_align);

        /**Restituisce la dimensione in byte del buffer*/
        static size_t GetBufferSize(IMAGE_BUFFER_PTR img_buff);

        /**Rende true se il buffer � valido*/
        static bool IsValid(IMAGE_BUFFER_PTR img_buff);

        /**Crea un pixel format per pixel rgba con 8 bit per canale*/
        static void CreateRGBA8888(PIXEL_FORMAT_PTR pf);

        static void CreateRGB888(PIXEL_FORMAT_PTR pf);

        /**Rende trasparente il colore transp_color impostando il canale alpha*/
        static bool MakeTransparent(IMAGE_BUFFER_PTR img_buff,COLOR transp_color);

        /**Rimuove il canale alpha settandolo su 0xFF (opaco))*/
        static bool MakeOpaque(IMAGE_BUFFER_PTR img_buff,const COLOR* exclude_color);

        /**Rende l'immagine semitrasparente impostando il canale alpha per tutti i pixel*/
        static bool MakeAlpha(IMAGE_BUFFER_PTR img_buff,unsigned char alpha,const COLOR* exclude_color);

        /**Sostituisce i pixel di unj colore con i pixel di un altro colore*/
        static bool ReplaceColor(IMAGE_BUFFER_PTR img_buff,COLOR col_to_replace,COLOR replace_with);

        /**Sostituisce tutti colori diversi da transp_color con il colore*/
        static bool MakeShadow(IMAGE_BUFFER_PTR img_buff,COLOR shadow_color,const COLOR* exclude_color);

        /**Scurisce dark_level 0=lascia inalterato 255=nero*/
        static bool MakeDarker(IMAGE_BUFFER_PTR img_buff,unsigned char dark_level,const COLOR* exclude_color);

        /**Schiarisce*/
        static bool MakeLighter(IMAGE_BUFFER_PTR img_buff,unsigned char light_level,const COLOR* exclude_color);

        /**Trasforma in grayscale*/
        static bool MakeGrayScale(IMAGE_BUFFER_PTR img_buff,const COLOR* exclude_color);

        /**Duplica il buffer, il buffer di destinazione deve essere gi� allocato e di dimensioni uguale al sorgente*/
        static bool CopyBuffer(IMAGE_BUFFER_PTR dest_buffer,const IMAGE_BUFFER_PTR src_buffer) throw (VideoException);

        /**Copia un rettangolo di dimensioni uguali al buffer destinazione (gi� allocato) dal buffer sorgente a partire dal
        vertice in basso a sinistra specificato da xfrom y from*/
        static bool GrabBuffer(IMAGE_BUFFER_PTR dest_buffer,const IMAGE_BUFFER_PTR src_buffer,int xfrom,int yfrom) throw (VideoException);

    };

    #ifdef _USEVIDEONAMESPACE_
};
#endif

#endif // IMGBUF_H_INCLUDED
