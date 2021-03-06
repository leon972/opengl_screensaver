/*********************************
Implementazione dell'InputManager
basato su DirectInput
Code by Leonardo Berti (c) 2009
**********************************/

#ifndef INPUTDX_H_INCLUDED
#define INPUTDX_H_INCLUDED

#include "input/inputmanager.h"
#include "input/input_exception.h"

#define WIN32_LEAN_AND_MEAN
#include "windows.h"

#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>

#include "lwtk/libhead.h"
#include "video/video_exception.h"
#include <tchar.h>
#include <string>

using namespace std;

namespace inputmanager {
   
    #define MAX_VKEY 256

    #define DINPUT_BUFFERSIZE  16 //numero di elementi memorizzabili nel buffer del mouse

    //macro che controlla lo stato di un tasto
    #define KEYDOWN(buff,key) (buff[key] & 0x80)
    #define KEYUP(buff,key) (buff[key] == 0)

    #define MAX_JOY_RANGE 1000

    //enumera gli oggetti del joystick e imposta i range max e min per gli assi
    BOOL CALLBACK EnumJoysticksCallback( const DIDEVICEINSTANCE* pdidInstance,VOID* pContext );
    BOOL CALLBACK EnumKeyboardCallback(const DIDEVICEINSTANCE* pdidInstance,VOID* pContext );
    BOOL CALLBACK EnumMouseCallback(const DIDEVICEINSTANCE* pdidInstance,VOID* pContext );


class DLL_EXPORT DXInputManager:public InputManager {
private:

        HWND                  m_hwnd;
        RECT                  m_winRC;
        unsigned char        m_Buff[MAX_VKEY];         //buffer dei tasti della tastiera
        HANDLE                m_hevtMouse;              //evento usato per gestire il mouse
        BOOL                  m_bKeyStatus[MAX_VKEY];
        int                   m_iASCII[MAX_VKEY];       //vettore di corrispondenze fra codici dei tasti DirectInput e codici ASCII
        int m_iStatus;
        DIMOUSESTATE          m_mouse_state;            //struttura che contiene lo stato del mouse (posizione stato dei tasti ecc...)
        DIMOUSESTATE          m_buffered_mouse_state;   //struttura che contiene lo stato bufferizzato del mouse (coordinate assolute)
        LONG                  EnumAllDevices(void);     //esegue l'enumerazione di tutti i device di input e memorizza le informazioni nella lista m_pDevices
        BOOL                  m_bJoystickAttached;      //flag che indica se un joystick � attaccato al pc
        DIJOYSTATE2           m_js;                     //stato del joystick
        HANDLE GetMouseHandle(void);


public:

        DXInputManager();

        virtual ~DXInputManager();

        //Inizializza la classe
        void Initialise(HWND hwnd) throw (InputException);

         //rilascia direct input
        void ShutDown();

        void ResetBufferdMousePosition();

        //------------- interfaccia InputManager ------------------

        /**Resetta lo stato dei tasti della tastiera*/
        virtual void ResetKyb();

        /**Resetta lo stato del mouse*/
        virtual void ResetMouse();

        /**Resetta lo stato del joystick*/
        virtual void ResetJoy();

        /**Acquisisce lo stato della tastiera*/
        virtual bool AcquireKeyboardState();

        virtual bool AcquireMouseState();

        virtual bool AcquireJoystickState();

        //TASTIERA

        virtual const char* GetKeyboardInfo();

        /**Rende true se il tasto � correntemente premuto*/
        virtual bool KeyStateDown(int key_code);

        /**Rende true se il tasto � correntemente rilasciato*/
        virtual bool KeyStateReleased(int key_code);

        /**Rende true se il tasto � stato premuto dall'ultima
        volta che � stato aggiornato loo stato della tastiera*/
        virtual bool KeyPressed(int key_code);

        /**Imposta lo stato di un tasto*/
        virtual void SetKeyState(int key_code,bool state);

        //MOUSE


        virtual const char* GetMouseInfo();

        /**Rende true se il mouse � presente*/
        virtual bool MouseAttached();

        /**Restituisce la X del mouse*/
        virtual int MouseX();

        /**Restituisca la Y del mouse*/
        virtual int MouseY();

        /**Resttuisce la posizione del mouse*/
        virtual void MouseXY(int* x,int* y);

        /**imposta la posizione assoluta del mouse */
        virtual void SetMousePosition(int x,int y);

        /**Restituisce lo stato della rotella del mouse*/
        virtual int MouseWheel();

        /**Determina se il tasto sinistro del mouse � premuto*/
        virtual bool MouseLeftButton();

        /**Determina se il tasto destro � premuto*/
        virtual bool MouseRightButton();

        /**Determina sel il tasto centrale � premuto*/
        virtual bool MouseMiddleButton();

        //JOYSTICK

        virtual const char* GetJoystickInfo();
        /**Restituisce true se � presente il joystick*/
        virtual bool JoystickAttached();
        /**asse X joystick*/
        virtual int JoystickX();
        /**asse Y oystick*/
        virtual int JoystickY(); //assey joystick
        /**rende true se il tasto button � premuto*/
        virtual bool JoystickButtons(int button); //stato del tasto del joystick
        /**rende true se c'� almeno un tasto premuto*/
        virtual bool KbHit();

        //-----------------------------------------------------------

      /*  int GetDeviceCount(void); //restituisce il numero di device
        TCHAR *GetDeviceName(LONG Index); //nome del device con indice Index
        TCHAR *GetDeviceProductName(LONG Index); //nome di produzione del device con indice Index
        DWORD GetDeviceType(LONG Index); //tipo DirectInput del device con indice Index
        */

        void ReacquireJoystick();

        HRESULT GetBufferedMouseState(void);
    };


};


#endif // INPUTDX_H_INCLUDED
