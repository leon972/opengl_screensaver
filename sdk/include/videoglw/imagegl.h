/**********************************************
Immagine bidimensionale realizzata tramite
una texture OpenGL
Code by L.Berti (c) 2008
***********************************************/

#ifndef IMAGEGL_H_INCLUDED
#define IMAGEGL_H_INCLUDED

#include "lwtk/libhead.h"
#include "image/image.h"
#include "image/imgbuf.h"
#include "video/video_exception.h"
#include "gl/gl.h"
#include <list>
#include <string>

#ifdef _USEVIDEONAMESPACE_


namespace video
{
#endif

#ifndef TEXTURE_RECTANGLE_EXT
#define TEXTURE_RECTANGLE_EXT 0x84F5
#endif

/**Immagine RGBA8888
NB:OpenGL supporta per default solo immagini che hanno lati di dimensioni
esprimibili come 2^n (anche se il lati possono essere diversi)
la limitazione non � presente se � disponibile l'extension ARB_texture_non_power_of_2
oppure ARB_texture_rectangle
*/



class DLL_EXPORT ImageGL:public virtual Image
{
    friend class ImageMgrGl;
    friend class VideoGlWin32;
    friend class SpriteGL;

    protected:

    IMAGE_BUFFER img_buffer; //buffer immagine
    //parametri usati con glTextImage2D
    GLenum tx_format; //es. GL_RGBA
    GLenum tx_type; //es. GL_UNSIGNED_BYTE
    GLuint texture_id; //id texture usato con glBindTexture
    int last_error;
    //usato per il blitting, se usa l'estensione GL_TEXTURE_RECTANGLE_ARB sono uguali alla larghezza e altezza
    //in pixel altrimenti sono entrambi 1.0
    float txwidth,txheight;
    int BindTexture(bool reg_img) throw(VideoException);
    void UnbindTexture();
    void UpdateBuffer();

    void reset();

    static std::list<ImageGL*> reg_images;

    //funzioni usate per tenere traccia delle immagini create in modo
    //da rispristinare quando si distrugge l'openGL context (esempio al cambiamento fullscreen/windowed)
    static void RegisterImage(ImageGL* img);
    static void UnregisterImage(ImageGL* img);
    /**Ricrea il binding delle immagini con le textures*/
    static void RestoreImages();
    static void ToUpperCase(std::string* s);

    static bool static_init;

    static GLenum texture_2d_target;

    static void InitStatic();

    public:

    static const int err_error_binding=-100;
    static const int err_invalid_state=-101;
    static const int err_binding=-102;

    virtual ~ImageGL();
    ImageGL();

    /**Larghezza in pixel*/
    virtual int GetWidth() const;
    /**Altezza in pixel*/
    virtual int GetHeight() const;
    /**Pitch in byte*/
    virtual int GetPitch() const;
    /**Restituisce il formato pixel*/
    virtual const PIXEL_FORMAT GetPixelFormat() const;
    /**Controlla se l'immagine � vuota*/
    virtual bool IsEmpty() const;
    /**Restituisce il puntatore al buffer immagine*/
    virtual const IMAGE_BUFFER* GetBuffer() const;
    /**Error flag*/
    virtual int GetLastError(void) const;
     /**Carica da un reader*/
    virtual bool Load(io::Reader* reader,const TCHAR* format) throw (VideoException);
    /**Carica da un file*/
    virtual bool Load(const TCHAR* file_name) throw (VideoException);
    /**Capovolge l'immagine*/
    virtual void FlipVertical();
    virtual void FlipHorizontal();
    virtual void Unload();
    virtual void Blit(int x,int y) const;
    virtual void Blit(int x,int y,int raster_op) const;
    virtual void BlitRot(int x,int y,float alpha_deg) const;
    /**Esegue il blitting del rettangolo definito in src_rect.
    NB:il rettangolo � definito nel sistema di coordinate dell'immagine.
    Il top � minore del bottom. y=0 si riferisce alla linea piu' bassa dell'immagine
    mentre il y=height alla linea piu' alta (l'ASSE Y ' RIVOLTO IN ALTO!!)*/
    virtual void BlitRect(int x,int y,const SEL_RECT* src_rect) const;
    virtual void BlitRectRot(int x,int y,const SEL_RECT* src_rect,float alpha_deg) const;

};

#ifdef _USEVIDEONAMESPACE_
};
#endif

#endif // IMAGEGL_H_INCLUDED
