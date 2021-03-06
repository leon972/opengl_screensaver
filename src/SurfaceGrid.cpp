/* 
 * File:   PointGrid.cpp
 * Author: Leonardo Berti
 * 
 * Created on 31 ottobre 2010, 15.02
 */

#include "SurfaceGrid.h"
#include <iostream>
#include <lwtk/lwtk.h>

using namespace std;

/**
 * Crea una griglia di punti
 * il numero di linee verticali è tilew+1 mentre quelle orizzontali sono tileh+1
 * @param tilew numero di tile orizzontali (il numero di punti è n. tile+1)
 * @param tileh numero di tile verticali
 */
SurfaceGrid::SurfaceGrid(int tilew, int tileh) {

    this->tilew = tilew;
    this->tileh = tileh;
    initialize();

}

/**
 * Restituisce il numero di quadrati (tile) orizzontali
 * @return
 */
int SurfaceGrid::GetXTiles() {
    return tilew;
}

/**
 * Restituisce il numero di tile verticali
 * @return
 */
int SurfaceGrid::GetYTiles() {
    return tileh;
}

void SurfaceGrid::initialize() {

    //ad ogni punto sulla griglia corrisponde un punto nello spazio
    dataSize = (tilew + 1)*(tileh + 1)*3;
    vertices = new double[dataSize]; 
    //colori dei vertici compreso canale alpha    
    lastError = 0;
    quadIndices = new int[(tilew + 1)*2];

    color_array_size=(tilew + 1)*(tileh + 1)*8;
    //usa un buffer di dimensione doppia per permettere la rotazione dei colori
    colors = new float[color_array_size];
    color_offset=0;
    color_mid_offset=color_array_size/2; //offset a metà del buffer colori
    size_t offs = 0;
    //inizializza gli indici dei punti sulla griglia da usare con i quad strip
    //vengono memorizzati solo gli indici della prima riga, poi si fa variare il vertex pointer
    for (int i = 0; i <= tilew ; i++) {
        quadIndices[offs++] = i;
        quadIndices[offs++] = (tilew + 1) + i;
    }

}

SurfaceGrid::~SurfaceGrid() {

    SAFE_DELETE_ARRAY(quadIndices);
    SAFE_DELETE_ARRAY(colors);
    SAFE_DELETE_ARRAY(normals);
    SAFE_DELETE_ARRAY(vertices);  
}

SurfaceGrid::SurfaceGrid() {

}


void SurfaceGrid::setColorStep(int step) {
    color_step=4*step;
}

/**
 * Rotazione dei colori
 * @param step
 */
bool SurfaceGrid::rotateColors() {

    color_offset+=color_step; //ogni punto ha 4 canali (RGBA)
    if (color_offset>=color_mid_offset) {
        color_offset %=color_mid_offset;
        return true;

    }
    return false;

}

/**
 * Imposta un punto sulla griglia
 * @param x indice punto lungo x, va da 0 a tilew compreso
 * @param y indice punto lungo y, va da 0 a tileh compreso
 * @param point da settare
 */
void SurfaceGrid::setPoint(int x, int y, const CHVector3<double>& point) {

    lastError = 0;

    if (x >= 0 && x <= tilew && y >= 0 && y <= tileh) {

        int offset = getOffset(x, y);
        vertices[offset] = point.x;
        vertices[offset + 1] = point.y;
        vertices[offset + 2] = point.z;
    } else lastError = 1;
}

void SurfaceGrid::getPointFast(CHVector3<double>* point, int x, int y) const {

    int offset = (y * (tilew + 1) + x)*3;
    point->x = vertices[offset];
    point->y = vertices[offset + 1];
    point->z = vertices[offset + 2];
}

/**
 * Acquisisce le coordinate di un punto di una griglia
 * @param point
 * @param x
 * @param y
 */
void SurfaceGrid::getPoint(CHVector3<double>* point, int x, int y) const {

    if (x >= 0 && x <= tilew && y >= 0 && y <= tileh && point) {

        int offset = getOffset(x, y);
        point->x = vertices[offset];
        point->y = vertices[offset + 1];
        point->z = vertices[offset + 2];
    }
}

/**
 * Imposta la normale per un punto della griglia
 * @param x
 * @param y
 * @param normal
 */
void SurfaceGrid::setNormal(int x, int y, const CHVector3<double>& normal) {

    if (x >= 0 && x <= tilew && y >= 0 && y <= tileh) {
        int offset = getOffset(x, y);
        normals[offset] = normal.x;
        normals[offset + 1] = normal.y;
        normals[offset + 2] = normal.z;
    }
}

/**
 * Acquisisce la normale per un punto della griglia
 * @param normal
 * @param x
 * @param y
 */
void SurfaceGrid::getNormal(CHVector3<double>* normal, int x, int y) const {

    if (x >= 0 && x <= tilew && y >= 0 && y <= tileh && normal) {

        int offset = getOffset(x, y);
        normal->x = normals[offset];
        normal->y = normals[offset + 1];
        normal->z = normals[offset + 2];
    }
}

