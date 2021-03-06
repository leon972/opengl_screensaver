/**********************************************
Catena cinematica di sprite
implementazione OpenGL
Code by L.Berti (c) 2008
***********************************************/

#ifndef TSPRITEGL_H_INCLUDED
#define TSPRITEGL_H_INCLUDED

#include "lwtk/libhead.h"
#include "2dengine/tsprite.h"
#include "spriteglw.h"

#include <vector>

using namespace std;

#ifdef _USEVIDEONAMESPACE_
namespace video {
    #endif

    class SpriteTreeGL;

    typedef enum BLIT_MODE_ENUM
    {
        BLT_DRAW=1, //disegna gli sprite
        BLT_UPDATE_L_TO_W=2, //aggiorna la matrice loc to world

    } BLIT_MODE;

    /**
    Sprite collegato allo sprite tree
    */

    typedef struct LINKED_SPRITE_TYP {
        SpriteTreeGL* child_sprite;
        //il link con indice src_hot_spot
        //viene collegato al link della base con indice dest_hot_spot
        int src_hot_spot; //indice link del sorgente (child_sprite)
        int dest_hot_spot; //indice link dello spritre tree base

        bool operator == (const LINKED_SPRITE_TYP& lk) {
            return (lk.child_sprite==child_sprite);
        }

    } LINKED_SPRITE,*LINKED_SPRITE_PTR;

/**
Sprite linkabile ad altri sprite in modo da costruire una catena (o albero) cinematico
*/
class DLL_EXPORT SpriteTreeGL:public virtual SpriteTree,protected SpriteGL {
private:

        SpriteTreeGL* parent; //sprite genitore
        SpriteTreeGL* ancestor; //radice dell'albero
        int linked_hot_spot; //hot spot usato per collegare questo prite al parent

protected:

        list<LINKED_SPRITE> children;
        //matrice di trasformazione dal sistema di riferimento locale in quello assoluto (screen)
        //viene aggiornata dal metodo Blit
        mutable CHMatrix33<float> loc_to_world;
        void InitSprTree();
        void UpdateLocToWorld() const;
        void BlitEx(BLIT_MODE mode) const;

public:

        SpriteTreeGL(Image* image);
        SpriteTreeGL();
        virtual ~SpriteTreeGL();

        //int. SpriteTree
        virtual void Add(SpriteTree* st,int dest_hot_spot,int src_hot_spot);
        virtual void Remove(SpriteTree* st);
        virtual int ItemsCount() const;
        /**Trasforma da coordinate relative ad assolute*/
        virtual void LocalToWorld(CVector2<float>* world,const CVector2<float>& local,bool is_dirty) const;
        virtual void LocalToWorld(CVector2<float>* world,const CVector2<float>& local) const;
         /**Restituisce la rotazione assoluta (riferita al sistema fisso)*/
        virtual float GetAbsRotation() const;
        /**Restituisce la rotazione assoluta aggiornando la matrice di trasformazione*/
        virtual float GetAbsRotation(bool is_dirty) const;


        /**Restituisce lo sprite genitore*/
        virtual SpriteTree* GetParent() const;
        /**Restituisce lo sprite radice della catena cinematica*/
        virtual SpriteTree* GetAncestor() const;

        //int. sprite
        //Interfaccia Sprite
        /**Imposta la frame corrente*/
        virtual bool SetCurFrame(int frame);
        /**Incrementa la frame corrente*/
        virtual int IncFrame();
        /**decrementa la frame corrente*/
        virtual int DecFrame();
        /**acquisisce il numero di frame corrente */
        virtual int GetCurFrame() const ;
        virtual const Image* GetCurFramePtr() const ;
        virtual const Image* GetFramePtr(int frame) const;
        /**restituisce il massimo indice delle frames*/
        virtual int GetMaxFramesIndex() const;
        /**Imposta la frame con indice idx_frame*/
        virtual bool SetFrame(int idx_frame,const Image& img);
        virtual bool SetFrame(int idx_frame,const Image& img,const SEL_RECT& src_grab_rect);

        virtual int AddFrame(const Image& img);
        virtual int AddFrame(const Image& img,const SEL_RECT& src_grab_rect);

        /**Aggiunge un hot spot alla frame*/
        virtual int AddFrameHotSpot(int frame,int lDeltax,int lDeltay);
        /**Imposta un hot spot esistente*/
        virtual bool SetFrameHotSpot(int frame,int iHotSpot,int lDeltax,int lDeltay);
        /**rimuove un hot spot per la frame*/
        virtual bool RemoveFrameHotSpot(int frame,int iHotSpot);
        /**Restituisce il numero di hot spot per la frame*/
        virtual int GetFrameHotSpotCount(int frame) const;
        /**Imposta l'hot spot per framer corrente.Le operazioni di blitting verranno
        effettuate usando questo hot spot come origine*/
        virtual bool SetCurHotSpot(int iHotSpot);
        virtual int GetCurHotSpot() const;


        virtual bool SetBoundPoly(int frame_index,const BOUND_POLY* ppoly); //imposta il bounding polygon della frame
        virtual const BOUND_POLY* GetBoundPoly(void) const; //rende il poligono di contenimento corrente
        virtual void GetFrameHotSpot(int frame,int iHotSpot,int *plx,int *ply) const;


        //virtual void GetJointPosition(int *xj,int *yj,int iHotSpot) const;

        /**Trasforma da coordinate locali nel sistema di rif. dello sprite, in coordinate del sistema fisso*/
        //virtual void LocalToWorld(CVector2<float>* world,const CVector2<float>& local) const;

        virtual void SetPosition(float x,float  y);
        virtual void SetPosition(const CVector2<float>& pos);
        virtual void GetPosition(float *x,float *y) const;

        virtual void SetVelocity(float deg_angle,float speed);      //imposta il vettore velocit� (angolo e modulo)
        virtual void SetVelocity(const CVector2<float>& vel);

        virtual void SetVelocityAngle(float deg_angle);
        virtual float GetVelocityAngle();  //acquisisce l'angolo di direzione
        virtual float GetSpeed(void) const;  //acquisisce il modulo della velocit�
        virtual CVector2<float> GetVelocity() const;
        virtual void GetVelocity(CVector2<float>* vel) const ;
        virtual void SetImageRotation(float deg_angle);
        virtual float GetImageRotation();
        virtual void SetAnimSpeed(const float speed);
        virtual float GetAnimSpeed(void) const ;
        virtual bool SetAnimRange(int iframe_start,int iframe_end);
        virtual void GetAnimRange(int *iframe_start,int *iframe_end) const;
        virtual void ResetAnimRange();
        virtual void SetAnimLoopType(ANIM_LOOP_TYPE type);
        virtual ANIM_LOOP_TYPE GetAnimLoopType() const;
        virtual void UpdatePosition();                                      //aggiorna la posizione e la frame dello sprite
        virtual CVector2<float> GetPosition() const;
        virtual void ClearFrames();
        virtual void Animate(void);
        virtual void Blit() const;
        virtual void Blit(int x,int y) const;
        //int. Renderable
        virtual bool render();
        virtual int last_error();
        virtual bool is_visible();
        virtual void set_visible(bool visible);
        virtual bool operator== (const Renderable& val);

    };

    #ifdef _USEVIDEONAMESPACE_
};
#endif

#endif // TSPRITEGL_H_INCLUDED
