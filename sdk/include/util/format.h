/*******************************
 Formatatore e parser numerico
Code by Leonardo Berti (c) 2009
********************************/

#ifndef FORMAT_H_INCLUDED
#define FORMAT_H_INCLUDED

#include <tchar.h>
#include "localedef.h"
#include <stddef.h>


namespace util
{
    /**
     *Eccezione usata dal formattatore
     */
    class ParseException
    {
        private:

        const TCHAR* message;

        public:

        ParseException(const TCHAR* msg);
        const TCHAR* GetMsg() const;

    };

    /**
     *Formato numerico
     * fornisce metodi per il parsing di numeri interi e floating point da espressioni stringa
     */
    class NumberFormat
    {

        private:

        static const unsigned  MAX_CHARS=256;

        TCHAR dec_sep;
        TCHAR th_sep;
        TCHAR temp[MAX_CHARS];
        TCHAR fmt[16];
        /**
         *Analizza una stringa che rappresenta un numero intero o floating point
         *Toglie eventuali spazi
         *@return la stringa senza spazi e caratteri di tabulazione
         *@throw ParseException se la rappresentazione del numero non è corretta
         */
        const TCHAR* PurgeString(const TCHAR* s) throw (ParseException);

        /**
         * Usata internamente per la formattazione
         * @param text
         * @return
         */
        void FormatNumber(TCHAR* dest,const TCHAR* src,size_t size);

        /**
         * Numero di decimali correnti
         * @param text
         * @return
         */
        int precision; 

        public:

        /**
         * Crea una istanza tenendo conto della localizzazione
         * @param loc localizzazione
         * @return
         */
        NumberFormat(const Locale& loc);

        /**
         * Crea una istanza del formattatore impostando direttamente il simbolo del separatore decimale e delle migliaia
         * @param dec_sep separatore decimale
         * @param th_sep separatore delle migliaia
         *
         */
        NumberFormat(const TCHAR* dec_sep,const TCHAR* th_sep);

        /**
         *Crea una istanza del formattatore specificando il separatore decimale da usare
         */
        NumberFormat(const TCHAR* dec_sep);

        virtual ~NumberFormat();

        /**
         *Esegue il parsing di una stringa che rappresenta un numero interno e ne restituisce il valore
         * @text stringa che rappresenta un intero
         * @throw ParseException se text non è la rappresentazione corretta di un intero
         */
        int ParseInt(const TCHAR* text) throw (ParseException);

        /**
         *Esegue il parsing di un numero decimale usando le impostazioni correnti
         */
        float ParseFloat(const TCHAR* text) throw (ParseException);

        /**
         *Esegue il parsing di un numero decimale usando le impostazioni correnti
         */
        double ParseDouble(const TCHAR* text) throw (ParseException);

        /**
         *esegue il parsing restituendo zero in caso di eccezione
         */
        int SafeParseInt(const TCHAR* text);
        float SafeParseFloat(const TCHAR* text);
        double SafeParseDouble(const TCHAR* text);

        /**
         *Formatta un intero e restituisce il risultato in dest e come valore di ritorno
         *@param dest buffer di output per la formattazione
         * @param n intero da formattare
         * @size dimensione di dest
         * @return il puntatore a dest
         */
        const TCHAR* format(TCHAR* dest,int n,size_t size);
        const TCHAR* format(TCHAR* dest,float n,size_t size);
        const TCHAR* format(TCHAR* dest,double n,size_t size);

        /**
         * imposta i decimali da visualizzare (rende la precisione precedente)
         */
        int SetPrecision(int prec);

        /**
         *restituisce la precisione attuale
         */
        int GetPrecision();

    };
};

#endif // FORMAT_H_INCLUDED
