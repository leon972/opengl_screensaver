/*  
 * Parametric surfaces screen saver
 * copyright (c) 2010 by Leonardo Berti
 *
 * File:   Animator.cpp
 * Author: Leonardo Berti
 * 
 * Created on 2 novembre 2010, 23.21
 */

#include "Animator.h"

/*
 SurfaceFactory* factory;
    FunctionGrid* f1; //superficie iniziale
    FunctionGrid* f2; //superficie finale
    FunctionGrid* finterp; //superficie intermedia interpolata
    FunctionGrid* currentSurface; //superficie corrente
    FunctionGrid* nextSurface;//superficie successiva
    int step;
    int loops;
    L3DEngine* engine3d;

 */

Animator::Animator(L3DEngine* engine3d, int tilew, int tileh) : engine3d(engine3d), f1(0), f2(0), tilew(tilew), tileh(tileh), animProgram(0), currentSurface(0), nextSurface(0), factory(0) {

    initialize();
}

void Animator::initialize() {

    factory = new SurfaceFactory(tilew, tileh);
    f1 = new FunctionGrid(tilew, tileh);
    f2 = new FunctionGrid(tilew, tileh);
    //finterp = new FunctionGrid(tilew, tileh);
    f1->Add(f1);
    f2->Add(f2);
    factory->makeRandomSurface(*f1);
    factory->makeRandomSurface(*f2);

    //DEBUG
    //factory->makeSurface(*f1,SURF_WEIRD_BOY);
   // factory->makeSurface(*f2,SURF_WEIRD_BOY);

    currentSurface = f1;
    currentSurface->Add(currentSurface);
    //inizializza il colore (nota:se non viene inizializzato la sup. non sarà visibile)
    currentSurface->generateColorGradient();
    currentSurface->setColorStep(16);
    engine3d->AddChildNode(currentSurface);
    nextSurface = f2;
    nextSurface->Add(nextSurface);
    r_step_init = 0.0001; //r_step iniziale     //0.0001
    r_step = r_step_init; //step interpolazione
    r_step_inc = 0.00001; //incremento di r_step //0.00001
    step_interp = 0;
    firstLoop = true;
    animMode = ANIM_NORMAL;
    loops = 80; //800 //numero di cicli prima di passare alla superficie successiva
    loops_interp = 6; //6 //numero di cicli prima di incrementare r e passare alla successiva interpolazione
    step = loops;
    makeProgram(); //crea il programma inziale di animazione   

}

/**
 * Velocità rotazione (valore default 1.8)
 * @param deg_per_cycle
 */
void Animator::setRotSpeed(float deg_per_cycle) {
    if (factory) factory->setRotSpeed(deg_per_cycle);
}

/**
 * Velocità gradiente colore (valore default 16)
 */
void Animator::setColorGradientSpeed(int colStep) {

    if (currentSurface) currentSurface->setColorStep(abs(colStep));
}

/**
 * Cicli prima di passare a nuova superficie (valore di default 80)
 * @param cycles
 */
void Animator::setPersistCycles(int cycles) {
    loops = cycles;
}

Animator::~Animator() {

    SAFE_DELETE(f2);
    SAFE_DELETE(f1);
    SAFE_DELETE(factory);
    SAFE_DELETE(animProgram);
}

/**
 *Esegue una istruzione del programma di animazione
 */
void Animator::execute(AnimInstruction* instr) {

    if (instr == 0) return;

    switch (instr->command) {

        case MAKE_RANDOM:
            //crea una superficie casuale
            factory->makeRandomSurface(*nextSurface);
            break;
        case MAKE_SURFACE:
            //crea un superficie specifica
            factory->makeSurface(*nextSurface, instr->intParam);
            break;

        case KEEP_CURRENT_TYPE:

            //crea una superficie dello stesso tipo di quella corrente
            factory->makeSameTypeSurface(*nextSurface);
            break;
    }

}

/**
 *Crea un programma di animazione
 */
