/*****************************************
Code by Leonardo Berti (c) 2008
Retta e semiretta,segmento o vettore orientato
******************************************/

#ifndef SLINE_H_INCLUDED
#define SLINE_H_INCLUDED

#include "math/libmath.h"
#include "geomdefs.h"
#include "math/vectors2.h"
#include "math/vectors3.h"

using namespace mathengine;

namespace geom
{

class Segment2;

/**Retta nel piano bidimensionale*/
class MATH_EXPORT StrightLine2
{
    private:

    //coseni direttori
    REAL cx,cy;
    //punto dal quale passa la retta
    CVector2<REAL> O;

    void init(const CVector2<REAL>& p0,REAL cx,REAL cy);

    public:

    static bool GetIntersect(CVector2<REAL>* Pi,const CVector2<REAL>& O1,REAL a1,REAL b1,const CVector2<REAL>& O2,REAL a2,REAL b2);

    StrightLine2(); //y=0
    /**Costruisce la retta usando un versore e un punto*/
    StrightLine2(const CVector2<REAL>& vers,const CVector2<REAL>& point);
    /**costruisce la retta usando un segmento*/
    StrightLine2(const Segment2& seg);
    /**costruisce la retta usando un punto e il coefficiente angolare*/
    StrightLine2(const CVector2<REAL>& p,REAL m);
    /**costruisce la retta usando 2 punti*/
    StrightLine2(CVector2<REAL>& p1,CVector2<REAL>& p2);
    /**Restituisce un punto appartenente alla retta (punto di riferimento)*/
    const CVector2<REAL>& GetRefPoint() const;
    /**Restituisce la y che corrisponde x se non esiste y rende false*/
    bool GetY(REAL*y,REAL x);
    /**Restituisce la x che corrisponde ad y*/
    bool GetX(REAL*x,REAL y);

    /**Restituiscono i due coseni direttori*/
    REAL GetCosX() const;
    REAL GetCosY() const;
};

/**Segmento (o vettore) orientato P-O bidimensionale*/
class MATH_EXPORT Segment2
{
    private:

    /**vertice*/
    CVector2<REAL> P;
    /**punto di applicazione*/
    CVector2<REAL> O;

    REAL a,b; //coseni direttori lungo x e lungo y

    /**Restituisce il punto appartnente al segmento corrispondente
    al parametro t.Se il punto non appartiene al segmento rende false*/
    bool GetPoint(CVector2<REAL>* p,REAL t) const;

    void setup(const CVector2<REAL>& p,const CVector2<REAL>& o);

    public:


    Segment2(const CVector2<REAL>& p,const CVector2<REAL>& o);
    Segment2(REAL x1,REAL y1,REAL x2,REAL y2);
    Segment2();

    CVector2<REAL> GetP() const;
    CVector2<REAL> GetO() const;
    void SetP(const CVector2<REAL>& P);
    void SetO(const CVector2<REAL>& O);

    /**Restituisce il vettore libero a partire dal vettore applicato*/
    CVector2<REAL> GetVector() const;

    /**Calcola il punto di instersezione con un altro segmento seq
    se non c'è intersezione rende false*/
    bool Intersect(CVector2<REAL>* point,const Segment2& seg) const;
    /**Calcola l'intersezione con una retta*/
    bool Intersect(CVector2<REAL>* point, const StrightLine2& line) const;
    /**Restituisce il modulo*/
    REAL magnitude() const;
    /**Restituisce i coseni direttori*/
    REAL GetCosX() const;
    REAL GetCosY() const;
    void GetBoundBox(RECT_TYP<REAL>* bbox) const;

};

};


#endif // SLINE_H_INCLUDED
