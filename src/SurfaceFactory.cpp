/* 
 * Parametric surfaces screen saver
 * copyright (c) 2010 by Leonardo Berti
 *
 * File:   SurfaceFactory.cpp
 * Author: Proprietario
 * 
 * Created on 31 ottobre 2010, 15.38
 */

#include "SurfaceFactory.h"
#include "I3DSurface.h"
#include "surface_lib.h"

SurfaceFactory::SurfaceFactory(int tilew, int tileh):rotSpeed(1.8) {

    this->tilew = tilew;
    this->tileh = tileh;
    //randomize timer
    time_t cur_time = time(0);
    tm* tm_info = localtime(&cur_time);
    srand(tm_info->tm_sec + tm_info->tm_min * 60);
}

SurfaceFactory::~SurfaceFactory() {
}

int SurfaceFactory::getTypeCount() {
    return TYPE_COUNT;
}

/**
 * Restituisce la superficie in base al tipo
 * @param type
 * @return 
 */
I3DSurface* SurfaceFactory::getSurface(int type) {

    switch (type) {

        case SURF_PLANE:        
            return new PlaneZ(0, 0, 0, tilew, tileh);        
        case SURF_PARABOLOID:
        {
            double a = getRandFloat(0.0, 0.07);
            return new Paraboloid(a, a, tilew, tileh);
        }
        case SURF_CYLINDER:        
            return new Cylinder(getRandFloat(50, 80), getRandFloat(50, 80), tilew, tileh);        
        case SURF_SPHERE:        
            return new Sphere(getRandFloat(60,180),tilew,tileh);        
        case SURF_SPIRAL:
        {
            double R=getRandFloat(20,70);
            double R1=getRandFloat(R/2,R*1.4);
            return new Spiral(R,R1,tilew,tileh);
        }
        case SURF_PUMPKIN:        
            return new Zucca(getRandFloat(70,220),getRandFloat(10,80),getRandFloat(2,5),tilew,tileh);
        case SURF_WAVES:
        {
            double R=getRandFloat(-50,70);
            double R1=getRandFloat(-50,70);
            double R2=getRandFloat(0,20);
            double P1=getRandFloat(2,8);
            double P2=getRandFloat(2,8);
            double P3=getRandFloat(2,6);
            Waves* w=new Waves(R,R1,R2,P1,P2,P3,tilew,tileh);
            return w;
        }
        case SURF_TORUS:        
            return new Torus(getRandFloat(100,160),getRandFloat(10,80),tilew,tileh);                
        case SURF_WEIRD_TORUS:
            return new WeirdTorus(getRandFloat(100,220),getRandFloat(10,100),rand()%4+2,tilew,tileh);
        case SURF_HELIX:        
            return new Helix(getRandFloat(120,350),getRandFloat(80,230),getRandFloat(120,410),tilew,tileh);        
        case SURF_HORN:        
            return new Horn(getRandFloat(100,160),getRandFloat(10,80),getRandFloat(120,410),getRandFloat(120,350),tilew,tileh);        
        case SURF_CYLINDRIC_SPIRAL:
            return new CylindricSpiral(getRandFloat(10,40),getRandFloat(100,200),getRandFloat(20,400),getRandFloat(3,5),tilew,tileh);
        case SURF_KLEIN_BOTTLE:       
            return new KleinBottle(getRandFloat(14,18),getRandFloat(7,9),getRandFloat(1.5,4),getRandFloat(60,90),tilew,tileh);
        case SURF_KLEIN_BOTTLE2:
            return new Figure8KleinBottle(getRandFloat(2,8),getRandFloat(80,180),tilew,tileh);
        case SURF_HYPERBOLIC_PARABOLOID:
            return new HyperbolicParaboloid(getRandFloat(6,50),getRandFloat(6,50),tilew,tileh);
        case SURF_HYPERBOLOID:
            return new Hyperboloid(getRandFloat(0.4,6),getRandFloat(0.4,6),getRandFloat(0.1,5),tilew,tileh);
        case SURF_ELLIPSOID:
            return new Ellipsoid(getRandFloat(20,200),getRandFloat(20,200),getRandFloat(20,200),tilew,tileh);
        case SURF_MOBIUS_STRIP:
            return new MobiusStrip(getRandFloat(55,68),getRandFloat(0.9,6),tilew,tileh);
        case SURF_BOYS:
            return new BoysSurface(tilew,tileh);
        case SURF_DINI:
           // return new DiniSurface(getRandFloat(70,110),getRandFloat(6,9),tilew,tileh);
            return new PlaneZ(0, 0, 0, tilew, tileh);
        case SURF_ENNEPER:
            return new EnneperSurface(tilew,tileh);
        case SURF_STEINER_ROMAN:
            return new SteinerRomanSurface(tilew,tileh);
        case SURF_WEIRD_POLAR1:
            return new WeirdPolar1(getRandFloat(100,180),getRandFloat(20,80),getRandFloat(0.1,1.1),getRandFloat(0.6,4),tilew,tileh);
        case SURF_TWISTER:
            return new Twister(getRandFloat(10,180),getRandFloat(10,180),getRandFloat(-5,5),getRandFloat(300,500),tilew,tileh);
        case SURF_WEIRD:
            return new WeirdSurface(getRandFloat(100,200),getRandFloat(0.2,10),getRandFloat(0.2,5),getRandFloat(0.5,6),getRandFloat(5,25),tilew,tileh);
        case SURF_SHELL:
            return new Shell(getRandFloat(100,150),getRandFloat(100,200),getRandFloat(0.2,2.6),getRandFloat(2,18),getRandFloat(4,35),tilew,tileh);
        case SURF_HILLS:
            return new Hills(rand()%18+1,getRandFloat(-190,190),tilew,tileh);
        case SURF_CONE:
            return new Cone(getRandFloat(0.8,2),tilew,tileh);
        case SURF_ROTO_SOLID:
            return new RotoSolid(getRandFloat(0.7,3),tilew,tileh);
        case SURF_ROTO_DAMP:
            return new RotoDamp(getRandFloat(20,100),getRandFloat(0,100),getRandFloat(80,500),tilew,tileh);
        case SURF_WEIRD_BOY:
            return new WeirdBoy(getRandFloat(0.5,8),getRandFloat(-80,80),getRandFloat(-80,80),tilew,tileh);
        default:
        {
            return new PlaneZ(0, 0, 0, tilew, tileh);
        }
    }
}

