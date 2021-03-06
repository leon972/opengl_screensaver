/****************************************
Implementazione della classe Sprite
per OpenGL e Win32
Code by L.Berti (c) 2008
*****************************************/

#ifndef SPRITEGLW_H_INCLUDED
#define SPRITEGLW_H_INCLUDED

#include "lwtk/libhead.h"
#include "video/videodef.h"
#include "2dengine/sprite.h"
#include "videoglw/imagegl.h"
#include "math/matrix2.h"

#ifdef _USEVIDEONAMESPACE_
namespace video {
    #endif

    typedef struct SPRITE_FRAME_TYP {

        //nota: usa i puntatori perchè le stesse informazioni potrebbero essere usate da sprite diversi
        const ImageGL* image;
        const SEL_RECT* sel_rect;
        const BOUND_POLY* bound_poly;
        vector< CVector2<int> > hot_spots; //hot spot

        void reset() {
            image=0;
            sel_rect=0;
            bound_poly=0;
            hot_spots.clear();
        }

    } SPRITE_FRAME,*SPRITE_FRAME_PTR;

class DLL_EXPORT SpriteGL:public virtual Sprite {
private:

        std::vector<SPRITE_FRAME> frames;

        CVector2<float> velocity;

        int max_frame_index;
        int cur_hot_spot;
        //immagine e rettangolo di grabbing correnti
        //vengono settati quando si seleziona una frame
        const ImageGL* cur_image;
        const SEL_RECT* cur_rect;
        float anim_speed;
        float anim_clock;
        float img_alpha; //rotazione immagine
        int anim_start,anim_end;
        bool visible;
        ANIM_LOOP_TYPE anim_type;

        /**aggiorna la matrice di trasformazione*/
        //void UpdateTMatrix() const;

protected:

        int cur_frame;
        int deltax,deltay; //hot spot corrente
        //matrice corrente di trasformazione relativa;sono ammesse solo rotazioni intorno a z
        //nel caso di catene cinematiche di sprite è la matrice che trasforma dal sistema di
        //riferimento dello sprite genitore nel sistema di riferimento dello sprite corrente
        mutable CHMatrix33<float> tmatrix;
        void init();
        void IntBlit(const GLfloat* m,int linkx,int linky) const;

public:

        SpriteGL();
        SpriteGL(Image* img);
        virtual ~SpriteGL();

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
        virtual int AddFrame(const IMAGE_RECT& img_rect);

        virtual const BOUND_POLY* GetBoundPoly(void) const; //rende il poligono di contenimento corrente
        virtual bool SetBoundPoly(int frame_index,const BOUND_POLY* ppoly); //imposta il bounding polygon della frame

        virtual int AddFrameHotSpot(int frame,int lDeltax,int lDeltay);
        virtual bool SetFrameHotSpot(int frame,int iHotSpot,int lDeltax,int lDeltay);
        virtual void GetFrameHotSpot(int frame,int iHotSpot,int *plx,int *ply) const;
        /**rimuove un hot spot per la frame*/
        virtual bool RemoveFrameHotSpot(int frame,int iHotSpot);
        /**Restituisce il numero di hot spot per la frame*/
        virtual int GetFrameHotSpotCount(int frame) const;
        /**Imposta l'hot spot per framer corrente.Le operazioni di blitting verranno
        effettuate usando questo hot spot come origine*/
        virtual bool SetCurHotSpot(int iHotSpot);
        /**acquisisce l'id dell'hot spot corrente*/
        virtual int GetCurHotSpot() const;

        /**Trasforma le coordinate dal sistema di riferimento locale (usa come origine l'hot spot corrente)
        al sistema di riferimento fisso (video)*/
        virtual void LocalToWorld(CVector2<float>* world,const CVector2<float>& local) const;

        virtual void SetPosition(float x,float  y);
        virtual void SetPosition(const CVector2<float>& pos);
        virtual void GetPosition(float *x,float *y) const;

        virtual void SetVelocity(float deg_angle,float speed);      //imposta il vettore velocità (angolo e modulo)
        virtual void SetVelocity(const CVector2<float>& vel);
        /**imposta l'angolo della velocità*/
        virtual void SetVelocityAngle(float deg_angle);
        virtual float GetVelocityAngle();  //acquisisce l'angolo di direzione
        virtual float GetSpeed(void) const;  //acquisisce il modulo della velocità
        virtual CVector2<float> GetVelocity() const;
        virtual void GetVelocity(CVector2<float>* vel) const ;
        /**Imposta la rotazione dello sprite senza variare la direzione della velocità*/
        virtual void SetImageRotation(float deg_angle);
        virtual float GetImageRotation();
        virtual void SetAnimSpeed(const float speed);
        virtual float GetAnimSpeed(void) const ;
        virtual bool SetAnimRange(int iframe_start,int iframe_end);
        virtual void GetAnimRange(int *iframe_start,int *iframe_end) const;
        void ResetAnimRange();
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

#endif // SPRITEGLW_H_INCLUDED
