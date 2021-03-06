/*************************************************
Immagini PCX a 8 bit (ZSoft Paintbrush PCX)
Code by L.Berti (c) 2009
**************************************************/

#ifndef PCX_H_INCLUDED
#define PCX_H_INCLUDED

#ifdef _USEVIDEONAMESPACE_
namespace video
{
#endif

#define PCX_ERR_NONE 0
#define PCX_ERR_CANT_OPEN_FILE -1
#define PCX_ERR_INVALID_FORMAT -2
#define PCX_ERR_UNSUPPORTED_FORMAT -3
#define PCX_ERR_PALETTE_LOADING -4
#define PCX_ERR_INVALID_PARAMS -5
#define PCX_ERR_ALLOC_BUFFER -6

//header PCX (768 bytes)

typedef struct
{
  
  char manufacturer;             //vale sempre 10
  char version;                  //0=Ver. 2.5 Paintbrush 2=ver. 2.8 con palette 3=versione 2.8 con default 5=ver. Paintbrush 3 o superiore
  char encoding;                 //Vale sempre 1, indica codifica RLE dei pixel
  char bits_per_pixel;           //numero di bit per pixel
  int x,y;                       //angolo sup. sinistro dell'immagine
  int width,height;              //NB: larghezza in pixel -1 e altezza in pixel -1 !!! (dimensione immagine in pixel)
  int horz_res;                  //n. pixel direzione x
  int vert_res;                  //n. pixel nella direzione y
  char ega_palette[48];          //Palette EGA
  char reserved;                 //non usato
  char num_colors_planes;        //numero di piani dell'ìmmagine
  int bytes_per_line;            //numero di byte per ogni linea orizzontale
  int palette_typ;               //?
  char padding[58];              //byte padding

} PCX_HEADER,*PCX_HEADER_PTR;

/**
Caricamento e memorizzazione di file PCX a 8 bit (256 colori)*/
class PCX
{
  
  private:
  
  static int last_error;

  public:
  /**Legge l'intestazione del file*/
  static bool GetHeader(PCX_HEADER_PTR header,const char* filename);

  /**Legge la palette rgb in rgb_palette.rgb_palette deve avere già le dimensioni oppurtune
  ogni canale viene lasciato inalterato come dimensioni rispetto all'originale (0-255).
  la sequenza è RGB
  (il buffer della palette deve essere di 768 byte (256*3))
  */
  static bool GetPalette(void* rgb_palette,const char* filename);

  /**Legge e decodifica il buffer immagine
  NOTA: il buffer viene allocato dalla funzione stessa!!
  */
  static bool GetImageBuffer(PCX_HEADER_PTR header,unsigned char** buffer,void* rgb_palette,const char* filename);

  /**Determina se l'header del file pcx è valido*/
  static bool IsValidHeader(const PCX_HEADER_PTR header);
  
  static int GetLastError();

};

#ifdef _USEVIDEONAMESPACE_
};
#endif

#endif
