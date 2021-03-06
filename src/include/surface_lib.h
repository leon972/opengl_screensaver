/* 
 * File:   surface_lib.cpp
 * Author: Leonardo Berti
 * Libreria di superfici usate dello screen saver
 * Created on 2 novembre 2010, 19.18
 */

#ifndef SURFACE_LIB_H
#define	SURFACE_LIB_H

#include "I3DSurface.h"
#include <cmath>
#include <cstdlib>

/**
 * Restituisce il passo (radianti) da usare per compiere un numero di rotazioni complete
 * @param ncycles
 * @return
 */
double getCyclicStep(double ncycles, int ntiles) {

    return (double) ncycles * M_PI * 2 / (ntiles - 1);

}

float getRandFloat(float min, float max) {

    return ((float) rand() / RAND_MAX)*(max - min) + min;

}

/**
 * calcola la massima distanza dall'origine di una superficie
 */
double maxDist(const I3DSurface& surf, int tilew, int tileh) {

    double point[3];
    memset(point, 0, sizeof (double) *3);

    double u_step = surf.getStepU();
    double v_step = surf.getStepV();
    double u = 0;
    double v = surf.getV1();
    double curDist = 0;

    for (int j = 0; j <= tileh; j++) {

        u = surf.getU1();

        for (int i = 0; i <= tilew; i++) {

            //calcola il punto alle coordinate u,v
            surf.calcPoint(point, u, v);

            //quadrato della distanza
            double d = point[0] * point[0] + point[1] * point[1] + point[2] * point[2];

            if (d > curDist) curDist = d;

            u += u_step;
        }

        v += v_step;
    }

    //restituisce la distanza del punto più lontano dall'origine
    return sqrt(curDist);
}

class SurfaceBase : public I3DSurface {
protected:

    double u1, v1; //coordinate parametriche di partenza
    double u_step, v_step; //step coordinate parametriche
    CHVector3<double> transl;
    const char* name;

public:

    SurfaceBase() {
        transl.x = 0;
        transl.y = 0;
        transl.z = -240;
        name=""; //default
    }

    /**
     * restituisce la coordinata u iniziale
     */
    double getU1() const {
        return u1;
    }

    /**
     *restituisce la v iniziale
     */
    double getV1() const {
        return v1;
    }

    /**
     *passo u
     */
    double getStepU() const {
        return u_step;
    }

    /**
     *passo v
     */
    double getStepV() const {
        return v_step;
    }

    CHVector3<double> getTranslation() const {
        return transl;
    }

    const char* getName() const {
        return name;
    }

};

///////////////////////////////// PlaneZ ///////////////////////////////////////

/**
 * Piano
 */
class PlaneZ : public SurfaceBase {
private:

    double Cu, Cv, C0;

public:

    PlaneZ(double Cu, double Cv, double C0, int tilew, int tileh) {

        this->Cu = Cu;
        this->Cv = Cv;
        this->C0 = C0;
        u_step = 5;
        v_step = 5;
        u1 = -(tilew * 5)*0.5;
        v1 = -(tileh * 5)*0.5;
        transl.z = -350;
        name = "plane";
    }

    virtual ~PlaneZ() {

    }

    void calcPoint(double* point, double u, double v) const {

        point[0] = u; //x
        point[1] = v; //y
        point[2] = Cu * u + Cv * v + C0; //z
    }

};

//////////////////////////// Paraboloid ////////////////////////////////////

class Paraboloid : public SurfaceBase {
private:

    double A, B;

public:

    Paraboloid(double A, double B, int tilew, int tileh) {

        this->A = A;
        this->B = B;
        u_step = 5;
        v_step = 5;
        u1 = -(tilew * u_step)*0.5;
        v1 = -(tileh * v_step)*0.5;
        transl.z = -500;
        name = "paraboloid";
    }

    virtual ~Paraboloid() {

    }

    void calcPoint(double* point, double u, double v) const {

        point[0] = u; //x
        point[1] = v; //y
        point[2] = u * u * A * 0.1 + v * v * B * 0.1; //z
    }

};

///////////////////////////////////// Cylinder ///////////////////////////////

class Cylinder : public SurfaceBase {
private:

    double A, B;

public:

