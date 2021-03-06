/***********************************
Utilità di gestione palette VGA (DOS)
-funzioni di caricamento e memorizzazione su file
-varie
Code by Leonardo Berti (c) 2009
************************************/


#ifndef _VGAPALETTE_MGR_INCLUDE_
#define _VGAPALETTE_MGR_INCLUDE_

#include "palette.h"

class VGAPaletteManager:public VGAPalette
{
   private:
   
   VGA_RGB_COLOR palette[PALETTE_ENTRIES];
   void WaitForVsync(); //attende il retrace
   float *fpalette; //usate per il fading da una palette all'altra
   float *fincrs;

   public:
   
   VGAPaletteManager();
   virtual ~VGAPaletteManager();
   int GetLastError();  
   /**Acquisisce la palette corrente settata nella VGA*/
   void AcquireCurrentVGAPalette();
   /**Carica la palette standard VGA*/
   void LoadVGAPalette();
   /**Carica la palette da file in formato JASC-PAL (PaintShopPro)*/
   bool LoadJascPalette(char* filename);
   /**Salva la palette nel formato JASC-PAL*/
   bool SaveJascPalette(char* filename);
   /**Applica la palette corrente*/
   void ApplyPalette();
   /**Imposta tutti i registri della palette a zero*/
   void SetZeroPalette();
   /**Imposta tutti i colori della palette sul colore color*/
   void SetFlatPalette(const VGA_RGB_COLOR& color);
   /**Crea una palette monocolore in dest_pal*/
   void CreateFlatPalette(VGA_RGB_COLOR_PTR dest_pal,const VGA_RGB_COLOR& color);
   /**Trasforma la palette in scala di grigi*/
   void CreateGrayScale(VGA_RGB_COLOR_PTR pal);
   /**Trasforma la palette in una scala di tonalità*/
   void CreateColorScale(VGA_RGB_COLOR_PTR pal,const VGA_RGB_COLOR& color);
   /**Esegue il fading da una palette settata a zero alla palette indicata in palette
   nwaits=numero di attese del retrace verticale
   */
   void FadeFromBlack(const VGA_RGB_COLOR_PTR pal_dest,bool nwaits);
   /**Esegue il fading verso il nero*/
   void FadeToBlack(const VGA_RGB_COLOR_PTR pal_init,bool nwaits);
   /**Esegue il fading dal bianco alla palette specificata*/
   void FadeFromWhite(const VGA_RGB_COLOR_PTR pal_dest,bool nwaits);
   /**Esegue il fading verso il bianco*/
   void FadeToWhite(const VGA_RGB_COLOR_PTR pal_init,bool nwaits);
   /**Esegue il fading da una palette ad un altra in modo proporzionale*/
   void FadeSmooth(const VGA_RGB_COLOR_PTR dest,const VGA_RGB_COLOR_PTR src,int steps);
   /**Esegue il fading da una palette all'altra*/
   void Fade(const VGA_RGB_COLOR_PTR dest,const VGA_RGB_COLOR_PTR src,int nwaits);

};


#endif
