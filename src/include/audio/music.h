/**********************************************************
Interfaccia dell'engine sonoro (playback di file musicali)
(esecuzione di un singolo file musicale alla volta)
Code by L.Berti (c) 2009
************************************************************/


#ifndef MUSIC_H_INCLUDED
#define MUSIC_H_INCLUDED

#include "audio/audio_exception.h"
#include "io/reader.h"

namespace audio {

  

    class MusicFile
    {

        public:


        virtual ~MusicFile() {};

        /**Carica un file musicale da un reader*/
        virtual void Load(io::Reader* reader,const TCHAR* format,int num_buffers) throw (AudioException)=0;

        /**Carica un file musicale da disco*/
        virtual void Load(const char* file_full_path) throw (AudioException)=0;

        /**rilascia i dati*/
        virtual void Free()=0;

        /**playback del file caricato looping=se settato esegue in loop*/
        virtual void Play(bool looping,bool wait_for_completion) throw (AudioException)=0; //suona un file wav
        /**playback del file caricato*/
        virtual void Play() throw (AudioException)=0; //suona un file wav
        /**mette in pausa*/
        virtual void Pause() throw (AudioException)=0;
        /**Interrompe*/
        virtual void Stop()=0;
        /**Imposta il volume*/
        virtual float SetVolume(float volume)=0;
        /**Acquisisce il volume*/
        virtual float GetVolume()=0;
        /**Bilanciamento canale destro e sinistro*/
        /**Imposta il pan.Il valore va da -1.0 (max output sul canale sinistro) a 1.0 (max output sul canale destro)*/
        virtual float SetPan(float value)=0;
        /**Restituisce il valore del pan*/
        virtual float GetPan()=0;
        /**Rende true se l'effetto sonoro � in esecuzione*/
        virtual bool IsPlaying()=0;
        /**Restituisc il nome del file*/
        virtual const char* GetName()=0;
        /**Avvia il fading*/
        virtual void StartFading(float from_volume,float to_volume,float step) throw(AudioException)=0;
        /**Esegue uno step di fading rende true se non � ancora arrivato al volume finale*/
        virtual bool Fade()=0;
        /**Restituisce la durata in secondi dello stream*/
        virtual double GetDuration()=0;
        /**Restituisce la posizione corrente in secondi*/
        virtual double GetCurrentPosition()=0;

    };

    class MusicManager
    {
        public:

        virtual ~MusicManager() { }
        /**Restituisce un nuovo music file*/
        virtual MusicFile* GetNewMusicFile()=0;
        /**Rilascia tutti i music file creati*/
        virtual void FreeAllMusic()=0;

    };

};


#endif // MUSIC_H_INCLUDED
