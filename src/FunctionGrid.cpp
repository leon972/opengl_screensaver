/*   
 * Parametric surfaces screen saver
 * copyright (c) 2010 by Leonardo Berti
 *
 *
 * File:   FunctionGrid.cpp
 * Author: Leonardo Berti
 * 
 * Created on 31 ottobre 2010, 15.33
 */

#include "ColorRamp.h"


#include "SurfaceGrid.h"
#include "SurfaceFactory.h"
#include "I3DSurface.h"

FunctionGrid::~FunctionGrid() {
}

FunctionGrid::FunctionGrid(int tilew, int tileh) {

    this->tilew = tilew;
    this->tileh = tileh;

    //impostazione iniziale
    rotAxis.x = 0;
    rotAxis.y = 1;
    rotAxis.z = 0;
    omega = DEG_TO_RAD(1.0);
    SetPosition(0, -300, 0);
    C1 = CL_YELLOW;
    C2 = CL_RED;
    C3 = CL_BLUE;

    initialize();
}

/**
 * Calcola la superficie scrivendo i punti nella griglia
 * @param surface
 */
void FunctionGrid::calcSurface(const I3DSurface& surface) {

    double u = surface.getU1();
    double v = surface.getV1();
    double* point;
    double step_u = surface.getStepU();
    double step_v = surface.getStepV();
    size_t offs;

    for (int j = 0; j <= tileh; j++) {

        u = surface.getU1();
        offs = (j * (tilew + 1))*3;

        for (int i = 0; i <= tilew ; i++) {

            point = &vertices[offs];
            //calcola il punto alle coordinate u,v
            surface.calcPoint(point, u, v);

            offs += 3; //passa al punto successivo
            u += step_u;
        }

        v += step_v;
    }
}

/**
 * Esegue la fusione della superficie corrente con un'altra
 * @param next
 * @param r parametro blend r=0 questa superficie r=1 successiva, valori intermedi=blend
 */
void FunctionGrid::blend(const FunctionGrid& next, float r) {

    size_t dataSize = (tilew + 1)*(tileh + 1);
    size_t offs = 0;
    float r1 = 1.0 - r;

    if (r >= 1.0) {

        memcpy(vertices,next.vertices,dataSize*sizeof(double)*3);

    } else {
        for (size_t idx = 0; idx < dataSize; idx++) {

            offs = idx * 3;

            vertices[offs] = r1 * vertices[offs] + r * next.vertices[offs];
            vertices[offs + 1] = r1 * vertices[offs + 1] + r * next.vertices[offs + 1];
            vertices[offs + 2] = r1 * vertices[offs + 2] + r * next.vertices[offs + 2];

        }
    }

    //interpola asse rotazione
    next.getRotAxis(&tempVec);

    rotAxis.x = r1 * rotAxis.x + r * tempVec.x;
    rotAxis.y = r1 * rotAxis.y + r * tempVec.y;
    rotAxis.z = r1 * rotAxis.z + r * tempVec.z;
    rotAxis.normalize(); //corregge errori di arrotondamento

    //interpola omega
    omega = omega * r1 + next.getOmega() * r;

    //interpola la posizione
    GetPosition(&tempVec);
    next.getOrigin(&tempVec1);

    tempVec.x = r1 * tempVec.x + r * tempVec1.x;
    tempVec.y = r1 * tempVec.y + r * tempVec1.y;
    tempVec.z = r1 * tempVec.z + r * tempVec1.z;

    SetPosition(tempVec.x, tempVec.y, tempVec.z);
}

/**
 * Applica il colore al vettore dei colori
 * @param colorRamp
 */

void FunctionGrid::rotate() {

    if (!glIsEnabled(GL_COLOR_ARRAY)) glEnableClientState(GL_COLOR_ARRAY);

    //ruota la griglia intorno all'asse di rotazione
    Rotate(omega, rotAxis);

}

void FunctionGrid::setRotAxis(float vx, float vy, float vz, float omega_deg) {


    rotAxis.w = 1.0;
    rotAxis.x = vx;
    rotAxis.y = vy;
    rotAxis.z = vz;
    rotAxis.normalize();
    omega = DEG_TO_RAD(omega_deg);

}

/**
 * Acquisisce l'asse di rotazione corrente
 * @param rotAxis
 */
void FunctionGrid::getRotAxis(CHVector3<real>* rotAxis) const {
    *rotAxis = this->rotAxis;
}

/**
 * imposta la velocità angorlare di rotazione (in radianti)
 */
void FunctionGrid::setOmega(double omega) {
    this->omega = omega;
}

/**
 * acquisisce la velocità di rotazione (in radianti)
 */
double FunctionGrid::getOmega() const {
    return omega;
}

/**
 * Acquisisce la posizione dell'origine
 */
void FunctionGrid::getOrigin(CHVector3<real>* origin) const {

    GetPosition(origin);

}

/**
 *Imposta l'origine
 */
void FunctionGrid::setOrigin(const CHVector3<real>& origin) {
    this->SetPosition(origin.x, origin.y, origin.z);
}

//static

COLOR FunctionGrid::getRandomColor() {

    size_t sz = sizeof (colorTable) / sizeof (COLOR);
    return colorTable[rand() % sz];
}

/**
 * resetta i colori generando un gradiente casuale
 */
void FunctionGrid::generateColorGradient() {

    C1 = FunctionGrid::getRandomColor();
    C2 = FunctionGrid::getRandomColor();
    C3 = FunctionGrid::getRandomColor();
    colorize(C1, C2, 0);
    colorize(C2, C3, 1);

}

/**
 * ruota il gradiente
 * (swap parte 1 e 2 dell'array color
 */
void FunctionGrid::rotateColorGradient() {

    COLOR N = getRandomColor();
    C1 = C2;
    C2 = C3;
    C3 = N;
    colorize(C1, C2, 0);
    colorize(C2, C3, 1);

}

void FunctionGrid::setCurrentSurfaceName(const char* name) {
    currentSurfaceName = name;
}

const char* FunctionGrid::getCurrentSurfaceName() const {
    return currentSurfaceName;

}

/**
 * Esegue la colorazione con una rampa di colore di una delle due parti della mappa
 * colori
 * @param colorRamp
 * @param section 0=prima metà mappa 1=seconda metà mappa colori
 */
void FunctionGrid::colorize(COLOR c1, COLOR c2, int section) {

    size_t p = 0;
    size_t npoints = (tileh + 1)*(tilew + 1);
    size_t offs;
    size_t offst_sec = section == 1 ? color_mid_offset : 0;
    float perc;
    ColorRamp colorRamp(c1, c2);

    for (int y = 0; y <= tileh; y++) {

        //offset vettore dei colori
        offs = y * (tileh + 1)*4 + offst_sec;

        for (int x = 0; x <= tilew; x++) {

            size_t offs1 = offs + x * 4;

            perc = (float) p / npoints;

            colorRamp.getColor(&colors[offs1], &colors[offs1 + 1], &colors[offs1 + 2], &colors[offs1 + 3], perc);

            ++p;

        }
    }
}