    Cylinder(double A, double B, int tilew, int tileh) {

        this->A = A;
        this->B = B;
        u_step = getCyclicStep(1, tilew);
        v_step = 4;
        u1 = 0;
        v1 = -120;
        name = "cylinder";
    }

    virtual ~Cylinder() {

    }

    void calcPoint(double* point, double u, double v) const {

        point[0] = A * cos(u); //x
        point[1] = B * sin(u); //y
        point[2] = v * 0.7; //z
    }

};

/////////////////////////////////// Sphere ///////////////////////////////////

class Sphere : public SurfaceBase {
private:

    double R;

public:

    Sphere(double R, int tilew, int tileh) {

        this->R = R;
        u1 = 0;
        v1 = -M_PI_2;
        u_step = getCyclicStep(1, tilew);
        v_step = getCyclicStep(0.5, tileh);
        transl.z = -340;
        name = "sphere";

    }

    virtual ~Sphere() {

    }

    void calcPoint(double* point, double u, double v) const {

        point[0] = R * cos(v) * cos(u);
        point[1] = R * cos(v) * sin(u);
        point[2] = R * sin(v);
    }
};

/////////////////////////////////// Spiral //////////////////////////////////

class Spiral : public SurfaceBase {
private:

    double R, R1;

public:

    Spiral(double R, double R1, int tilew, int tileh) {

        this->R = R;
        this->R1 = R1;
        u1 = 0;
        v1 = -M_PI_2;
        u_step = getCyclicStep(3, tilew);
        v_step = getCyclicStep(0.5, tileh);
        transl.z = -240;
        name = "conic spiral";
    }

    void calcPoint(double* point, double u, double v) const {

        point[0] = (R + u * 8) * cos(v) * cos(u);
        point[1] = (R + u * 8) * cos(v) * sin(u);
        point[2] = R1 * sin(v);

    }

};

//////////////////////////////////// Zucca /////////////////////////////////

class Zucca : public SurfaceBase {
private:

    double R, R1, P1;

public:

    Zucca(double R, double R1, double P1, int tilew, int tileh) {

        this->R = R;
        this->R1 = R1;
        this->P1 = P1;

        u1 = 0;
        v1 = -M_PI_2;
        u_step = getCyclicStep(1, tilew);
        v_step = getCyclicStep(0.5, tileh);
        transl.z = -(R + R1 + 70);
        name = "unknown";
    }

    void calcPoint(double* point, double u, double v) const {

        point[0] = (R + R1 * cos(P1 * u)) * cos(v) * cos(u);
        point[1] = (R + R1 * cos(P1 * u)) * cos(v) * sin(u);
        point[2] = R * sin(v);
    }
};

///////////////////////////////////// Waves //////////////////////////////////

class Waves : public SurfaceBase {
private:

    double R, R1, R2, P1, P2, P3;
    int tilew, tileh;

public:

    Waves(double R, double R1, double R2, double P1, double P2, double P3, int tilew, int tileh) {

        this->R = R;
        this->R1 = R1;
        this->R2 = R2;
        this->P1 = P1;
        this->P2 = P2;
        this->P3 = P3;

        this->tilew = tilew;
        this->tileh = tileh;

        u1 = -tilew * 3;
        v1 = -tileh * 3;
        u_step = 6;
        v_step = 6;
        transl.z = -tilew * 5;
        name = "waves";

    }

    void calcPoint(double* point, double u, double v) const {

        point[0] = u;
        point[1] = v;
        point[2] = cos(u * P1 / tilew) * R - sin(v * P2 / tileh) * R1 + R2 * cos(u * v * P3 * 0.01 / tilew);

    }

};

//////////////////////////////// Torus //////////////////////////////////////

class Torus : public SurfaceBase {
private:

    double R1, R2;
    int tilew, tileh;

public:

    /**
     *
     * @param R1 raggio grande
     * @param R2 raggio piccolo
     * @param tilew
     * @param tileh
     */
    Torus(double R1, double R2, int tilew, int tileh) {

        this->tilew = tilew;
        this->tileh = tileh;

        u1 = 0;
        v1 = 0;
        u_step = getCyclicStep(1, tilew);
        v_step = getCyclicStep(1, tileh);
        this->R1 = R1;
        this->R2 = R2;
        transl.z = -R1 * 2 - 100;
        name = "torus";

    }

