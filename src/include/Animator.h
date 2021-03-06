/*   
 * Parametric surfaces screen saver
 * copyright (c) 2010 by Leonardo Berti
 *
 *
 * File:   Animator.h
 * Author: Leonardo Berti
 *
 * Created on 2 novembre 2010, 23.21
 */

#ifndef ANIMATOR_H
#define	ANIMATOR_H

#include <vector>
#include "SurfaceFactory.h"
#include "FunctionGrid.h"
#include "3dengine/3dengine.h"

using namespace std;

enum AnimMode {
    ANIM_NORMAL, ANIM_BLENDING, ANIM_FADE, ANIM_EXIT

};

//istruzioni programma di animazione

enum AnimCommand {
    MAKE_RANDOM, //crea una superficie random
    MAKE_SURFACE, //crea la superficie specificata dall'argomento
    KEEP_CURRENT_TYPE, //la prossima superficie è dello stesso tipo di quella attuale
};

//una istruzione del programma di animazione
//il programma di animazione è costituito da una sequenza di AnimInstruction

class AnimInstruction {
public:

    AnimCommand command; //comando
    int intParam; //valore argomento del comando
};

//programma di animazione

class AnimProgram {
private:
    int ip; //istruction pointer
    vector<AnimInstruction> instructions;

public:

    AnimProgram() : ip(0) {
    }

    virtual ~AnimProgram() {
        instructions.clear();
    }

    virtual

    AnimInstruction* getNextInstruction() {
        if (ip >= instructions.size()) return 0;
        else return &instructions[ip++];
    }

    void restart() {
        ip = 0;
    }

    void pushInstruction(AnimCommand command, int arg) {

        AnimInstruction inst;
        inst.command = command;
        inst.intParam = arg;
        instructions.push_back(inst);
    }

    int getIpIndex() {
        return ip;
    }
};

/**
 * Esegue l'animazione delle superfici (rotazione e creazione)
 * usando un programma di animazione che determina quale superficie
 * scegliere ad ogni step
 */
class Animator {
private:

    SurfaceFactory* factory;
    FunctionGrid* f1; //superficie iniziale
    FunctionGrid* f2; //superficie finale
    //FunctionGrid* finterp; //superficie intermedia interpolata
    FunctionGrid* currentSurface; //superficie corrente
    FunctionGrid* nextSurface; //superficie successiva
    FunctionGrid* startSurface;
    int tilew, tileh;
    int step;
    int loops;
    int step_interp;
    int loops_interp;
    float r; //fattore di interpolazione fra superfici : Sn+1(x,y,z)=Sn(x,y,z)*r+(1-r)*Next(x,y,z)
    float r_step; //step fattore di interpolazione r
    float r_step_init; //r_step inizio interpolazione
    float r_step_inc; //incremento di r_step ad ogni ciclo   
    bool firstLoop;
    AnimMode animMode;
    L3DEngine* engine3d;
    AnimProgram* animProgram;
    string blendName;

    void execute(AnimInstruction* instr);
    void makeProgram();
    void initialize();

public:

    Animator(L3DEngine* engine3d, int tilew, int tileh);

    virtual ~Animator();
    bool update();
    const char* getCurrentSurfaceName() const;

    /**
     * Velocità rotazione (valore default 1.8)
     * @param deg_per_cycle
     */
    void setRotSpeed(float deg_per_cycle);

    /**
     * Velocità gradiente colore (valore default 16)
     */
    void setColorGradientSpeed(int colStep);

    /**
     * Cicli prima di passare a nuova superficie (valore di default 80)
     * @param cycles
     */
    void setPersistCycles(int cycles);


};

#endif	/* ANIMATOR_H */

