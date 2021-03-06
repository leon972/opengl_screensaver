/**********************************************
Catena cinematica di sprite
Code by L.Berti (c) 2008
***********************************************/

#ifndef TSPRITE_H_INCLUDED
#define TSPRITE_H_INCLUDED

#include "sprite.h"

#ifdef _USEVIDEONAMESPACE_
namespace video {
    #endif

class SpriteTree: public virtual Sprite {
public:

        virtual ~SpriteTree() {
        }

        /**Aggiunge una catena di sprite collegandola a questo sprite
        NB: se lo sprite è composto da piu' frames occorre che tutte le frame abbiano
        lo stesso numero di hot spot.
        */

        virtual void Add(SpriteTree* st,int dest_hot_spot,int src_hot_spot)=0;
        virtual void Remove(SpriteTree* st)=0;
        virtual int ItemsCount() const=0;

        /**Trasforma da coordinate locali nel sistema di rif. dello sprite, in coordinate del sistema fisso
        @param is_dirty indica che l'ultima matrice calcolata non è valida e la riaggiorna
        */
        virtual void LocalToWorld(CVector2<float>* world,const CVector2<float>& local,bool is_dirty) const=0;
        /**Trasforma da coordinate locali nel sistema di rif. dello sprite, in coordinate del sistema fisso
           aggiornando la matrice di trasformazione local to world*/
        virtual void LocalToWorld(CVector2<float>* world,const CVector2<float>& local) const=0;
        /**Restituisce la rotazione assoluta (riferita al sistema fisso)*/
        virtual float GetAbsRotation() const=0;
        /**Restituisce la rotazione assoluta aggiornando la matrice di trasformazione*/
        virtual float GetAbsRotation(bool is_dirty) const=0;


        /**Restituisce lo sprite genitore*/
        virtual SpriteTree* GetParent() const=0;
        /**Restituisce lo sprite radice della catena cinematica*/
        virtual SpriteTree* GetAncestor() const=0;

    };

    #ifdef _USEVIDEONAMESPACE_
};
#endif

#endif // TSPRITE_H_INCLUDED
