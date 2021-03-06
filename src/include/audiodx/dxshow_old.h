/***********************************************
DXMusic - implementa l'interfaccia MusicManager
usando DirectShow
Code by L.Berti 2009
************************************************/

#ifndef DXSHOW_H_INCLUDED
#define DXSHOW_H_INCLUDED

#include "audio/music.h"
#include "video/video_exception.h"
#include <dshow.h>
#include <map>

//rilascia una interfaccia COM
#ifndef SAFE_RELEASE
#define SAFE_RELEASE(i) {if (i) i->Release(); i = NULL;}
#endif

using namespace std;

namespace audio
{
    #define FILTER_NAME_SIZE 32

    typedef struct
    {
        IBaseFilter *pSource;
        IPin *pPin;
        string file_name;
        WCHAR wFilterName[FILTER_NAME_SIZE];

    } DXSHOW_MEDIA_INFO,*DXSHOW_MEDIA_INFO_PTR;

    class DXMusicManager:public MusicManager
    {
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
        IBaseFilter* pCurrentFilter;

        //file musicali caricati (filtri)
        map<MUSIC_HANDLE,DXSHOW_MEDIA_INFO> loaded_media;

        MUSIC_HANDLE handle_gen;
        MUSIC_HANDLE GetHandleByName(const char* filter_name);
        bool IsFilterInGraph(const IBaseFilter* filter) throw (VideoException);
        void DXMusicManager::CreateFilterName(WCHAR* dest,MUSIC_HANDLE h);

        public:

        DXMusicManager() throw (VideoException);
        virtual ~DXMusicManager();

        //////////////////// Interfaccia MusicManager ////////////////////

        /**Carica un file musicale da un reader*/
        virtual MUSIC_HANDLE Load(io::Reader* reader,const TCHAR* format,int num_buffers) throw (VideoException);

        /**Carica un file musicale da disco*/
        virtual MUSIC_HANDLE Load(const char* file_name,int num_buffers) throw (VideoException);

        /**rilascia un buffer sonoro*/
        virtual void FreeMusic(MUSIC_HANDLE h);

         /**rilascia tutti gli effetti sonori caricati*/
        virtual void FreeAllMusics();

        /**esegue un effetto sonoro caricato looping=se settato esegue in loop*/
        virtual void Play_Music(MUSIC_HANDLE h,bool looping,bool wait_for_completion) throw (VideoException); //suona un file wav
        /**esegue un effetto sonoro caricato*/
        virtual void Play_Music(MUSIC_HANDLE snd) throw (VideoException); //suona un file wav
        /**Interrompe un effetto sonoro*/
        virtual bool StopMusic();
        /**Rende true se l'effetto sonoro � in esecuzione*/
        virtual bool IsPlaying();

        ///////////////////////////////////////////////////////////////////

    };
};

#endif // DXSHOW_H_INCLUDED
