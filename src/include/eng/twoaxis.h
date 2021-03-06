/************************************************
Modello dinamico (molto) approssimato
per veicolo a 2 assi nel piano longitudinale
Code by Leonardo Berti - 2009
*************************************************/

#ifndef _TWOAXIS_VEHICLE_
#define _TWOAXIS_VEHICLE_

#ifndef MATHDEFS_H_INCLUDED

#define M_CONV 0.01745329251994329577
#define M_CONV1 57.2957795130823208768

//conversione da gradi in radianti
#define DEG_TO_RAD(x) x*M_CONV
//conversione da radianti in gradi
#define RAD_TO_DEG(x) x*M_CONV1

#endif

namespace two_axis_vehicle
{

    static const float g=9.81; //acc. di gravit� sulla terra
    static const float rair=1.20; //densit� dell'aria [kg/m^3] (si suppone fissa)


//tipo motore
typedef enum
{
    TWO_STROKES=2,  //motore 2 tempi
    FOUR_STROKES=4  //motore 4 tempi

} NSTROKES_TYPE;

typedef enum
{
    C_OTTO=0,       //ciclo Otto
    C_DIESEL=1,     //ciclo Diesel

} CYCLE_TYPE;


/**
Definizione caratteristiche del motore
*/

class EngineDef
{
    protected:

    public:
    virtual ~EngineDef() {}

    static float rpm_to_omega(float rpm);

    static float omega_to_rpm(float omega);

    /**Restituisce la potenza [W] assegnata la parzializzazione e la velocit� di rotazione [rad/s] */
    virtual float GetPower(float throttle,float omega) const=0;
    /**Restituisce la coppia [Nm]*/
    virtual float GetTorque(float throttle,float omega) const=0;
    /**Restituisce il momento di inerzia del motore (costante) [kg * m^2]*/
    virtual float GetMomentOfInertia() const=0;
    /**Restituisce la coppia resistente dovuta agli attriti interni (freno motore) [Nm]*/
    virtual float GetDampingTorque(float angular_velocity) const=0;
    /**Restituisce la minima velocit� angolare di rotazione necessaria a mantenerlo in moto [rad/s]*/
    virtual float GetMinAngularVelocity() const=0;
    /**Restituisce il coefficiente di riempimento del cilindro
    in base al carico (da 0 a 1) e al alla velocit� di rotazione*/
    virtual float GetLv(float c,float omega) const=0;
    /**Restituisce il numero di giri che corrisponde alla potenza massima [giri/1']*/
    virtual float GetMaxRPM() const=0;
    /**Restituisce la cilindrata in cc*/
    virtual float GetDisplacement() const=0;
    /**Restituisce il tipo di ciclo*/
    virtual CYCLE_TYPE GetCycleType() const=0;
    /**Restituisce 2 o 4 tempi*/
    virtual NSTROKES_TYPE GetStrokes() const=0;
    /**Restituisce la potenza massima*/
    virtual float GetMaxPower() const=0;
    /**Restituisce la dosatura (portata massa aria/portata massa combustibile) in funzione della velocit� di rotazione normalizzata rispetto
    alla velocit� di rotazione massima
    */
    virtual float GetAlpha(float wn) const=0;
};

class BadParamsVideoException
{
    private:

    const char* msg;

    public:
    BadParamsVideoException(const char* msg);
    const char* GetMessage() const;
};


class EngineVideoException
{
    private:

    const char* msg;

    public:
    EngineVideoException(const char* msg);
    const char* GetMessage() const;
};

/**Carico applicato al motore
nota si puo' imporre o una coppia resistente o una velocit�
ma non l'una e l'altra
*/
class EngineLoad
{
    public:
    virtual ~EngineLoad() {}
    /**Restituisce la coppia [Nm] che si oppone al motore*/
    virtual float GetTorque() const=0;
    /**Restituisce la velocit� imposta al motore*/
    virtual float GetOmega() const=0;
};

/**
Definizione interfaccia di controllo e monitoraggio del motore
*/
class EngineControl:public EngineDef
{
    public:
    virtual ~EngineControl() {
    };

