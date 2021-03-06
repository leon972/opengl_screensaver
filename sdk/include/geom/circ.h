/*********************************
Soluzione analitica di circonferenze nel piano
Code by Leonardo Berti (c) 2010
**********************************/

#ifndef CIRC_H_INCLUDED
#define CIRC_H_INCLUDED

#include "math/mathdefs.h"
#include "math/libmath.h"
#include "geomdefs.h"
#include "sline.h"

using namespace mathengine;

namespace geom
{
  /**
  Circonferenza nel piano X-Y
  */
  class MATH_EXPORT Circle2
  {
      private:

      REAL xc,yc,radius,r2;

      public:

      Circle2();
      Circle2(REAL xc,REAL yc,REAL radius);
      virtual ~Circle2();

      REAL GetRadius() const;

      REAL GetCenterX() const;

      REAL GetCenterY() const;

      void SetRadius(REAL radius);

      void SetCenterX(REAL xc);

      void SetCenterY(REAL yc);

      void SetCenter(REAL xc,REAL yc);

      /**Calcola i punti di intersezione point1 e point con la circonferenza circle,
      se non c'� intersezione rende false
      */
      bool Intersect(CVector2<REAL>* point1,CVector2<REAL>* point2,const Circle2& circle) const throw(InvalidGeomEntityVideoException);

      /**
      Determina se il punto point � interno o appartenente alla circonferenza
      */
      bool IsInside(const CVector2<REAL>& point) const;

      /**
      Determina la retta tangente in un punto (il punto deve appartenere alla circonferenza
      */
      StrightLine2 GetTangent(const CVector2<REAL>& point) const throw (InvalidPointVideoException);

      /**
      Determina la retta tangente in un punto individuato dall'angolo theta (misurato in senso antiorario a partire dall'asse x)*/
      StrightLine2 GetTangent(const REAL theta_rad) const throw (InvalidPointVideoException);

      /**calcola l'area*/
      REAL GetArea();

      /**calcola la lunghezza della circonferenza*/
      REAL GetLength();
  };

};

#endif // CIRC_H_INCLUDED
