/* 
 *  
 * Parametric surfaces screen saver
 * copyright (c) 2010 by Leonardo Berti
 *
 *
 * File:   ParametricSurfacesDemo.h
 * Author: Proprietario
 *
 * Created on 14 novembre 2010, 12.18
 */

#ifndef PARAMETRICSURFACESDEMO_H
#define	PARAMETRICSURFACESDEMO_H

#include <cstdlib>
#include <iostream>
#include <3dengineglw/3dengineglw.h>
#include <3dengine/3dengine.h>
#include <3dengineglw/factory3dglw.h>
#include <3dengine/factory3d.h>
#include <lwtk/exception.h>
#include "Animator.h"
#include "SurfaceFactory.h"
#include "screen_saver.h"


using namespace std;
using namespace video;
using namespace mathengine;
using namespace renderer3d;

/**
 *Classe animazione superfici
 */
class ParametricSurfacesDemo : public AnimationEvent,public MouseMoveEvents, public KeyEvents {
private:

    Factory3D* factory3d;
    L3DEngine* renderer;
    // SceneNode* sceneNode;
    //  FunctionGrid* fn1;
    //  SurfaceFactory* surfaceFactory;
    Animator* animator;
    float deltaRotation;
    int screen_width, screen_height, bpp;
    bool fullscreen;
    bool displayNames; //visualizza nomi superfici

public:

    ParametricSurfacesDemo();
    virtual ~ParametricSurfacesDemo();
    void initialize();
    void start() throw (Exception);
    bool Animate();


    /**
     * Velocità rotazione (valore default 1.8)
     * @param deg_per_cycle
     */
    void setRotSpeed(float deg_per_cycle);

    /**
     * Velocità gradiente colore (valore default 16)
     */
    void setColorGradientSpeed(int colStep);

    /**
     * Cicli prima di passare a nuova superficie (valore di default 80)
     * @param cycles
     */
    void setPersistCycles(int cycles);

    /**
     * Imposta la modalità video da utilizzare
     * @param screen_width
     * @param screen_height
     * @param screen_bpp
     * @param fullscreen
     */
    void setDisplaySettings(int screen_width, int screen_height, int screen_bpp, bool fullscreen);

    void setDisplayNames(bool display);

   

    /**
     * Quando si muove il mouse deve terminare
     * @param x
     * @param y
     */
    void MouseMove(int x, int y);


    /**Tasto premuto*/
    int KeyDown(const KeyInfo* key_info);
    /**Tasto rilasciato*/
    int KeyUp(const KeyInfo* key_info);
    /**Tasto ASCII premuto*/
    int KeyPressed(const KeyInfo* key_info);

};

#endif	/* PARAMETRICSURFACESDEMO_H */