    void calcPoint(double* point, double u, double v) const {

        point[0] = (R1 + R2 * cos(v)) * cos(u);
        point[1] = (R1 + R2 * cos(v)) * sin(u);
        point[2] = R2 * sin(v);
    }

};

/////////////////////////////////// WeirdTorus ////////////////////////////////

class WeirdTorus : public SurfaceBase {
private:

    double R1, R2;
    double D;
    int tilew, tileh;

public:

    /**
     *
     * @param R1 raggio grande
     * @param R2 raggio piccolo
     * @param tilew
     * @param tileh
     */
    WeirdTorus(double R1, double R2, double D, int tilew, int tileh) {

        this->tilew = tilew;
        this->tileh = tileh;

        u1 = 0;
        v1 = 0;
        u_step = getCyclicStep(1, tilew);
        v_step = getCyclicStep(1, tileh);
        this->R1 = R1;
        this->R2 = R2;
        this->D = D;
        transl.z = -R1 * 3 - 180;
        name = "weird torus";

    }

    void calcPoint(double* point, double u, double v) const {

        double r = R1 * (2 + sin(D * u));

        point[0] = (r + R2 * cos(v)) * cos(u); //x
        point[1] = (r + R2 * cos(v)) * sin(u); //y
        point[2] = R2 * sin(v); //z
    }

};

/////////////////////////////////// Helix //////////////////////////////////////

class Helix : public SurfaceBase {
private:

    double pitch; //passo
    double R; //raggio
    double L; //lunghezza
    int tilew, tileh;

public:

    Helix(double pitch, double R, double L, int tilew, int tileh) {

        this->pitch = pitch;
        this->R = R;
        this->L = L;
        this->tilew = tilew;
        this->tileh = tileh;

        u1 = 0;
        v1 = -R / 2;
        u_step = getCyclicStep(L / pitch, tilew);
        v_step = R / tileh;

        transl.z = -(L > R ? L : R) - 40;

        name = "helix";

    }

    void calcPoint(double* point, double u, double v) const {

        point[0] = v * cos(u); //x
        point[1] = pitch * u / (2 * M_PI) - L / 2; //y
        point[2] = v * sin(u); //z

    }


};

//////////////////////////////// Horn /////////////////////////////////////////

class Horn : public SurfaceBase {
private:

    double R, r1, L, pitch;
    double dec;
    double uf;
    double vf;

public:

    Horn(double R, double r1, double L, double pitch, int tilew, int tileh) {

        this->R = R;
        this->r1 = r1;
        this->L = L;
        this->pitch = pitch;

        u1 = 0;
        v1 = 0;
        u_step = getCyclicStep(L / pitch, tilew);
        v_step = getCyclicStep(1, tileh);

        uf = u_step*tilew;
        vf = v_step*tileh;

        dec = -r1 / tilew;

        transl.z = -(L > (R + r1) ? L : (R + r1)) - 40;
        name = "horn";

    }

    void calcPoint(double* point, double u, double v) const {

        double r = u / uf;
        double rc = r1 * (1 - r);

        point[0] = (R + rc * cos(v)) * cos(u);
        point[1] = (R + rc * cos(v)) * sin(u);
        point[2] = rc * sin(v) + L * r - L / 2;

    }

};

class CylindricSpiral : public SurfaceBase {
private:

    double Ri, Rf, L;
    double gf;
    double uf;

public:

    CylindricSpiral(double Ri, double Rf, double L, double ncycles, int tilew, int tileh) {

        this->Ri = Ri;
        this->Rf = Rf;
        this->L = L;

        u1 = 0;
        v1 = 0;

        u_step = getCyclicStep(ncycles, tilew);
        v_step = L / tileh;
        transl.z = L > Rf ? -L : -Rf;
        transl.z -= 180;

        uf = tilew * u_step + u1;

        //di quanto si aumenta il raggio
        gf = (Rf - Ri) / (uf - u1);
        name = "cylindric spiral";

    }

    void calcPoint(double* point, double u, double v) const {

        double d1 = gf*u;

        point[0] = (Ri + d1) * cos(u);
        point[1] = (Ri + d1) * sin(u);
        point[2] = v;

    }

};

///////////////////////////////// Klein's bottle ///////////////////////////////