    /**Accende il motore*/
    virtual void Start() throw(EngineVideoException)=0;
    /**Spenge il motore*/
    virtual void Stop() throw(EngineVideoException)=0;
    /**Restituisce true se � acceso*/
    virtual bool IsStarted()=0;
    /**Restituisce la velocit� di rotazione corrente [giri/1']*/
    virtual float GetRPM()=0;
    /**Restituisce la velocit� di rotazione in [rad/s]*/
    virtual float GetOmega()=0;
    /**Imposta a parzializzazione*/
    virtual void SetThrottle(float alpha)=0;
    /**Restituisce la parzializzazione*/
    virtual float GetThrottle()=0;
    /**Restituisce la potenza erogata [W]*/
    virtual float GetOutputPower()=0;
    /**Restituisce la coppia erogata [Nm] */
    virtual float GetOutputTorque()=0;
    /**Imposta un carico resistente*/
    virtual void ApplyLoad(EngineLoad* load)=0;
};



/**
Ipotetico motore a combustione interna
(versione basata sul coefficiente di riempimento)
*/
class InternalCombustionEngine:public EngineControl
{
    private:

    //parametri usati per determinare il coefficiente di riempimento del cilindro
    float C2,C1,C0; //coefficienti parabole 0=carico 0% 1=carico 50% 3=carico 100%
    float C1_0;
    float mC1;

    protected:

    int nstrokes;  //4=4 tempi 2=2 tempi
    int epsilon;   //2=per motore a 4 tempi, 1 per motore a 2 tempi
    float V;       //cilindrata [cm^3]
    float Hi;      //potere calorifico inferiore del carburante [MJ/kg]
    float as;      //dosatura stechiometrica per il combustibile usato
    float Kp;      //costante [J] che raggruppa tutti i termini considerati
                   //costanti nel calcolo della potenza
    float alpha;   //dosatura (rapporto massa aria/masssa combustibile)
    float lv;      //coefficiente di riempimento
    float Im;      //momento di inerzia [kg*m^2]
    float omega;   //velocit� di rotazione attuale [rad/s]
    float min_omega; //velocit� minima di funzionamento [rad/s]
    float throttle; //parzializzazione corrente da 0 a 1
    CYCLE_TYPE cycle_type; //otto o diesel
    NSTROKES_TYPE nstroke_type; //2 o 4 tempi
    float eg;        //rendimento globale del motore
    float max_rpm;   //velocit� che corrisponde alla pot. massima
    float max_omega;
    float max_Lv_omega; //valore della velocit� angolare che corrisponde al riempimento max. (coppia max)
    float max_Lv; //massimo coeff. di riempimento
    float Pmax;      //potenza massima [W]
    bool started;
    EngineLoad* engine_load;

    void InitializeLvParams() throw (EngineVideoException);

    public:

    virtual ~InternalCombustionEngine();
    /**
    ctype=tipo ciclo
    nt=2 o 4 tempi
    V=cilindrata [cm^3]
    I=momento di inerzia [kg*m^2]
    rpmmax=numero di giri al minuto che corrispondono alla potenza massima
    Pmax=potenza massima [kW] del motore in corrispondenza di rpmmax
    */

    InternalCombustionEngine (CYCLE_TYPE ctype,NSTROKES_TYPE nt,float V,float I,float rpmmax,float Pmax) throw (EngineVideoException);

    /**Restituisce la potenza [W] assengata la parzializzazione e la velocit� di rotazione [giri/1'] */
    float GetPower(float throttle,float omega) const;
    /**Restituisce la coppia*/
    float GetTorque(float throttle,float omega) const;
    /**Restituisce il momento di inerzia del motore*/
    float GetMomentOfInertia() const;
    /**Restituisce la dosatura in base alla velocit� di rotazione*/
    float GetAlpha(float wn) const;
    /**Restituisce la coppia resistente dovuta agli attriti interni (freno motore) [Nm]*/
    float GetDampingTorque(float angular_velocity) const;
    /**Velocit� angolare minima del motore*/
    float GetMinAngularVelocity() const;
    /**Accende il motore*/
    void Start() throw(EngineVideoException);
    /**Spenge il motore*/
    void Stop() throw(EngineVideoException);
    /**Restituisce true se � acceso*/
    bool IsStarted();
    /**Restituisce la velocit� di rotazione corrente [giri/1']*/
    float GetRPM();
    /**Restituisce la velocit� di rotazione in [rad/s]*/
    float GetOmega();
    /**Restituisce il numero di giri che corrisponde alla massima potenza [giri/1']*/
    float GetMaxRPM() const;
    /**Restituisce la cilindrata in cc*/
    float GetDisplacement() const;
    /**Restituisce il tipo di ciclo*/
    CYCLE_TYPE GetCycleType() const;
    /**Restituisce 2 o 4 tempi*/
    NSTROKES_TYPE GetStrokes() const;
    /**Restituisce la potenza massima*/
    float GetMaxPower() const;
    /**Imposta la parzializzazione da 0.0 a 1.0*/
    void SetThrottle(float a);
    /**Restituisce la parzializzazione*/
    float GetThrottle();
    /**Restituisce la potenza erogata [W]*/
    float GetOutputPower();
    /**Restituisce la coppia erogata [Nm] */
    float GetOutputTorque();
    /**Restituisce il coefficiente di riempimento*/
    float GetLv(float c,float omega) const;
    /**Applica un carico al motore*/
    void ApplyLoad(EngineLoad* load);
};

/**
Modello semplificato di motore a combustion interna
ocorre fornire la potenza massima e il corrispondente regime
e la coppia massima e il corrispondente regime.La potenza e coppia
in funzione di omega e alpha sono ottenuti usando una mappatura
*/
class InternalCombustionEngine2:public EngineControl
{
    protected:

    float omega_cmax; //velocit� alla coppia max. [rpm]
    float omega_pmax;//velocit� alla pot. massima [rpm]
    float pmax; //pot. massima [kW]
    float cmax; //coppia massima [Nm]

    int nstrokes;  //4=4 tempi 2=2 tempi
    int epsilon;   //2=per motore a 4 tempi, 1 per motore a 2 tempi
    float V;       //cilindrata [cm^3]
    float Hi;      //pot. calorifico inf. combustibile
    float Im;      //mom. inerzia del motore [kg*m^2]
    float omega;   //velocit� di rotazione attuale [rad/s]
    float min_omega; //velocit� minima di funzionamento [rad/s]
    float throttle; //parzializzazione corrente da 0 a 1
    CYCLE_TYPE cycle_type; //otto o diesel
    NSTROKES_TYPE nstroke_type; //2 o 4 tempi
    float eg;        //rendimento globale del motore
    float A[3],B[3],C[3],D[3]; //coefficienti delle curve 100% (indice 2) amissione,50% ammissione (indice 1),0% (al minimo) indice 0;

    void init();
    //calcola i coeeficienti della curva di 4� grado usato per approssimare la coppia
    void solve(float* a,float* b,float* c,float* d,float omega_cmax,float cmax,float omega_pmax,float pmax) throw (EngineVideoException);

    public:

    /**
    I=momento di inerzia [kg*m^2]
    omega_cmax=velocit� di rotazione in giri/1' che corrisponde alla coppia max
    omega_pmax=velocit� di rotazione in giri/1' che corrisponde alla potenza massima
    cmax=coppia massima [Nm]
    pmax=potenza massima [kW]
    */
    InternalCombustionEngine2(float I,float omega_cmax,float cmax,float omega_pmax,float pmax) throw (EngineVideoException);

    /**Imposta altri parametri (non usati nel calcolo, vengono inseriti solo per compatibilit� con l'interfaccia)
      V=cilindrata cc
      nt=TWO_STROKES=2,  //motore 2 tempi
         FOUR_STROKES=4
      ctype= C_OTTO=0,       //ciclo Otto
             C_DIESEL=1,
      */

    void setExtraParameters(CYCLE_TYPE ctype,NSTROKES_TYPE nt,float V);

     /**Restituisce la potenza [W] assengata la parzializzazione e la velocit� di rotazione [giri/1'] */
    float GetPower(float throttle,float omega) const;
    /**Restituisce la coppia*/
    float GetTorque(float throttle,float omega) const;
    /**Restituisce il momento di inerzia del motore*/
    float GetMomentOfInertia() const;
    /**Restituisce la dosatura in base alla velocit� di rotazione*/
    float GetAlpha(float wn) const;
    /**Restituisce la coppia resistente dovuta agli attriti interni (freno motore) [Nm]*/
    float GetDampingTorque(float angular_velocity) const;
    /**Velocit� angolare minima del motore*/
    float GetMinAngularVelocity() const;
    /**Accende il motore*/
    void Start() throw(EngineVideoException);
    /**Spenge il motore*/
    void Stop() throw(EngineVideoException);
    /**Restituisce true se � acceso*/
    bool IsStarted();
    /**Restituisce la velocit� di rotazione corrente [giri/1']*/
    float GetRPM();
    /**Restituisce la velocit� di rotazione in [rad/s]*/
    float GetOmega();
    /**Restituisce il numero di giri che corrisponde alla massima potenza [giri/1']*/
    float GetMaxRPM() const;
    /**Restituisce la cilindrata in cc*/
    float GetDisplacement() const;
    /**Restituisce il tipo di ciclo*/
    CYCLE_TYPE GetCycleType() const;
    /**Restituisce 2 o 4 tempi*/
    NSTROKES_TYPE GetStrokes() const;
    /**Restituisce la potenza massima*/
    float GetMaxPower() const;
    /**Imposta la parzializzazione da 0.0 a 1.0*/
    void SetThrottle(float a);
    /**Restituisce la parzializzazione*/
    float GetThrottle();
    /**Restituisce la potenza erogata [W]*/
    float GetOutputPower();
    /**Restituisce la coppia erogata [Nm] */
    float GetOutputTorque();
    /**Restituisce il coefficiente di riempimento*/
    float GetLv(float c,float omega) const;
    /**Applica un carico al motore*/
    void ApplyLoad(EngineLoad* load);
};

/**Definizione caratteristiche della frizione*/
class ClutchDef
{
    public:

