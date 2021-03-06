/*****************************************************************
video.h
Interfaccia che gestisce l'input dell'utente e il ciclo grafico di disegno
per le animazioni di un'area rettangolare del video
Code by Leonardo Berti 2008
******************************************************************/

#ifndef CANVAS_H_INCLUDED
#define CANVAS_H_INCLUDED

#include "videodef.h"
#include "lwtk/mouse.h"
#include "lwtk/keys.h"
#include "lwtk/widget.h"
#include "lwtk/paintevt.h"

using namespace lwtk;

#ifdef _USEVIDEONAMESPACE_
namespace video
{
#endif

class AnimationEvent
{
    public:
    /**Viene invocato ad ogni ciclo di animazione*/
    virtual bool Animate()=0;
};

class Canvas
{
    public:

    virtual ~Canvas() {}

    /**Abilita/disabilita il tracing di debug su file*/
    virtual void TraceMode(bool enable)=0;
    /**Rende true se il tracing � abilitato*/
    virtual bool isTraceEnabled()=0;

    /**Restituisce la larghezza in pixel dell'area di disegno*/
    virtual int GetWidth()=0;
    /**Restituisce l'altezza in pixel dell'area di disegno*/
    virtual int GetHeight()=0;
    /**Restituisce la posizione x del vertice in alto a sinistra*/
    virtual int GetLeft()=0;
    /**Restituisce la posizione y del vertice in alto a sinistra*/
    virtual int GetTop()=0;

    //invia un messaggio sull'output di debug se TraceMode � on
    virtual void OutputDebugMsg(const char* msg)=0;

    /**Eventi ridisegno (vengono invocati quanto l'area viene ridisegnata*/
    virtual PaintEvent* AddPaintEvent(PaintEvent* evt)=0;
    virtual bool RemovePaintEvent(PaintEvent* evt)=0;

    /**Eventi tastiera*/
    virtual KeyEvents* AddKeyEvents(KeyEvents* e)=0;
    virtual bool RemoveKeyEvents(KeyEvents* e)=0;
    /**Eventi mouse*/
    virtual MouseEvents* AddMouseEvents(MouseEvents* e)=0;
    virtual bool RemoveMouseEvents(MouseEvents* e)=0;
    /**Eventi movimento del mouse*/
    virtual MouseMoveEvents* AddMouseMoveEvents(MouseMoveEvents* e)=0;
    virtual bool RemoveMouseMoveEvents(MouseMoveEvents* e)=0;
    /**Eventi focus*/
    FocusEvents* AddFocusEvents(FocusEvents* evt);
    bool RemoveFocusEvents(FocusEvents* evt);
    /**Eventi di animazione*/
    virtual AnimationEvent* AddAnimationEvent(AnimationEvent* evt)=0;
    virtual bool RemoveAnimationEvent(AnimationEvent* evt)=0;
    /**Avvia il loop di animazione*/
    virtual void StartAnimation()=0;
    /**Interrompe il loop di aggiornamento grafico*/
    virtual void StopAnimation()=0;
    /**Avvia il loop di animazione specificando i tasti di uscita e toggle full screen*/
    virtual void StartAnimation(int exit_key,int toggle_fullscreen_key)=0;


};

#ifdef _USEVIDEONAMESPACE_
};
#endif

#endif // CANVAS_H_INCLUDED