class KleinBottle : public SurfaceBase {
private:

    double R1, R2, f, a;

public:

    /**
     *
     * @param R1 fatt. moltiplicativo per x e z valore di riferimento 16
     * @param R2 fatt. molt.di y val. rif=R1/2
     * @param a parametro per z val. rif=3
     * @param f par. y val. rif=80
     * @param tilew
     * @param tileh
     */
    KleinBottle(double R1, double R2, double a, double f, int tilew, int tileh) {

        this->R1 = R1;
        this->R2 = R2;
        this->a = a;
        this->f = f;
        u_step = getCyclicStep(1, tilew);
        v_step = getCyclicStep(1, tileh);
        u1 = -M_PI;
        v1 = M_PI;
        transl.z = -maxDist(*this, tilew, tileh) - 120;
        name = "Klein's bottle";


    }

    void calcPoint(double* point, double u, double v) const {

        /*  double n=(a+cos(u*0.5)*sin(v)-sin(u*0.5)*sin(2*v));

          point[0]=S*n*cos(u);
          point[1]=S*n*sin(u);
          point[2]=S*(sin(u*0.5)*sin(v)+cos(u*0.5)*sin(2*v));
         * */

        double cu = cos(u);
        double su = sin(u);
        double cv = cos(v);
        double sv = sin(v);


        //equation from Andrew J.P. Maclean paper:Parametric Equations for Surfaces

        point[0] = -R1 * cu * (3 * cv + 5 * su * cv * cu - 30 * su - 60 * su * pow(cu, 6) + 90 * su * pow(cu, 4));
        point[1] = -R2 * su * (f * cv * pow(cu, 7) * su + 48 * cv * pow(cu, 6) - f * cv * pow(cu, 5) * su - 48 * cv * pow(cu, 4) - 5 * cv * pow(cu, 3) * su - 3 * cv * cu * cu + 5 * su * cv * cu + 3 * cv - 60 * su);
        point[2] = R1 * sv * (a + 5 * su * cu) - 50;

    }

};

///////////////////////////////// KleinBottle2 ////////////////////////////////////

class Figure8KleinBottle : public SurfaceBase {
private:

    double a;
    double S; //fattore di scala

public:

    //a >2

    Figure8KleinBottle(double a, double S, int tilew, int tileh) {

        this->a = a;
        this->S = S;
        u_step = getCyclicStep(1, tilew);
        v_step = getCyclicStep(1, tileh);
        u1 = 0;
        v1 = 0;
        transl.z = -S * (a + 2) - 180;
        name = "Figure 8 Klein's bottle";


    }

    void calcPoint(double* point, double u, double v) const {

        double n = (a + cos(u * 0.5) * sin(v) - sin(u * 0.5) * sin(2 * v));

        point[0] = S * n * cos(u);
        point[1] = S * n * sin(u);
        point[2] = S * (sin(u * 0.5) * sin(v) + cos(u * 0.5) * sin(2 * v));

    }

};

//////////////////////////// Hyperbolic Paraboloid ////////////////////////////

class HyperbolicParaboloid : public SurfaceBase {
private:

    double a;
    double b;

public:

    HyperbolicParaboloid(double a, double b, int tilew, int tileh) {

        this->a = a*a;
        this->b = b*b;
        u_step = 4;
        v_step = 4;
        double w = u_step*tilew;
        double h = v_step*tileh;
        u1 = -w * 0.5;
        v1 = -h * 0.5;

        double tu = u1 * u1 / this->a;
        double tv = v1 * v1 / this->b;
        double tc = w * 0.5;

        if ((h * 0.5) > tc) tc = h * 0.5;
        if (tu > tc) tc = tu;
        if (tv > tc) tc = tv;

        transl.z = -tc - 100;
        name = "hyperbolic paraboloid";

    };

    void calcPoint(double* point, double u, double v) const {

        point[0] = u;
        point[1] = v;
        point[2] = (v * v) / b - (u * u) / a;
    }

};

/////////////////////////////// Hyperboloid ////////////////////////////////////

class Hyperboloid : public SurfaceBase {
private:

    double a, b, c;

public:

