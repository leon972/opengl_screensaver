/*****************************************************************
inputmanager.h
Interfaccia per un sistema di input generico
Code by Leonardo Berti 1/1/2007
 ******************************************************************/

#ifndef INPUTMANAGER_H_INCLUDED
#define INPUTMANAGER_H_INCLUDED

#define _USEINPUTNAMESPACE_

#ifdef _USEINPUTNAMESPACE_
namespace inputmanager {
#endif

    /**keyboard scan codes
    codici fisici dei tasti della tastiera
    da usare con i metodi dell'input manager
     */
#define KYB_ESC             0x01
#define KYB_RETURN          0x1C    /* Enter on main keyboard */
#define KYB_LCONTROL        0x1D
#define KYB_RCONTROL        0x9D

#define KYB_LEFT            0xCB    /* LeftArrow on arrow keypad */
#define KYB_RIGHT           0xCD    /* RightArrow on arrow keypad */
#define KYB_UP              0xC8    /* UpArrow on arrow keypad */
#define KYB_DOWN            0xD0    /* DownArrow on arrow keypad */

#define KYB_F1              0x3B
#define KYB_F2              0x3C
#define KYB_F3              0x3D
#define KYB_F4              0x3E
#define KYB_F5              0x3F
#define KYB_F6              0x40
#define KYB_F7              0x41
#define KYB_F8              0x42
#define KYB_F9              0x43
#define KYB_F10             0x44
#define KYB_F11             0x57
#define KYB_F12             0x58
#define KYB_F13             0x64    /*                     (NEC PC98) */
#define KYB_F14             0x65    /*                     (NEC PC98) */
#define KYB_F15             0x66    /*                     (NEC PC98) */

#define KYB_1               0x02
#define KYB_2               0x03
#define KYB_3               0x04
#define KYB_4               0x05
#define KYB_5               0x06
#define KYB_6               0x07
#define KYB_7               0x08
#define KYB_8               0x09
#define KYB_9               0x0A
#define KYB_0               0x0B
#define KYB_MINUS           0x0C    /* - on main keyboard */
#define KYB_EQUALS          0x0D
#define KYB_BACK            0x0E    /* backspace */
#define KYB_TAB             0x0F
#define KYB_Q               0x10
#define KYB_W               0x11
#define KYB_E               0x12
#define KYB_R               0x13
#define KYB_T               0x14
#define KYB_Y               0x15
#define KYB_U               0x16
#define KYB_I               0x17
#define KYB_O               0x18
#define KYB_P               0x19
#define KYB_LBRACKET        0x1A
#define KYB_RBRACKET        0x1B
#define KYB_A               0x1E
#define KYB_S               0x1F
#define KYB_D               0x20
#define KYB_F               0x21
#define KYB_G               0x22
#define KYB_H               0x23
#define KYB_J               0x24
#define KYB_K               0x25
#define KYB_L               0x26
#define KYB_SEMICOLON       0x27
#define KYB_APOSTROPHE      0x28
#define KYB_GRAVE           0x29    /* accent grave */
#define KYB_LSHIFT          0x2A
#define KYB_BACKSLASH       0x2B
#define KYB_Z               0x2C
#define KYB_X               0x2D
#define KYB_C               0x2E
#define KYB_V               0x2F
#define KYB_B               0x30
#define KYB_N               0x31
#define KYB_M               0x32
#define KYB_COMMA           0x33
#define KYB_PERIOD          0x34    /* . on main keyboard */
#define KYB_SLASH           0x35    /* / on main keyboard */
#define KYB_RSHIFT          0x36
#define KYB_MULTIPLY        0x37    /* * on numeric keypad */
#define KYB_LMENU           0x38    /* left Alt */
#define KYB_SPACE           0x39
#define KYB_CAPITAL         0x3A

#define KYB_NUMLOCK         0x45
#define KYB_SCROLL          0x46    /* Scroll Lock */
#define KYB_NUMPAD7         0x47
#define KYB_NUMPAD8         0x48
#define KYB_NUMPAD9         0x49
#define KYB_SUBTRACT        0x4A    /* - on numeric keypad */
#define KYB_NUMPAD4         0x4B
#define KYB_NUMPAD5         0x4C
#define KYB_NUMPAD6         0x4D
#define KYB_ADD             0x4E    /* + on numeric keypad */
#define KYB_NUMPAD1         0x4F
#define KYB_NUMPAD2         0x50
#define KYB_NUMPAD3         0x51
#define KYB_NUMPAD0         0x52
#define KYB_DECIMAL         0x53    /* . on numeric keypad */
#define KYB_OEM_102         0x56    /* <> or \| on RT 102-key keyboard (Non-U.S.) */
#define KYB_KANA            0x70    /* (Japanese keyboard)            */
#define KYB_ABNT_C1         0x73    /* /? on Brazilian keyboard */
#define KYB_CONVERT         0x79    /* (Japanese keyboard)            */
#define KYB_NOCONVERT       0x7B    /* (Japanese keyboard)            */
#define KYB_YEN             0x7D    /* (Japanese keyboard)            */
#define KYB_ABNT_C2         0x7E    /* Numpad . on Brazilian keyboard */
#define KYB_NUMPADEQUALS    0x8D    /* = on numeric keypad (NEC PC98) */
#define KYB_PREVTRACK       0x90    /* Previous Track (KYB_CIRCUMFLEX on Japanese keyboard) */
#define KYB_AT              0x91    /*                     (NEC PC98) */
#define KYB_COLON           0x92    /*                     (NEC PC98) */
#define KYB_UNDERLINE       0x93    /*                     (NEC PC98) */
#define KYB_KANJI           0x94    /* (Japanese keyboard)            */
#define KYB_STOP            0x95    /*                     (NEC PC98) */
#define KYB_AX              0x96    /*                     (Japan AX) */
#define KYB_UNLABELED       0x97    /*                        (J3100) */
#define KYB_NEXTTRACK       0x99    /* Next Track */
#define KYB_NUMPADENTER     0x9C    /* Enter on numeric keypad */
#define KYB_MUTE            0xA0    /* Mute */
#define KYB_CALCULATOR      0xA1    /* Calculator */
#define KYB_PLAYPAUSE       0xA2    /* Play / Pause */
#define KYB_MEDIASTOP       0xA4    /* Media Stop */
#define KYB_VOLUMEDOWN      0xAE    /* Volume - */
#define KYB_VOLUMEUP        0xB0    /* Volume + */
#define KYB_WEBHOME         0xB2    /* Web home */
#define KYB_NUMPADCOMMA     0xB3    /* , on numeric keypad (NEC PC98) */
#define KYB_DIVIDE          0xB5    /* / on numeric keypad */
#define KYB_SYSRQ           0xB7
#define KYB_RMENU           0xB8    /* right Alt */
#define KYB_PAUSE           0xC5    /* Pause */
#define KYB_HOME            0xC7    /* Home on arrow keypad */

#define KYB_PRIOR           0xC9    /* PgUp on arrow keypad */
#define KYB_PGUP            KYB_PRIOR

#define KYB_END             0xCF    /* End on arrow keypad */
#define KYB_PGDOWN          KYB_END

#define KYB_NEXT            0xD1    /* PgDn on arrow keypad */
#define KYB_INSERT          0xD2    /* Insert on arrow keypad */
#define KYB_DELETE          0xD3    /* Delete on arrow keypad */
#define KYB_LWIN            0xDB    /* Left Windows key */
#define KYB_RWIN            0xDC    /* Right Windows key */
#define KYB_APPS            0xDD    /* AppMenu key */
#define KYB_POWER           0xDE    /* System Power */
#define KYB_SLEEP           0xDF    /* System Sleep */
#define KYB_WAKE            0xE3    /* System Wake */
#define KYB_WEBSEARCH       0xE5    /* Web Search */
#define KYB_WEBFAVORITES    0xE6    /* Web Favorites */
#define KYB_WEBREFRESH      0xE7    /* Web Refresh */
#define KYB_WEBSTOP         0xE8    /* Web Stop */
#define KYB_WEBFORWARD      0xE9    /* Web Forward */
#define KYB_WEBBACK         0xEA    /* Web Back */
#define KYB_MYCOMPUTER      0xEB    /* My Computer */
#define KYB_MAIL            0xEC    /* Mail */
#define KYB_MEDIASELECT     0xED    /* Media Select */ 

