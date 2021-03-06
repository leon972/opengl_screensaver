/*************************************
Libreria di funzioni grafiche per la
modalità VGA 13h (DOS)
Code by Leonardo Berti (c) 2009
Gestione immagini a 8 bit
(16 bit DOS real mode)
**************************************/

#ifndef _IMG8BIT_INCLUDE_
#define _IMG8BIT_INCLUDE_

//codici errore
#define IMG_NO_ERROR 0
#define IMG_ERROR_READING -1
#define IMG_INVALID_IMAGE -2
#define IMG_INVALID_DATASOURCE -3
#define IMG_INVALID_FORMAT -4
#define IMG_UNSUPPORTED_FORMAT -5
#define IMG_UNSUPPORTED_OPERATION -6
#define IMG_BUFF_ALLOC_ERROR -7
#define IMG_UNSUPPORTED_BPP -8
#define IMG_BLITTER_NOT_SET -9
#define IMG_IS_EMPTY -10

//formati immagini caricabili
#define FMT_UNKNOWN 0
#define FMT_PCX 1
#define FMT_BMP 2

#include "vga/palette.h"
#include "vga/iblit.h"
#include "vga/vgadef.h"

class VGAImage
{
   private:

     VGA_IMAGE_BUFFER img_buffer;
     unsigned char transp_color; //colore trasparente
     IVGABlitter* blitter;

     static int last_error;
     //restituisce il formato dell'immagine in base all'estensione del
     static int GetFmtFromName(const char* fname);

   public:

    /**Crea la tabella degli offset per un buffer assegnato pitch e altezza immagine (restituisce il puntatore alla tabella)
    la procedura chiamante deve farsi carico di rilasciare la memoria della tabella creata
    */
    static const unsigned int* CreateOffsetTable(unsigned int** offs_table,int h,unsigned int pitch);

    VGAImage();
    virtual ~VGAImage();
    /**Larghezza in pixel*/
    int GetWidth() const;
    /**Altezza in pixel*/
    int GetHeight() const;
    /**Pitch in byte*/
    int GetPitch() const;
    /**Controlla se l'immagine è vuota*/
    bool IsEmpty() const;
    /**Restituisce il puntatore al buffer immagine*/
    VGA_IMAGE_BUFFER_PTR GetBuffer() const;
    /**Carica da file (in base all'estensione del file)*/
    bool Load(const char* file,bool apply_palette);
    /**Carica l'immagine da file specificando il formato*/
    bool Load(const char* file,int fmt,bool apply_palette);
    /**Crea una immagine vuota*/
    bool Create(int width,int height);
    /**Resetta l'immagine e dealloca la memoria*/
    void Unload();
    /**Error flag*/
    int GetLastError(void) const;
    /**Capovolge l'immagine*/
    void FlipVertical();
    void FlipHorizontal();
    void Blit(int x,int y);
    void Blit(int x,int y,int raster_opt);
    void BlitRot(int x,int y,float alpha_deg);
    void BlitRect(int x,int y,const VGA_RECT_PTR src_rect);
    void BlitRect(int x,int y,const VGA_RECT_PTR src_rect,int raster_opt);
    void BlitRectRot(int x,int y,const VGA_RECT_PTR src_rect,float alpha_deg);

    //------- funzioni da inserire nell'interfaccis standard ----
    //salva su file
    bool Save(const char* file);
    //imposta il blitter usato per il blitting dell'immagine
    void SetBlitter(IVGABlitter& blitter);
    /**Acquisisce il colore trasparente corrente*/
    unsigned char GetTranspColor();
    /**Imposta il colore trasparente corrente*/
    void SetTranspColor(unsigned char color);

};

#endif