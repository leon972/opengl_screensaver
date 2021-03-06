/*************************************************
Immagini TGA (TARGA)
Code by L.Berti (c) 2008
**************************************************/

#ifndef TGA_H_INCLUDED
#define TGA_H_INCLUDED

#include "lwtk/libhead.h"
#include "image/imgbuf.h"
#include "video/videodef.h"
#include "io/reader.h"
#include "video/video_exception.h"
#include <tchar.h>

using namespace io;

#ifdef _USEVIDEONAMESPACE_
namespace video
{
#endif

/**Header dei file TGA*/
typedef struct TGA_HEADER_TYP
{
    unsigned char idLength;
    unsigned char colorMapType;
    unsigned char imageTypeCode;
    unsigned char colorMapSpec[5];
    unsigned short xOrigin;
    unsigned short yOrigin;
    unsigned short width;
    unsigned short height;
    unsigned char bpp;
    unsigned char imageDesc;

} TGA_HEADER,*TGA_HEADER_PTR;

class DLL_EXPORT TGA
{
    private:

    TGA();
    static void ZeroHeader(TGA_HEADER_PTR header);

    public:

    /**tipi di immagine TGA (imageTypeCode)*/
    static const int tga_no_image_data=0;
    static const int tga_uncomp_mapped=1; //uncompressed color mapped
    static const int tga_uncomp_rgba=2;
    static const int tga_uncomp_gray=3; //gray scale
    static const int tga_rle_mapped=9;  //run length encoded color mapped
    static const int tga_rle_rgba=10;
    static const int tga_rle_gray=11;

    /**Carica l'immagine TGA in un buffer RGBA8888*/
    static int Load(IMAGE_BUFFER_PTR dest,const TCHAR* filename) throw (VideoException);

    /**Carica l'immagine TGA in un buffer RGBA8888*/
    static int Load(IMAGE_BUFFER_PTR dest,Reader* reader) throw (VideoException);

    static TGA_HEADER GetHeader(const TCHAR* filename);

    static TGA_HEADER GetHeader(Reader* reader);

};

#ifdef _USEVIDEONAMESPACE_
};
#endif

#endif // TGA_H_INCLUDED

