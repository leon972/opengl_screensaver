/*
 *
 * Parametric surfaces screen saver
 * copyright (c) 2010 by Leonardo Berti
 *
 * File:   SurfaceFactory.h
 * Author: Proprietario
 *
 * Created on 31 ottobre 2010, 15.38
 */

#ifndef SURFACEFACTORY_H
#define	SURFACEFACTORY_H
#include "FunctionGrid.h"
#include "ColorRamp.h"
#include <cstdlib>
#include <ctime>
#include <cmath>

//superfici disponibili
#define SURF_PLANE 0
#define SURF_PARABOLOID 1
#define SURF_CYLINDER 2
#define SURF_SPHERE 3
#define SURF_SPIRAL 4
#define SURF_PUMPKIN 5
#define SURF_WAVES 6
#define SURF_TORUS 7
#define SURF_WEIRD_TORUS 8
#define SURF_HELIX 9
#define SURF_HORN 10
#define SURF_CYLINDRIC_SPIRAL 11
#define SURF_KLEIN_BOTTLE 12
#define SURF_HYPERBOLIC_PARABOLOID 13
#define SURF_HYPERBOLOID 14
#define SURF_ELLIPSOID 15
#define SURF_KLEIN_BOTTLE2 16
#define SURF_MOBIUS_STRIP 17
#define SURF_BOYS 18
#define SURF_DINI 19
#define SURF_ENNEPER 20
#define SURF_STEINER_ROMAN 21
#define SURF_WEIRD_POLAR1 22
#define SURF_TWISTER 23
#define SURF_WEIRD 24
#define SURF_SHELL 25
#define SURF_HILLS 26
#define SURF_CONE 27
#define SURF_ROTO_SOLID 28
#define SURF_ROTO_DAMP 29
#define SURF_WEIRD_BOY 30

//n. di superfici disponibili
//nota:mantenere questo valore superiore di qualche unità all'id massimo delle sup.
//quando viene richiesto un id non esistente >id max e <TYPE_COUNT genera un piano
//come superficie di default

#define TYPE_COUNT 38

/**
 *Factory per le superfici parametriche
 * genera le equazioni delle superfici impostando
 * alcuni parametri in modo casuale
 */
class SurfaceFactory {
private:

    int type;
    //numero ti tiles usati nella generazione delle funzioni
    int tilew, tileh;
    //paremtri generici
    double R, R1, R2, P1, P2, P3;
    void setRandomColors();
    ColorRamp colorRamp;
    COLOR getRandomColor();
    I3DSurface* getSurface(int type);
    int lastTypeCreated;
    float rotSpeed;



public:

    static float getRandFloat(float min, float max);


    SurfaceFactory(int tilew, int tileh);
    virtual ~SurfaceFactory();
    int getTypeCount();

    /**
     * Crea una superficie di tipo specifico
     * @param fg
     * @param type
     */
    void makeSurface(FunctionGrid& fg, int type);
    /**
     * Crea un superficie scegliendo a caso dalla libreria delle superfici
     * @param fg
     */
    void makeRandomSurface(FunctionGrid& fg);
    /**
     * Crea una superficie dello stesso tipo dell'ultima creata
     * @param fg
     */
    void makeSameTypeSurface(FunctionGrid& fg);

    /**
     * Velocità rotazione (valore default 1.8)
     * @param deg_per_cycle
     */
    void setRotSpeed(float deg_per_cycle);


};

#endif	/* SURFACEFACTORY_H */