size_t SurfaceGrid::getOffset(int x, int y) const {

    return (y * (tilew + 1) + x)*3;

}

/**
 * calcola le normali ad ogni punto
 */
void SurfaceGrid::calcNormals() {

    CHVector3<double> vp;
    CHVector3<double> vo;
    CHVector3<double> n;
    CHVector3<double> vx;
    CHVector3<double> vy;

    for (int y = 0; y < tileh; y++) {

        size_t offs = y * (tilew + 1)*3;

        for (int x = 0; x < tilew; x++) {

            size_t offs1 = offs + x * 3;

            getPointFast(&vp, x + 1, y);
            getPointFast(&vo, x, y);

            vx = vp - vo;

            getPointFast(&vp, x, y + 1);

            vy = vp - vo;

            n.cross_product(vx, vy);

            n.normalize();

            normals[offs1] = n.x;
            normals[offs1 + 1] = n.y;
            normals[offs1 + 2] = n.z;

        }
    }

    //normali sul bordo esterno orizzontale
    for (int x = 0; x < tilew; x++) {

        getNormal(&n, x, tileh);
        setNormal(x, tileh + 1, n);
    }

    //normali sul bordo verticale esterno
    for (int y = 0; y < tileh; y++) {
        getNormal(&n, tilew, y);
        setNormal(tilew + 1, y, n);
    }

    //normale vertice esterno
    getNormal(&n, tilew, tileh);
    setNormal(tilew + 1, tileh + 1, n);

}

void SurfaceGrid::dump() {

    cout << "-------------------" << endl;
    cout << "tilew=" << tilew << " tileh=" << tileh << endl << endl;
    cout << "indices:" << endl;

    for (int i = 0; i < (tilew + 1)*2; i++) {
        cout << quadIndices[i] << ',';
    }

    cout << endl << "-------------------" << endl;

    cout << "grid:" << endl;

    int cnt = 0;
    int cnt1 = 0;

    for (size_t i = 0; i < dataSize; i++) {

        cout << vertices[i] << ",";
        if (++cnt % 3 == 0) cout << " - ";


        if (++cnt1 == (tilew + 1)*3) {

            cnt1 = 0;
            cout << endl;

        }


    }

    cout << "---- fine dump ----";

}

/**
 * Esegue il rendering della griglia
 * @return
 */
bool SurfaceGrid::render() {

    for (int y = 0; y < tileh; y++) {

        size_t offs = y * (tilew + 1)*3;

        glVertexPointer(3, GL_DOUBLE, 0, &vertices[offs]);
       // glNormalPointer(GL_DOUBLE, 0, &normals[offs]);
        glColorPointer(4, GL_FLOAT, 0, &colors[color_offset+y * (tilew + 1)*4]);
        //nota bene:in glDrawElements usare GL_UNSIGNED_INT come tipo indice
        glDrawElements(GL_QUAD_STRIP, (tilew + 1)*2 - 2, GL_UNSIGNED_INT, quadIndices);

    }

    return true;
}

int SurfaceGrid::last_error() {
    return lastError;
}

bool SurfaceGrid::is_visible() {
    return visible;
}

void SurfaceGrid::set_visible(bool visible) {
    this->visible = visible;
}

bool SurfaceGrid::operator==(const Renderable& val) {
    return this == &val;
}

bool SurfaceGrid::isNormalEnabled() const {
    return enableNormals;
}

/**
 * Abilita le normali
 * @param enable
 */
void SurfaceGrid::setNormalEnabled(bool enable) {
    if (enable) {
            glEnableClientState(GL_NORMAL_ARRAY);
            if (!normals) normals=new double[dataSize];
    }
    else glDisableClientState(GL_NORMAL_ARRAY);
}

bool SurfaceGrid::isColorEnabled() const {
    return glIsEnabled(GL_COLOR_ARRAY);
}

/**
 * Abilita i colori vertice per vertice
 * @param enable
 */
void SurfaceGrid::setColorEnabled(bool enable) {
    if (enable) {
        glEnableClientState(GL_COLOR_ARRAY);
    } else {
        glDisableClientState(GL_COLOR_ARRAY);
    }
}

/**
 * Acquisisce il colore di un vertice
 */
COLOR SurfaceGrid::getColor(int x, int y) const {

    size_t offs = (y * (tilew + 1) + x)*4;

    return Video::getRGBAColorFloat(colors[offs], colors[offs + 1], colors[offs + 2], colors[offs + 3]);

}

void SurfaceGrid::setColor(int x, int y, const COLOR c) {

    size_t offs = (y * (tilew + 1) + x)*4;

    float r, g, b, a;
    Video::toRGBAFloat(&r, &g, &b, &a, c);

    colors[offs] = r;
    colors[offs + 1] = g;
    colors[offs + 2] = b;
    colors[offs + 3] = a;
}

