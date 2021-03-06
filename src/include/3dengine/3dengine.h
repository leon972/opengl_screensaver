/*****************************************************************
Interfaccia per un semplice motore grafico 3D
Code by Leonardo Berti (c) 2007
******************************************************************/

#ifndef L3DENGINE_H_INCLUDED
#define L3DENGINE_H_INCLUDED

#include<list>
#include "lwtk/libhead.h"
#include "video/video.h"      //interfaccia video 2D
#include "camera.h"
#include "math/vectors3.h"    //vettori a 2,3 e 3 dim in coord. omogenee
#include "math/matrix2.h"     //matrici 2x2,3x3 e 3x3 in coord. omogenee
#include "math/quat2.h"       //quaternions

//nota : queste istruzioni del preprocessore servono ad esclude i namespace
//per rendere i file compatibili con alcuni vecchi compilatori
#ifdef _USENAMESPACE_
using namespace mathengine; //namespace usato dai moduli matematici
#endif

#ifdef _USEVIDEONAMESPACE_
namespace video {
    #endif

//rendering flags
    #define RD_WIREFRAME 0x1
    #define RD_FLAT 0x2
    #define RD_GORAUD_SHADING 0x4
    #define RD_PHONG_SHADING 0x8
    #define RD_LIGHTS 0x10
    #define RD_CULL_FACES 0x20

//errori
    #define ERR_INVALID_FOVY 301
    #define ERR_SHADING_MODE_UNSUPPORTED 302
    #define ERR_RENDER_LIST_OVERFLOW 303
    #define ERR_INVALID_3DOBJECT 304

//vertici




    /**-interfaccia modello 3D.contiene la definizione dei vertici, texture ecc... */
class Model3D:public Renderable {
public:

       virtual  ~Model3D() {}

        /**Aggiunge un vertice (usato per formare triangoli o quads)
           restituisce l'indice del vertice*/
        virtual unsigned int AddVertex(real x,real y,real z)=0;
        /**imposta un triangolo del modello vi=indici dei vertici*/
        virtual unsigned int AddTriangle(unsigned int v1,unsigned int v2,unsigned int v3)=0;
        /**aggiunge un triangolo specificando il colore*/
        virtual unsigned int AddTriangle(unsigned int v1,unsigned int v2,unsigned int v3,COLOR color)=0;
        /**aggiunge una linea*/
        virtual unsigned int AddLine(unsigned int v1,unsigned int v2)=0;
        virtual unsigned int AddLine(unsigned int v1,unsigned int v2,COLOR color)=0;
        /**aggiunge un quad*/
        virtual unsigned int AddQuad(unsigned int v1,unsigned int v2,unsigned int v3,unsigned int v4)=0;
        /**aggiunge un quad specificando il colore*/
        virtual unsigned int AddQuad(unsigned int v1,unsigned int v2,unsigned int v3,unsigned int v4,COLOR color)=0;
        /**imposta la normale di un triangolo (da usare per impostare manualmente la normale.Le funzioni Add... calcolano la normale automaticamente)*/
        virtual bool SetTriangleNormal(unsigned int tindex,real nx,real ny,real nz)=0;
        /**imposta la normale di un quad*/
        virtual bool SetQuadNormal(unsigned int qindex,real nx,real ny,real nz)=0;

        virtual unsigned int GetVertexCount()=0;

        virtual unsigned int GetTriangleCount()=0;

        virtual unsigned int GetQuadCount()=0;
    };


    /**Rendering view port*/
    class DLL_EXPORT Viewport {

private:

        real x,y,w,h; //dimensioni e posizione del view port

public:

        Viewport(real xv,real yv,real width,real height);

        Viewport(void);

        /**imposta dimensioni e posizione*/
        void Set(real xv,real yv,real width,real height);

        /**incrementa posizione e dimensioni*/
        void Incr(real incx,real incy,real incw,real inch);
    };


    /**classe astratta Engine 3D*/
class DLL_EXPORT L3DEngine:public virtual Video {
protected:

        Camera* m_pCurCam;
        Viewport* m_pCurVp;
        int m_rendering_flags;
        //alcune primitive utili per i test
public:

        L3DEngine(void);

        virtual ~L3DEngine(void);

        /**aggiunge un oggetto da renderizzare alla scene node radice*/
        virtual void Add(Renderable* r)=0;

        /**rimuove un oggetto renderizzabile dalla scene-node radice*/
        virtual void Remove(Renderable* r)=0;

        /**aggiunde una scene-node alla scene-node radice*/
        virtual void AddChildNode(SceneNode* node)=0;

        /**rimuove una scene-node dalla scene node radice*/
        virtual void RemoveChildNode(SceneNode* node)=0;

        /**Crea un cubo*/
        static void CreateCube(Model3D* cube,real x,real y,real z,real side);

        /**Crea un parallelepipedo*/
        static void CreateCuboid(Model3D* cuboid,real x,real y,real z,real sidex,real sidey,real sidez);

        /**Crea una piramide a base quadrata*/
        static void CreatePyramid(Model3D* pyramid,real x,real y,real z,real side,real height);

        /**Crea una sfera*/
        static void CreateSphere(Model3D* sphere,real x,real y,real z,real radius);

        static void CreateSphere(Model3D* sphere,real x,real y,real z,real radius,COLOR col1,COLOR col2);

        /**aggiunge un pavimento di lato side*/
        static void CreateFloor(Model3D* floor,real side,real yfloor);

        /**imposta i flag correnti per il rendering nel view port di default*/
        virtual void SetRenderingFlags(int flags)=0;

        /**Acquisisce i rendering flags*/
        virtual int GetRenderingFlags(void)=0;

        /**esegue il rendering*/
        virtual void RenderScene(void)=0;

        /**imposta la camera corrente*/
        void SetCurrentCamera(Camera& camera);

        /**imposta il viewport corrente*/
        void SetCurrentViewport(Viewport& vp);

        /**Acquisisce la telecamera corrente*/
        Camera* GetCurrentCamera(void);

        /**Acquisisce il viewport corrente*/
        Viewport* GetCurrentViewport(void);

        /**Inizia il disegno di oggetti bidimensionali*/
        virtual bool Begin2D(void)=0;

        /**Termina il disegno di oggetti bidimensionali*/
        virtual bool End2D(void)=0;

        /**Restituisce true se l'engine � in modalit� 2D*/
        virtual bool is2DMode(void)=0;

    };

    #ifdef _USEVIDEONAMESPACE_
};
#endif

#endif // 3DENGINE_H_INCLUDED
