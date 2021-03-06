/*
 * 
 * Parametric surfaces screen saver
 * copyright (c) 2010 by Leonardo Berti
 *
 * File:   screen_saver.cpp
 * Author: Leonardo Berti
 *
 * Created on 31 ottobre 2010, 12.51
 */

#include <cstdlib>
#include <iostream>
#include <3dengineglw/3dengineglw.h>
#include <3dengine/3dengine.h>
#include <3dengineglw/factory3dglw.h>
#include <3dengine/factory3d.h>
#include "Animator.h"
#include "SurfaceFactory.h"
#include "screen_saver.h"
#include "ParametricSurfacesDemo.h"

using namespace std;
using namespace video;
using namespace mathengine;
using namespace renderer3d;

ParametricSurfacesDemo::ParametricSurfacesDemo() {

    animator = 0;
    factory3d = 0;

}

ParametricSurfacesDemo::~ParametricSurfacesDemo() {

    SAFE_DELETE(factory3d);
    SAFE_DELETE(animator);

}

void ParametricSurfacesDemo::setRotSpeed(float deg_per_cycle) {
    if (animator) animator->setRotSpeed(deg_per_cycle);
}

void ParametricSurfacesDemo::setColorGradientSpeed(int colStep) {
    if (animator) animator->setColorGradientSpeed(colStep);
}

void ParametricSurfacesDemo::setPersistCycles(int cycles) {
    if (animator) animator->setPersistCycles(cycles);
}

void ParametricSurfacesDemo::setDisplaySettings(int screen_width, int screen_height, int screen_bpp, bool fullscreen) {
    this->screen_width = screen_width;
    this->screen_height = screen_height;
    this->bpp = screen_bpp;
    this->fullscreen = fullscreen;
}

void ParametricSurfacesDemo::setDisplayNames(bool display) {
    displayNames = display;
}

void ParametricSurfacesDemo::initialize() {

    //settaggio default
    screen_width = 1024;
    screen_height = 768;
    bpp = 32;
    fullscreen = false;

    //auto garbage collector
    factory3d = Factory3DGlw::GetInstance(true);
    //Arcade engine 3D
    renderer = factory3d->GetNewL3DEngine();

    animator = new Animator(renderer, TILEW, TILEH);
}

void ParametricSurfacesDemo::start() throw (Exception) {

    renderer->SetGraphMode(screen_width, screen_height, bpp, fullscreen);

    //aggiunge un listener per ascoltare le richieste di interruzione dello screen saver da parte del sistema
    renderer->AddAnimationEvent(this);
    //listener movimenti mouse:quando muove il mouse deve terminare
    renderer->AddMouseMoveEvents(this);
    renderer->AddKeyEvents(this);

    renderer->SetRenderingFlags((renderer->GetRenderingFlags() | RD_WIREFRAME) & ~RD_CULL_FACES);


    Camera* cam = renderer->GetCurrentCamera();

    cam->SetFarClipPlane(3000); //3000

    cam->ApplyPerspective();

    renderer->StartAnimation(VK_ESCAPE, 0);

}



/**
 * Muovendo il mouse interrompe lo screen saver
 * @param x
 * @param y
 */
void ParametricSurfacesDemo::MouseMove(int x, int y) {

    static int cnt = 0;

    if (cnt++ > 8) {

        renderer->StopAnimation();
    }
}

bool ParametricSurfacesDemo::Animate() {

    animator->update();

    renderer->RenderScene();

    if (displayNames) {

        renderer->Begin2D();

        renderer->SetTextColor(CL_GRAY);

        renderer->WriteText(10, screen_height - 20, animator->getCurrentSurfaceName());

        renderer->End2D();
    }

    return true;
}

/**Tasto premuto*/
int ParametricSurfacesDemo::KeyDown(const KeyInfo* key_info) {
    //premendo un tasto interrompe lo screen saver
    renderer->StopAnimation();
}

/**Tasto rilasciato*/
int ParametricSurfacesDemo::KeyUp(const KeyInfo* key_info) {

}

/**Tasto ASCII premuto*/
int ParametricSurfacesDemo::KeyPressed(const KeyInfo* key_info) {

}


