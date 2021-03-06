/**************************************************
Fader.
Usato per creare effetti fade to black fade to color ecc...
****************************************************/

#ifndef FADER_H_INCLUDED
#define FADER_H_INCLUDED


#include "video.h"

#ifdef _USEVIDEONAMESPACE_
namespace video
{
#endif

class Fader
{
    public:

    virtual ~Fader() {}
    /**Inizializza il fader specificando il colore finale*/
    virtual void FadeToColor(COLOR dest_color,int steps,Video* screen)=0;
    /**Inizializza il fader specificando il colore iniziale*/
    virtual void FadeFromColor(COLOR src_color,int steps,Video* screen)=0;
    /**Esegue un passo,quando ha raggiunto il colore finale rende false,altrimenti rende true*/
    virtual bool Fade()=0;
    /**Restituisce il passo corrente [1..steps]*/
    virtual int GetCurrentStep()=0;
    /**Resetta*/
    virtual void Reset()=0;
    /**Restituisce true se il fading non è completo*/
    virtual bool IsFading()=0;
    /**Inverte la direzione del fading*/
    virtual void Invert()=0;

};

#ifdef _USEVIDEONAMESPACE_
};
#endif

#endif // FADER_H_INCLUDED
