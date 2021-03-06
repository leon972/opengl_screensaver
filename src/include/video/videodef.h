/*****************************************************************
video.h
Interfaccia per un sistema grafico portabile
Code by Leonardo Berti 2008
******************************************************************/

#ifndef VIDEODEF_H_INCLUDED
#define VIDEODEF_H_INCLUDED

#define _USENAMESPACE_
#define _USEVIDEONAMESPACE_

#ifdef _USEVIDEONAMESPACE_
namespace video
{
#endif

//tabella colori comuni
//nota: il byte meno significativo è impostato su FF perchè sono colori opachi

#define CL_BLACK 0x000000FF
#define CL_TRANSPARENT 0x00000000
#define CL_WHITE 0xFFFFFFFF
#define CL_DARKBLUE 0x000080FF
#define CL_DARKGREEN 0x008000FF
#define CL_CYAN 0x008080FF
#define CL_DARKRED 0x800000FF
#define CL_MAGENTA 0xFF00FFFF
#define CL_DARKYELLOW 0x808000FF
#define CL_LIGHTGRAY 0x808080FF
#define CL_GRAY 0x404040FF
#define CL_BLUE 0x0000FFFF
#define CL_GREEN 0x00FF00FF
#define CL_LIGHTCYAN 0x00FFFFFF
#define CL_RED 0xFF0000FF
#define CL_LIGHTMAGENTA 0xFF00FFFF
#define CL_YELLOW 0xFFFF00FF
#define CL_VIOLET 0x9400D3FF
#define CL_PINK 0xFFC0CBFF
#define CL_ORANGE 0xFFA500FF
#define CL_DARKORANGE 0xFF8C00FF
#define CL_LIGHTYELLOW 0xFFFFE0FF
#define CL_LIGHTBLUE 0x1E90FFFF
#define CL_BROWN 0xA0522DFF
#define CL_BEIGE 0xF5F5DCFF
#define CL_TURQUOISE 0x40E0D0FF
#define CL_GREENYELLOW 0xADF52FFF
#define CL_SKYBLUE 0x87CEFAFF
#define CL_NAVY 0x191970FF
#define CL_AQUAMARINE 0x7FFFD4FF
#define CL_GOLD 0xFFD700FF

//utilità
#ifndef SAFE_DELETE
#define SAFE_DELETE(p)       { if(p) { delete (p);     (p)=0; } }
#endif

#ifndef SAFE_DELETE_ARRAY
#define SAFE_DELETE_ARRAY(p) { if(p) { delete[] (p);   (p)=0; } }
#endif

typedef unsigned int COLOR;

typedef enum ORIGIN_POS_TYP
{
    UPPER_LEFT=0,
    UPPER_RIGHT=1,
    LOWER_LEFT=2,
    LOWER_RIGHT=3,
    CENTER=4

} OriginPos,*OriginPos_Ptr;

typedef enum HAXIS_DIR_TYP
{
    LEFT_TO_RIGHT=0,
    RIGHT_TO_LEFT=1

} HAxisDir,*HAxisDir_Ptr;

typedef enum VAXIS_DIR_TYP
{
    TOP_DOWN=0,
    BOTTOM_UP=1

} VAxisDir,*VAxisDir_Ptr;

typedef struct PIXELFORMAT_TYP
{
    int bpp; //bit per pixel
    int redMask;
    int greenMask;
    int blueMask;
    int alphaMask;

    int redBits;
    int greenBits;
    int blueBits;
    int alphaBits;

    int redShift; //shift
    int greenShift;
    int blueShift;
    int alphaShift;

} PIXEL_FORMAT,*PIXEL_FORMAT_PTR;

typedef struct PALETTE_ENTRY_TYP
{
    unsigned char red;
    unsigned char green;
    unsigned char blue;

} PALETTE_ENTRY,*PALETTE_ENTRY_PTR;

typedef struct
{
   unsigned char r,g,b,a;

} RGBA8888_PIXEL,*RGBA8888_PIXEL_PTR;

/**pixel RGB con 8 bit per canale*/
typedef struct
{
  unsigned char r,g,b;

} RGB888_PIXEL,*RGB888_PIXEL_PTR;




// colore a 24 formato 888
#define RGB24BIT(r,g,b) ((b) + ((g) << 8) + ((r) << 16) )

// colore a 32 bit (8 bit per canale alpha)
#define RGBA32BIT(r,g,b,a) ((b<<8) + ((g) << 16) + ((r) << 24) + (a))

//colore a 32 bit con opaco
#define RGB_COLOR(r,g,b) ( r<<24 | g<<16 | b<<8 | 0xFF )

#define REDCHANNEL(c) ( (c >> 24) & 0x000000FF)
#define GREENCHANNEL(c) ( (c >> 16) & 0x000000FF)
#define BLUECHANNEL(c) ( (c >> 8) & 0x000000FF)
#define ALPHACHANNEL(c) ( c & 0x000000FF)

#ifdef _USEVIDEONAMESPACE_
};
#endif

#endif // VIDEODEF_H_INCLUDED
