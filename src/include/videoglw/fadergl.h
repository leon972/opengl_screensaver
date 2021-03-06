/**************************************************
Fader.
Usato per creare effetti fade to black fade to color ecc...
****************************************************/

#ifndef FADERGL_H_INCLUDED
#define FADERGL_H_INCLUDED

#include "lwtk/libhead.h"
#include "video/fader.h"

#ifdef _USEVIDEONAMESPACE_
namespace video
{
#endif

typedef enum FADE_MODE_ENUM
{
    FADE_OUT=0,
    FADE_IN=1

} FADE_MODE;

class DLL_EXPORT FaderGL:public Fader
{
    private:

    int cur_step;
    int tot_steps;
    int scr_width,scr_height;
    float cur_alpha;
    float init_alpha;
    float dest_alpha;
    float step_alpha;
    float r,g,b;
    Video* pscreen;

    FADE_MODE fade_mode;

    void InitFade(COLOR dest_color,int steps,FADE_MODE mode,Video* screen);

    public:

    FaderGL();

    /**Inizializza il fader specificando il colore finale*/
    virtual void FadeToColor(COLOR dest_color,int steps,Video* screen);
    /**Inizializza il fader specificando il colore iniziale*/
    virtual void FadeFromColor(COLOR src_color,int steps,Video* screen);
    /**Esegue un passo,quando ha raggiunto il colore finale rende false,altrimenti rende true*/
    virtual bool Fade();
    /**Restituisce il passo corrente [1..steps]*/
    virtual int GetCurrentStep();
    /**Resetta*/
    virtual void Reset();
    /**Restituisce true se il fading non è completo*/
    virtual bool IsFading();
    /**Inverte la direzione del fading*/
    virtual void Invert();

};

#ifdef _USEVIDEONAMESPACE_
};
#endif

#endif // FADERGL_H_INCLUDED