    /**Restituisce la massima coppia trasmissibile*/
    virtual float GetMaxTorque()=0;

};

typedef enum
{
    CLUTCH_DISENGAGED=0,
    CLUTCH_ENGAGED=1

} CLUTCH_STATE;

/**Controllo della frizione*/
class ClutchControl:public ClutchDef
{
    public:
    virtual ~ClutchControl(){    }
    /**Innesta la frizione nell'intervallo di tempo t*/
    virtual void Engage(float t)=0;
    /**Disinnesta la frizione*/
    virtual void Disengage()=0;
    /**Restituisce lo stato corrente*/
    virtual CLUTCH_STATE GetState()=0;
};

/**Frizione
per ora solo un abbozzo, da completare
*/
class DiskClutch:public ClutchControl
{
    private:

    float max_torque;
    bool engaged;

    public:

    /**Crea una frizione di default*/
    DiskClutch();
    virtual ~DiskClutch();
    virtual float GetMaxTorque();
    /**Innesta la frizione nell'intervallo di tempo t*/
    virtual void Engage(float t);
    /**Disinnesta la frizione*/
    virtual void Disengage();
    /**Restituisce lo stato corrente*/
    virtual CLUTCH_STATE GetState();
};

class GearsShiftDef
{
    public:

    virtual ~GearsShiftDef() {}
    /**Restituisce il rapporto di trasmissione (vel. albero condotto/vel. albero motore)
    -1=retromarcia
    */
    virtual float GetRatio(int shift)=0;
    /**Restituisce il rendimento meccanico per una certa velocit� di rotazione in ingresso*/
    virtual float GetEfficiency(float input_ang_vel)=0;
    /**Restituisce il momento di inerzia del cambio ridotto all'albero di uscita [kg * m^2]*/
    virtual float GetOutputMInertia(int shift)=0;
    /**Restituisce il momento di inerzia del cambio ridotto all'albero di ingresso [kg * m^2]*/
    virtual float GetInputMInertia(int shift)=0;
    /**restituisce il numero di rapporti escluso la retromarcia*/
    virtual int GetNumGears()=0;
};

/**Eccezione che viene generata se si sbaglia
la cambiata (si saltano le marce)*/
class BadShiftVideoException
{
    private:

    const char* msg;
    int req_gear;
    int cur_gear;

    public:
    BadShiftVideoException(const char* msg,int cur_gear,int req_gear);
    const char* GetMessage() const;
    /**marcia corrente*/
    int GetCurrentGear();
    /**marcia che si � tentato di inserire*/
    int GetRequestedGear();
};

/**Definizione del cambio*/
class GearsShiftControl:public GearsShiftDef
{
    public:

    virtual ~GearsShiftControl() {}
    /**Restituisce il rapporto di trasmissione corrente
    inteso come rapporto fra la velocit� dell'albero condotto e quella
    dell'albero di ingresso*/
    virtual float GetRatio()=0;
    /**Cambia marcia*/
    virtual void Shift(int new_gear) throw (BadShiftVideoException)=0;
    /**Restituisce la marcia corrente*/
    virtual int GetCurrentGear()=0;
    /**Impone la velocit� angolare in ingresso*/
    virtual void SetInputAngularVelocity(float omega)=0;
    /**Restituisce la velocit� angolare in uscita*/
    virtual float GetOutputAngularVelocity()=0;
    /**Restituisce il rendimento meccanico corrente*/
    virtual float GetEfficiency()=0;
    /**Restituisce il momento di inerzia ridotto all'albero di uscita*/
    virtual float GetMomentOfInertia()=0;
};

/**Cambio ad ingranaggi
nota: i rapporti di trasmissione si intendono sempre come
rapporto tra la velocit� dell'albero condotto e quella dell'albero motore
*/
class GearsShift:public GearsShiftControl
{
    protected:

