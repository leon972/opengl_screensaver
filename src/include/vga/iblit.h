/**************************************************
Interfaccia per tutti i blitter di immagini VGA
Code by Leonardo Berti (c) 2009
(16 bit DOS real mode)
***************************************************/

#ifndef _I_VGA_BLITTER_
#define _I_VGA_BLITTER_

#include "vgadef.h"

//raster operations
#define RASTER_COPY 1         //copia tenendo conto dei pixel trasparenti
#define RASTER_COPY_FILL 2    //copia ignorando i pixel trasparenti
#define RASTER_COPY_ON_MASK 4 //copia solo sui pixel non trasparenti
#define RASTER_COPY_NO_MASK 8 //copia solo sui pixel destinazione trasparenti
#define RASTER_COPY_SHADOW 16 //effetto "ombra"
#define RASTER_COPY_HILIGHT 32 //effetto "luce"

class IVGABlitter
{
  public:

  virtual ~IVGABlitter() {};

  /**Acquisisce il colore trasparente corrente*/
  virtual unsigned char GetTranspColor()=0;
  /**Imposta il colore trasparente corrente*/
  virtual void SetTranspColor(unsigned char color)=0;

  /**Imposta il buffer di destinazione
  offs_table=tabella degli offset del buffer di destinazione
  */
  virtual void SetDestBuffer(unsigned char* buffer,int width,int height,int pitch,const unsigned int* offs_table)=0;

  virtual void SetDestBuffer(VGA_IMAGE_BUFFER_PTR img,const unsigned int* offs_table)=0;

  /**Esegue il blitting tenendo conto della trasparenza impostata nel blitter (clipping automatico)*/
  virtual void Blit(int x,int y,VGA_IMAGE_BUFFER_PTR img)=0;
  /**Esegue il blitting compiendo una operazione raster sui pixel (clipping automatico)*/
  virtual void Blit(int x,int y,int raster_opt,VGA_IMAGE_BUFFER_PTR img)=0;
  /**Esegue il blitting senza clipping e senza trasparenza*/
  virtual void BlitFastCopyNoClip(int x,int y,VGA_IMAGE_BUFFER_PTR img)=0;
  /**Esegue il blitting senza trasparenza con clipping*/
  virtual void BlitFastCopy(int x,int y,VGA_IMAGE_BUFFER_PTR img)=0;
  /**Blit speciale ottimizzato per copiare l'immagine su tutto il buffer destinazione (no clip non trasp.)*/
  virtual void BlitFastCls(VGA_IMAGE_BUFFER_PTR img)=0;
  /**Esegue il blitting con rotazione*/
  virtual void BlitRot(int x,int y,float alpha_deg,VGA_IMAGE_BUFFER_PTR img)=0;
  /**Esegue il blitting di un rettangolo dell'immagine*/
  virtual void BlitRect(int x,int y,const VGA_RECT_PTR src_rect,VGA_IMAGE_BUFFER_PTR img)=0;
  /**Esegue il blitting di un rettangolo dell'immagine*/
  virtual void BlitRect(int x,int y,const VGA_RECT_PTR src_rect,int raster_opt,VGA_IMAGE_BUFFER_PTR img)=0;
  /**Esegue il blitting con rotazione di un rettangolo dell'immagine*/
  virtual void BlitRectRot(int x,int y,const VGA_RECT_PTR src_rect,float alpha_deg,VGA_IMAGE_BUFFER_PTR img)=0;

};

#endif