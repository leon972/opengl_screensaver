/*****************************************

FileReader

Code by L.Berti (c) 2008

******************************************/

#ifndef FREADER_H_INCLUDED
#define FREADER_H_INCLUDED

#include "lwtk/libhead.h"
#include "io/reader.h"
#include "io/ioexception.h"
#include <string>
#include <fstream>
#include <tchar.h>

using namespace std;


namespace io
{
    /**Lettore di file binario*/
    class DLL_EXPORT FileReader:public Reader
    {
        protected:

        string cur_file_name;
        ifstream file;
        int last_error;

        public:



        FileReader();
        FileReader (const TCHAR* filename);
        virtual ~FileReader ();

        const TCHAR* GetFileName();
        Reader* open() throw (IOException);
        Reader* open(const TCHAR* filename) throw (IOException);
        bool is_open();

        /**interfaccia Reader*/
        /**Chiude l'oggetto*/
        virtual void close();
        /**Legge un byte*/
        virtual unsigned char read();
        /**Legge bytes in un array*/
        virtual size_t read(char* dest,size_t size);
        /**Legge nelms elementi di item_size bytes in dest restituisce il numero di elementi letti*/
        virtual size_t read(void* dest,size_t item_size,size_t nelms);
        /**Rende true se � possibile avviare la lettura*/
        virtual bool ready();
        /**Rende true se siamo alla fine del buffer*/
        virtual bool eof();
        /**salta n bytes*/
        virtual size_t skip(int n);
        /**Resetta*/
        virtual void reset();
        /**Restituisce le dimensioni in bytes*/
        virtual size_t size();
        /**posiziona il puntatore di lettura*/
        virtual size_t seek(size_t pos,READER_POS fpos);
        /**Error flag*/
        virtual int GetLastError(void) const;
    };
};

#endif // IOWIN_H_INCLUDED
