/********************************************
Interfaccia di disegno di primitive 2D base
Code by L.Berti (c) 2008
*********************************************/

#ifndef GRAPHICS_H_INCLUDED
#define GRAPHICS_H_INCLUDED

#include "videodef.h"
#include "font.h"
#include <tchar.h>

#ifdef _USEVIDEONAMESPACE_
namespace video
{
#endif

/**
Interfaccia per i dispositivi di ouput grafici
consente il disegno di primitive di base su un oggetto di output
grafico
*/

class Graphics {

public:

        virtual ~Graphics() {}
        virtual void Cls(void)=0;
        virtual void Cls(COLOR c)=0;
        virtual void SetClearScreenColor(COLOR color)=0;
        //imposta un pixel dell'area grafica
        virtual void SetPixel(int x,int y)=0;
        //traccia una linea con il colore di disegno corrente
        virtual void DrawLine(int x1,int y1,int x2,int y2)=0;
        //disegna un rettangolo
        virtual void DrawRect(int x1,int y1,int x2,int y2)=0;
        //rettangolo stondato
        virtual void RoundRect(int x1,int y1,int x2,int y2,int radius,bool filled)=0;
        //riempie un rettangolo
        virtual void FillRect(int x1,int y1,int x2,int y2)=0;
        //disegna un cerchio
        virtual void DrawCircle(int cx,int cy,float radius)=0;
        //disegna un arco
        virtual void DrawArc(int cx,int cy,float radiusx,float radiusy,float deg_ang_start,float deg_ang_finish)=0;
        //disegna un'ellisse
        virtual void DrawEllipse(int cx,int cy,float radiusx,float radiusy)=0;
        //riempie un cerchio
        virtual void FillCircle(int cx,int cy,float radius)=0;
        //riempie un'ellisse
        virtual void FillEllipse(int cx,int cy,float radiusx,float radiusy)=0;
        //disegna un settore riempito con il colore di riempimento corrente
        virtual void FillArc(int cx,int cy,float radiusx,float radiusy,float deg_ang_start,float deg_ang_finish)=0;
        //larghezza linea disegno
        virtual void SetLineWidth(int width)=0;
        virtual int GetLineWidth()=0;
        //imposta il colore trasparente il blitting
        virtual void SetTransparentBlitColor(COLOR color)=0;
        //acquisisce il colore trasparente per il blitting
        virtual COLOR GetTransparentBlitcolor(void)=0;
        //crea il colore a partire dai valori RGB
        //imposta il colore per il disegno
        virtual void SetDrawColor(COLOR color)=0;
        virtual void SetDrawColor(unsigned char red,unsigned char green,unsigned char blue)=0;
        virtual void SetDrawColor(unsigned char red,unsigned char green,unsigned char blue,unsigned char alpha)=0;
        //imposta il colore di riempimento
        virtual void SetFillColor(COLOR color)=0;
        virtual void SetFillColor(unsigned char red,unsigned char green,unsigned char blue)=0;
        virtual void SetFillColor(unsigned char red,unsigned char green,unsigned char blue,unsigned char alpha)=0;
        //imposta il colore di output per il testo
        virtual void SetTextColor(COLOR color)=0;
        virtual void SetTextColor(unsigned char red,unsigned char green,unsigned char blue)=0;
        virtual void SetTextColor(unsigned char red,unsigned char green,unsigned char blue,unsigned char alpha)=0;
        //output di testo alle coordinate x,y
        virtual void WriteText(int x,int y,const TCHAR* formatText ...)=0;
        //restituisce la larghezza del font corrente
        virtual int GetFontWidth(void)=0;
        //restituisce l'altezza del font corrente
        virtual int GetFontHeight(void)=0;
        //ottiene il colore per il disegno
        virtual COLOR GetDrawColor(void)=0;
        //ottiene il colore corrente per il riempimento
        virtual COLOR GetFillColor(void)=0;
        //ottiene il colore di output per il testo corrente
        virtual COLOR GetTextColor(void)=0;
        virtual COLOR GetPixel(int x,int y)=0;
        //ottiene la larghezza in pixel dell'area grafica
        virtual int GetScreenWidth(void)=0;
        //ottiene l'altezza in pixel dell'area grafica
        virtual int GetScreenHeight(void)=0;
        //ottiene il numero di bit per pixel
        virtual int GetScreenBpp(void)=0;
        //rende true se è in modalità color palette
        virtual bool IsPaletteColorMode(void)=0;

        virtual bool IsFullScreen(void)=0;

        //Restituisce la posizione dell'origine degli assi di riferimento
        virtual OriginPos GetOriginPos(void)=0;

        //restituisce la direzione dell'asse verticale
        virtual VAxisDir GetVerticalAxisDir(void)=0;

        //restituisce la direzione dell'asse orizzontale
        virtual HAxisDir GetHorizontalAxisDir(void)=0;

        /**Imposta il font corrente per la finestra*/
        virtual void SetFont(Font* font)=0;
        /**Ottiene il font corrente*/
        virtual Font* GetFont()=0;
        /**applica un rettangolo di clipping*/
        virtual void SetClippingArea(int x,int y,int x1,int y1)=0;
        /**rimuove il rettangolo di clipping*/
        virtual void RemoveClippingArea()=0;
};


#ifdef _USEVIDEONAMESPACE_
};
#endif


#endif // GRAPHICS_H_INCLUDED
