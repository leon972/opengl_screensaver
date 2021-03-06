/*****************************************
Definisce la struttura per una Texture OpenGL
******************************************/

#ifndef TEXTDEF_H_INCLUDED
#define TEXTDEF_H_INCLUDED

#include "image/image.h"

typedef struct OGL_TEXTURE_TYP
{
    //dimensioni in pixel
    int width; //larghezza in pixel
    int height; //altezza in pixel
    GLEnum target; //es. GL_TEXTURE_2D
    GLint level; //usato per il mipmap (texture base ha livello 0)
    GLint internal_format; //es. GL_RGBA
    GLenum pixel_format; //es. GL_RGBA
    GLenum buffer_type; //es. GL_UNSIGNED_BYTE
    int border; //0=senza bordo 1 con bordo
    GLuint texture_id; //id texture usato con glBindTexture

} OGL_TEXTURE,*OGL_TEXTURE_PTR;

#endif // TEXTDEF_H_INCLUDED
