/*********************************
Collider - gestione collisioni 2D
Code by Leonardo Berti (c) 2008
**********************************/

#ifndef COLLIDER_H_INCLUDED
#define COLLIDER_H_INCLUDED

#include "geom/geomdefs.h"
#include "lwtk/libhead.h"

using namespace geom;

namespace collider {
    #ifdef __cplusplus
//quando si compila in c++ questa serve a fare in modo che non vengano 'decorati'
//i nomi dal linker
    extern "C" {
        #endif

        /**
        collisione fra rettangoli, rende true se i rettangoli collidono
        */
        DLL_EXPORT bool CollideRect(const RECT_TYP<float>& rc1,const RECT_TYP<float>& rc2);

        #ifdef __cplusplus
    }
    #endif

};

#endif // COLLIDER_H_INCLUDED