    int cur_gear;
    float cur_ratio;
    float rear_transfer_ratio; //rapporto retromarcia
    float *gear_ratios; //rapporti di trasmissione
    int num_gears; //numero rapporti
    float Iout,Iin; //momenti di inerzia albero di uscita + ingranaggi e albero di ingresso + ingranaggi
    float omega;

    void SetRatio(int gear,float ratio);


    public:

     /**Crea un cambio di default*/
     GearsShift();
     /**Crea un cambio a cinque marce
     r1=prima , r2=seconda ecc... rr=retromarcia*/
     GearsShift(float r1,float r2,float r3,float r4,float r5,float rr);
     /**Crea un cambio a 6 marce*/
     GearsShift(float r1,float r2,float r3,float r4,float r5,float r6,float rr);

     virtual ~GearsShift();

     /**Imposta il momento di inerzia (di solito trascurabile)
     input_shaft=albero primario (ingresso)
     output_shaft=albero secondario (uscita)
     */
     void SetMomentOfInertia(float input_shaft,float output_shaft);
     /**Restituisce il rapporto di trasmissione (vel. albero condotto/vel. albero motore)
     -1=retromarcia
     */
     float GetRatio(int shift);
    /**Restituisce il rendimento meccanico per una certa velocit� di rotazione in ingresso*/
     float GetEfficiency(float input_ang_vel);
    /**Restituisce il momento di inerzia del cambio ridotto all'albero di uscita [kg * m^2]*/
     float GetOutputMInertia(int gear);
    /**Restituisce il momento di inerzia del cambio ridotto all'albero di ingresso [kg * m^2]*/
     float GetInputMInertia(int gear);
     /**Restituisce il rapporto di trasmissione corrente
    inteso come rapporto fra la velocit� dell'albero condotto e quella
    dell'albero di ingresso*/
     float GetRatio();
    /**Cambia marcia*/
     void Shift(int new_gear) throw (BadShiftVideoException);
    /**Restituisce la marcia corrente*/
     int GetCurrentGear();
     /**Numero rapporti*/
     int GetNumGears();
     /**Restituisce il rendimento meccanico corrente*/
     float GetEfficiency();
     /**Impone la velocit� angolare in ingresso*/
     void SetInputAngularVelocity(float omega);
     /**Restituisce la velocit� angolare in uscita*/
     float GetOutputAngularVelocity();
     float GetMomentOfInertia();
};

/**Trasmissione
(comprende l'albero di uscita dal cambio la coppia conica e il differenziale)
*/
class Transmission
{
    public:
    virtual ~Transmission() {};
    /**Rapporto di trasmissione (velocit� rotazione ruote/velocit� albero in uscita dal cambio)*/
    virtual float GetRatio()=0;
    /**Rendimento alla velocit� angolare corrente*/
    virtual float GetEfficiency()=0;
    /**Impone la velocit� angolare in ingresso (velocit� albero uscita cambio)*/
    virtual void SetInputAngularVelocity(float omega)=0;
    /**Restituisce la velocit� angolare in uscita (vel. angolare ruote*/
    virtual float GetOutputAngularVelocity()=0;
    /**Restituisce il momento di inerzia*/
    virtual float GetMomentOfInertia()=0;
};

/**Trasmissione*/
class TransmissionImpl:public Transmission
{
    private:

    float ratio;
    float efficiency;
    float omega; //velocit� rotazione albero in ingreeso [rad/s]
    float Ir; //momento inerzia della trasmissione (albero in uscita dal cambio)

    public:

