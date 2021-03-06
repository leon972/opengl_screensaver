/*******************************************
Implementazione OpenGL del manager immagini RGBA8888
********************************************/

#ifndef IMAGEMGRGLW_H_INCLUDED
#define IMAGEMGRGLW_H_INCLUDED

#include "lwtk/libhead.h"
#include "image/imagemgr.h"
#include "videoglw/imagegl.h"

#ifdef _USEVIDEONAMESPACE_
namespace video
{
#endif

/**Gestione immagini RGBA8888*/

class DLL_EXPORT ImageMgrGl:public ImageMgr
{
    private:

    IMAGE_BUFFER_PTR GetBuffer(Image* img);
    ImageGL* pimg;

    public:

    ImageMgrGl();

     /**Rende tutti i pixel con colore transp_color trasparenti*/
    virtual bool MakeTransparent(Image*,COLOR transp_color);

    /**Rimuove il canale alpha settandolo su 0xFF (opaco))*/
    virtual bool MakeOpaque(Image*,const COLOR* exclude_color);

    /**Rende l'immagine semitrasparente impostando il canale alpha per tutti i pixel*/
    virtual bool MakeAlpha(Image*,unsigned char alpha,const COLOR* exclude_color);

    /**Sostituisce i pixel di unj colore con i pixel di un altro colore*/
    virtual bool ReplaceColor(Image*,COLOR col_to_replace,COLOR replace_with);

    /**Sostituisce tutti colori diversi da transp_color con il colore*/
    virtual bool MakeShadow(Image*,COLOR shadow_color,const COLOR* transp_color);

    /**Scurisce dark_level 0=lascia inalterato 255=nero*/
    virtual bool MakeDarker(Image*,unsigned char dark_level,const COLOR* transp_color);

    /**Schiarisce*/
    virtual bool MakeLighter(Image*,unsigned char light_level,const COLOR* transp_color);

    /**Scala di grigi*/
    virtual bool MakeGrayScale(Image*,const COLOR* transp_color);

    /**Copia un'immagine*/
    virtual bool CopyImage(Image* dest_img,const Image* src_img) throw (VideoException);

    virtual bool GrabImage(Image* dest_img,const Image* src_img,const SEL_RECT_PTR rect) throw (VideoException);

};

#ifdef _USEVIDEONAMESPACE_
};
#endif

#endif // IMAGEMGRGLW_H_INCLUDED
