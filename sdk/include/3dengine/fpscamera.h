/*****************************************************************
Interfaccia per un semplice motore grafico 3D
(implementazione parziale)
Code by Leonardo Berti (c) 2007
******************************************************************/

#ifndef FPSCAMERA_H_INCLUDED
#define FPSCAMERA_H_INCLUDED

#include "video/video.h"      //interfaccia video 2D
#include "camera.h"           //telecamera base
#include "math/vectors3.h"    //vettori a 2,3 e 3 dim in coord. omogenee
#include "math/matrix2.h"     //matrici 2x2,3x3 e 3x3 in coord. omogenee
#include "math/quat2.h"       //quaternions
#
//nota : queste istruzioni del preprocessore servono ad esclude i namespace
//per rendere i file compatibili con alcuni vecchi compilatori
#ifdef _USENAMESPACE_
using namespace mathengine; //namespace usato dai moduli matematici
#endif

#ifdef _USEVIDEONAMESPACE_
namespace video {
    #endif

    /**
    Interfaccia per la telecamera tipo FPS (first person shooter)
    La camera ha un sistema di assi locali definito cosi:
    Z=profondità, la camera guarda nel senso delle Z negative
    X=orizzontale rivolto a destra
    Y=verticale rivolto in alto
    */

class FPSCamera:public virtual Camera {
public:

        virtual ~FPSCamera() {}
        virtual void YawLeft()=0;
        virtual void YawRight()=0;
        virtual void PitchUp()=0;
        virtual void PitchDown()=0;
        virtual void MoveForward()=0;
        virtual void MoveBackward()=0;
        virtual void UpdateCamByMouse(int cx,int cy,int x,int y)=0;
        virtual void SetYawDeltaAngle(real deg)=0;
        virtual void SetPitchDeltaAngle(real deg)=0;
        virtual void SetSpeed(real speed)=0;
        virtual void SetForward(const CHVector3<real>& vers_dir)=0;
    };

    #ifdef _USEVIDEONAMESPACE_
}
#endif

#endif // FPSCAMERA_H_INCLUDED
