/*****************************************************************
inputwin32.h
Implementa l'interfaccia inputmanager per Windows
Code by Leonardo Berti 6/5/2007
******************************************************************/

#ifndef INPUTWIN32_H_INCLUDED
#define INPUTWIN32_H_INCLUDED

#include "lwtk/libhead.h"
#include "input/inputmanager.h"
#define WIN32_LEAN_AND_MEAN
#include "windows.h"
#include "input/input_exception.h"

#ifdef _USEINPUTNAMESPACE_
namespace inputmanager
{
#endif



class DLL_EXPORT InputWin32:public InputManager
{
    private:

    static InputWin32* instance;
    static const int MAX_KEYS=256;
    static const BYTE HBIT_MSK=0x80;

    BYTE keys[MAX_KEYS];

    InputWin32();

    POINT m_MousePos;

    public:

    static InputWin32* getInstance();

    virtual ~InputWin32();

    //Interfaccia InputManager ----------------------------------

    /**Resetta lo stato dei tasti della tastiera*/
    void ResetKyb();
	/**Resetta lo stato del mouse*/
	void ResetMouse();
	/**Resetta lo stato del joystick*/
	void ResetJoy();

    //TASTIERA

    const char* GetKeyboardInfo();

    bool AcquireKeyboardState() throw (InputException);

    /**Acquisisce lo stato del mouse*/
    bool AcquireMouseState();

    /**Acquisisce lo stato del joystick*/
    bool AcquireJoystickState();

    /**Rende true se il tasto � correntemente premuto
    nb:usa i virtual key di Windows che sono diversi dagli scan code fisici del tasto
    */
    bool KeyStateDown(int key_code);

    /**Rende true se il tasto � correntemente rilasciato*/
    bool KeyStateReleased(int key_code);

    bool KeyPressed(int key_code);

     /**Imposta lo stato di un tasto*/
    void SetKeyState(int key_code,bool state);

    //MOUSE
    const char* GetMouseInfo();

    /**Rende true se il mouse � presente*/
    bool MouseAttached();

    /**Restituisce la X del mouse*/
    int MouseX();

    /**Restituisca la Y del mouse*/
    int MouseY();

    /**Restituisce la posizione del mouse*/
    void MouseXY(int* x,int* y);

    /**imposta la posizione assoluta del mouse */
    void SetMousePosition(int x,int y);

    /**Restituisce lo stato della rotella del mouse*/
    int MouseWheel();

    /**Determina se il tasto sinistro del mouse � premuto*/
    bool MouseLeftButton();

    /**Determina se il tasto destro � premuto*/
    bool MouseRightButton();

    /**Determina sel il tasto centrale � premuto*/
    bool MouseMiddleButton();

    //JOYSTICK

    const char* GetJoystickInfo();

    /**Restituisce true se � presente il joystick*/
    bool JoystickAttached();
    /**asse X joystick*/
    int JoystickX();
    /**asse Y oystick*/
	int JoystickY(); //assey joystick
	/**rende true se il tasto button � premuto*/
	bool JoystickButtons(int button); //stato del tasto del joystick
    /**rende true se almeno un tasto � stato della tastiera � premuto*/
    virtual bool KbHit();
	//fine interfaccia InputManager

};

#ifdef _USEINPUTNAMESPACE_
}
#endif

#endif // INPUTWIN32_H_INCLUDED