void Animator::makeProgram() {

    SAFE_DELETE(animProgram);

    int prg = rand() % 12;

    animProgram = new AnimProgram();

    const bool debug = false;

    if (debug) {

        //DEBUG
        for (int i = 0; i < 5; i++) {
            animProgram->pushInstruction(MAKE_SURFACE, SURF_WEIRD_BOY);
        }

        return;

        //settare su -1 quando si vuol provare una sup. specifica
        prg = -1;

    }
   
    // cout<<"program="<<prg<<endl;

    switch (prg) {

        default:

            //sup. casuali
            for (int i = 0; i < 5; i++) {
                animProgram->pushInstruction(MAKE_RANDOM, 0);
            }

            break;
        case 1:

            for (int i = 0; i < 3; i++) {

                animProgram->pushInstruction(MAKE_RANDOM, 0);
                animProgram->pushInstruction(KEEP_CURRENT_TYPE, 0);
                animProgram->pushInstruction(KEEP_CURRENT_TYPE, 0);
            }

            break;

        case 2:

            animProgram->pushInstruction(MAKE_SURFACE, SURF_SPIRAL);
            animProgram->pushInstruction(MAKE_SURFACE, SURF_HORN);
            animProgram->pushInstruction(MAKE_SURFACE, SURF_SPIRAL);
            animProgram->pushInstruction(KEEP_CURRENT_TYPE, SURF_SPHERE);
            animProgram->pushInstruction(MAKE_SURFACE, SURF_WAVES);
            animProgram->pushInstruction(KEEP_CURRENT_TYPE, 0);
            animProgram->pushInstruction(KEEP_CURRENT_TYPE, 0);
            animProgram->pushInstruction(MAKE_SURFACE, SURF_PLANE);
            animProgram->pushInstruction(MAKE_RANDOM, 0);
            animProgram->pushInstruction(MAKE_SURFACE, SURF_WEIRD_TORUS);
            animProgram->pushInstruction(MAKE_SURFACE, SURF_WEIRD_TORUS);
            animProgram->pushInstruction(MAKE_SURFACE, SURF_HORN);
            animProgram->pushInstruction(MAKE_SURFACE, SURF_SPHERE);

            break;

        case 3:

            animProgram->pushInstruction(MAKE_SURFACE, SURF_KLEIN_BOTTLE);
            animProgram->pushInstruction(KEEP_CURRENT_TYPE, 0);
            animProgram->pushInstruction(MAKE_SURFACE, SURF_MOBIUS_STRIP);
            animProgram->pushInstruction(KEEP_CURRENT_TYPE, 0);
            animProgram->pushInstruction(MAKE_SURFACE, SURF_KLEIN_BOTTLE);
            animProgram->pushInstruction(MAKE_SURFACE, SURF_KLEIN_BOTTLE2);
            animProgram->pushInstruction(MAKE_SURFACE, SURF_ENNEPER);
            animProgram->pushInstruction(KEEP_CURRENT_TYPE, 0);
            animProgram->pushInstruction(KEEP_CURRENT_TYPE, 0);
            animProgram->pushInstruction(MAKE_SURFACE, SURF_STEINER_ROMAN);
            animProgram->pushInstruction(MAKE_SURFACE, SURF_MOBIUS_STRIP);
            animProgram->pushInstruction(MAKE_SURFACE, SURF_BOYS);
            animProgram->pushInstruction(KEEP_CURRENT_TYPE, 0);
            animProgram->pushInstruction(MAKE_RANDOM, 0);
            animProgram->pushInstruction(MAKE_SURFACE, SURF_STEINER_ROMAN);
            animProgram->pushInstruction(MAKE_SURFACE, SURF_SPHERE);
            animProgram->pushInstruction(MAKE_SURFACE, SURF_KLEIN_BOTTLE);

            break;

        case 4:

            animProgram->pushInstruction(MAKE_SURFACE, SURF_PLANE);
            animProgram->pushInstruction(KEEP_CURRENT_TYPE, 0);
            animProgram->pushInstruction(MAKE_RANDOM, 0);
            animProgram->pushInstruction(MAKE_SURFACE, SURF_KLEIN_BOTTLE);
            animProgram->pushInstruction(MAKE_SURFACE, SURF_PLANE);
            animProgram->pushInstruction(MAKE_SURFACE, SURF_SPHERE);
            animProgram->pushInstruction(MAKE_SURFACE, SURF_DINI);
            animProgram->pushInstruction(MAKE_SURFACE, SURF_SPIRAL);
            animProgram->pushInstruction(MAKE_SURFACE, SURF_DINI);
            animProgram->pushInstruction(MAKE_SURFACE, SURF_DINI);
            animProgram->pushInstruction(MAKE_RANDOM, 0);
            animProgram->pushInstruction(MAKE_SURFACE, SURF_PLANE);

            break;

        case 5:

            animProgram->pushInstruction(MAKE_RANDOM, 0);
            animProgram->pushInstruction(KEEP_CURRENT_TYPE, 0);
            animProgram->pushInstruction(KEEP_CURRENT_TYPE, 0);
            animProgram->pushInstruction(MAKE_SURFACE, SURF_WAVES);
            animProgram->pushInstruction(KEEP_CURRENT_TYPE, 0);
            animProgram->pushInstruction(KEEP_CURRENT_TYPE, 0);
            animProgram->pushInstruction(MAKE_SURFACE, SURF_PLANE);
            animProgram->pushInstruction(MAKE_SURFACE, SURF_HORN);
            animProgram->pushInstruction(KEEP_CURRENT_TYPE, 0);
            animProgram->pushInstruction(KEEP_CURRENT_TYPE, 0);
            animProgram->pushInstruction(MAKE_SURFACE, SURF_HELIX);
            animProgram->pushInstruction(MAKE_SURFACE, SURF_DINI);
            animProgram->pushInstruction(MAKE_RANDOM, 0);
            animProgram->pushInstruction(MAKE_SURFACE, SURF_SPIRAL);
            animProgram->pushInstruction(MAKE_SURFACE, SURF_SPHERE);
            animProgram->pushInstruction(KEEP_CURRENT_TYPE, 0);
            animProgram->pushInstruction(MAKE_SURFACE, SURF_SPIRAL);
            animProgram->pushInstruction(MAKE_RANDOM, 0);
            animProgram->pushInstruction(MAKE_RANDOM, 0);

            break;

        case 6:

            animProgram->pushInstruction(MAKE_RANDOM, 0);
            animProgram->pushInstruction(KEEP_CURRENT_TYPE, 0);
            animProgram->pushInstruction(MAKE_SURFACE, SURF_SHELL);
            animProgram->pushInstruction(KEEP_CURRENT_TYPE, 0);
            animProgram->pushInstruction(KEEP_CURRENT_TYPE, 0);
            animProgram->pushInstruction(KEEP_CURRENT_TYPE, 0);
            animProgram->pushInstruction(MAKE_SURFACE, SURF_PUMPKIN);
            animProgram->pushInstruction(MAKE_SURFACE, SURF_WEIRD);
            animProgram->pushInstruction(KEEP_CURRENT_TYPE, 0);
            animProgram->pushInstruction(KEEP_CURRENT_TYPE, 0);
            animProgram->pushInstruction(MAKE_SURFACE, SURF_SPHERE);
            animProgram->pushInstruction(MAKE_SURFACE, SURF_CYLINDER);
            animProgram->pushInstruction(MAKE_SURFACE, SURF_SPHERE);
            animProgram->pushInstruction(MAKE_SURFACE, SURF_WEIRD_POLAR1);
            animProgram->pushInstruction(KEEP_CURRENT_TYPE, 0);
            animProgram->pushInstruction(KEEP_CURRENT_TYPE, 0);
            animProgram->pushInstruction(MAKE_SURFACE, SURF_SHELL);
            animProgram->pushInstruction(KEEP_CURRENT_TYPE, 0);
            animProgram->pushInstruction(MAKE_RANDOM, 0);
            animProgram->pushInstruction(KEEP_CURRENT_TYPE, 0);


            break;

        case 7:

            animProgram->pushInstruction(MAKE_SURFACE, SURF_HILLS);
            animProgram->pushInstruction(KEEP_CURRENT_TYPE, 0);
            animProgram->pushInstruction(KEEP_CURRENT_TYPE, 0);
            animProgram->pushInstruction(MAKE_SURFACE, SURF_WAVES);
            animProgram->pushInstruction(MAKE_SURFACE, SURF_HILLS);
            animProgram->pushInstruction(MAKE_SURFACE, SURF_WAVES);
            animProgram->pushInstruction(MAKE_SURFACE, SURF_HILLS);

            break;

        case 8:

            animProgram->pushInstruction(MAKE_SURFACE, SURF_ROTO_SOLID);
            animProgram->pushInstruction(KEEP_CURRENT_TYPE, 0);
            animProgram->pushInstruction(KEEP_CURRENT_TYPE, 0);
            animProgram->pushInstruction(MAKE_SURFACE, SURF_ROTO_DAMP);
            animProgram->pushInstruction(KEEP_CURRENT_TYPE, 0);
            animProgram->pushInstruction(KEEP_CURRENT_TYPE, 0);
            animProgram->pushInstruction(MAKE_RANDOM, 0);
            animProgram->pushInstruction(KEEP_CURRENT_TYPE, 0);
            animProgram->pushInstruction(KEEP_CURRENT_TYPE, 0);
            animProgram->pushInstruction(MAKE_SURFACE, SURF_WEIRD);
            animProgram->pushInstruction(MAKE_SURFACE, SURF_HELIX);
            animProgram->pushInstruction(MAKE_SURFACE, SURF_HORN);
            animProgram->pushInstruction(KEEP_CURRENT_TYPE, 0);
            animProgram->pushInstruction(MAKE_SURFACE, SURF_WEIRD_TORUS);
            animProgram->pushInstruction(KEEP_CURRENT_TYPE, 0);
            animProgram->pushInstruction(KEEP_CURRENT_TYPE, 0);
            animProgram->pushInstruction(MAKE_SURFACE, SURF_ROTO_SOLID);
            animProgram->pushInstruction(MAKE_SURFACE, SURF_ROTO_DAMP);
            animProgram->pushInstruction(MAKE_SURFACE, SURF_ROTO_SOLID);

            break;

        case 9:

            animProgram->pushInstruction(MAKE_SURFACE, SURF_WEIRD_BOY);
            animProgram->pushInstruction(KEEP_CURRENT_TYPE, 0);
            animProgram->pushInstruction(KEEP_CURRENT_TYPE, 0);
            animProgram->pushInstruction(MAKE_SURFACE, SURF_PLANE);
            animProgram->pushInstruction(MAKE_SURFACE, SURF_WEIRD_BOY);
            animProgram->pushInstruction(KEEP_CURRENT_TYPE, 0);
            animProgram->pushInstruction(MAKE_SURFACE, SURF_CYLINDER);
            animProgram->pushInstruction(MAKE_SURFACE, SURF_WEIRD_BOY);
            animProgram->pushInstruction(MAKE_SURFACE, SURF_CYLINDER);
            animProgram->pushInstruction(MAKE_SURFACE, SURF_PLANE);
            animProgram->pushInstruction(MAKE_SURFACE, SURF_HELIX);
            animProgram->pushInstruction(MAKE_SURFACE, SURF_WEIRD_BOY);
            animProgram->pushInstruction(KEEP_CURRENT_TYPE, 0);
            animProgram->pushInstruction(MAKE_SURFACE, SURF_ROTO_DAMP);
            animProgram->pushInstruction(MAKE_SURFACE, SURF_WEIRD_BOY);
            animProgram->pushInstruction(KEEP_CURRENT_TYPE, 0);
            animProgram->pushInstruction(MAKE_SURFACE, SURF_ROTO_SOLID);
            animProgram->pushInstruction(MAKE_SURFACE, SURF_WEIRD_BOY);
            animProgram->pushInstruction(MAKE_SURFACE, SURF_CYLINDER);


            break;


        case -1:
            //usato per DEBUG
            break;


    }
}

