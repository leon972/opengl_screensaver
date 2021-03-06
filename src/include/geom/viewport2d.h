/***************************************
Trasformazioni da coordinate logiche a
fisiche per un viewport 2D
Code by Leonardo Berti (c) 2009
*****************************************/

#ifndef VIEWPORT2D_H_INCLUDED
#define VIEWPORT2D_H_INCLUDED

#include "math/libmath.h"
#include "geom/geomdefs.h"
#include <map>

namespace geom
{
    //orientamento assi logici
    enum PHYSX_AXIS_DIR
    {
        LEFT_TO_RIGHT=0,
        RIGHT_TO_LEFT=1
    };

    enum PHYSY_AXIS_DIR
    {
        BOTTOM_UP=0,
        TOP_DOWN=1
    };

    typedef struct
    {
        double Wl,Hl;
        double Oxl,Oyl;
    } VIEWPORT2D_STATE,*VIEWPORT2D_STATE_PTR;

    //accezione generica parametri viewport
    class MATH_EXPORT Viewport2DException
    {

    };

    class MATH_EXPORT Viewport2D
    {

        protected:

        //larghezza fisica
        double Wf;
        //altezza fisica
        double Hf;
        //larghezza logica
        double Wl;
        //altezza logica
        double Hl;

        double Wf2,Hf2; //semilarghezza e semialtezza fisiche

        std::map<int,VIEWPORT2D_STATE> state_bookmarks;

        //punto in coordinate logiche che corrisponde al
        //centro del viewport
        double Oxl;
        double Oyl;
        //phys_width/logic_width (fattore di conversione da unit� fisiche a logiche asse x
        double flx,fly;
        //phys_height/logic_height; lf=1/fl
        double lfx,lfy;
        //costanti moltiplicative che tengono conto della direzione degli assi
        double x_dir,y_dir;


        public:

        Viewport2D(double phys_width,double phys_height,PHYSX_AXIS_DIR x_axis,PHYSY_AXIS_DIR y_axis) throw (Viewport2DException);

        /**
        Imposta il viewport.
        orig_lx e orig_ly = coordinate del punto in coordinate logiche che andranno
        a coincidere con il centro fisico del viewport
        logic_width e logic_height=larghezza e altezza del viewport nel sistema logico
        */

        void SetViewport(double orig_lx,double orig_ly,double logic_width,double logic_height) throw (Viewport2DException);

        /**Imposta il viewport impostando le coordinate del rettangolo nel riferimento logico*/
        void SetViewportRect(double left,double bottom,double right,double top) throw (Viewport2DException);

        /**Esegue una traslazione
        il punto di coordinate logiche logic_x,logic_y andr� a coincidere con il
        pounto fisico phys_x phys_y
        */
        void Pan(double logic_x,double logic_y,double phys_x,double phys_y);

        /**Esegue lo zoom
        logic_len � la misura in unit� logiche di quanto viene ingrandito o ristretto il viewport
        mantenendo l'aspect ratio corrente
        */
        void Zoom(double logic_len) throw (Viewport2DException);

        /**Imposta la larghezza fisica del viewport*/
        void SetPhysWidth(double fw) throw (Viewport2DException);
        /**Imposta l'altezza fisica*/
        void SetPhysHeight(double fh) throw (Viewport2DException);

        //trasforma da coordinare fisiche a logiche
        double GetLogicX(double phys_x);
        double GetLogicY(double phys_y);

        //trasforma da unit� fisiche a logiche
        double ToLogicUnitsX(double phys_len);
        double ToLogicUnitsY(double phys_len);
        //da unit� lotgiche a fisiche
        double ToPhysUnitsX(double logic_len);
        double ToPhysUnitsY(double logic_len);

        //trasforma da coordinate logiche a fisiche
        double GetPhysX(double logic_x);
        double GetPhysY(double logic_y);

        /**Restituisce la larghezza logica*/
        double GetLogicWidth();
        /**Restituisce la larghezza fisica*/
        double GetLogicHeight();
        /**Restituisce la larghezza fisica*/
        double GetPhysWidth();
        /**Restituisce l'altezza fisica*/
        double GetPhysHeight();
        /**Restituisce la X logica del centro del viewport*/
        double GetLogicCenterX();
        /**Restituisce la Y logica del centro del viewport*/
        double GetLogicCenterY();
        /**Restituisce l'aspect ratio (larghezza/altezza)*/
        double GetLogicAspectRatio();
        double GetPhysAspectRatio();
        /**Aggiunge un bookmark della posizione e zoom correnti
        restituisce l'id del bookmark da usare per il ripristino
        */
        int AddBookmark();
        /**Ripristina una posizione salvata*/
        void RestoreBookmark(int bookmark) throw (Viewport2DException);
        /**Rimouve un bookmark*/
        void RemoveBookmark(int bookmark) throw (Viewport2DException);
        /**Elimina tutti i bookmark*/
        void ClearBookmarks();

    };
};

#endif // VIEWPORT2D_H_INCLUDED
