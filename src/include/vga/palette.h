/***********************************
Gestione della palette colori VGA (DOS)
Code by Leonardo Berti (c) 2008
************************************/

#ifndef _VGAPALETTE_INCLUDE_
#define _VGAPALETTE_INCLUDE_

//porte VGA per la gestione della palette:
# define PALETTE_MASK         0x3c6
# define PALETTE_REGISTER_RD  0x3c7
# define PALETTE_REGISTER_WR  0x3c8
# define PALETTE_DATA         0x3c9
//numero di colori nella palette VGA
#define PALETTE_ENTRIES       256

typedef  float pal_clampf; //valore flat compreso fra 0.0 e 1.0

typedef struct VGA_RGB_COLOR
{
   unsigned char red;    //compreso fra 0 e 64
   unsigned char green;  //compreso fra 0 e 64
   unsigned char blue;   //compreso fra 0 e 64
   
   VGA_RGB_COLOR(unsigned char r,unsigned char g,unsigned char b)
   {
     red=r;
     green=g;
     blue=b;
   }
   
   VGA_RGB_COLOR()
   {
      red=green=blue=0;
   }
   
   void set(unsigned char r,unsigned char g,unsigned char b)
   {
      red=r;
      green=g;
      blue=b;
   }

} *VGA_RGB_COLOR_PTR;

class VGAPalette
{  
   private:


   public:

   /**Imposta un colore della palette*/
   void SetPaletteEntry(int index,const VGA_RGB_COLOR_PTR color);
   void SetPaletteEntryRGB(int index,unsigned char red,unsigned char green,unsigned char blue);
   void SetPaletteEntryF(int index,pal_clampf red,pal_clampf green,pal_clampf blue);
   /**Acquisisce un colore dalla palette*/
   void GetPaletteEntry(int index,VGA_RGB_COLOR_PTR color);
   /**Crea un entry RGB a partire da valori float limitati 0-1*/
   void MakeRGB(VGA_RGB_COLOR_PTR color,pal_clampf red,pal_clampf green,pal_clampf blue);
   /**Crea una sfumatura dal colore iniziale a quello finale*/
   void SetPaletteShade(int index1,const VGA_RGB_COLOR_PTR first,int index2,const VGA_RGB_COLOR_PTR last);
   /**Imposta i registri della palette specificati in entries*/
   void VGAPalette::SetPaletteEntries(VGA_RGB_COLOR_PTR entries,int from_index,int num_entries);
   /**Acquisisce una sequenza di registri della palette in entries (già dimensionato) a partire da from_index per un totale di num_entries registri*/
   void VGAPalette::GetPaletteEntries(VGA_RGB_COLOR_PTR entries,int from_index,int num_entries);
   /**Imposta tutti i 256 registri della palette specificati in entries*/
   void VGAPalette::SetAllPalette(VGA_RGB_COLOR_PTR entries);
   /**Acquisisce tutti i 256 registri della palette e li salva in entries (già dimensionato*/
   void VGAPalette::GetAllPalette(VGA_RGB_COLOR_PTR entries);
   
    //trasforma una palette con canali a 8 bit (0-255) in una con canali a 6 bit (0-63)
   static void To6BitPalette(VGA_RGB_COLOR_PTR palette,int num_entries);

};


#endif