bool Animator::update() {

    switch (animMode) {

        case ANIM_NORMAL:

            if (step++ >= loops) {

                step = 0;
                r_step = r_step_init;
                step_interp = 0;
                r = 0.0;
                animMode = ANIM_BLENDING;

                AnimInstruction* inst = animProgram->getNextInstruction();

                if (inst == 0) {
                    //se ha terminato il programma ne crea un altro
                    makeProgram();
                    inst = animProgram->getNextInstruction();
                }

                //cout<<"ip="<<animProgram->getIpIndex()<<endl;

                //esegue l'istruzione del programma di animazione
                execute(inst);

                //blending
                blendName.assign(currentSurface->getCurrentSurfaceName());
                blendName += " -> ";
                blendName += nextSurface->getCurrentSurfaceName();

                currentSurface->setCurrentSurfaceName(blendName.c_str());
            }

            break;
        case ANIM_BLENDING:

            if (step_interp++ >= loops_interp) {

                step_interp = 0;

                r += r_step;

                r_step += r_step_inc;

                if (r >= 0.20) {

                    animMode = ANIM_NORMAL;
                    r = 1.0;
                    step = 0;
                    r_step = r_step_init;
                    currentSurface->setCurrentSurfaceName(nextSurface->getCurrentSurfaceName());
                }

                //esegue l'interpolazione fra le due superfici
                currentSurface->blend(*nextSurface, r);
            };

            break;

        case ANIM_FADE:

            break;
        case ANIM_EXIT:

            break;
    }

    if (currentSurface->rotateColors()) {
        //genera un nuovo colore nel gradiente
        currentSurface->rotateColorGradient();
    }

    currentSurface->rotate();

    return true;
}

const char* Animator::getCurrentSurfaceName() const {

    if (currentSurface) return currentSurface->getCurrentSurfaceName();

}



