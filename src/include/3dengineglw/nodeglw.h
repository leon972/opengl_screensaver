#ifndef NODEGLW_H_INCLUDED
#define NODEGLW_H_INCLUDED

using namespace std;

#include "lwtk/libhead.h"
#include "3dengine/3dengine.h"
#include "3dengine/node.h"

#ifdef _USEVIDEONAMESPACE_
namespace video {
#endif

class DLL_EXPORT SceneNodeGlw:public SceneNode {

friend class L3DEngineGlWin32;

private:

        CHMatrix33<real> tmatrix; //matrice di trasformazione object to world
        CHMatrix33<real> temp,temp1; //usate internamente
        CHVector3<real> u,v,n; //terna vettori di riferimento nelle coordinate world
        //Model3D* pmodel; //modello a cui si riferisce l'oggetto3D
        unsigned int idx_renderlist; //indice elemento iniziale della render list
        bool visible; //flag che indica se l'oggetto � visibile

        GLfloat model_to_world[16]; //matrice fissa di trasformazione model to world

        //funzioni usate internamente dall'engine per propagare notifiche
        void NotifyAddedToRenderer();
        void NotifyRemovedFromRenderer();
        SceneNodeGlw* parent_node;

        std::list<Renderable*> renderable_objects; //lista degli oggetti renderizzabili contenuti nel nodo
        std::list<SceneNode*> children_nodes;


public:

        SceneNodeGlw();
        virtual  ~SceneNodeGlw();

        /*Interfaccia SceneNode*/
        void SetPosition(real x,real y,real z);
        /**acquisisce la posizione*/
        void GetPosition(CHVector3<real>* pos) const;
        /**Imposta la matrice di trasformazione iniziale (per default � la matrice identica*/
        void SetTransformMatrix(const CHMatrix33<real>& mat);
        /**Restituisce la matrice di trasformazione corrente*/
        CHMatrix33<real> GetTransformMatrix() const;
        void IncrPosition(real dx,real dy,real dz);
        /**traslazione rispetto agli assi locali*/
        void Translate(real dx,real dy,real dz);
        /**Imposta il nuovo sistema di riferimento per l'oggetto (assi corpo) tramite gli angoli di Eulero
           le rotazioni successive avvengono nella sequenza psi,theta,phi
           psi=rotazione intorno a Z,rot. theta intorno alla linea dei nodi e phi intorno al nuovo asse Z (Z')
           angoli espressi in radianti*/
        void SetEulerAngles(real psi_rad,real theta_rad,real phi_rad);
        /**Esegue una rotazione tramite gli angoli di eulero a partire dalla posizione corrente*/
        void RotateEulerAngles(real psi_rad,real theta_rad,real phi_rad);
        /**esegue una rotazione relativa al versore vers_axis riferito agli assi corpo*/
        void Rotate(real theta_rad,const CHVector3<real>& vers_axis);
        /**rotazione intorno agli assi locali*/
        void RotateX(real theta_rad);
        void RotateY(real theta_rad);
        void RotateZ(real theta_rad);
        /**Scala*/
        void Scale(real fx,real fy,real fz);
        /**Imposta la matrice identit� per questo nodo*/
        void SetIdentityMatrix(void);

        void Add(Renderable* r);
        void Remove(Renderable* r);
        void RemoveAllRenderables();
        const std::list<Renderable*>* GetRenderableObjects() const;

        void AddChildNode(SceneNode* node);
        void RemoveChildNode(SceneNode* node);
        void RemoveAllChildrenNodes();
        SceneNode* GetParentNode() const;
        const std::list<SceneNode*>* GetChildrenNodes() const;
        /**Imposta la visibilit�*/
        void SetVisible(bool visible);
        bool IsVisible() const;

        bool render();       
      
        int last_error();

        //notifica il cambiamento modalit� (con conseguente distruzione e creazione nuovo rendering context)
        void NotifySetupLights(bool update_position);

    };

    #ifdef _USEVIDEONAMESPACE_
};
#endif


#endif // NODEGLW_H_INCLUDED
