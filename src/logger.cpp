/*************************************************************
Logger statico usato per il debig
Code by L.Berti (c) 2008
***************************************************************/


#include "logger/logger.h"
#include <iostream>
#include <fstream>
#include <ostream>
#include <ctime>
#include <cstdarg>
#include <cstring>

using namespace std;

namespace debug {

    char Logger::m_filename[1024];
    std::ofstream Logger::m_stream;
    clock_t Logger::m_curClock=0;
    const char* Logger::cur_file=0;
    const char* Logger::default_file="debug.log";
    bool m_file_ok;
    Logger Logger::m_instance;


    Logger::Logger() {
        m_file_ok=false;
    }

    Logger::~Logger() {
        Close();
    }

    void Logger::Close() {
        if (m_stream.is_open())
        {
            if (strcmp(cur_file,default_file)==0) WriteTimestamp("*** End log ***");
            m_stream.close();
        }

    }

    Logger& Logger::GetInstance() {
        return m_instance;
    }

    /**Se il file di log non � aperto apre il file log di default*/
    bool Logger::CheckFile() {

        if (!m_stream.is_open()) {

            m_stream.open(default_file,ios_base::app);

            bool op=m_stream.is_open();

            if (op) {

                cur_file=default_file;
                WriteTimestamp("*** Begin log ***");
            }

            m_file_ok=true;

            return op;

        } else return true;
    }

    /**Cancella il file di log*/
    bool Logger::ResetLog() {

        if (!cur_file) cur_file=default_file;

        if (m_stream.is_open()) m_stream.close();
        if (cur_file) m_stream.open(cur_file,ios_base::out);
        m_file_ok=m_stream.is_open();
        return m_file_ok;
    }

    const char* Logger::GetLogFile() {
        return cur_file;
    }

    /**Imposta il file corrente, se il file non esiste lo crea, se esiste
    aggiunge informazioni al file esistente*/
    bool Logger::SetLogFile(const char* filename) {

        if (!cur_file) cur_file=default_file;
        if (strcmp(filename,cur_file)==0) return true;
        if (m_stream.is_open()) m_stream.close();
        m_stream.open(filename,ios_base::app);
        bool op=m_stream.is_open();

        if (op) {

            m_file_ok=true;
            cur_file=filename;
        }

        return op;

    }

    void Logger::log(const char* formatText ...) {

        if (!m_file_ok) CheckFile();

        char strText[1024]; //testo formattato da visualizzare
        va_list argumentPtr; //punta alla lista degli argomenti opzionali

        if (formatText == 0) return;

        CheckFile();

        va_start(argumentPtr, formatText);

        vsprintf(strText, formatText, argumentPtr);

        va_end(argumentPtr);

        m_stream<<strText;
    }

    /**resetta il timer e scrive il messaggio msg sul file log*/
    void Logger::StartClock(char* msg) {

        m_curClock=clock();

        if (!m_file_ok) CheckFile();

        if (msg) m_stream<<msg<<" (clock start) "<<endl;
    }

    /**Restituisce il tempo in secondi dall'ultimo reset del timer*/
    double Logger::GetClock() {
        return (double)(clock()-m_curClock)/CLOCKS_PER_SEC;
    }

    /**Scrive il timer e il messaggio msg sul file*/
    void Logger::WriteClock(const char* msg) {

        if (!m_file_ok) CheckFile();
        if (msg) m_stream<<msg<<" (clock="<<GetClock()<<" s)";
        else m_stream<<"clock="<<GetClock()<<" s";
    }

    /**Scrive il timestamp*/
    void Logger::WriteTimestamp(const char* msg) {

        if (!m_file_ok) CheckFile();
        time_t t=time(0);
        if (msg) m_stream<<msg<<" "<<asctime(localtime(&t));
        else m_stream<<asctime(localtime(&t));
        m_stream<<endl;
    }

    /**Restituisce il timestamp in formato ASCII*/
    char* Logger::GetTimestamp() {

        time_t t=time(0);
        return asctime(localtime(&t));
    }

    /**Scrive un valore esadecimale*/
    void Logger::WriteHex(unsigned int v) {

        if (!m_file_ok) CheckFile();
        m_stream.setf(ios_base::hex,ios_base::basefield);
        m_stream<<v;
        m_stream.setf(ios_base::fmtflags(0),ios_base::basefield);
    }



    void Logger::flush() {
        if (!m_file_ok) CheckFile();
        m_stream.flush();
    }

    /**Rende true se il file � aperto*/
    bool Logger::isOpen() {

        return m_stream.is_open();
    }

    /**New line*/
    void Logger::NewLine() {
        if (!m_file_ok) CheckFile();
        m_stream<<endl;
    }

    //output dei tipi dati base
    Logger& operator<< (Logger& fl,const char*text) {

        if (!m_file_ok) Logger::CheckFile();
        Logger::m_stream<<text;
        return fl;
    }

    Logger& operator<< (Logger& fl,char ch) {

        if (!m_file_ok) Logger::CheckFile();
        Logger::m_stream<<ch;
        return fl;
    }

    Logger& operator<< (Logger& fl,unsigned char ch) {

        if (!m_file_ok) Logger::CheckFile();
        Logger::m_stream<<ch;
        return fl;
    }

    Logger& operator<< (Logger& fl,int i) {
        if (!m_file_ok) Logger::CheckFile();

        Logger::m_stream<<i;
        return fl;
    }

    Logger& operator<< (Logger& fl,unsigned int i) {

        if (!m_file_ok) Logger::CheckFile();
        Logger::m_stream<<i;
        return fl;
    }

    Logger& operator<< (Logger& fl,short i) {

        if (!m_file_ok) Logger::CheckFile();
        Logger::m_stream<<i;
        return fl;
    }

    Logger& operator<< (Logger& fl,unsigned short i) {

        if (!m_file_ok) Logger::CheckFile();
        Logger::m_stream<<i;
        return fl;
    }

    Logger& operator<< (Logger& fl,long i) {

        if (!m_file_ok) Logger::CheckFile();
        Logger::m_stream<<i;
        return fl;
    }

    Logger& operator<< (Logger& fl,unsigned long i) {

        if (!m_file_ok) Logger::CheckFile();
        Logger::m_stream<<i;
        return fl;
    }

    Logger& operator<< (Logger& fl,float f) {

        if (!m_file_ok) Logger::CheckFile();
        Logger::m_stream<<f;
        return fl;
    }

    Logger& operator<< (Logger& fl,double d) {

        if (!m_file_ok) Logger::CheckFile();
        Logger::m_stream<<d;
        return fl;
    }

    Logger& operator<< (Logger& fl,bool b) {

        if (!m_file_ok) Logger::CheckFile();
        Logger::m_stream<<b;
        return fl;
    }

    Logger& operator<< (Logger& fl,const void* p) { //output di un indirizzo#endif // Logger_H_INCLUDED

        if (!m_file_ok) Logger::CheckFile();
        Logger::m_stream<<p;
        return fl;
    }

};
