/*****************************************************************
Implementazione di un motore grafico 3D con OpenGL per Win32
Code by Leonardo Berti (c) 2007
******************************************************************/

#ifndef CAMERAGLW_H_INCLUDED
#define CAMERAGLW_H_INCLUDED

#include "lwtk/libhead.h"
#include "video/video.h"      //interfaccia video 2D
#include "videoglw/videoglw.h"
#include "nodeglw.h"
#include "math/vectors3.h"    //vettori a 2,3 e 3 dim in coord. omogenee
#include "math/matrix2.h"     //matrici 2x2,3x3 e 3x3 in coord. omogenee
#include "math/quat2.h"       //quaternions
#include "3dengine/node.h"
#include "Logger/Logger.h"
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

class DLL_EXPORT CameraGlWin32:public virtual Camera
{
    friend class L3DEngineGlWin32;

    protected:

        real fovy; //field of view Y (angolo in gradi)
        real aspect_ratio; //rapporto x/y del campo visivo
        real znear,zfar; //near e far clipping plane

        void Init(real fovy_deg,real aspect_ratio,real znear,real zfar);
        void UpdateLocalFrame(const CHMatrix33<real>& m);
        void UpdateCenterPoint();
        void NotifySetupLights(bool update_position);

        real incx,incy,incz;
        CHVector3<real> position; //punto in cui si trova la telecamera
        //versori della terna di assi locali
        CHVector3<real> vers_x; //destra
        CHVector3<real> vers_y; //alto
        CHVector3<real> vers_z; //in avanti
        CHVector3<real> center; //punto in cui guarda (serve per velocizzare il calcolo con gluLookAt)
        CHVector3<real> up; //direzione verticale corrente

        CHMatrix33<real> m; //general
        CHVector3<real> v; //general

        //oggetti che vengono renderizzati prima di eseguire la trasformazione della telecamera
        SceneNodeGlw local_objects;

    public:

        CameraGlWin32();
        virtual ~CameraGlWin32();
        CameraGlWin32(real fovy_deg,real aspect_ratio,real znear,real zfar);

        //direziona la camera in modo da guardare il punto p
        void LookAtPoint(const HPOINT3D& p);
        //sposta la camera nel punto p
        void SetPosition(const HPOINT3D& p);

        /**Restituisce la posizione corrente*/
        void GetPosition(HPOINT3D_PTR pos);

        void Move(const CHVector3<real>& displacement);

        //ruota (rotazioni succesive riferite agli assi locali)
        void Roll(real deg);
        void Yaw(real deg);
        void Pitch(real deg);

        void Transform(const CHMatrix33<real>& tm);

        //incrementa la posizione
        void MoveForward(real inc);
        void MoveBackward(real inc);
        //si sposta di lato (X) (destra e sinistra)
        void MoveLeft(real inc);
        void MoveRight(real inc);
        //si sposta in alto e basso (Y)
        void MoveUp(real inc);
        void MoveDown(real inc);

        void OrbitYaw(real deg,real axis_distance);

         /**esegue una rotazione di rollio intorno ad un asse appartenente al piano ZY e parallelo a Z
        posto a distanza axis_distance dall'asse Z*/
        void OrbitRoll(real deg,real axis_distance);

        /**Esegue una rotazione di beccheggio intorno ad un asse appartenente al piano ZX, parallelo a X
        e posto a distanza axis_distance da X*/
        void OrbitPitch(real deg,real axis_distance);

         /**resetta gli assi locali allineandoli a quelli di riferimento*/
        void ResetAxis(void);

        /**Imposta gli assi (avanti e alto) (riferiti al sistema ssoluto)
        i vettori passati possono anche non essere unitari, ivettori passati
        non devono essere paralleli!
        */
        void setAxisYZ(const CHVector3<real>& versy,const CHVector3<real>& versz);
        void setAxisXY(const CHVector3<real>& versx,const CHVector3<real>& versy);
        void setAxisZX(const CHVector3<real>& versz,const CHVector3<real>& versx);

        /**Acquisisce gli assi locali*/
        void GetLocalAxis(CHVector3<real>* versx,CHVector3<real>* versy,CHVector3<real>* versz);


        //------ membri specifici per questa implementazione ---
        //moltiplica la matrice corrente per la matrice prospettica
        void ApplyPerspective(void);

        //Applica la trasformazione
        void ApplyTransform(void);

        bool render();

        //Aspect ratio (w/h)
        void SetAspectRatio(real aspect_ratio);

        real GetAspectRatio(void);

        //Field of view y in gradi
        void SetFOVY(real fovy_deg);
        real GetFOVY(void);
        //far clipping plane
        void SetFarClipPlane(real zfar);
        real GetFarClipPlane(void);
        //near clipping plane
        void SetNearClipPlane(real znear);
        real GetNearClipPlane(void);

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
}
#endif

#endif // CAMERAGLW_H_INCLUDED
