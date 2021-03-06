/*************************
Interfaccia di un binary reader
**************************/

#ifndef READER_H_INCLUDED
#define READER_H_INCLUDED

#include <cstdio>

namespace io
{
    enum READER_POS
    {
        READER_BEGIN=0,
        READER_END=1
    };


    /**Legge bytes da una sorgente dati*/
    class Reader
    {
        public:

        //flag di errori base
        static const int err_eof=-1;
        static const int invalid_state=-2;
        static const int file_not_found=-3;
        static const int err_open=-4;
        static const int file_name_not_set=-5;
        static const int feof=-6;
        static const int invalid_dest_buffer=-7;

        virtual ~Reader() {}

        /**Chiude l'oggetto*/
        virtual void close()=0;
        /**Legge un byte*/
        virtual unsigned char read()=0;
        /**Legge bytes in un array*/
        virtual size_t read(char* dest,size_t size)=0;
        /**Legge nelms elementi di item_size bytes in dest restituisce il numero di elementi letti*/
        virtual size_t read(void* dest,size_t item_size,size_t nelms)=0;
        /**Rende true se � possibile avviare la lettura*/
        virtual bool ready()=0;
        /**Rende true se siamo alla fine del buffer*/
        virtual bool eof()=0;
        /**salta n bytes*/
        virtual size_t skip(int n)=0;
        /**Resetta*/
        virtual void reset()=0;
        /**Restituisce le dimensioni in bytes*/
        virtual size_t size()=0;
        /**posiziona il puntatore di lettura*/
        virtual size_t seek(size_t pos,READER_POS fpos)=0;
        /**Error flag*/
        virtual int GetLastError(void) const =0 ;

    };
};

#endif // READER_H_INCLUDED