/**
 * Restituisce un random float compreso fra min e max escluso
 * @param min
 * @param max
 * @return 
 */
float SurfaceFactory::getRandFloat(float min, float max) {

    return ((float) rand() / RAND_MAX)*(max - min) + min;
    
}

void SurfaceFactory::makeSurface(FunctionGrid& fg, int type) {

    I3DSurface* surf = getSurface(type);

    fg.calcSurface(*surf);

    //imposta il nome della superficie corrente
    fg.setCurrentSurfaceName(surf->getName());

    //rotaz. asse fisso
    fg.setRotAxis(getRandFloat(-1.0, 1.0), getRandFloat(-1.0, 1.0), getRandFloat(-1.0, 1.0), getRandFloat(-rotSpeed, rotSpeed));

    CHVector3<double> t = surf->getTranslation();
    // trasla l'oggetto per portarlo davanit alla telecamera
    fg.SetPosition(t.x,t.y,t.z);
 
    delete surf;
}

/**
 * Velocità rotazione (valore default 1.8)
 * @param deg_per_cycle
 */
void SurfaceFactory::setRotSpeed(float deg_per_cycle) {
    rotSpeed=deg_per_cycle;
}

void SurfaceFactory::makeRandomSurface(FunctionGrid& fg) {

    static int last_type=-1;
    int type;
    int cnt=0;

    do
    {
        type=rand()%TYPE_COUNT;

    } while (type==last_type && ++cnt<20);
    
    last_type=type;

    lastTypeCreated=type;

    makeSurface(fg,type);
}

void SurfaceFactory::makeSameTypeSurface(FunctionGrid& fg) {

    makeSurface(fg,lastTypeCreated);

}

COLOR SurfaceFactory::getRandomColor() {

    unsigned char r = 0, g = 0, b = 0, a = 0xFF;

    int cnt = 0;

    while (r + g + b < 25 && cnt++ < 20) {
        r = rand() % 256;
        g = rand() % 256;
        b = rand() % 256;
    }

    if ((rand() % 10) == 1) {
        //usa l'alpha blending
        a = rand() % 256;
    } else a = 0xFF;

    return Video::getRGBAColor(r, g, b, a);

}

void SurfaceFactory::setRandomColors() {

  //  colorRamp.setFirstColor(getRandomColor());
   // colorRamp.setSecondColor(getRandomColor());
    colorRamp.setFirstColor(CL_YELLOW);
    colorRamp.setSecondColor(CL_DARKGREEN);
}


