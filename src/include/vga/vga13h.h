/*************************************
Libreria di funzioni grafiche per la
modalità VGA 13h (DOS)
Code by Leonardo Berti (c) 2008
**************************************/

#ifndef _VGA13H_INCLUDE_
#define _VGA13H_INCLUDE_

#include "vgadef.h"

typedef unsigned char COLOR_INDEX;

class VideoVGA13h
{
  friend class VGAImage;

  private:

    unsigned char* video_buffer;
    unsigned char* double_buffer;
    unsigned char* rom_char_set;
    unsigned short double_buffer_segment;   //16 bit unsigned
    unsigned short double_buffer_offset;    //16 bit unsigned

    //tabella degli offset del buffer video e doppio buffer
    unsigned int offsTable[VGA13H_SCREEN_HEIGHT];
    //tabella seno e coseno
    float sinTable[MAX_ANGLE];
    float cosTable[MAX_ANGLE];
    
    char tmpMsg[MSG_LEN];

    COLOR_INDEX fill_color,draw_color,text_color;

    void InitData();

    void ClearBuffer(int color,unsigned char *buffer);

    unsigned char GetBufferPixel(int x,int y,const unsigned char *buffer);

  public:

    VideoVGA13h();
    
    virtual ~VideoVGA13h();

    /**Inizializza la VGA in modalità 13h (320x200 8 bpp)*/
    void SetVGA320x200x8();
    /**Imposta la modalità testo*/
    void SetTextMode();
    /**Restituisce la larghezza in pixel del video*/
    int GetWidth();
    /**Restituisce l'altezza in pixel del video*/
    int GetHeight();
    /**Restituisce il numero di colori nella palette*/
    int GetNumColors();
    /**Restituisce l'offset della memoria video del punto di coordinate x,y*/
    unsigned int VideoOffset(int x,int y);
    /**Restituisce il puntatore alla memoria video*/
    unsigned char* GetVideoBuffer();
    /**Restituisce il puntatore al back buffer*/
    unsigned char* GetBackBuffer();
    /**Restituisce la tabella degli offset*/
    const unsigned int* GetOffsetTable();
    /**Setta un pixel nel back buffer (clip)*/
    void SetPixel(int x,int y,unsigned char color);
    /**Setta il pixel senza clipping*/
    void SetPixelNoClip(int x,int y,unsigned char color);
    /**Acquisce un pixel dal back buffer*/
    unsigned char GetPixel(int x,int y);
    /**Pulisce il back buffer*/
    void Cls();
    /**Pulisce il backbuffer con il colore specificato*/
    void Cls(unsigned char color);
    /**Attende il retrace verticale del video*/
    void WaitForVsync(void);
    /**Copia il back buffer nel buffer video*/
    void ShowBackBuffer();
    /**Copia il backbuffer senza attendere il retrace (no vsync) */
    void ShowBackBufferNoWait();
    /**Imposta il colore di disegno corrente*/
    void SetDrawColor(COLOR_INDEX color);
    COLOR_INDEX GetDrawColor();
    /**Imposta il colore di riempimento corrente*/
    void SetFillColor(COLOR_INDEX color);
    COLOR_INDEX GetFillColor();
    /**Imposta il colore di output di testo corrente*/
    void SetTextColor(COLOR_INDEX color);
    COLOR_INDEX GetTextColor();
    /**Disegna una linea da punto a punto usando il colore corrente*/
    void DrawLine(int x1,int y1,int x2,int y2);
    /**Disegna una linea orizzontale con clipping*/
    void DrawHLine(int x1,int x2,int y);
    /**Disegna una linea orizzontale senza eseguire il clipping*/
    void DrawHLineNoClip(int x1,int x2,int y);
    /**Disegna una linea verticale*/
    void DrawVLine(int y1,int y2,int x);
    /**Disegna un rettangolo*/
    void DrawRect(int x1,int y1,int x2,int y2);
    /**Riempie un rettangolo con il colore di riempimento*/
    void FillRect(int x1,int y1,int x2,int y2);
    /**Traccia un cerchio*/
    void DrawCircle(int cx,int cy,float radius);
    /**Traccia una ellisse*/
    void DrawEllipse(int cx,int cy,float radiusx,float radiusy);
    /**Riempie un trapezio*/
    void FillTrapezium(int xa1,int xa2,int y1,int xb1,int xb2,int y2);
    /**Riempie un cerchio*/
    void FillCircle(int cx,int cy,float radius);
    /**Disegna un carattere alle coordinate xc,yc*/
    void BlitChar(int xc,int yc,char c);
    /**Output di una stringa*/
    void BlitString(int xc,int yc,char* text,int sep);
    //output di testo alle coordinate x,y
    void WriteText(int x,int y,char* formatText ...);
    //debugging functions
    void InitFakeGraphicMode();
};



#endif