    Hyperboloid(double a, double b, double c, int tilew, int tileh) {

        this->a = a;
        this->b = b;
        this->c = c;

        v_step = getCyclicStep(1, tileh);
        u_step = 0.1;
        u1 = -tilew * 0.5 * u_step;

        double tc = c * abs(u1);
        double temp = a * sqrt(1 + abs(u1) * abs(u1));
        if (temp > tc) tc = temp;

        transl.z = -tc - 20;

        name = "hyperboloid";

    }

    void calcPoint(double* point, double u, double v) const {

        double f = sqrt(1 + u * u);

        point[0] = a * f * cos(v);
        point[1] = b * f * sin(v);
        point[2] = c*u;
    }

};

/////////////////////////////// Ellipsoid //////////////////////////////////

class Ellipsoid : public SurfaceBase {
private:

    double Rx, Ry, Rz;

public:

    Ellipsoid(double Rx, double Ry, double Rz, int tilew, int tileh) {

        this->Rx = Rx;
        this->Ry = Ry;
        this->Rz = Rz;
        u1 = 0;
        v1 = -M_PI_2;
        u_step = getCyclicStep(1, tilew);
        v_step = getCyclicStep(0.5, tileh);

        double tc = Rx;
        if (Ry > tc) tc = Ry;
        if (Rz > tc) tc = Rz;

        transl.z = -tc - 100;
        name = "ellipsoid";

    }

    void calcPoint(double* point, double u, double v) const {

        double cv = cos(v);

        point[0] = Rx * cos(u) * cv;
        point[1] = Ry * sin(v);
        point[2] = Rz * sin(u) * cv;

    }

};

///////////////////////////// Mobius Strip ////////////////////////////////////

class MobiusStrip : public SurfaceBase {
private:

    double R;
    double a;

public:

    /**
     * Costruisce il nastro di Mobius
     * @param R fattore di scala (val. riferimento 60)
     * @param a a>0 se aumenta il nastro è più stretto val. rif=3
     * @param tilew
     * @param tileh
     */
    MobiusStrip(double R, double a, int tilew, int tileh) {

        this->R = R;
        this->a = a;

        u1 = 0;
        u_step = getCyclicStep(1, tilew);

        double w = 1;
        v_step = w / tileh;
        v1 = -w / 2;
        transl.z = -(R + a) - 100;
        name = "Mobius strip";

    }

    void calcPoint(double* point, double u, double v) const {

        double c = a - v * sin(u / 2);

        point[0] = R * c * sin(u) / 3;
        point[1] = R * c * cos(u) / 3;
        point[2] = R * v * cos(u / 2);

    }

};

////////////////////////////// Boys Surface ////////////////////////////////////

class BoysSurface : public SurfaceBase {
private:

    double R;

public:

    /**
     *
     * @param R fattore di scala
     */
    BoysSurface(int tilew, int tileh) {

        R = 70;

        this->R = R;
        u1 = 0;
        u_step = M_PI / (tilew - 1);
        v1 = 0;
        v_step = M_PI / (tileh - 1);
        transl.z = -2 * R;
        name = "Boy's surface";

    }

    void calcPoint(double* point, double u, double v) const {

        double x = cos(u) * sin(v);
        double y = sin(u) * sin(v);
        double z = cos(v);

        double x2 = x*x;
        double y2 = y*y;
        double z2 = z*z;

        point[0] = R * 0.5 * (2 * x2 - y2 - z2 + 2 * y * z * (y2 - z2) + z * x * (x2 - z2) + x * y * (y2 - x2));
        point[1] = R * sqrt(3) / 2 * (y2 - z2 + (z * x * (z2 - x2) + x * y * (y2 - x2)));
        point[2] = R / 8 * (x + y + z)*(pow(x + y + z, 3) + 4 * (y - x)*(z - y)*(x - z));

    }


};

/////////////////////////////// Dini's Surface ////////////////////////////////

class DiniSurface : public SurfaceBase {
private:

    double a, b;

public:

    /**
     *
     * @param a raggio di rotazione (valore tipico 90)
     * @param b allungamento (valore tipico 8)
     * @param tilew
     * @param tileh
     */
    DiniSurface(double a, double b, int tilew, int tileh) {

        this->a = a;
        this->b = b;
        u1 = 0;
        v1 = 0;
        u_step = getCyclicStep(4, tilew);
        v_step = (M_PI - 0.01) / (tileh + 1);
        transl.z = -a * 3;
        name = "Dini's surface";

    }

