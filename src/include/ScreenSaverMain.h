/* 
 * Parametric surfaces screen saver
 * copyright (c) 2010 by Leonardo Berti
 *
 * Created on 14 novembre 2010, 11.22
 */

#ifndef SCREENSAVERWINDOW_H
#define	SCREENSAVERWINDOW_H

#include <windows.h>
#include <scrnsave.h>
#include <cstdlib>
#include <iostream>
#include <3dengineglw/3dengineglw.h>
#include <3dengine/3dengine.h>
#include <3dengineglw/factory3dglw.h>
#include <3dengine/factory3d.h>
#include "Animator.h"
#include "SurfaceFactory.h"
#include "screen_saver.h"
#include "logger/logger.h"
#include "ParametricSurfacesDemo.h"
#include "lwtk/lwtk.h"

//flag che indica di eseguire lo screen saver come normale applicazione
//disattivare per compilare come screen saver
#define APPLICATION_MODE

using namespace std;
using namespace video;
using namespace mathengine;
using namespace renderer3d;
using namespace debug;

ParametricSurfacesDemo demo;

enum ScreenSaverMode {
    SCR_NONE,SCR_CONFIG,SCR_PREVIEW,SCR_PASSWORD,SCR_SAVER
};

//screen res
#define SCREEN_RES_320_200_32 0
#define SCREEN_RES_640_480_32 1
#define SCREEN_RES_800_600_32 2
#define SCREEN_RES_1024_768_32 3
#define SCREEN_RES_1152_864_32 4
#define SCREEN_RES_1280_720_32 5
#define SCREEN_RES_1280_768_32 6
#define SCREEN_RES_1280_960_32 7
#define SCREEN_RES_1280_1024_32 8
#define SCREEN_RES_1360_768_32 9
#define SCREEN_RES_1360_1024_32 10

//settaggio velocità
#define SPEED_SLOW 0
#define SPEED_NORMAL 1
#define SPEED_FAST 2

/**
 *Settaggi dello screen saver
 */
class SAVER_SETTINGS {

public:

    bool displayNames; //visualizza i nomi delle funzioni
    int screenRes; //risoluzione in modalità full screen
    int rotSpeed; //celocità rotazione
    int transformSpeed; //velocità trasformazione
    int colorSpeed; //velocità variazione gradiente colore
    
};

ScreenSaverMode m_currentMode=SCR_NONE;
HWND externHWND=0;
HINSTANCE hInstance;
Logger& logger=Logger::GetInstance();

/**
 *Windows invoca lo screen saver passando alcuni parametri particolari sulla command line
 @param externHWND restituisce l'hwnd della finestra da utilizzare per il preview o altro 
 */
ScreenSaverMode getFromCommandLine(const char* cmdLine,HWND& externHWND);

/**
 * Dialog di configurazione dello screen saver
 * @param hDlg
 * @param msg
 * @param wParam
 * @param lParam
 * @return
 */
BOOL WINAPI ScreenSaverConfigureDialog (HWND hwnd);


/**
 * Program entry point
 * Windows invoca lo screen saver passando una stringa di comando che indica la modalità
 * (es. preview config ecc...)
 * @param hThisInstance
 * @param hPrevInstance
 * @param lpszArgument
 * @param nCmdShow
 * @return
 */
int WINAPI WinMain (HINSTANCE hThisInstance,HINSTANCE hPrevInstance,LPSTR lpszArgument,int nCmdShow);

/**
 *Registrazione sotto classi dialog di configurazione
 */
BOOL WINAPI RegisterDialogClasses(HANDLE hInst);

/**
 *Verifica la password nel caso di windows 9x
 */
BOOL VerifyPassword(HWND hwnd);

/**
 * Acquisisce il valore di un settaggio dal registry
 * @param key
 * @return
 */
const char* GetSetting(const char* key);

/**
 * Scrive il valore di un settaggio nel registry
 * @param key
 * @param value
 * @return
 */
bool SaveSetting(const char* key,const char* value);

/**
 *Carica un settaggio e setta il combo
 */
int LoadComboSetting(ComboBox& cmb,const char* key,int defaultIndex);

/**
 *Salva un settaggio leggendo il valore selezionato dal combo *
 */
bool SaveComboSetting(const ComboBox& cmb,const char* key);

/**
 *Salva i settaggi dello screen saver nel registry leggendoli dai controlli
 * del dialog di configurazione
 */
void SaveSettings();

/**
 *Carica i settaggi dal registry
 */
SAVER_SETTINGS LoadSettings();

/**
 *Visualizza i settaggi sul dialog
 */
void ShowSettings(const SAVER_SETTINGS& s);

#endif	/* SCREENSAVERWINDOW_H */

