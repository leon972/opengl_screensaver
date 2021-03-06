/*
 * Formule per moto di un punto materiale
 * File:   newton.h
 * Author: Leonardo Berti
 *
 * Created on 14 febbraio 2011, 23.27
 */

#ifndef NEWTON_H
#define	NEWTON_H

#include "math/vectors.h"
#include "math/mathdefs.h"

namespace eng {

    using namespace mathengine;

    /**
     * F=m*a
     * @param m
     * @param a
     * @return
     */
    inline VECTOR3D GetForce(const real m,const VECTOR3D &a) {

        VECTOR3D r(m*a.x,m*a.y,m*a.z);
        return r;
    }

    /**
     * Quantità di moto di un punto materiale con massa mass e velocità velocity
     * @param mass massa 
     * @param velocity velocità
     * @return m*v
     */
    inline VECTOR3D GetMomentum(const real mass,const VECTOR3D &velocity) {
        
        VECTOR3D r(mass*velocity.x,mass*velocity.y,mass*velocity.z);
        return r;
        
    }

    /**
     * Momento angolare di un punto materiale di massa mass e velocità velocity
     * @param mass massa
     * @param velocity velocità
     * @param r0 posizione punto di riferimento (R-O)
     * @return m r0 ^ velocity
     */
    inline VECTOR3D GetAngularMomentum(const real mass,const VECTOR3D &velocity,const VECTOR3D &r0) {

        VECTOR3D dest_ang_momentum;
        
        crossProduct3Ex(&dest_ang_momentum, r0, velocity);
        dest_ang_momentum.x *= mass;
        dest_ang_momentum.y *= mass;
        dest_ang_momentum.z *= mass;

        return dest_ang_momentum;
    }

    
    /**
     * Energia cinetica di un punto materiale
     * @param mass massa
     * @param velocity velocità
     * @return l'energia cinetica 1/2 * mass * velocity * velocity
     */
    inline real GetKineticEnergy(const real mass,const VECTOR3D &velocity) {
        
        return 0.5*mass*(velocity.x*velocity.x+velocity.y*velocity.y+velocity.z*velocity.z);
        
    }
    
    /**
     * potenza
     * @return mass * acceleration * velocity
     */
    inline real GetPower(const real mass,const VECTOR3D &acceleration,const VECTOR3D velocity) {
        
        return mass * dotProduct3(acceleration,velocity);
        
    }

    
    /**
     * Restituisce la poszione di un punto che si muove di moto rettilineo unif. accelerato
     * dopo un certo tempo a partire dall'istante iniziale
     * @param t tempo misurato a partire da t0 istante iniziale
     * @param a accelerazione
     * @param v0 velocità all'istante t0
     * @param s0 posizione all'istante t0
     * @return la posizione all'istante t
     */
    VECTOR3D GetDisplacement(const real t,const VECTOR3D &a,const VECTOR3D &v0,const VECTOR3D &s0);

    /**
     *Calcola il tempo impiegato per raggiungere una certa posizione
     * @param s posizione all'istante t
     * @param a accelerazione
     * @param v0 velocità iniziale
     * @param s0 posizione iniziale
     * @param dest_time1 rende la prima soluzione
     * @param dest_time2 rende la seconda soluzione
     *
     */
    void GetTime(real &dest_time1,real &dest_time2,const real s,const real a,const real v0,const real s0) throw (InvalidArgumentVideoException);
    

};

#endif	/* NEWTON_H */