    void calcPoint(double* point, double u, double v) const {

        point[0] = a * cos(u) * sin(v);
        point[1] = a * sin(u) * sin(v);
        point[2] = a * (cos(v) + log(tan(v / 2))) + b*u;
    }

};

///////////////////////////// Enneper Surface /////////////////////////////////

class EnneperSurface : public SurfaceBase {
private:
    double R;
public:

    /**
     *
     * 
     * @param tilew
     * @param tileh
     */
    EnneperSurface(int tilew, int tileh) {

        R = 3;

        this->R = R;
        double us = 15;
        double vs = 15;
        u1 = -us * 0.5;
        v1 = -vs * 0.5;
        u_step = us / tilew;
        v_step = vs / tilew;
        transl.z = -(pow(us * 0.5, 3) + us * 4) * R;
        name = "Enneper's surface";

    }

    void calcPoint(double* point, double u, double v) const {

        point[0] = R * (u - u * u * u / 3 + u * v * v);
        point[1] = R * (v - v * v * v / 3 + v * u * u);
        point[2] = R * (u * u - v * v);
    }

};

///////////////////////////////// Steiner's Roman Surface////////////////////////////////

class SteinerRomanSurface : public SurfaceBase {
private:

    double R;

public:

    SteinerRomanSurface(int tilew, int tileh) {

        R = 60;
        u1 = 0;
        v1 = 0;
        u_step = getCyclicStep(1, tilew);
        v_step = getCyclicStep(1, tileh);

        transl.z = -R * 1.1;

        name = "Steiner's Roman surface";

    }

    void calcPoint(double* point, double u, double v) const {

        point[0] = R * cos(v) * cos(v) * sin(2 * u) / 2;
        point[1] = R * sin(u) * sin(2 * v) / 2;
        point[2] = R * cos(u) * sin(2 * v) / 2;
    }

};

/////////////////////////////////// WeirdPolar1 ////////////////////////////////

class WeirdPolar1 : public SurfaceBase {
private:

    double R;
    double a;
    double b;
    double c;
    int tilew, tileh;

    void init() {
        transl.z = -maxDist(*this, tilew, tileh) - 100;
    }

public:

    /**
     *
     * @param R valore tipico 200 (raggio esterno)
     * @param a valore tipico 40 (modulo)
     * @param b valore tipico 0.9 (esponente)
     * @param c valore tipico 1.4 (frequenza)
     * @param tilew
     * @param tileh
     */
    WeirdPolar1(double R, double a, double b, double c, int tilew, int tileh) {

        this->R = R;
        this->a = a;
        this->b = b;
        this->c = c;
        this->tilew = tilew;
        this->tileh = tileh;
        u1 = 0;
        u_step = getCyclicStep(1, tilew);
        v1 = 0;
        v_step = R / tileh;
        name = "weird polar n.1";
        init();
    }

    void calcPoint(double* point, double u, double v) const {

        //parametrizzazione polare
        point[0] = v * cos(u);
        point[1] = v * sin(u);
        point[2] = a * cos(c * v * M_PI / R) + pow(v, b);
    }

};

////////////////////////////////////// Twister ///////////////////////////////

class Twister : public SurfaceBase {
private:

    double phi;
    double a;
    double b;
    double L;

public:

    /**
     *
     * @param a semiasse x ellisse
     * @param b semiasse y ellisse
     * @param ntwist numero di rotazioni nell'intera lunghezza
     * @param L lunghezza
     * @param tilew
     * @param tileh
     */
    Twister(double a, double b, double ntwist, double L, int tilew, int tileh) :
    a(a), b(b), L(L) {
        u1 = 0;
        u_step = getCyclicStep(1, tilew);
        v1 = -L / 2;
        v_step = L / tileh;
        transl.z = -maxDist(*this, tilew, tileh) - 100;
        phi = M_PI * ntwist / L;
        name = "twister";
    }

    void calcPoint(double* point, double u, double v) const {

        double x = a * cos(u);
        double y = b * sin(u);
        double t = phi*v;

        //parametrizzazione polare (esegue una rotazione dell'ellisse
        point[0] = x * cos(t) - y * sin(t);
        point[1] = x * sin(t) + y * cos(t);
        point[2] = v;
    }

};

