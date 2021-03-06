/*****************************************************************
Implementazione di un motore grafico 3D con OpenGL per Win32
Code by Leonardo Berti (c) 2007
******************************************************************/

#ifndef FPSCAMGLW_H_INCLUDED
#define FPSCAMGLW_H_INCLUDED

#include "lwtk/libhead.h"
#include "video/video.h"      //interfaccia video 2D
#include "videoglw/videoglw.h"
#include "3dengine/fpscamera.h"
#include "math/vectors3.h"    //vettori a 2,3 e 3 dim in coord. omogenee
#include "math/matrix2.h"     //matrici 2x2,3x3 e 3x3 in coord. omogenee
#include "math/quat2.h"       //quaternions
#include "3dengine/3dengine.h"
#include "filelogger/filelogger.h"
#include <list>           //std list

//nota : queste istruzioni del preprocessore servono ad esclude i namespace
//per rendere i file compatibili con alcuni vecchi compilatori
#ifdef _USENAMESPACE_
using namespace mathengine; //namespace usato dai moduli matematici
#endif

#ifdef _USEVIDEONAMESPACE_
namespace video
{
#endif

class DLL_EXPORT FPSCameraGlWin32:public CameraGlWin32,public FPSCamera
{
    protected:

    CHVector3<real> forward;
    CHVector3<real> backward;
    CHVector3<real> temp;
    CHMatrix33<real> my;
    CHMatrix33<real> my1;
    real speed;
    real yaw_angle; //rad
    real pitch_angle; //rad

    /**Inizializza le variabili membro*/
    void ResetDefParams();

    public:

    FPSCameraGlWin32();
    FPSCameraGlWin32(real fovy_deg,real aspect_ratio,real znear,real zfar);
    virtual ~FPSCameraGlWin32();

    void MoveForward();
    void MoveBackward();
    void YawLeft();
    void YawRight();
    void PitchUp();
    void PitchDown();
    /**Aggiorna la posizione in base alla posizione corrente del mouse
    cx,cy=centro schermo oppure ultima pos. mouse,x,y,=posizione attuale*/
    void UpdateCamByMouse(int cx,int cy,int x,int y);
    void SetYawDeltaAngle(real deg);
    void SetPitchDeltaAngle(real deg);
    void SetSpeed(real speed);
    /**Imposta il versore della direzione in avanti*/
    void SetForward(const CHVector3<real>& vers_dir);

    /**aggiunge un oggetto da renderizzare alla scene node radice*/
    void Add(Renderable* r);

    /**rimuove un oggetto renderizzabile dalla scene-node radice*/
    void Remove(Renderable* r);

    /**aggiunde una scene-node alla scene-node radice*/
    void AddChildNode(SceneNode* node);

    /**rimuove una scene-node dalla scene node radice*/
    void RemoveChildNode(SceneNode* node);



};

#ifdef _USEVIDEONAMESPACE_
};
#endif

#endif // FPSCAMGLW_H_INCLUDED
