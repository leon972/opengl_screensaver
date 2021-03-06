/**********************************************************
Interfaccia dell'engine sonoro (musica e effetti sonori)
Code by L.Berti (c) 2009
14-7-2009
************************************************************/

#ifndef AUDIO_H_INCLUDED
#define AUDIO_H_INCLUDED

#include "io/reader.h"
#include <tchar.h>
#include "audio/audio_exception.h"

namespace audio
{
    typedef int SOUND_HANDLE;

    #define EMPTY_SOUND -1
   

    /**Numero di canali usati per l'inizializzazione*/
    enum SOUND_CHANNELS
    {
        CH_MONO=0,
        CH_STEREO=2
    };

    /**Frequenza di campionamento in Hertz (sono riportati i valori piu' comuni)*/
    enum SAMPLE_FREQ
    {
        FREQ_11KHz=11025,
        FREQ_22KHz=22050,
        FREQ_44KHz=44100
    };

    enum BITS_PER_SAMPLE
    {
        SMP_8_BIT=8,
        SMP_16_BIT=16,
        SMP_32_BIT=32,
        SMP_64_BIT=64
    };


    class SoundManager
    {
        public:

        static const float MAX_VOLUME=1.0f;
        static const float MIN_VOLUME=0.0f;

        static const float LEFT_PAN=-1.0f;
        static const float RIGHT_PAN=1.0f;
        static const float CENTER_PAN=0.0f;

        virtual ~SoundManager() {}
        /**Carica un file WAV da un reader*/
        virtual SOUND_HANDLE Load(io::Reader* reader,const TCHAR* format,int num_buffers) throw (AudioException)=0;
        /**Carica un file WAV da un file*/
        virtual SOUND_HANDLE Load(const TCHAR* file_name,int num_buffers) throw (AudioException)=0;
        /**rilascia un buffer sonoro*/
        virtual void FreeSound(SOUND_HANDLE snd)=0;
        /**rilascia tutti gli effetti sonori caricati*/
        virtual void FreeAllSounds()=0;//libera tutti i suoni caricati
        //nota il metodo si chiama Play_Sound con l'underscore per non generare conflitti con PlaySound di windows
        /**esegue un effetto sonoro caricato looping=se settato esegue in loop*/
        virtual void Play_Sound(SOUND_HANDLE snd,bool looping) throw (AudioException)=0; //suona un file wav
        /**esegue un effetto sonoro caricato*/
        virtual void Play_Sound(SOUND_HANDLE snd) throw (AudioException)=0; //suona un file wav
        /**Interrompe un effetto sonoro*/
        virtual void StopSound(SOUND_HANDLE snd)=0;
        /**Rende true se l'effetto sonoro � in esecuzione*/
        virtual bool IsPlaying(SOUND_HANDLE snd)=0;
        /**Imposta il volume di un suono.Il volume va da 0.0 a 1.0=max volumne*/
        virtual float SetVolume(SOUND_HANDLE snd,float volume)=0;
        /**Restituisce il volume di un suono*/
        virtual float GetVolume(SOUND_HANDLE snd)=0;
        /**Imposta il pan.Il valore va da -1.0 (max output sul canale sinistro) a 1.0 (max output sul canale destro)*/
        virtual float SetPan(SOUND_HANDLE snd,float value)=0;
        /**Restituisce il valore del pan per il canale scelto*/
        virtual float GetPan(SOUND_HANDLE snd)=0;

    };
};

#endif // AUDIO_H_INCLUDED
