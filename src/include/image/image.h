/****************************************
Interfaccia di una generica immagine
bidimensionale
Code by L.Berti 2008
*****************************************/

#ifndef IMAGE_H_INCLUDED
#define IMAGE_H_INCLUDED

#include "video/videodef.h"
#include "io/reader.h"
#include "tchar.h"
#include "image/imgbuf.h"


#ifdef _USEVIDEONAMESPACE_
namespace video {
#endif



/**Un'immagine costituita da un rettangolo di pixel*/
class Image {
public:

     /**basic error flags*/
     static const int no_error=0;
     static const int error_reading=-1;
     static const int invalid_image=-2;
     static const int invalid_datasource=-3;
     static const int invalid_format=-4;
     static const int unsupported_format=-5;
     static const int unsupported_operation=-6;
     static const int buff_alloc_error=-7;
     static const int unsupported_bpp=-8;

     virtual ~Image() {}
     /**Larghezza in pixel*/
     virtual int GetWidth() const =0;
     /**Altezza in pixel*/
     virtual int GetHeight() const =0 ;
     /**Pitch in byte*/
     virtual int GetPitch() const =0;
     /**Restituisce il formato pixel*/
     virtual const PIXEL_FORMAT GetPixelFormat() const =0;
     /**Controlla se l'immagine � vuota*/
     virtual bool IsEmpty() const =0;
     /**Restituisce il puntatore al buffer immagine*/
     virtual const IMAGE_BUFFER* GetBuffer() const=0;
     /**Carica da un reader*/
     virtual bool Load(io::Reader* reader,const TCHAR* format) throw (VideoException)=0;
     /**Carica da un file*/
     virtual bool Load(const TCHAR* file_name)=0;
     /**Resetta l'immagine e dealloca la memoria*/
     virtual void Unload()=0;
     /**Error flag*/
     virtual int GetLastError(void) const =0;
     /**Capovolge l'immagine*/
     virtual void FlipVertical()=0;
     virtual void FlipHorizontal()=0;
     virtual void Blit(int x,int y) const=0;
     virtual void Blit(int x,int y,int raster_opt) const=0;
     //aggiungere BlitNoClip e BlicCopy (ignora la trasparenza)
     //aggiungere Create(width,height)   (crea una immagine vuota)
     virtual void BlitRot(int x,int y,float alpha_deg) const=0;
     virtual void BlitRect(int x,int y,const SEL_RECT* src_rect) const=0;
     virtual void BlitRectRot(int x,int y,const SEL_RECT* src_rect,float alpha_deg) const=0;

};

/**
Una porzione di immagine definita dal rettangolo di selezione sel_rect
*/
class IMAGE_RECT {
public:

     SEL_RECT* sel_rect;
     const Image* image;

     IMAGE_RECT() {
          image=0;
          sel_rect=0;
     }

     IMAGE_RECT(Image* img,SEL_RECT* r) {
          image=img;
          sel_rect=r;
     }

     void Blit(int x,int y) const {

          if (!image) return;

          if (sel_rect==0) {
               image->Blit(x,y);
          } else image->BlitRect(x,y,sel_rect);
     }

     int GetWidth() const
     {
         if (!image) return 0;

         if (sel_rect==0)
         {
             return image->GetWidth();
         }
         else return sel_rect->GetWidth();
     }

     int GetHeight() const
     {
         if (!image) return 0;

         if (sel_rect==0)
         {
             return image->GetHeight();
         }
         else return sel_rect->GetHeight();

     }

};

#ifdef _USEVIDEONAMESPACE_
};
#endif

#endif // IMAGE_H_INCLUDED