    /**Crea una trasmissione*/
    TransmissionImpl(float ratio,float efficiency,float Ir);
    /**Rapporto di trasmissione (velocit� rotazione ruote/velocit� albero secondario)*/
    float GetRatio();
    /**Rendimento*/
    float GetEfficiency();
    /**Impone la velocit� angolare in ingresso (velocit� albero uscita cambio)*/
    void SetInputAngularVelocity(float omega);
    /**Restituisce la velocit� angolare in uscita (vel. angolare ruote*/
    float GetOutputAngularVelocity();
    /**Restituisce il momento di inerzia della trasmissione*/
    float GetMomentOfInertia();
};

/**Impianto frenante*/
class BrakesDef
{
    public:
    virtual ~BrakesDef() {}
    /**Restituisce il coefficiente di ripartizione della frenata (Mfa/Mfr)*/
    virtual float GetK()=0;
    /**Restituisce la coppia frenante massima all'avantreno [Nm]*/
    virtual float GetMaxFTorque()=0;
    /**Restituisce la coppia frenante massima al retrotreno [Nm]*/
    virtual float GetMaxRTorque()=0;
};

/**Interfaccia controllo freni*/
class BrakesControl:public BrakesDef
{
    public:
    virtual ~BrakesControl() {}
    /**frena , force_perc compreso fra 0 e 1*/
    virtual void Brake(float force_perc)=0;
    /**Rilascia il freno*/
    virtual void DisengageBrakes()=0;
    /**Restituisce la coppia frenante applicata all'avantreno*/
    virtual float GetFTorque()=0;
    /**Restituisce la coppia frenante applicata al retrotreno*/
    virtual float GetRTorque()=0;
};

/**Impianto frenante realizzato tramite freni a disco*/
class DiskBrakes:public BrakesControl
{
    protected:

    float K;       //coeff. ripartizione frenate
    float brake_f; //forza frenante attuale [N]
    float max_brake_f; //massima forza applicabile
    float epsilon_f; //efficienza del freno [m]
    static const int nbrakes_items=4; //4 elementi frenenati per ogni asse

    public:
    virtual ~DiskBrakes();
    /**K=coeff. ripartizione frenata Mfanteriore/Mfposteriore
    f=coefficiente di attrito freni
    rf=raggio medio su cui agiscono gli elementi frenanti [mm]
    max_force=massima forza applicabile ad ogni elemento frenante [N]
    */
    DiskBrakes(float K,float f,float rf,float max_force);
    /**frena applicando una percentuale della forza massima applicabile perc_brake va da 0 a 1*/
    void Brake(float perc_brake);
    /**Rilascia il freno*/
    void DisengageBrakes();
    /**Restituisce la coppia frenante applicata all'avantreno*/
    float GetFTorque();
    /**Restituisce la coppia frenante applicata al retrotreno*/
    float GetRTorque();
    /**Restituisce il coefficiente di ripartizione della frenata (Mfa/Mfr)*/
    float GetK()=0;
    /**Restituisce la coppia frenante massima all'avantreno [Nm]*/
    float GetMaxFTorque();
    /**Restituisce la coppia frenante massima al retrotreno [Nm]*/
    float GetMaxRTorque();
};

/**tipo di strada*/
typedef enum TRACK_TYPE
{
    TRACK_BAD=0,  //asfalto cattivo
    TRACK_NORMAL, //asfalto normale
    TRACK_GOOD,   //asfalto buono
    TRACK_STONY_BAD, //fondo naturale cattivo
    TRACK_STONY_NORMAL,
    TRACK_STONY_GOOD, //fondo naturale buono
    TRACK_SAND,     //sabbia
};

typedef enum TRACK_CONDITION
{
    TRACK_DRY=0, //normale asciutto
    TRACK_WET, //bagnato
    TRACK_SNOW, //neve (5 cm)
    TRACK_SNOW_H, //neve (10 cm)
    TRACK_ICE, //ghiaccio
};

/**Ruota + pneummatico*/
class WheelDef
{
    public:
    virtual ~WheelDef() {
    };
    /**Restituisce il moemento di inerzia della ruota + pneummatico [kg*m^2]*/
    virtual float GetMomentOfInertia()=0;
    /**Restituisce il raggio geometrico della ruota*/
    virtual float GetRadius()=0;
    /**Restituisce il raggio di rotolamento su strada piana [m]
    dipende dalla struttura del pneummatico (radiale,convenzionale) dalla velocit�,dal carico ed altri fattori
    R0=V/omega e h<R0<R
    */
    virtual float GetR0()=0;
    /**Altezza centro ruota dal piano della strada*/
    virtual float GetH()=0;
    /**Restituisce il coefficiente di rotolamento in funzione del tipo di strada e della velocit�*/
    virtual float GetF(float V,TRACK_TYPE ttype,TRACK_CONDITION tcond)=0;
    /**Restituisce il coefficiente di aderenza longitudinale*/
    virtual float GetMx(float V,float omega,TRACK_TYPE ttype,TRACK_CONDITION tcond)=0;
    /**Restituisce la velocit� angolare critica*/
    virtual float GetMaxOmega()=0;
};

class WheelControl:public WheelDef
{
    public:
    virtual ~WheelControl() {};

