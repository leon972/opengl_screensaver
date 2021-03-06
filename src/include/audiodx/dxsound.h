/*******************************************
Implementazione Direct Sound dell'interfaccia
SoundManager.
Code by L.Berti (c) 2009
14-7-2009
********************************************/

#ifndef DXSOUND_H_INCLUDED
#define DXSOUND_H_INCLUDED

#include "lwtk/libhead.h"
#include "audio/sound.h"
#include <windows.h>
#include <list>
#include <dsound.h>
#include <mmsystem.h>

using namespace std;

namespace audio {

    //struttura che contiene le informazioni di un file sonoro
    typedef struct SOUND_STRUCTTag {
        char *strFileName;
        LPDIRECTSOUNDBUFFER *lpDSBuffers;  //buffer sonori
        int iNumBuffers;                   //numero di buffer creati


    } SOUND_STRUCT,*SOUND_STRUCT_PTR;

    #define DD_INIT_STRUCT(ddstruct) { memset(&ddstruct,0,sizeof(ddstruct)); ddstruct.dwSize=sizeof(ddstruct); }

    #define MAXSOUNDS 80    //numero massimo di file sonori manipolati
    #define MAXBUFFERS 160

//converte da formato multibyte a unicode
//CP_ACP indica che la stringa multibyte usa il code page ANSI
    #define MULTI_TO_WIDE( x,y )  MultiByteToWideChar( CP_ACP, \
            MB_PRECOMPOSED, y, -1, x, _MAX_PATH );

    #define NUMEVENTS 2


class DLL_EXPORT DXSoundManager:public SoundManager {

private:

        //impostazioni del buffer primario
        SOUND_CHANNELS sndChannels; //mono / stereo
        SAMPLE_FREQ sample_freq;
        BITS_PER_SAMPLE m_bps;


        //handler finestra di riferimento:se non � settato l'engine non funziona!
        HWND hwnd;
        //file handle per il file wav
        HMMIO m_hmmio;
        //chunk information
        MMCKINFO m_mmckinfoData, m_mmckinfoParent;
        WAVEFORMATEX *m_pwfx;
        HANDLE m_rghEvent[NUMEVENTS];
        LPDIRECTSOUND8 m_lpds; 	//oggetto direct sound
        LPDIRECTSOUNDBUFFER m_lpdsbPrimary;
        SOUND_STRUCT m_sndArray[MAXSOUNDS];
        DSBUFFERDESC m_dsbdescPrimary;
        LPDIRECTSOUNDNOTIFY m_lpdsNotify;
        DSBUFFERDESC m_dsbdesc;	//struttura che descrive il buffer sonoro
        int m_iStatus;

        //carica un suono nel direcsound buffer
        HRESULT DD_Load_Sound(LPSTR strFileName,LPDIRECTSOUNDBUFFER *lppdsb) throw (AudioException);
        BOOL RestoreBuffer( LPDIRECTSOUNDBUFFER pDSB,BOOL *pbWasRestored);

        //controlla che la classe sia inizializzata
        void CheckInit() throw (AudioException);
        SOUND_STRUCT_PTR GetSoundBuffers(SOUND_HANDLE snd) throw (AudioException);
        const TCHAR* CreateTempFile(const TCHAR* prefix,const TCHAR* extension);
        static const int TMP_FILE_SZ=MAX_PATH+64;
        TCHAR sTempFile[TMP_FILE_SZ];//buffer usato per la creazione di un file temporaneo
        TCHAR sTempDir[MAX_PATH];

public:

        DXSoundManager();
        DXSoundManager(SOUND_CHANNELS sndChannels,SAMPLE_FREQ sample_freq,BITS_PER_SAMPLE bps);


        void Initialise(HWND hwnd,GUID *pguid) throw (AudioException);

        void ShutDown();

        void SetHWND(HWND hwnd);

        virtual ~DXSoundManager();

        //interfaccia SoundManager -----------------------
        /**Carica un file WAV da un reader*/
        virtual SOUND_HANDLE Load(io::Reader* reader,const TCHAR* format,int num_buffers) throw (AudioException);
        /**Carica un file WAV da un file*/
        virtual SOUND_HANDLE Load(const TCHAR* file_name,int num_buffers) throw (AudioException);
        /**rilascia un buffer sonoro*/
        virtual void FreeSound(SOUND_HANDLE snd);
        /**rilascia tutti gli effetti sonori caricati*/
        virtual void FreeAllSounds();//libera tutti i suoni caricati
        /**esegue un effetto sonoro caricato*/
        virtual void Play_Sound(SOUND_HANDLE snd,bool looping) throw (AudioException); //suona un file wav
        /**esegue un effetto sonoro caricato*/
        virtual void Play_Sound(SOUND_HANDLE snd) throw (AudioException); //suona un file wav
        /**Interrompe un effetto sonoro*/
        virtual void StopSound(SOUND_HANDLE snd);
        /**Rende true se l'effetto sonoro � in esecuzione*/
        bool IsPlaying(SOUND_HANDLE snd);
        /**Imposta il volume di un suono.Il volume va da 0.0 a 1.0=max volumne*/
        virtual float SetVolume(SOUND_HANDLE snd,float volume);
        /**Restituisce il volume di un suono*/
        virtual float GetVolume(SOUND_HANDLE snd);
        /**Imposta il pan.Il valore va da -1.0 (max output sul canale sinistro) a 1.0 (max output sul canale destro)*/
        virtual float SetPan(SOUND_HANDLE snd,float value);
        /**Restituisce il valore del pan*/
        virtual float GetPan(SOUND_HANDLE snd);
        //-------------------------------------------------

    };
};

#endif // DXSOUND_H_INCLUDED