    class InputManager {
    public:

        virtual ~InputManager() {
        }


        //TASTIERA

        virtual const char* GetKeyboardInfo() = 0;

        /**Resetta lo stato dei tasti della tastiera*/
        virtual void ResetKyb() = 0;

        /**Acquisisce lo stato della tastiera*/
        virtual bool AcquireKeyboardState() = 0;

        /**Rende true se il tasto � correntemente premuto
        nota:key_code Scan code fisico del tasto
         */
        virtual bool KeyStateDown(int key_code) = 0;

        /**Rende true se il tasto � correntemente rilasciato*/
        virtual bool KeyStateReleased(int key_code) = 0;

        /**Rende true se il tasto � stato premuto dall'ultima
        volta che � stato aggiornato loo stato della tastiera*/
        virtual bool KeyPressed(int key_code) = 0;

        /**Imposta lo stato di un tasto*/
        virtual void SetKeyState(int key_code, bool state) = 0;

        /**rende true se c'� almeno un tasto premuto*/
        virtual bool KbHit() = 0;

        //MOUSE

        virtual const char* GetMouseInfo() = 0;

        /**Acquisisce lo stato del mouse*/
        virtual bool AcquireMouseState() = 0;

        /**Resetta lo stato del mouse*/
        virtual void ResetMouse() = 0;

        /**Rende true se il mouse � presente*/
        virtual bool MouseAttached() = 0;

        /**Restituisce la X del mouse*/
        virtual int MouseX() = 0;

        /**Restituisca la Y del mouse*/
        virtual int MouseY() = 0;

        /**Resttuisce la posizione del mouse*/
        virtual void MouseXY(int* x, int* y) = 0;

        /**imposta la posizione assoluta del mouse */
        virtual void SetMousePosition(int x, int y) = 0;

        /**Restituisce lo stato della rotella del mouse*/
        virtual int MouseWheel() = 0;

        /**Determina se il tasto sinistro del mouse � premuto*/
        virtual bool MouseLeftButton() = 0;

        /**Determina se il tasto destro � premuto*/
        virtual bool MouseRightButton() = 0;

        /**Determina sel il tasto centrale � premuto*/
        virtual bool MouseMiddleButton() = 0;

        //JOYSTICK

        virtual const char* GetJoystickInfo() = 0;

        /**Resetta lo stato del joystick*/
        virtual void ResetJoy() = 0;

        /**Acquisisce lo stato del joystick*/
        virtual bool AcquireJoystickState() = 0;

        /**Restituisce true se � presente il joystick*/
        virtual bool JoystickAttached() = 0;

        /**asse X joystick -1 = sinistra 1 = destra*/
        virtual int JoystickX() = 0;

        /**asse Y oystick -1 = in alto 1=in basso*/
        virtual int JoystickY() = 0; //assey joystick

        /**rende true se il tasto button � premuto
        il primo tasto ha indice 0
         */
        virtual bool JoystickButtons(int button) = 0; //stato del tasto del joystick


    };

#ifdef _USEINPUTNAMESPACE_
}
#endif

#endif // INPUTMANAGER_H_INCLUDED
