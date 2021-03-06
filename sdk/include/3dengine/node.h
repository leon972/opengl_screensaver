#ifndef NODE_H_INCLUDED
#define NODE_H_INCLUDED

#include<list>
#include "video/video.h"      //interfaccia video 2D
#include "math/vectors3.h"    //vettori a 2,3 e 3 dim in coord. omogenee
#include "math/matrix2.h"     //matrici 2x2,3x3 e 3x3 in coord. omogenee
#include "math/quat2.h"       //quaternions
#include "video/renderable.h"

//nota : queste istruzioni del preprocessore servono ad esclude i namespace
//per rendere i file compatibili con alcuni vecchi compilatori
#ifdef _USENAMESPACE_
using namespace mathengine; //namespace usato dai moduli matematici
#endif

#ifdef _USEVIDEONAMESPACE_
namespace video {
    #endif

    typedef CHVector3<real> HPOINT3D;
    typedef CHVector3<real>* HPOINT3D_PTR;

    typedef HPOINT3D VERTEX;
    typedef HPOINT3D_PTR VERTEX_PTR;



    /** Interfaccia Node , contiene la trasformazione geometrica da fare
        prima del rendering e la lista di tutti gli oggetti da renderizzare
        A sua volta lo scene node puo' contenere altri nodi in quanto un nodo
        implementa l'interfaccia Renderable
        */

    class SceneNode {

        //friend class RenderList;
        //friend class L3DEngineGlWin32;
       
public:       
        virtual ~SceneNode()
        {
        }

        virtual void Add(Renderable* r)=0;
        virtual void Remove(Renderable* r)=0;
        virtual void RemoveAllRenderables()=0;
        virtual const std::list<Renderable*>* GetRenderableObjects() const=0;

        virtual void AddChildNode(SceneNode* node)=0;
        virtual void RemoveChildNode(SceneNode* node)=0;
        virtual void RemoveAllChildrenNodes()=0;
        virtual SceneNode* GetParentNode() const=0;
        virtual const std::list<SceneNode*>* GetChildrenNodes() const=0;

        /**imposta la posizione dell'oggetto*/
        virtual void SetPosition(real x,real y,real z)=0;
        /**Imposta direttamente la matrice di trasformazione*/
        virtual void SetTransformMatrix(const CHMatrix33<real>& mat)=0;
        /**Restituisce la matrice di trasformazione corrente*/
        virtual CHMatrix33<real> GetTransformMatrix() const=0;
        /**incrementa la posizione rispetto agli fissi*/
        virtual void IncrPosition(real dx,real dy,real dz)=0;
        /**traslazione rispetto agli assi locali*/
        virtual void Translate(real dx,real dy,real dz)=0;
        /**Imposta il nuovo sistema di riferimento per l'oggetto (assi corpo) tramite gli angoli di Eulero
           le rotazioni successive avvengono nella sequenza psi,theta,phi
           psi=rotazione intorno a Z,rot. theta intorno alla linea dei nodi e phi intorno al nuovo asse Z (Z')
           angoli espressi in radianti*/
        virtual void SetEulerAngles(real psi_rad,real theta_rad,real phi_rad)=0;
        /**Esegue una rotazione tramite gli angoli di eulero a partire dalla posizione corrente*/
        virtual void RotateEulerAngles(real psi_rad,real theta_rad,real phi_rad)=0;
        /**esegue una rotazione relativa al versore vers_axis riferito agli assi corpo*/
        virtual void Rotate(real theta_rad,const CHVector3<real>& vers_axis)=0;
        /**rotazione intorno agli assi locali*/
        virtual void RotateX(real theta_rad)=0;
        virtual void RotateY(real theta_rad)=0;
        virtual void RotateZ(real theta_rad)=0;
        //rotazione intorno
        /**acquisisce la posizione*/
        virtual void GetPosition(CHVector3<real>* pos) const=0;
        /**scala l'oggetto*/
        virtual void Scale(real fx,real fy,real fz)=0;
        /**resetta la matrice corrente*/
        virtual void SetIdentityMatrix(void)=0;
        /**Imposta la visibilit�*/
        virtual void SetVisible(bool visible)=0;

        virtual bool render()=0;
        virtual bool IsVisible() const=0;
       
        virtual int last_error()=0;

    };

    #ifdef _USEVIDEONAMESPACE_
};
#endif


#endif // RENDERABLE_H_INCLUDED