/////////////////////////////// WeirdSurface ////////////////////////////////////

class WeirdSurface : public SurfaceBase {
private:

    double R, a, b, c, n;

public:

    /**
     *
     * @param R 
     * @param a 
     * @param b 
     * @param c 
     * @param n raggio di disturbo
     * @param tilew
     * @param tileh
     */
    WeirdSurface(double R, double a, double b, double c, double n, int tilew, int tileh) :
    R(R), a(a), b(b), c(c), n(n) {

        u1 = 0;
        u_step = getCyclicStep(1, tilew);
        v1 = -M_PI_2;
        v_step = getCyclicStep(0.5, tileh);
        name = "weird surface";
        transl.z = -maxDist(*this, tilew, tileh) - 200;

    }

    void calcPoint(double* point, double u, double v) const {

        double r = R + n * cos(a * u + b * v + c * sin(v * u * c / 12));

        //double r=R+100*u/(2*M_PI)+10*cos(12*v);

        //parametrizzazione polare (esegue una rotazione dell'ellisse
        point[0] = r * cos(v) * cos(u);
        point[1] = r * cos(v) * sin(u);
        point[2] = r * sin(v);
    }

};

/////////////////////////////// Shell //////////////////////////////////////////

class Shell : public SurfaceBase {
private:

    double nspirals;
    double R, dR;
    double waves;
    double grooveh;
    double uf;

public:

    /**
     *
     * @param R raggio iniziale (100)
     * @param dR delta raggio alla fine delle spirali (80)
     * @param nspirals numero di spirali (1)
     * @param nwaves numero di ondulazioni sulla superficie (10)
     * @param grooveh altezza scanalture (10)
     * @param tilew
     * @param tileh
     */
    Shell(double R, double dR, double nspirals, double nwaves, double grooveh, int tilew, int tileh) :
    R(R), dR(dR), nspirals(nspirals), waves(nwaves), grooveh(grooveh) {
        u1 = 0;
        uf = M_PI * 2 * nspirals;
        u_step = (uf - u1) / tilew;
        v1 = -M_PI_2;
        v_step = getCyclicStep(0.5, tileh);
        transl.z = -maxDist(*this, tilew, tileh) - 120;
        name = "shell";

    }

    /**
     * le coordinate del punto punto x(u,v),y(u,v),z(u,v)
     * @param point
     * @param u
     * @param v
     */
    void calcPoint(double* point, double u, double v) const {

        double r = R + dR * u / uf + grooveh * cos(waves * v);

        //parametrizzazione polare (esegue una rotazione dell'ellisse
        point[0] = r * cos(v) * cos(u);
        point[1] = r * cos(v) * sin(u);
        point[2] = r * sin(v);


    }

};

///////////////////////////////// Cone ///////////////////////////////////

class Cone:public SurfaceBase {

private:

    double m;
    double vf;

public:

    /**
     * Cono
     * @param m coefficiente angolare generatrici
     * @param tilew n. tilex
     * @param tileh n. tile y
     */
    Cone(float m,int tilew,int tileh):m(m) {

        v1=-100;
        vf=100;
        v_step=(vf-v1)/tileh;
        u1=0;
        u_step=getCyclicStep(1,tilew);
        name="cone";

        //spostamento verso l'asse z negativo (dentro al video)
        transl.z = -maxDist(*this, tilew, tileh) - 120;

    }

    void calcPoint(double* point, double u, double v) const {

        double r=m*v;

        point[0]=r*cos(u);
        point[2]=r*sin(u);
        point[1]=v;

    }

};

//////////////////////////////// Hills ////////////////////////////////////////

class Hills : public SurfaceBase {
private:

    static const int MAX_HILLS = 20;
    int nhills;
    double height;
    double uf, vf;
    double px[MAX_HILLS]; //punti sommità colline
    double py[MAX_HILLS];
    double A[MAX_HILLS]; //altezza colline

public:

