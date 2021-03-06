#ifndef LIGHT_H_INCLUDED
#define LIGHT_H_INCLUDED

#include "math/vectors3.h"    //vettori a 2,3 e 3 dim in coord. omogenee
#include "math/matrix2.h"     //matrici 2x2,3x3 e 3x3 in coord. omogenee
#include "math/quat2.h"       //quaternions
#include "video/video.h"      //interfaccia video 2D
#include "3dengine.h"

//nota : queste istruzioni del preprocessore servono ad esclude i namespace
//per rendere i file compatibili con alcuni vecchi compilatori
#ifdef _USENAMESPACE_
using namespace mathengine; //namespace usato dai moduli matematici
#endif

#ifdef _USEVIDEONAMESPACE_
namespace video
{
#endif

/**luce posizionale*/
class Light:public Renderable
{
    public:

    virtual ~Light() {}
    /**imposta tutti i colori per la luce (ambient,diffuse,specular)*/
    virtual void SetColor(COLOR c)=0;
    virtual COLOR GetColor()=0;
    virtual void SetAmbientColor(COLOR c)=0;
    virtual COLOR GetAmbientColor()=0;
    virtual void SetDiffuseColor(COLOR c)=0;
    virtual COLOR GetDiffuseColor()=0;
    virtual void SetSpecularColor(COLOR c)=0;
    virtual COLOR GetSpecularColor()=0;
    virtual void SetPosition(const CHVector3<real>& pos)=0;
    virtual CHVector3<real> GetPosition()=0;
    /**imposta l'attenuazione della luce secondo la formula 1/(Kc+Kl*d+Kq*d*d)
    dove Kc è il termine costante, Kl è il termine lineare e Kq il quadratico
    impostando Kc=1 e Kl=Kq=0 la luce non viene attenuata in base alla distanza d*/
    virtual void SetAttenuation(float Kc,float Kl,float Kq)=0;
    virtual void GetAttenuation(float* Kc,float* Kl,float* Kq)=0;
    /**abilita/disabilita la luce*/
    virtual void SetEnabled(bool enabled)=0;
    /**restituisce true se la luce è abilitata*/
    virtual bool IsEnabled()=0;
    /**attiva/disattiva il disegno del simbolo della luce (per scopo di debug)*/
    virtual void SetLightSymbolEnabled(bool enabled)=0;
    /**restituisce true se il disegno del simbolo della luce è abilitato*/
    virtual bool IsLightSymbolEnabled()=0;

};

/**luce direzionale*/
class DirectionalLight:public Light
{
    public:

    virtual ~DirectionalLight() {}
    virtual void SetDirection(const CHVector3<real>& direction)=0;
    virtual CHVector3<real> GetDirection()=0;

};

/**luce tipo spot*/
class SpotLight:public DirectionalLight
{
    public:

    virtual ~SpotLight() {}
    /**angolo del cono di luce*/
    virtual void SetSpotAngle(float deg)=0;
    /**concentrazione della luce verso il centro del cono:è un valore compreso fra 0 e 1
    0 significa che non c'è attenuazione verso il bordo, 1 signific che la lkuce è concentrata tutta verso il centro del cono*/
    virtual void SetSpotExponent(float v)=0;

};

#ifdef _USEVIDEONAMESPACE_
};
#endif

#endif // LIGHT_H_INCLUDED
