/**********************************************
2D Sprite
Code by L.Berti (c) 2008
***********************************************/

#ifndef SPRITE_H_INCLUDED
#define SPRITE_H_INCLUDED

#include "video/videodef.h"
#include "image/image.h"
#include "math/vectors2.h"
#include "video/renderable.h"
#include "geom/geomdefs.h"
#include <vector>

using namespace mathengine; //namespace usato dai moduli matematici

#ifdef _USEVIDEONAMESPACE_
namespace video
{
#endif

using namespace std;

typedef geom::POLYGON<float> BOUND_POLY;

/*typedef struct BOUND_POLY
{
	CVector2<float>* vertices;
	int nvertices;
};*/

enum ANIM_LOOP_TYPE
{
    ANIM_LOOP=0,
    ANIM_TO_AND_FRO=1
};

/**Sprite interface*/
class Sprite: public virtual Renderable
{
    public:

    virtual ~Sprite() {}
    //Interfaccia Sprite
    /**Imposta la frame corrente*/
    virtual bool SetCurFrame(int frame)=0;
    /**Incrementa la frame corrente*/
    virtual int IncFrame()=0;
    /**decrementa la frame corrente*/
	virtual int DecFrame()=0;
	/**acquisisce il numero di frame corrente */
	virtual int GetCurFrame() const =0;
	virtual const Image* GetCurFramePtr() const =0;
	virtual const Image* GetFramePtr(int frame) const=0;
	/**restituisce il massimo indice delle frames*/
	virtual int GetMaxFramesIndex() const = 0;
	/**Imposta la frame con indice idx_frame*/
	virtual bool SetFrame(int idx_frame,const Image& img)=0;
    virtual bool SetFrame(int idx_frame,const Image& img,const SEL_RECT& src_grab_rect)=0;

    virtual int AddFrame(const Image& img)=0;
    virtual int AddFrame(const Image& img,const SEL_RECT& src_grab_rect)=0;
    virtual int AddFrame(const IMAGE_RECT& img_rect)=0;

    /**Aggiunge un hot spot alla frame*/
    virtual int AddFrameHotSpot(int frame,int lDeltax,int lDeltay)=0;
	/**Imposta un hot spot esistente*/
	virtual bool SetFrameHotSpot(int frame,int iHotSpot,int lDeltax,int lDeltay)=0;
	/**rimuove un hot spot per la frame*/
	virtual bool RemoveFrameHotSpot(int frame,int iHotSpot)=0;
	/**Restituisce il numero di hot spot per la frame*/
	virtual int GetFrameHotSpotCount(int frame) const=0;
	/**Imposta l'hot spot per framer corrente.Le operazioni di blitting verranno
	effettuate usando questo hot spot come origine*/
	virtual bool SetCurHotSpot(int iHotSpot)=0;
	virtual int GetCurHotSpot() const=0;


	virtual bool SetBoundPoly(int frame_index,const BOUND_POLY* ppoly)=0; //imposta il bounding polygon della frame
	virtual const BOUND_POLY* GetBoundPoly(void) const=0; //rende il poligono di contenimento corrente
	virtual void GetFrameHotSpot(int frame,int iHotSpot,int *plx,int *ply) const=0;


    /**Imposta la posizione relativa di questo sprite*/
	virtual void SetPosition(float x,float  y)=0;
	virtual void SetPosition(const CVector2<float>& pos)=0;
	virtual void GetPosition(float *x,float *y) const=0;

	virtual void SetVelocity(float deg_angle,float speed)=0;      //imposta il vettore velocit� (angolo e modulo)
	virtual void SetVelocity(const CVector2<float>& vel)=0;

	virtual void SetVelocityAngle(float deg_angle)=0;
	virtual float GetVelocityAngle()=0;  //acquisisce l'angolo di direzione
	virtual float GetSpeed(void) const=0;  //acquisisce il modulo della velocit�
	virtual CVector2<float> GetVelocity() const=0;
	virtual void GetVelocity(CVector2<float>* vel) const =0;

	virtual void SetImageRotation(float deg_angle)=0;
	virtual float GetImageRotation()=0;

	virtual void LocalToWorld(CVector2<float>* world,const CVector2<float>& local) const=0;


	virtual void SetAnimSpeed(const float speed)=0;
	virtual float GetAnimSpeed(void) const =0;
	virtual bool SetAnimRange(int iframe_start,int iframe_end)=0;
	virtual void GetAnimRange(int *iframe_start,int *iframe_end) const=0;
	virtual void ResetAnimRange()=0;
	virtual void SetAnimLoopType(ANIM_LOOP_TYPE type)=0;
	virtual ANIM_LOOP_TYPE GetAnimLoopType() const=0;
	virtual void UpdatePosition()=0;                                      //aggiorna la posizione e la frame dello sprite
	virtual CVector2<float> GetPosition() const=0;
	virtual void ClearFrames()=0;
    virtual void Animate(void)=0;
    virtual void Blit() const=0;
    virtual void Blit(int x,int y) const=0;

  /*  virtual void AddChild(Sprite* child)=0;
    virtual bool RemoveChild(Sprite* child)=0;
    virtual Sprite* GetParent() const =0;
    virtual Sprite* GetRoot() const=0;
    virtual bool IsAncestor(const Sprite* spr) const=0;*/

};

#ifdef _USEVIDEONAMESPACE_
};
#endif


#endif // SPRITE_H_INCLUDED