    /**
     *
     * @param R raggio iniziale (100)
     * @param dR delta raggio alla fine delle spirali (80)
     * @param nspirals numero di spirali (1)
     * @param nwaves numero di ondulazioni sulla superficie (10)
     * @param grooveh altezza scanalture (10)
     * @param tilew
     * @param tileh
     */
    Hills(int nhills, double height, int tilew, int tileh) :
    nhills(nhills), height(height) {
        u1 = -200;
        uf = 200;
        u_step = (uf - u1) / tilew;
        v1 = u1;
        vf = uf;
        v_step = (vf - u1) / tileh;
        name = "random hills";
        
        if (this->nhills > MAX_HILLS) this->nhills = MAX_HILLS;

        //genera i punti di massimo o minimo casuali
        for (int i = 0; i<this->nhills; i++) {

            px[i] = getRandFloat(u1, uf);
            py[i] = getRandFloat(v1, vf);
            A[i] = getRandFloat(-height, height);
        }

        transl.z = -maxDist(*this, tilew, tileh) - 120;
    }

    /**
     * le coordinate del punto punto x(u,v),y(u,v),z(u,v)
     * @param point
     * @param u
     * @param v
     */
    void calcPoint(double* point, double u, double v) const {

        point[0] = u;
        point[2] = v;

        double y=0;
        double cx,cy;
        double d;

        for (int i=0;i<nhills;i++) {

            cx=u-px[i];
            cy=v-py[i];
            d=cx*cx+cy*cy;
            
            y+=A[i]*exp(-0.0006*d);

        }

        point[1] = y;

    }

};

///////////////////////////// RotoSolid ///////////////////////////////////////

class RotoSolid:public SurfaceBase {

private:

    double vf;
    double a;

public:

    /**
     *
     * @param a esponente (consigliato da
     * @param tilew
     * @param tileh
     */
    RotoSolid(double a,int tilew,int tileh):a(a) {

        v1=-100;
        vf=100;
        v_step=(vf-v1)/tileh;
        u1=0;
        u_step=getCyclicStep(1,tilew);
        name="spinning top";
        transl.z = -maxDist(*this, tilew, tileh) - 120;

    }

    void calcPoint(double* point, double u, double v) const {

       double r=100*exp(-pow(fabs(v),a)/10000);
          
        point[0]=r*cos(u);
        point[2]=r*sin(u);
        point[1]=v;
    }

};

////////////////////////////////// RotoDamp //////////////////////////////////

class RotoDamp:public SurfaceBase {

private:

    double vf;
    double A;
    double Ri;
    double tau;
    double f;

public:

    /**
     *
     * @param A raggio variabile (80)
     * @param Ri raggio interno (100)
     * @param tau smorzamento (80)
     * @param tilew
     * @param tileh
     */
    RotoDamp(double A,double Ri,double tau,int tilew,int tileh):A(A),Ri(Ri),tau(tau) {

        v1=-100;
        vf=100;
        v_step=(vf-v1)/tileh;
        u1=0;
        u_step=getCyclicStep(1,tilew);
        name="roto damp";
        transl.z = -maxDist(*this, tilew, tileh) - 120;
        f=1+rand()%4;

    }

    void calcPoint(double* point, double u, double v) const {


        double r=Ri+A*cos(v*f*M_PI/vf)*exp(-abs(v)/tau);

        point[0]=r*cos(u);
        point[2]=r*sin(u);
        point[1]=v;

    }

};

///////////////////////// WeirdBoy ////////////////////////////////////////////

class WeirdBoy:public SurfaceBase {

private:

    double uf;
    double vf;
    double a,b,c;


public:

    /**
     *
     * @param a 1-12
     * @param b 0-120
     * @param c 0-120
     * @param tilew
     * @param tileh
     */
    WeirdBoy(double a,double b,double c,int tilew,int tileh):a(a),b(b),c(c) {

        u1=0;
        u_step=getCyclicStep(1,tilew);
        v1=-100;
        vf=100;
        v_step=(vf-v1)/tileh;
        name="weird boy";
        transl.z = -maxDist(*this, tilew, tileh) - 120;

    }

    void calcPoint(double* point, double u, double v) const {

        double f=v*a/vf;
        double r=80+b*cos(cos(u/12))+c*sin(f*u);

        point[0]=r*cos(u);
        point[2]=r*sin(u)+c/5*cos(1.8*u+0.2);
        point[1]=v+20*sin(u/16);

    }


};

#endif	/* SURFACE_LIB_H */

