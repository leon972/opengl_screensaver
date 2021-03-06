/* 
 * File:   I3DSurface.h
 * Author: Leonardo Berti
 * interfaccia superficie
 * Created on 2 novembre 2010, 19.02
 */

#ifndef I3DSURFACE_H
#define	I3DSURFACE_H

#include "math/vectors3.h"

using namespace mathengine;

/**
 *Interfaccia per le superfici parametriche
 */
class I3DSurface
{
    public:

        //valori del parametro mode
        static const int FN_NORMAL=0x0;
        //questa opzione è usata nella interpolazione fra superfici
        static const int FN_USE_SCALE_FACTOR=0x1; //moltiplica il risultato per il valore della scala e somma al risultato già esistente

        /**
         * Calcola il punto dello spazio che corrisponde alle coordinate u,v
         * @param vertices punto con 3 coordinate x,y,z
         * @param u parametro u
         * @param v parametro v
         */
        virtual void calcPoint(double* point,double u,double v) const=0;
       
        /**
         * restituisce la coordinata u iniziale
         */
        virtual double getU1() const=0;

        /**
         *restituisce la v iniziale
         */
        virtual double getV1() const=0;
        /**
         *passo u
         */
        virtual double getStepU() const=0;
        /**
         *passo v
         */
        virtual double getStepV() const=0;

        /**
         traslazione
         */
        virtual CHVector3<double> getTranslation() const=0;
        /**
         nome superficie
         */
        virtual const char* getName() const=0;

};

#endif	/* I3DSURFACE_H */

