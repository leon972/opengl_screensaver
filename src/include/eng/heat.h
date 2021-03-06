/****************************************************************
 Code by Leonardo Berti (C) 2007

 Trasmissione del calore per conduzione in regime stazionario
 attraverso una parete piana multistrato

 ****************************************************************/

#ifndef HEAT_H_INCLUDED
#define HEAT_H_INCLUDED

#include <iostream>
#include <vector>
#include <string>

using namespace std;

/**Strato della parete*/
typedef struct HT_LAYER_TAG
{
    /**Conductivity
    coducibilità termica del materiale [W/mK]
    */
    double k;

    /**Thickness
    spessore dello strato [m]
    */
    double s;

    /**Temperature di interfaccia del layer*/
    double ti,te;

} HT_LAYER,*HT_LAYER_PTR;


/**Rappresenta una parete multistrato attraversata da un flusso termico
stazionario
*/

class ConductionWall
{
    protected:

        /**Temperature interna ed esterna*/
        double Ti,Te;

        /**Coefficienti di scambio termico per convezione
        lato 1 e 2 in [W/m^2K]*/
        double hi,he;
        vector<HT_LAYER> layers;
        double heat_flux;
        //resistenza totale
        double resistance;
        //spessore totale
        double thickness;
        /**Esegue il calcolo del flusso e delle temperature di interfaccia fra i layer*/
        void calculate();
        /**Restituisce il layer in base all'indice*/
        bool getLayer(HT_LAYER_PTR dest,int index);
        /**Flag che indica che la struttura è stata modificata ed occorre ricalcolarla*/
        bool modified;
        int last_error;


    public:

        /**Codici di errore*/
        static const int ERR_NONE=0;
        static const int ERR_INVALID_LAYER=-1;
        static const int ERR_NO_LAYER_DEFINED=-2;
        static const int ERR_BAD_VALUE=-3;

        ConductionWall();

        /**Temepratura lato 1 [K] o [°C]*/
        double getTi();
        /**Temperatura lato 2 [K] o [°C]*/
        double getTe();
        /**Imposta la temperatura lato 1*/
        void setTi(double temp);
        /**Imposta la temperatura lato 2*/
        void setTe(double temp);
        /**Coeff. di scambio termico convettivo lato interno [W/m^2K]*/
        double getHi();
        void setHi(double hi);
         /**Coeff. di scambio termico convettivo lato esterno [W/m^2K]*/
        double getHe();
        void setHe(double he);
        /**Restituisce il numero di layers*/
        int getLayerCount();
        /**Aggiunge uno strato alla parete e ne restituisce l'indice
        Gli strati vengono aggiunti a partire dal lato 1 (interno) verso il lato 2 (esterno)
        */
        int addLayer(double conductivity,double thickness);
        /**Aggiunge un layer specificando la resistenza e lo spessore*/
        int addCompoundLayer(double resistance,double thickness);
        /**Rimuove uno strato*/
        bool removeLayer(int layer_index);
        /**Resetta la struttura*/
        void clear();
        /**Restituisce la conducibilità termica dello strato*/
        double getLayerConductivity(int layer_index);
        /**Restituisce lo spessore dello strato*/
        double getLayerThickness(int layer_index);
        /**Restituisce la resistenza termica unitaria del layer [m^2K/W]*/
        double getResistance(int layer_index);
        /**Restituisce la resistenza termica totale della parete*/
        double getResistance();
        /**Restituisce lo spessore totale della parete*/
        double getThickness();
        /**Restituisce il flusso termico unitario [W/m^2]
        (flusso termico attraverso un'area unitaria)
        */
        double getUnitHeatFlux();
        /**Restituice la potenza termica trasmessa attreverso una parete di area A [W]*/
        double getHeatFlux(double A);
        /**Restitusce la temperatura lato 1 (interno) del layer con indice layer_index*/
        double getLayerTi(int layer_index);
        /**Restituisce la temperatura lato 2 (esterno) del layer con indice layer_index*/
        double getLayerTe(int layer_index);
        /**Restituisce il codice di errore dell'ultimo errore tracciato*/
        int getLastError();
};

#endif // HEAT_H_INCLUDED
