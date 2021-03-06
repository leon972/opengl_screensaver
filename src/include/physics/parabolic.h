/**
 Moto parabolico (soluzione esatta)
 * Code by Leonardo Berti (c) 2011
 */

#ifndef PARABOLIC_H
#define PARABOLIC_H

#include "math/mathdefs.h"
#include "math/vectors.h"

namespace eng {

    using namespace mathengine;
    
    /**
     *Calcola la posizione di un punto materiale nello spazio ad un certo tempo t
     * a partire dalla posizione iniziale,dalla velocità iniziale e dalla accelerazione
     */
    class ParabolicMotion {

    private:

        /**
         *Accelerazione
         */
        VECTOR3D a;
        /**
         *Velocità  iniziale
         */
        VECTOR3D v0;
        /**
         *posizione iniziale
         */
        VECTOR3D p0;

    public:

        /**
         * Determina la "gittata" del moto parabolico
         * @param theta_rad angolo in radianti fra la velocità iniziale v0
         * e la superficie (inclinata di beta_rad rispetto all'orizzontale)
         * @param beta_rad angolo di inclinazione del piano rispetto all'orizzontale (se il terreno è orizzontale settare su 0)
         * @param v0 velocità iniziale
         * @param g accelerazione di gravità
         * @return la gittata (misurata sul piano inclinato e non sull'orizzontale)
         */
        static double getRange(double theta_rad,double beta_rad,double v0,double g);

        ParabolicMotion();

        /**
         * Crea il solutore del moto parabolico
         * @param x0 x iniziale
         * @param y0 y iniziale
         * @param z0 z iniziale
         * @param ax comp. x dell'accelerazione
         * @param ay comp. y dell'accelerazione
         * @param az comp. z dell'accelerazione
         * @param vx comp.x della velocitÃ  iniziale
         * @param vy      y
         * @param vz      z
         */
        ParabolicMotion(const VECTOR3D &initial_position,const VECTOR3D &initial_velocity,const VECTOR3D &acceleration);

        /**
         * Imposta la posizione iniziale
         * @param x0
         * @param y0
         * @param z0
         */
        void SetInitialPosition(const VECTOR3D &position);

        /**
         * Acquisisce la posizione iniziale
         * @param x0
         * @param y0
         * @param z0
         */
        VECTOR3D GetInitialPosition() const;

        /**
         * Imposta la velocità iniziale
         * @param v0x
         * @param v0y
         * @param v0z
         */
        void SetInitialVelocity(const VECTOR3D &velocity);

        /**
         * Imposta l'accelerazione
         * @param ax
         * @param ay
         * @param az
         */
        void SetAcceleration(const VECTOR3D &acceleration);

        /**
         *Acquisisce la posizione all'istante t
         * @param position parametro out che restituisce la posizione
         * @param t tempo
         */
        void getCurrentPosition(VECTOR3D_PTR position,double t);

        /**
         * Acquisisce la velocità all'istante t
         * @param velocity velocità all'istante t
         * @param t tempo
         */
        void getCurrentVelocity(VECTOR3D_PTR velocity,double t);
       
    };
};

#endif
