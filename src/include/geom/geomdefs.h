/**********************************
Computational Geometry def.
Code by L.Berti (c) 2008
***********************************/

#ifndef GEOMDEFS_H_INCLUDED
#define GEOMDEFS_H_INCLUDED

#include "math/vectors2.h"
#include "math/vectors3.h"

using namespace mathengine;

namespace geom {
/**entit� geometrica degenere*/
class InvalidGeomEntityVideoException {
};

/**punto non valido per compiere l'operazione*/
class InvalidPointVideoException {
};

/**
rettangolo
left � considerato minore o uguale di right e top maggiore o uguale di bottom
in questo modo la classe pu� essere usata indipendentemente dalla direzione
degli assi
*/
template <class T> class RECT_TYP {
public:

     T left,right,top,bottom;

     RECT_TYP() {
          left=right=bottom=top=0;
     }

     RECT_TYP(T left,T right,T top,T bottom) {
          this->left=left;
          this->right=right;
          this->top=top;
          this->bottom=bottom;
     }

     T GetWidth() const {
          return fabs(static_cast<T>(right-left));
     }

     T GetHeight() const {
          return fabs(top-bottom);
     }

     /**
     sposta il rettangolo
     */
     void MoveTo(T new_left,T new_top) {

          T dx=new_left-left;
          T dy=new_top-top;

          left=new_left;
          top=new_top;
          right=dx+right;
          bottom=dy+bottom;
     }

     void Move(T dx,T dy) {
          left+=dx;
          right+dx;
          top+=dy;
          bottom+=dy;
     }

     void SetWidth(T new_width) {

          right=left+new_width;
     }

     void SetHeight(T new_height) {
          top=bottom+new_height;
     }

     void Resize(T new_width,T new_height) {
          top=bottom+new_height;
          right=left+new_width;
     }

     /**
     Determina il il punto � interno
     */
     bool IsInside(T px,T py) const {
          return (!(px<left || px>right || py>top || py<bottom));
     }

     /**
     Rende true se il rettangolo corrente collide con quello di riferimento rect
     */
     bool Collide(const RECT_TYP<T> &rect) const {
          return (!(rect.left>right || rect.right<left || rect.top<bottom || rect.bottom>top));
     }
};

template <class T> class POLYGON {
     CVector2<T>* vertices;
     int nvertices;
};
};

#endif // GEOMDEFS_H_INCLUDED
