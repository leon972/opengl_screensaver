/*****************************************************************
Interfaccia per un semplice motore grafico 3D
(implementazione parziale)
Code by Leonardo Berti (c) 2007
******************************************************************/

#ifndef CAMERA_H_INCLUDED
#define CAMERA_H_INCLUDED

#include "math/vectors3.h"    //vettori a 2,3 e 3 dim in coord. omogenee
#include "math/matrix2.h"     //matrici 2x2,3x3 e 3x3 in coord. omogenee
#include "math/quat2.h"       //quaternions
#include "video/video.h"      //interfaccia video 2D
#include "video/renderable.h"
#include "node.h"

//nota : queste istruzioni del preprocessore servono ad esclude i namespace
//per rendere i file compatibili con alcuni vecchi compilatori
#ifdef _USENAMESPACE_
using namespace mathengine; //namespace usato dai moduli matematici
#endif

#ifdef _USEVIDEONAMESPACE_
namespace video
{
#endif


/**
Interfaccia per la telecamera standard
La camera ha un sistema di assi locali definito cosi:
Z=profondità, la camera guarda nel senso delle Z negative
X=orizzontale rivolto a destra
Y=verticale rivolto in alto
*/

typedef CHVector3<real> HPOINT3D;
typedef CHVector3<real>* HPOINT3D_PTR;

/**Telecamera
Gli oggetti renderable che vengono aggiunti alla camera usando l'interfaccia
RenderableContainer vengono renderizzati prima di eseguire la trasformazione della
telecamera (es. oggetti fissi davanti alla telecamera)
*/

class Camera
{

    public:

        virtual ~Camera() {}

        /**Aspect ratio (w/h)*/
        virtual void SetAspectRatio(real aspect_ratio)=0;

        /**Restituise l'aspect ratio corrente*/
        virtual real GetAspectRatio(void)=0;

        /**Field of view y in gradi*/
        virtual void SetFOVY(real fovy_deg)=0;

        /**Restituisce il campo visivo corrente*/
        virtual real GetFOVY(void)=0;

        /**far clipping plane*/
        virtual void SetFarClipPlane(real zfar)=0;
        virtual real GetFarClipPlane(void)=0;

        /**near clipping plane*/
        virtual void SetNearClipPlane(real znear)=0;
        virtual real GetNearClipPlane(void)=0;

        /**applica la matrice di proiezione prospettica in base
        alle impostazioni della camera*/
        virtual void ApplyPerspective(void)=0;

        /**applica la trasformazione*/
        virtual void ApplyTransform(void)=0;

        /**esegue il rendering degli oggetti nel sistema di riferimento della telecamera*/
        virtual bool render()=0;

        /**direziona la camera in modo da guardare il punto p*/
        virtual void LookAtPoint(const HPOINT3D& p)=0;

        /**sposta la camera nel punto p (coordinate assolute)*/
        virtual void SetPosition(const HPOINT3D& p)=0;

        /**Si sposta secondo il vettore displacement espresso in coordinate relative agli
        assi fissi (sistema di riferimento assoluto)*/
        virtual void Move(const CHVector3<real>& displacement)=0;

        /**Restituisce la posizione corrente*/
        virtual void GetPosition(HPOINT3D_PTR pos)=0;

        //(rotazioni succesive riferite agli assi locali)
        /**rotazione intorno all'asse verticale (Y)*/
        virtual void Yaw(real deg)=0;

        /**rotazione intorno all'asse Z locale*/
        virtual void Roll(real deg)=0;

        /**rotazione intorno all'asse X locale*/
        virtual void Pitch(real deg)=0;

        /**Applica direttamente la matrice di trasformazione agli assi locali della camera*/
        virtual void Transform(const CHMatrix33<real>& tm)=0;

        /**rotazione intorno ad un asse parallelo all'asse verticale posto
        a distanza axis_distance e appartenente al piano YZ*/
        virtual void OrbitYaw(real deg,real axis_distance)=0;

        /**esegue una rotazione di rollio intorno ad un asse appartenente al piano ZY e parallelo a Z
        posto a distanza axis_distance dall'asse Z*/
        virtual void OrbitRoll(real deg,real axis_distance)=0;

        /**Esegue una rotazione di beccheggio intorno ad un asse appartenente al piano ZX, parallelo a X
        e posto a distanza axis_distance da X*/
        virtual void OrbitPitch(real deg,real axis_distance)=0;

        /**si sposta in avanti lungo l'asse Z locale*/
        virtual void MoveForward(real inc)=0;

        /**si sposta indietro*/
        virtual void MoveBackward(real inc)=0;

        /**si sposta di lato (X) (destra e sinistra)*/
        virtual void MoveLeft(real inc)=0;

        /**si sposta verso destra*/
        virtual void MoveRight(real inc)=0;

        /**si sposta in alto e basso (Y)*/
        virtual void MoveUp(real inc)=0;

        /**si sposta verso il basso*/
        virtual void MoveDown(real inc)=0;

        /**resetta gli assi locali allineandoli a quelli di riferimento*/
        virtual void ResetAxis(void)=0;
        /**Imposta gli assi locali della telecamera (riferiti al sistema fisso)*/
        virtual void setAxisYZ(const CHVector3<real>& versy,const CHVector3<real>& versz)=0;

        virtual void setAxisXY(const CHVector3<real>& versx,const CHVector3<real>& versy)=0;

        virtual void setAxisZX(const CHVector3<real>& versz,const CHVector3<real>& versx)=0;

        /**Acquisisce gli assi locali*/
        virtual void GetLocalAxis(CHVector3<real>* versx,CHVector3<real>* versy,CHVector3<real>* versz)=0;

        //gestione oggetti renderizzati nel sistema di riferimento della telecamera
         /**aggiunge un oggetto da renderizzare alla scene node radice
         (oggetto da renderizzare nel sistema di assi locali della camera)
         */
        virtual void Add(Renderable* r)=0;

        /**rimuove un oggetto renderizzabile dalla scene-node radice*/
        virtual void Remove(Renderable* r)=0;

        /**aggiunde una scene-node alla scene-node radice
        (oggetto da renderizzare nel sistema di assi locali della camera)
        */
        virtual void AddChildNode(SceneNode* node)=0;

        /**rimuove una scene-node dalla scene node radice
        (oggetto da renderizzare nel sistema di assi locali della camera)
        */
        virtual void RemoveChildNode(SceneNode* node)=0;



};

#ifdef _USEVIDEONAMESPACE_
}
#endif

#endif // CAMERA_H_INCLUDED
