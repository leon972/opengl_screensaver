/***********************************
Gestione risorse PAK (file impacchettati)
Code by L.Berti (c) 2009
************************************/

#ifndef PAK_H_INCLUDED
#define PAK_H_INCLUDED

#include "lwtk/libhead.h"
#include "io/reader.h"
#include "io/ioexception.h"
#include <tchar.h>
#include <fstream>
#include <list>

using namespace io;

namespace io {

    struct PAK_HEADER {
        char signature[2]; //PK
        unsigned short version;
        unsigned char encrypted; //1=encrypted
        char descr[32]; //descrizione
        unsigned char flags;
        unsigned char pad[26];
    };

    struct DATA_HEADER {
        char signature[2]; //DT //identificativo del chunk dati
        char name[32]; //nome della risorsa (es. test.wav)
        unsigned int size; //dimensione del buffer in bytes
        unsigned char flags;
        unsigned char flags2; //non usato
        unsigned char pad[20]; //non usato
    };

    //un file PAK � composto dall'intestazione PAK_HEADER
    //e una serie di buffer dati preceduti da un DATA_HEADER
    class DLL_EXPORT PAKFile {

private:

        static const short PAK_VERSION=1;
        static size_t PAK_HEADER_SIZE;
        static size_t DATA_HEADER_SIZE;

        mutable fstream file;
        const char* enc_key;
        const char* cur_file_name;
        int enc_len;
        mutable list<Reader*> readers;

        void open_file(const char* filename,const char* enc_key,std::ios_base::openmode mode) throw (IOException);
        void write_header(const char* descr,bool encrypted) throw(IOException);
        void write_data_header(const char* resname,unsigned int size,bool encrypted) throw (IOException);
        bool walk(DATA_HEADER& d,bool reset_walk,bool gotonext) throw (IOException);
        bool find(DATA_HEADER& d,const char* res_name,bool from_begin) throw (IOException);

public:

        /**Rende true se il file � un PAK valido.Rende false se non esiste o se non � valido*/
        static bool is_valid(const char* filename);
        /**Rende true se il file esiste*/
        static bool exists(const char* filename);

        PAKFile();
        virtual ~PAKFile();
        void open(const char* filename) throw (IOException);
        void open(const char* filename,const char* enc_key) throw (IOException);
        void create(const char* filename,const char* enc_key,const char* description) throw (IOException);
        void create(const char* filename) throw (IOException);
        void close();
        bool is_open() const;
        void get_header(PAK_HEADER* header) const throw (IOException);
        void add_data(Reader* reader,const char* name) throw (IOException);
        /**Restituisce il numero di risorse contenute*/
        size_t get_resource_count() throw (IOException);
        /**restituisce nel vettore info le intestazioni di tutte le risorse contenute info_length=dimensione del vettore*/
        int get_data_info(DATA_HEADER* info,size_t info_length)  throw (IOException);
         /**Restituisce le dimensioni del file*/
        size_t get_size() const;
        /**restituisce un reader in grado di leggere la risorsa*/
        Reader* get_resource(const char* res_name,bool autogc=true) throw (IOException);
        /**Salva su file una risorsa del file pak*/
        void save_to_file(const char* dest_file,const char* res_name) throw (IOException);

    };

    /**Reader usato per leggere una risorsa dal file
    questo oggetto viene restituito da PAKFile::get_resource
    */
class DLL_EXPORT PAKReader:public Reader {

        friend class PAKFile;

private:

        PAKReader();
        int last_error;
        const char* filename;
        size_t file_size;
        ifstream file; //file readonly binary
        //il pak reader puo' leggere solo tra i due limiti
        int beg_pos;
        int end_pos;
        const char* enc_key;
        int enc_len;
        int enc_pos;
        void set_file(const char* file_name,int pos,size_t file_size,const char* enc_key,int enc_len) throw(IOException);//imposta la lettura

public:

        virtual ~PAKReader();

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

#endif // PAK_H_INCLUDED
