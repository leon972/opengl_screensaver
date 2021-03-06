/**************************************
Definizioni utili per la gestione delle librerie 
grafiche per scheda VGA
****************************************/

#ifndef _VGA_DEFS_
#define _VGA_DEFS_

#ifdef __cplusplus
    #define __CPPARGS ...
#else
    #define __CPPARGS
#endif

//indirizzo memoria video (segment = 0xA000 offset=0000  A000:0000)
#define VGA13H_VIDEO_RAM  0xA0000000L
//dimensione in byte del buffer video (64k)
#define VGA13H_VIDEO_SIZE (size_t) 64000L
//puntatore alla tabella dei caratteri ASCII della ROM (F000:FA6E)
#define ROM_CHAR_SET 0xF000FA6EL

#define ROM_CHAR_HEIGHT 8
#define ROM_CHAR_WIDTH  8

//numero massimo di caratteri nei messaggi visualizzati da WriteText
#define MSG_LEN 128

#define VGA13H_SCREEN_WIDTH 320
#define VGA13H_SCREEN_HEIGHT 200
#define VGA13H_SCREEN_BPP 8
#define VGA13H_SCREEN_COLORS 256

#define VGA_320x200x8     (char)   0x13
#define TEXT_MODE         (char)   0x3

//porte VGA per manipolazione palette:
# define PALETTE_MASK         0x3c6
# define PALETTE_REGISTER_RD  0x3c7
# define PALETTE_REGISTER_WR  0x3c8
# define PALETTE_DATA         0x3c9

#define  VGA_INPUT_STATUS_1   0x3DA // vga status reg 1, bit 3 è il vsync
                                   // 1 - retrace in progress
                                   // 0 - no retrace

#define VGA_VSYNC_MASK 0x08        // maschera i bit non voluti del registro di stato della VGA

#define MAX_ANGLE 361
#define ANGLE_CONV  (float) 0.0174533  //fattore di conversione gradi->radianti

//buffer immagine piano in cui ogni pixel occupa un byte
typedef struct
{
   unsigned char* buffer;     //buffer a 8 bit per pixel
   int width;                 //larghezza dell'immagine in pixel
   int height;                //altezza immagine in pixel
   int pitch;                 //pitch (passo) del buffer immagine in byte

} VGA_IMAGE_BUFFER,*VGA_IMAGE_BUFFER_PTR;

typedef struct VGA_RECT
{
  int left,top,right,bottom;

  VGA_RECT(int l,int t,int r,int b)
  {
     left=l;
     top=t;
     right=r;
     bottom=b;
  }

  VGA_RECT()
  {
    left=right=top=bottom=0;
  }
  
  void set(int l,int t,int r,int b)
  {
    left=l;
    top=t;
    right=r;
    bottom=b;
  }

} *VGA_RECT_PTR;

#endif
