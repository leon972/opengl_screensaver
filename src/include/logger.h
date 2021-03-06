/*************************************************************
Logger statico usato per il debig
Code by L.Berti (c) 2008
***************************************************************/

#ifndef LOGGER_H_INCLUDED
#define LOGGER_H_INCLUDED

#include "lwtk/libhead.h"
#include <iostream>
#include <ostream>
#include <fstream>
#include <ctime>

#ifdef _DEBUG
#define LOG(x) debug::Logger::GetInstance()<<x;
#else
#define LOG(x)
#endif

namespace debug
{
    class DLL_EXPORT Logger
    {
         //output dei tipi dati base
        
        private:

        //non puo' essere istanziata
        Logger();

        static Logger m_instance;

        static char m_filename[1024];
        static std::ofstream m_stream;
        static clock_t m_curClock;
        static const char* default_file;
        static const char* cur_file;

        static bool CheckFile();

        public:

        friend Logger& operator<< (Logger& fl,const char*text);
        friend Logger& operator<< (Logger& fl,char ch);
        friend Logger& operator<< (Logger& fl,unsigned char ch);
        friend Logger& operator<< (Logger& fl,int i);
        friend Logger& operator<< (Logger& fl,unsigned int i);
        friend Logger& operator<< (Logger& fl,short i);
        friend Logger& operator<< (Logger& fl,unsigned short i);
        friend Logger& operator<< (Logger& fl,long i);
        friend Logger& operator<< (Logger& fl,unsigned long i);
        friend Logger& operator<< (Logger& fl,float f);
        friend Logger& operator<< (Logger& fl,double d);
        friend Logger& operator<< (Logger& fl,bool b);
        friend Logger& operator<< (Logger& fl,const void* p); //output di un indirizzo#endif // Logger_H_INCLUDED


        virtual ~Logger();

        static Logger& GetInstance();
        /**Cancella il file di log*/
        static bool ResetLog();
        static const char* GetLogFile();
        /**Imposta il file corrente, se il file non esiste lo crea, se esiste
        aggiunge informazioni al file esistente*/
        static bool SetLogFile(const char* filename);
         /**resetta il timer e scrive il messaggio msg sul file log*/
        static void StartClock(char* msg);
        /**Restituisce il tempo in secondi dall'ultimo reset del timer*/
        static double GetClock();
        /**Scrive il timer e il messaggio msg sul file*/
        static void WriteClock(const char* msg);
        /**Scrive il timestamp*/
        static void WriteTimestamp(const char* msg);
        /**Restituisce il timestamp in formato ASCII*/
        static char* GetTimestamp();
        /**Scrive un valore esadecimale*/
        static void WriteHex(unsigned int v);
        /**Rende true se il file � aperto*/
        static bool isOpen();
        /**New line*/
        static void NewLine();
        /**chiude il log*/
        static void Close();
        /**scrive del testo formattato*/
        static void log(const char* formatText ...);
        static void flush();
    };   
}

#endif // LOGGER_H_INCLUDED
