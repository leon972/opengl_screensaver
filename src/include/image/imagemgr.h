/************************************************
Trasformazioni del buffer immagine
*************************************************/

#ifndef IMAGEMGR_H_INCLUDED
#define IMAGEMGR_H_INCLUDED

#include "video/videodef.h"
#include "image/image.h"
#include <stddef.h>

#ifdef _USEVIDEONAMESPACE_
namespace video
{
#endif

class ImageMgr
{
    public:

    virtual ~ImageMgr() {}
    /**Rende tutti i pixel con colore transp_color trasparenti*/
    virtual bool MakeTransparent(Image* img,COLOR transp_color)=0;

    /**Rimuove il canale alpha settandolo su 0xFF (opaco))*/
    virtual bool MakeOpaque(Image* img,const COLOR* transp_color)=0;

    /**Rende l'immagine semitrasparente impostando il canale alpha per tutti i pixel*/
    virtual bool MakeAlpha(Image* img,unsigned char alpha,const COLOR* exclude_color)=0;

    /**Sostituisce i pixel di unj colore con i pixel di un altro colore*/
    virtual bool ReplaceColor(Image* img,COLOR col_to_replace,COLOR replace_with)=0;

    /**Sostituisce tutti colori diversi da transp_color con il colore*/
    virtual bool MakeShadow(Image* img,COLOR shadow_color,const COLOR* transp_color)=0;

    /**Scurisce dark_level 0=lascia inalterato 255=nero*/
    virtual bool MakeDarker(Image* img,unsigned char dark_level,const COLOR* transp_color)=0;

    /**Schiarisce*/
    virtual bool MakeLighter(Image* img,unsigned char light_level,const COLOR* transp_color)=0;

    /**Scala di grigi*/
    virtual bool MakeGrayScale(Image* img,const COLOR* exclude_color)=0;

    /**Copia un'immagine in un'altra immagine*/
    virtual bool CopyImage(Image* dest_img,const Image* src_img)=0;

    /**Copia una porzione rettangolore dell'immagine sorgente in quella destinazione.
    L'immagine destinazione viene dimensionata in base alle dimensioni del rettangolo copiato*/
    virtual bool GrabImage(Image* dest_img,const Image* src_img,const SEL_RECT_PTR rect)=0;


};

#ifdef _USEVIDEONAMESPACE_
};
#endif

#endif // IMAGEMGR_H_INCLUDED
