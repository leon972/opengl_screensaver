/**************************************
 Punto materiale
 soggetto a forze impulsive
 **************************************/

/* 
 * File:   mass_point.h
 * Author: Leonardo Berti
 *
 * Created on 14 febbraio 2011, 21.36
 */

#ifndef MASS_POINT_H
#define	MASS_POINT_H

#include "math/mathdefs.h"
#include "math/vectors.h"

namespace eng {

    using namespace mathengine;

    /**
     *Punto materiale
     * entità puntiforme dotata di massa
     */
    class MassPoint {
    protected:

        //velocità
        VECTOR3D velocity;
        //massa
        real mass;
        //forza
        VECTOR3D_PTR force;
        //posizione
        VECTOR3D position;

    public:

        /**
         * Crea un punto materiale
         * @param mass massa
         */
        MassPoint(real mass);

        /**
         * Crea un punto materiale
         * @param mass massa
         * @param initial_pos posizione iniziale
         * @param initial_velocity velocità iniziale
         */
        MassPoint(const real mass, const VECTOR3D &initial_pos, const VECTOR3D &initial_velocity);

        /**
         * Imposta la massa
         * @param mass
         */
        void SetMass(const real mass);

        /**
         * Acquisisce la massa
         * @param position
         */
        real GetMass() const;

        /**
         * Imposta la posizione
         * @param position
         */
        void SetPosition(const VECTOR3D &position);

        /**
         * Acquisisce la posizione
         * @param velocity
         */
        void GetPosition(VECTOR3D &position) const;

        /**
         * Restituisce la posizione
         * @return
         */
        VECTOR3D GetPosition() const;

        /**
         * Imposta la velocità dell particella
         * @param velocity
         */
        void SetVelocity(const VECTOR3D &velocity);

        /**
         * Acquisisce la velocità attuale della particella
         * @param dest_velocity
         */
        void GetVelocity(VECTOR3D &dest_velocity) const;

        /**
         * Restituisce la velocità
         * @param dest_force
         */
        VECTOR3D GetVelocity() const;

        /**
         * Imposta la forza che agisce sul punto materiale
         * @param force
         */
        void SetForce(const VECTOR3D_PTR force);

        /**
         * Restituisce la forza
         * @param dest_force
         */
        VECTOR3D_PTR GetForce() const;

        /**
         * Acquisisce la forza
         * @param dest_force usato come parametro di ritorno del valore della forza
         */
        void GetForce(VECTOR3D &dest_force) const;

        /**
         *Calcola l'energia cinetica dell particella
         */
        real GetKineticEnergy() const;

        /**
         * Calcola la quantità di moto
         * @param dt
         */
        void GetMomentum(VECTOR3D& dest_momentum) const;

        VECTOR3D GetMomentum() const;

        /**
         *Calcola il momento angolare rispetto ad O
         */
        void GetAngularMomentum(VECTOR3D &dest_ang_momentum, const VECTOR3D &r0) const;
        
        VECTOR3D GetAngularMomentum(const VECTOR3D &r0) const;

        /**
         *Aggiorna il punto materiale considerando un incremento di tempo dt
         *durante il quale la forza applicata viene considerata costante
         */
        void Update(const real dt);

        /**
         *Applica un impulso ed aggiorna la posizione e la velocità
         */
        void ApplyImpulse(const VECTOR3D &impulse);

    };

};

#endif	/* MASS_POINT_H */