    /**Restituisce lo scorrimento attuale
    sigma > 0 in trazione < 0 in frenata 0 in rotolamento puro
    */
    virtual float GetSlip()=0;
    /**Imposta la velocit� lineare del centro ruota e quella di rotazione
    NB:qui si considera V e omega indipendenti perch� la ruota non � detto che sia in rotolamento puro*/
    virtual void SetVelocity(float V,float omega)=0;
    /**Restituisce la velocit� del centro della ruota*/
    virtual float GetVelocity()=0;
    /**Restituisce la velocit� angolare attuale*/
    virtual float GetOmega()=0;
};

/**Ruota con pneummatico radiale*/
class WheelRadialTyre:public WheelControl
{
    protected:

        int tyre_ratio; //rapporto larghezza altezza
        int tyre_width; //larghezza in [mm]
        int tyre_radius; //raggio cerchio in [1"]
        const char* tyre_type; //tipo pneummatico
        float Ir; //momento di inerzia totale della ruota [kg*m^2]
        float R; //raggio geometrico ruota [m]
        float h; //altezza mozzo dal piano stradale [m]
        float R0; //raggio rotolamento [m]
        float omega; //velocit� di rotazione [rad/s]
        float max_omega; //velocit� critica di rotazione [rad/s]
        float V; //vel . centro ruota

    public:
    virtual ~WheelRadialTyre();

    /**
    tyre_width larghezza pneummatico in mm es. 205
    type_ratio rapporto fra altezza e larghezza pneummatico es. 45
    tyre_radius raggio cerchione in pollici es. 13
    tyre_type sigla marcatura pneummatico es. SR
    Ir momento inerzia della ruota completa di pneummatico [kg*m^2]
    */

    WheelRadialTyre(int tyre_width,int tyre_ratio,int tyre_diam,const char* tyre_type,float Ir) throw (BadParamsVideoException);

     /**Restituisce il moemento di inerzia della ruota + pneummatico [kg*m^2]*/
    float GetMomentOfInertia();
    /**Restituisce il raggio geometrico della ruota*/
    float GetRadius();
    /**Restituisce il raggio di rotolamento su strada piana [m]
    dipende dalla struttura del pneummatico (radiale,convenzionale) dalla velocit�,dal carico ed altri fattori
    R0=V/omega e h<R0<R
    */
    float GetR0();
    /**Altezza centro ruota dal piano della strada*/
    float GetH();
    /**Restituisce il coefficiente di rotolamento in funzione del tipo di strada e della velocit�*/
    float GetF(float V,TRACK_TYPE ttype,TRACK_CONDITION tcond);
    /**Restituisce il coefficiente di aderenza longitudinale
    Mx = Xf/Z Z=carico sul perno Xf=forza scambiata fra ruota e suolo
    */
    float GetMx(float V,float omega,TRACK_TYPE ttype,TRACK_CONDITION tcond);
    /**Restituisce la velocit� angolare critica*/
    float GetMaxOmega();
    /**Restituisce la velocit� angolare attuale*/
    float GetOmega();
    /**Restituisce lo scorrimento attuale
    sigma > 0 in trazione < 0 in frenata 0 in rotolamento puro
    */
    float GetSlip();
    /**Imposta la velocit� del centro ruota e la velocit� angolare*/
    void SetVelocity(float V,float omega);
    /**Restituisce la velocit� del centro della ruota*/
    float GetVelocity();
};

//tipo trazione del veicolo
typedef enum VEHICLE_TRACTION
{
    FRONT_AXIS=0, //trazione anteriore
    REAR_AXIS=1, //trazione posteriore
    ALL_AXIS=2, //trazione integrale
};

/**
Veicolo a due assi
gli assi corpo sono posizionati nel baricentro
con l'asse x rivolto in avanti e z in alto
*/
class TwoAxisVehicle
{
    protected:

