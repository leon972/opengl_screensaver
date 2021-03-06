/***************************************
Blitter per i caratteri grafici
Il charset � a spaziatura fissa
Implementazione usando l'engine arcade
I caratteri sono ordinati (secondo la codifica ASCII estesa) )in celle di uguali dimensioni
all'interno dell'immagine sorgente da sinistra a destra e dall'alto in basso
Il charset puo' contenere anche un sottoinsieme dei caratteri ASCII

5-2-2010
****************************************/
#ifndef CHARSETIMPL_H_INCLUDED
#define CHARSETIMPL_H_INCLUDED

#include "2dgameutils/charset.h"
#include "spriteglw.h"

namespace video
{

    class CharsetBlitterImpl:public CharsetBlitter
    {
        protected:

        //numero massimo di caratteri nel charset
        static const int MAX_TABLE_CHARS=256;
        //lunghezza massima del testo da stampare
        static const int MAX_TEXT_LENGTH=2048;

        //dimensioni del carattere
        int charWidth,charHeight;
        int asciiStartCode;//primo carattere ascii in tabella
        int nChars;//numero di caratteri nella tabella
        //rettangolo di grabbing tabella
        SEL_RECT tableRect;
        //rettangoli di grabbing usati per il blitting in coordinate
        //native del sistema di rendering
        SEL_RECT grabRects[MAX_TABLE_CHARS];
        //immagine che contiene il set di caratteri
        Image* sourceImage;
        //crea i rettangoli di grabbing grabRects
        void CreateRects(int tableLeft,int tableTop,int cols,int charWidth,int charHeight,int nChars) throw (VideoException);

        public:

        /**
        Crea un charset blitter-
        @param sourceImage immagine che contiene la tabella dei caratteri
        @param tableLeft ascissa bordo sinistro tabella
        @param tableTop ordinata bordo superiore tabella (coordinate in spazio immagine)
        @param cols numero di colonne nella tabella
        @param asciiStartCode codice ASCII primo carattere (gli altri sono in sequenza)
        @param nChars numero di caratteri validi
        @param charWidth larghezza carattere in pixel
        @param charHeight altezza carattere in pixel

        */
        CharsetBlitterImpl(Image* sourceImage,int tableLeft,int tableTop,int cols,int charWidth,int charHeight,int asciiStartCode,int nChars) throw (VideoException);

        ~CharsetBlitterImpl();

        /**
        Stampa una stringa alla posizione x,y (x,y) coordinate native nel sistema di rendering
        */
        virtual void print(int x,int y,const char* text, ...);
        /**
        altezza carattere in pixel
        */
        virtual int CharHeight();
        /**
        larghezza carattere in pixel
        */
        virtual int CharWidth();
        /**
        Restituisce la larghezza di una stringa in pixel
        */
        virtual int GetStringLength(const char* text);

    };

};


#endif // CHARSETIMPL_H_INCLUDED
