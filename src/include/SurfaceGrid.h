/* 
 * File:   PointGrid.h
 * Author: Leonardo Berti
 * Griglia di QUADS usata per tracciare una superficie generica nello spazio 3D
 * Created on 31 ottobre 2010, 15.02
 */

#ifndef POINTGRID_H
#define	POINTGRID_H
#include <gl/gl.h>			// Header File For The OpenGL32 Library
#include <gl/glu.h>			// Header File For The GLu32 Library
#include "3dengine/3dengine.h"
//#include "math/mathdefs.h"
#include "math/vectors3.h"

/**
 * E' una griglia di quad che utilliza OpenGL per il rendering
 */
class SurfaceGrid:public Renderable{

protected:

    int tileh,tilew;
    bool visible;
    //coordinate dei vertici della griglia, ogni vertice ha tre coordinate
    double* vertices;
    //normali di ogni vertice
    double* normals;
    //colori
    float* colors;
    //punta la posizione corrente del buffer dei colori (permette la rotazione dei colori)
    size_t color_offset;
    size_t color_mid_offset; //offset a metà del buffer colori (oltre questo offset si deve puntare a zero di nuovo )
    size_t color_array_size; //dimensione buffer colori
    //indici usati per disegnare le strips della griglia
    int* quadIndices;
    int lastError;
    bool enableNormals,enableColors;
    size_t dataSize;
    int color_step; //step rotazione colori (in posizioni e non in punti (punti*4))
   

    void initialize();

    SurfaceGrid();

    /**
     * Restituisce l'offset all'interno dei vettori vertices e normals
     * di un punto sulla griglia
     * @param x coordinate punto sulla griglia
     * @param y
     * @return  l'offset
     */
    size_t getOffset(int x,int y) const;
    
    void getPointFast(CHVector3<double>* point, int x, int y) const;



public:



    /**
     * Crea una griglia di punti
     * @param tilew numero di tile orizzontali
     * @param tileh numero di tile verticali
     */
    SurfaceGrid(int tilew,int tileh);

    SurfaceGrid(const SurfaceGrid& orig);

    bool isNormalEnabled() const;

    /**
     * imposta lo step rotazione colore
     * @param step step in punti 
     * @return 
     */
    void setColorStep(int step);

    /**
     * Esegue una rotazione dei colori spostando avanti il puntatore al buffer colori di step posizioni
     * @return true se lo step supera la metà del buffer (in questo caso di devono ricreare i colori)
     */
    bool rotateColors();

    /**
     * Restituisce il numero di tile sul lato Y
     * @return
     */
    int GetXTiles();

    /**
     * Restituisce il numero di tile sul lato Y
     * @return
     */
    int GetYTiles();

    /**
     * Abilita le normali
     * @param enable
     */
    void setNormalEnabled(bool enable);

    bool isColorEnabled() const;

    /**
     * Abilita i colori vertice per vertice
     * @param enable
     */
    void setColorEnabled(bool enable);

    /**
     * Imposta un punto della griglia
     * @param x
     * @param y
     * @param point
     */
    void setPoint(int x,int y,const CHVector3<double>& point);

    /**
     * Acquisisce le coordinate di un punto di una griglia
     * @param point
     * @param x
     * @param y
     */
    void getPoint(CHVector3<double>* point,int x,int y) const;

    /**
     * Imposta la normale per un punto della griglia
     * @param x
     * @param y
     * @param normal
     */
    void setNormal(int x,int y,const CHVector3<double>& normal);

    /**
     * Acquisisce la normale per un punto della griglia
     * @param normal
     * @param x
     * @param y
     */
    void getNormal(CHVector3<double>* normal,int x,int y) const;

    /**
     * Acquisisce il colore di un vertice
     */
    COLOR getColor(int x,int y) const;

    /**
     * Imposta il colore di un vertice
     * @param x
     * @param y
     * @param c
     */
    void setColor(int x,int y,const COLOR c);

    /**
     * calcola le normali ad ogni punto
     */
    void calcNormals();

    virtual ~SurfaceGrid();

    void dump();

    /**
     * Esegue il rendering della griglia
     * @return
     */
    bool render();
    
    int last_error();
    
    bool is_visible();
    
    void set_visible(bool visible);
    
    bool operator== (const Renderable& val);


};

#endif	/* POINTGRID_H */

