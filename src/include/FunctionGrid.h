/* 
 * Parametric surfaces screen saver
 * copyright (c) 2010 by Leonardo Berti
 *
 *
 * File:   FunctionGrid.h
 * 
 *
 * Created on 31 ottobre 2010, 15.33
 */

#ifndef FUNCTIONGRID_H
#define	FUNCTIONGRID_H

#include "SurfaceGrid.h"
#include "ColorRamp.h"
#include "math/mathdefs.h"
#include "math/quat2.h"
#include "3dengineglw/3dengineglw.h"
#include "I3DSurface.h"

static COLOR colorTable[] = {CL_YELLOW, CL_GREEN, CL_BLUE, CL_DARKGREEN,
    CL_LIGHTMAGENTA, CL_RED, CL_WHITE, CL_BROWN, CL_LIGHTGRAY, CL_LIGHTBLUE, CL_BEIGE, CL_DARKGREEN, CL_PINK,
    CL_VIOLET, CL_TURQUOISE, CL_AQUAMARINE, CL_GOLD, CL_ORANGE, CL_DARKORANGE, CL_GRAY, CL_CYAN, CL_DARKBLUE,
    CL_LIGHTMAGENTA,0xCCE322FF, 0xDDCC44FF, 0x440055FF, 0x44005599, 0x33442099, 0xABAC4499, 0x44FF88FF};

/**
 *Griglia di punti calcolati in base alla equazione della superficie
 *dotata di asse di rotazione e velocità di rotazione
 */
class FunctionGrid : public SurfaceGrid, public SceneNodeGlw {
protected:

    CHVector3<real> rotAxis; //asse di rotazione
    mutable CHVector3<real> tempVec, tempVec1;
    double omega; //vel. rotazione in radianti/ciclo
    //colori di controllo del gradiente di colore
    COLOR C1, C2, C3;
    void colorize(COLOR color_start, COLOR color_finish, int section);
    const char* currentSurfaceName;


public:

    static COLOR getRandomColor();

    FunctionGrid(int tilw, int tileh);
    void calcSurface(const I3DSurface& surface);

    //static void interpolate(FunctionGrid* dest,const FunctionGrid& start,const FunctionGrid& finish,float r);
    void blend(const FunctionGrid& next, float r);

    virtual ~FunctionGrid();

    void setCurrentSurfaceName(const char* name);

    const char* getCurrentSurfaceName() const;

    /**
     * resetta i colori generando un gradiente casuale
     */
    void generateColorGradient();

    /**
     * ruota il gradiente
     * (swap parte 1 e 2 dell'array color    
     */
    void rotateColorGradient();


    //imposta l'asse fisso di rotazione
    void setRotAxis(float vx, float vy, float vz, float omega_deg);
    /**
     * Acquisisce l'asse di rotazione corrente
     * @param rotAxis
     */
    void getRotAxis(CHVector3<real>* rotAxis) const;
    /**
     * imposta la velocità angorlare di rotazione
     */
    void setOmega(double omega);
    /**
     * acquisisce la velocità di rotazione (radianti/ciclo)
     */
    double getOmega() const;

    /**
     * Acquisisce la posizione dell'origine
     */
    void getOrigin(CHVector3<real>* origin) const;
    /**
     *Imposta l'origine
     */
    void setOrigin(const CHVector3<real>& origin);

    void rotate();

private:

};

#endif	/* FUNCTIONGRID_H */

