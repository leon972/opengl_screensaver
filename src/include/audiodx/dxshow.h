/***********************************************
DXMusic - implementa l'interfaccia MusicManager
usando DirectShow
Code by L.Berti 2009
************************************************/

#ifndef DXSHOW_H_INCLUDED
#define DXSHOW_H_INCLUDED

#include "lwtk/libhead.h"
#include "audio/music.h"
#include <dshow.h>
#include <map>

//rilascia una interfaccia COM
#ifndef SAFE_RELEASE
#define SAFE_RELEASE(i) {if (i) i->Release(); i = NULL;}
#endif
#ifndef SAFE_DELETE
#define SAFE_DELETE(p)  { if(p) { delete (p);     (p)=NULL; } }
#endif

using namespace std;

namespace audio {
    #define FILTER_NAME_SIZE 32

class DLL_EXPORT MusicFileDx:public MusicFile {
private:

        //costruttore dei Graph Filters
        IGraphBuilder *pGraphBuilder;
        //controlla lo streaming
        IMediaControl *pControl;
        //gestione eventi
        IMediaEvent   *pEvent;
        //posizionamento dello stream
        IMediaSeeking *pMediaSeeking;
        //filtro in esecuzione corrente
        IBaseFilter* pFilter;
        //interfaccia settaggio audio (volume ecc...)
        IBasicAudio  *pAudio;

        string file_name;
        bool loaded;
        bool paused;

        static const char* GetDxShowErrMsg(HRESULT hr);

        //il volume � espresso in centesimi di decibel -10000 significa -100 dB
        //0 significa volume massimo.In realt� si imposta l'attenuazione
        static const long MIN_VOLUME=-10000; //silenzio
        static const long MAX_VOLUME=0; //attenuazione 0
        static const long RIGHT_CHANNEL_MAX_ATT=-10000; //canale destro in silenzio
        static const long LEFT_CHANNEL_MAX_ATT=10000;

        void Initialise() throw (AudioException);

        bool IsFilterInGraph(const IBaseFilter* filter) throw (AudioException);
        //rimuove tutti i filtri dal filter graph
        void RemoveFilters() throw (AudioException);
        //variabili usate per implementare il fading
        float fade_cur,fade_end,fade_begin,fade_step;

public:

        MusicFileDx();

        virtual ~MusicFileDx();

        /**Carica un file musicale da un reader*/
        void Load(io::Reader* reader,const TCHAR* format,int num_buffers) throw (AudioException);

        /**Carica un file musicale da disco*/
        void Load(const char* file_full_path) throw (AudioException);

        /**rilascia i dati*/
        void Free();

        /**playback del file caricato looping=se settato esegue in loop*/
        void Play(bool looping,bool wait_for_completion) throw (AudioException); //suona un file wav
        /**playback del file caricato*/
        void Play() throw (AudioException); //suona un file wav
        /**mette in pausa*/
        void Pause() throw (AudioException);
        /**Interrompe*/
        void Stop();
        /**Rende true se l'effetto sonoro � in esecuzione*/
        bool IsPlaying();
         /**Imposta il volume da 0.0 a 1.0
        restituisce il volume impostato
        */
        float SetVolume(float volume);
        float GetVolume();

        /**Imposta il pan.Il valore va da -1.0 (max output sul canale sinistro) a 1.0 (max output sul canale destro)*/
        float SetPan(float value);
        /**Restituisce il valore del pan*/
        float GetPan();

        /**Restituisc il nome del file*/
        const char* GetName();

        /**Avvia il fading*/
        void StartFading(float from_volume,float to_volume,float step) throw(AudioException);
        /**Esegue uno step di fading rende true se non � ancora arrivato al volume finale*/
        bool Fade();
        /**Restituisce la durata in secondi dello stream*/
        double GetDuration();
        /**Restituisce la posizione corrente in secondi*/
        double GetCurrentPosition();

    };


    class DLL_EXPORT MusicManagerDX:public MusicManager
    {
        private:

        list<MusicFile*> mfiles;
        bool autogc;

        public:

        MusicManagerDX(bool autogc);
        virtual ~MusicManagerDX();
        /**Restituisce un nuovo music file*/
        MusicFile* GetNewMusicFile();
        /**Rilascia tutti i music file creati*/
        void FreeAllMusic();

    };

};

#endif // DXSHOW_H_INCLUDED