    float m;   //massa totale [kg]
    float wheel_base;   //passo [m] (p=l1+l2)
    float l2;  //distanza orizzontale fra baricentro e asse posteriore
    float l1;  //distanza orizzontale fra baricentro e asse anteriore
    float hg;  //altezza del baricentro rispetto al suolo [m]
    float Rf;  //raggio nominale ruote anteriori [m]
    float Irf; //momento di inerzia ruote anteriori [kg*m^2]
    float Irr; //momento di inerzia ruote posteriori [kg*m^2]
    float Rr;  //raggio nominale ruote posteriori [m]
    float perch; //percentuale del raggio ruote altezza mozzo rispetto al terreno
    float Cx; //coefficiente aerodinamico di resistenza al moto in direzione x
    float Cp; //coefficiente di portanza (negativo in presenza di superfici deportanti)
    float Iy; //momento di inerzia dell'intero veicolo rispetto all'asse corpo y
    float Vs; //velocit� del veicolo nella direzione del moto
    float Vx; //componente x nel sistema assi fisso della velocit� assoluta
    float Vz; //componente z nel sistema assi fisso della velocit� assoluta
    float a;  //accelerazione attuale
    float S;  //superficie frontale del veicolo usata per il calcolo delle forze aerodinamiche
    TRACK_TYPE track_type; //tipo strada
    TRACK_CONDITION track_cond; //condizioni strada
    float track_radius;
    float track_slope; //pendenza in radianti positiva in salita negativa in discesa
    float cos_a,sin_a;
    VEHICLE_TRACTION traction_type; //anteriore o posteriore o integrale
    WheelControl* traction_axis;

    EngineControl* engine; //motore
    ClutchControl* clutch; //frizione
    GearsShiftControl* shift; //cambio
    Transmission* transmission; //trasmissione
    BrakesControl* brake_system; //freni
    WheelControl* front_wheels; //ruote anteriori
    WheelControl* rear_wheels; //ruote posteriori

    //aggiorna le velocit� del cambio,trasmissisione e ruote in base alla velocit� del motore
    void UpdateGearsChain();
    //restituisce l'efficienza globale cambio+trasmissione+frizione
    float GetTotalTransmEff();

    public:

    /**Crea il veicolo assegnando:
    vmass massa totale [kg]
    p passo (distanza assi) [m]
    cmperc percentuale posizione baricentro 0.5=centrale >0.5 spostato in avanti <0.5 spostato indietro
    cmh altezza baricentro rispetto al terreno
    Cx=coefficiente aerodinamico di restitenza al moto in direzione x
    Cp=coeff. di portanza
    S=sup. frontale usata per il calcolo delle forze aerodinamiche
    */
    TwoAxisVehicle(float vmass,float wheel_base,float cmperc,float cmh,float Cx,float Cp,float S,float Iy,VEHICLE_TRACTION traction) throw (BadParamsVideoException);
    virtual ~TwoAxisVehicle();
    /**Installa il motore sul veicolo*/
    void InstallEngine(EngineControl* engine);
    /**Installa il cambio*/
    void InstallShift(GearsShiftControl* shift);
    /**Installa la frizione*/
    void InstallClutch(ClutchControl* clutch);
    /**Installa la trasmissione*/
    void InstallTransmission(Transmission* transmission);
    /**Installa l'impianto frenante*/
    void InstallBrakeSystem(BrakesControl* brakes_system);
    /**Ruote anteriori*/
    void InstallFrontWheels(WheelControl* front_wheels);
    /**Ruote posteriori*/
    void InstallRearWheels(WheelControl* rear_wheels);
    /**Imposta la velocit� iniziale [m/s]*/
    void SetVelocity(float v);
    /**Imposta la pendenza attuale della strada [deg] e il raggio di curvatura nel piano verticale (positivo se la strada � concava)
    slope=pendenza strada [deg]
    radius=raggio curvatura profilo stradale [m] (zero significa raggio infinito:strada rettilinea)
    f0=coefficiente di rotolamento dovuto al tipo di strada
    */
    void SetTrack(float slope,float radius,TRACK_TYPE ttype,TRACK_CONDITION tcond);
    /**Restituisce il modulo della velocit� del baricentro del veicolo [m/s]*/
    float GetVelocity();
    /**Restituisce il modulo dell'accelerazione del baricentro in seguito alla condizioni attuali [m/s^2]*/
    float GetAcceleration();
    /**Restituisce la potenza attuale necessaria al moto [W]*/
    float GetReqPower();
    /**restituisce la forza resistente al moto alla velocit� attuale [N]*/
    float GetReqForce();
    /**Restituisce la forza di trazione disponibile alla ruota (tiene conto dell'aderenza)*/
    float GetAvForce();
    /**Restituisce la potenza disponibile al moto (tiene conto dell'aderenza) [W]*/
    float GetAvPower();
    /**Restituisce la massa apparente traslante [kg]*/
    float GetTranslMass();
    /**Restituisce la massa apparente rotante [kg * m^2]*/
    float GetRotMass();
    /**Restituisce le forze scambiate tra ruote e terreno in direzione verticale
    */
    void GetWheelsForcesZ(float* Zfront,float *Zrear);
};

};//fine namespace

#endif
