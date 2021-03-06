/*************************************
Blitter per la modalità 13h (320x200x256)
Code by Leonardo Berti (c) 2009
(16 bit DOS real mode)
**************************************/

#ifndef _VGA13H_BLITTER_INCLUDE_
#define _VGA13H_BLITTER_INCLUDE_

#include "iblit.h"
#include "vgadef.h"

/**Blitter specifico per la modalità 13h e immagini a 8 bit con pitch multiplo di 2
NOTA:le funzioni di blitting assumono che le impostazioni del buffer di destinazione
siano corrette e non fanno nessun controllo sui parametri passati
*/
class BlitterVGA13h:public virtual IVGABlitter
{
  private:

   //info buffer destinazione
   int dest_w;
   int dest_h;
   int dest_pitch;
   unsigned char* dest_buff;
   const unsigned int* offsTable;
   int transp_color;

  public:

  BlitterVGA13h();
  virtual ~BlitterVGA13h();
  
  /**Acquisisce il colore trasparente corrente*/
  unsigned char GetTranspColor();
  /**Imposta il colore trasparente corrente*/
  void SetTranspColor(unsigned char color);

  /**Imposta il buffer di destinazione
  offs_table=tabella degli offset del buffer di destinazione
  */
  void SetDestBuffer(unsigned char* buffer,int width,int height,int pitch,const unsigned int* offs_table);
  
  void SetDestBuffer(VGA_IMAGE_BUFFER_PTR img,const unsigned int* offs_table);

  /**Esegue il blitting tenendo conto della trasparenza impostata nel blitter (clipping automatico)*/
  void Blit(int x,int y,VGA_IMAGE_BUFFER_PTR img);
  /**Esegue il blitting compiendo una operazione raster sui pixel (clipping automatico)*/
  void Blit(int x,int y,int raster_opt,VGA_IMAGE_BUFFER_PTR img);
  /**Esegue il blitting senza clipping e senza trasparenza*/
  void BlitFastCopyNoClip(int x,int y,VGA_IMAGE_BUFFER_PTR img);
  /**Esegue il blitting senza trasparenza con clipping*/
  void BlitFastCopy(int x,int y,VGA_IMAGE_BUFFER_PTR img);
  /**Blit speciale ottimizzato per copiare l'immagine su tutto il buffer destinazione (no clip non trasp.)
  assume che l'immagine sorgente e la destinazione siano uguali ed entrambe con larghezza divisibile per 4
  */
  virtual void BlitFastCls(VGA_IMAGE_BUFFER_PTR img);
  /**Esegue il blitting con rotazione*/
  void BlitRot(int x,int y,float alpha_deg,VGA_IMAGE_BUFFER_PTR img);
  /**Esegue il blitting di un rettangolo dell'immagine*/
  void BlitRect(int x,int y,const VGA_RECT_PTR src_rect,VGA_IMAGE_BUFFER_PTR img);
  /**Esegue il blitting di un rettangolo dell'immagine*/
  void BlitRect(int x,int y,const VGA_RECT_PTR src_rect,int raster_opt,VGA_IMAGE_BUFFER_PTR img);
  /**Esegue il blitting con rotazione di un rettangolo dell'immagine*/
  void BlitRectRot(int x,int y,const VGA_RECT_PTR src_rect,float alpha_deg,VGA_IMAGE_BUFFER_PTR img);

};

#endif