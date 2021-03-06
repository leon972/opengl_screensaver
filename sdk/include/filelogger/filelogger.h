/*************************************************************
Logger comune per i messaggi di errore e i messaggi di debug
Code by L.Berti (c) 2007
***************************************************************/

#ifndef FILELOGGER_H_INCLUDED
#define FILELOGGER_H_INCLUDED

#include <iostream>
#include <ostream>
#include <fstream>
#include <ctime>

#define MAX_FNAME 1024

class FileLogger
{
    //operatori output dei tipi di base:vanno dichiarati friend perchè devono accedere a m_stream che è private
    friend FileLogger& operator<< (FileLogger& fl,const char*text);
    friend FileLogger& operator<< (FileLogger& fl,char ch);
    friend FileLogger& operator<< (FileLogger& fl,unsigned char ch);
    friend FileLogger& operator<< (FileLogger& fl,int i);
    friend FileLogger& operator<< (FileLogger& fl,unsigned int i);
    friend FileLogger& operator<< (FileLogger& fl,short i);
    friend FileLogger& operator<< (FileLogger& fl,unsigned short i);
    friend FileLogger& operator<< (FileLogger& fl,long i);
    friend FileLogger& operator<< (FileLogger& fl,unsigned long i);
    friend FileLogger& operator<< (FileLogger& fl,float f);
    friend FileLogger& operator<< (FileLogger& fl,double d);
    friend FileLogger& operator<< (FileLogger& fl,bool b);
    friend FileLogger& operator<< (FileLogger& fl,const void* p); //output di un indirizzo

    private:

        //static FileLogger* m_instance;
        char m_filename[MAX_FNAME];
        std::ofstream m_stream;

        clock_t m_curClock;

    public:

        FileLogger();
        virtual ~FileLogger();
        /**Otttiene una istanza del file logger*/
        //static FileLogger* getInstance();
        /**Avvia il log*/
        bool BeginLog(char* filename,bool append);
        /**Chiude il log*/
        void CloseLog();
        /**Restituisce il nome del file corrente*/
        char* GetFileName();
        void put(char* text);
        /**resetta il timer e scrive il messaggio msg sul file log*/
        void StartClock(char* msg);
        /**Restituisce il tempo in secondi dall'ultimo reset del timer*/
        double GetClock();
        /**Scrive il timer e il messaggio msg sul file*/
        void WriteClock(char* msg);
        /**Scrive il timestamp*/
        void WriteTimestamp(char* msg);
        /**Restituisce il timestamp in formato ASCII*/
        char* GetTimestamp();
        /**Scrive un valore esadecimale*/
        void WriteHex(unsigned int v);
        /**Rende true se il file è aperto*/
        bool isOpen();
        /**New line*/
        void newLine();

};

//output dei tipi dati base
FileLogger& operator<< (FileLogger& fl,const char*text);
FileLogger& operator<< (FileLogger& fl,char ch);
FileLogger& operator<< (FileLogger& fl,unsigned char ch);
FileLogger& operator<< (FileLogger& fl,int i);
FileLogger& operator<< (FileLogger& fl,unsigned int i);
FileLogger& operator<< (FileLogger& fl,short i);
FileLogger& operator<< (FileLogger& fl,unsigned short i);
FileLogger& operator<< (FileLogger& fl,long i);
FileLogger& operator<< (FileLogger& fl,unsigned long i);
FileLogger& operator<< (FileLogger& fl,float f);
FileLogger& operator<< (FileLogger& fl,double d);
FileLogger& operator<< (FileLogger& fl,bool b);
FileLogger& operator<< (FileLogger& fl,const void* p); //output di un indirizzo#endif // FILELOGGER_H_INCLUDED

#endif
