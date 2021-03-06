/* 
 /* 
 * Parametric surfaces screen saver
 * copyright (c) 2010 by Leonardo Berti
 *
 * File:   ScreenSaverWindow.cpp
 * Author: Proprietario
 * 
 * Created on 14 novembre 2010, 11.22
 */

#include "ScreenSaverMain.h"
#include <cstdlib>
#include <iostream>
#include <3dengineglw/3dengineglw.h>
#include <3dengine/3dengine.h>
#include <3dengineglw/factory3dglw.h>
#include <3dengine/factory3d.h>
#include "Animator.h"
#include "SurfaceFactory.h"
#include "logger/logger.h"
#include "lwtkwin32/lwtkwin32.h"
#include "video/video.h"

using namespace std;
using namespace video;
using namespace mathengine;
using namespace renderer3d;
using namespace lwtk;

lwtk::Application* application = 0; //lwtk application
lwtk::Window* window = 0; //config dialog
CheckBox* chkNames = 0; //display surface names
ComboBox* cmbRes = 0; //screen resolution
ComboBox* cmbRotSpeed = 0; //velocità rotazione
ComboBox* cmbTransformSpeed = 0; //frequenza passaggio da una superficie ad un altra
ComboBox* cmbColorSpeed = 0; //velocità trasformazione colore
//chiave base per il salvataggio dei settaggi nel registry
LPCTSTR BASE_KEY = "Software\\lbprog\\PSsaver";
//usato come valore ri ritorno temporaneo
const size_t BUFF_SIZE = 256;
char resBuff[BUFF_SIZE];
const char* SET_DISPLAY_NAMES = "display_names";
const char* SET_SCRN_RES = "screen_res";
const char* SET_ROT_SPEED = "rot_speed";
const char* SET_TRANSFORM_SPEED = "transf_speed";
const char* SET_COLOR_SPEED = "color_speed";

class SaveAction : public ActionEvent {

    void ActionPerformed(Widget* src) {
        //salva i settaggi
        SaveSettings();
    }
};

class ExitAction : public ActionEvent {

    void ActionPerformed(Widget* src) {
        if (window) window->Close();
    }

};

class AboutAction : public ActionEvent {

    void ActionPerformed(Widget* src) {
        if (window) window->MsgBox("About", MSG_OK | MSG_ICO_INFORMATION, "Parametric Surfaces Screensaver \n Coded by Leonardo Berti (c) 2010");
    }

};

/**
 * Dialog di configurazione dello screen saver
 * @param hDlg
 * @param msg
 * @param wParam
 * @param lParam
 * @return
 */
BOOL WINAPI ScreenSaverConfigureDialog(HWND hwnd) {
    //::MessageBox(hwnd, TEXT("Parametric surfaces screen saver"), TEXT("Info"), MB_OK);

    // DialogBox(hInstance, MAKEINTRESOURCE(IDD_DLG1), hwnd, ConfigDlgProc);

    const int DLG_W = 400;
    const int DLG_H = 310;
    const int BTU_H = 40;
    const int BTU_W = 100;

    application = lwtk::Win32Application::GetInstance();

    window = application->GetNewWindow(TEXT("Parametric Surfaces Screen Saver configuration"), false, false, false);

    chkNames = application->GetNewCheckBox("Display surfaces names");

    chkNames->Move(10, 10);

    window->Add(chkNames);

    SaveAction s;

    Button* btuSave = application->GetNewButton("Save");

    btuSave->AddActionEvent(&s);

    Button* btuExit = application->GetNewButton("Exit");

    ExitAction ea;

    btuExit->AddActionEvent(&ea);

    btuExit->Resize(BTU_W, BTU_H);

    btuSave->Move(40, DLG_H - 80);

    btuSave->Resize(BTU_W, BTU_H);

    btuExit->Move(DLG_W - 40 - BTU_W, DLG_H - 80);

    Button* btuAbout = application->GetNewButton("About");

    btuAbout->SetBackground(CL_TURQUOISE);

    AboutAction aa;

    btuAbout->AddActionEvent(&aa);

    btuAbout->Resize(BTU_W, BTU_H);

    btuAbout->Move((DLG_W - btuAbout->GetWidth()) / 2, DLG_H - 80);

    window->Add(btuAbout);

    //ricentra il testo
    btuAbout->SetText("About");

    window->Add(btuSave);

    window->Add(btuExit);

    //risoluzione video
    cmbRes = application->GetNewComboBox(DROPDOWN_READ_ONLY);

    cmbRes->AddElement("320 x 200 32 bit"); //0
    cmbRes->AddElement("640 x 480 32 bit"); //1
    cmbRes->AddElement("800 x 600 32 bit"); //2
    cmbRes->AddElement("1024 x 768 32 bit"); //3
    cmbRes->AddElement("1152 x 864 32 bit"); //4
    cmbRes->AddElement("1280 x 720 32 bit"); //5
    cmbRes->AddElement("1280 x 768 32 bit"); //6
    cmbRes->AddElement("1280 x 960 32 bit"); //7
    cmbRes->AddElement("1280 x 1024 32 bit"); //8
    cmbRes->AddElement("1360 x 768 32 bit"); //9
    cmbRes->AddElement("1360 x 1024 32 bit"); //10


    Label* lb = application->GetNewLabel("Screen resolution");

    lb->Move(10, 40);

    window->Add(lb);

    cmbRes->Move(140, 40);

    cmbRes->SetWidth(160);

    window->Add(cmbRes);

    cmbRotSpeed = application->GetNewComboBox(DROPDOWN_READ_ONLY);

    cmbRotSpeed->AddElement("Slow");
    cmbRotSpeed->AddElement("Normal");
    cmbRotSpeed->AddElement("Fast");

    cmbRotSpeed->SetWidth(160);

    lb = application->GetNewLabel("Rotation speed");

    lb->Move(10, 70);

    window->Add(lb);

    cmbRotSpeed->Move(160, 70);

    window->Add(cmbRotSpeed);

    cmbTransformSpeed = application->GetNewComboBox(DROPDOWN_READ_ONLY);

    cmbTransformSpeed->AddElement("Slow");
    cmbTransformSpeed->AddElement("Normal");
    cmbTransformSpeed->AddElement("Fast");

    cmbTransformSpeed->SetWidth(160);

    lb = application->GetNewLabel("Transform speed");

    lb->Move(10, 100);

    window->Add(lb);

    cmbTransformSpeed->Move(160, 100);

    window->Add(cmbTransformSpeed);

    cmbColorSpeed = application->GetNewComboBox(DROPDOWN_READ_ONLY);

    cmbColorSpeed->SetWidth(160);

    cmbColorSpeed->AddElement("Slow");
    cmbColorSpeed->AddElement("Normal");
    cmbColorSpeed->AddElement("Fast");

    //velocità cambiamento colore
    lb = application->GetNewLabel("Color gradient speed");
    lb->Move(10, 130);

    window->Add(lb);

    cmbColorSpeed->Move(160, 130);

    window->Add(cmbColorSpeed);

    window->SetWidth(DLG_W);

    window->SetHeight(DLG_H);

    //carica e visualizza i settaggi dello screen saver
    ShowSettings(LoadSettings());

    //termina il programma alla chiusura del dialog
    window->Show(W_QUIT_ON_CLOSE);

    application->Release();

    window = 0;
    //rilascia la memoria allocata
    delete application;

    return TRUE;
}

/**
 * Esegue il parsing della command line inviata dal sistema operativo allo screen saver
 * (codice adattato da "How to write a 32bit screen saver" 1997-1999 Lucian Wischik.
 * @param c
 * @return
 */
ScreenSaverMode getFromCommandLine(const char* c, HWND& externHWND) {

    ScreenSaverMode res = SCR_NONE;

    if (*c == '\"') {
        c++;
        while (*c != 0 && *c != '\"') c++;
    } else {
        while (*c != 0 && *c != ' ') c++;
    }
    if (*c != 0) c++;
    while (*c == ' ') c++;

    if (*c == 0) {
        //configurazione
        res = SCR_CONFIG;

    } else {

        if (*c == '-' || *c == '/') c++;
        if (*c == 'p' || *c == 'P' || *c == 'l' || *c == 'L') {
            c++;
            while (*c == ' ' || *c == ':') c++;
            //if ((strcmp(c, "scrprev") == 0) || (strcmp(c, "ScrPrev") == 0) || (strcmp(c, "SCRPREV") == 0)) hwnd = CheckForScrprev();
            //else externHWND = (HWND) atoi(c);
            //hwnd della finestra di preview
            externHWND = reinterpret_cast<HWND> (atoi(c));
            res = SCR_PREVIEW;
        } else if (*c == 's' || *c == 'S') {
            //modalità screen saver
            res = SCR_SAVER;
        } else if (*c == 'c' || *c == 'C') {
            c++;
            while (*c == ' ' || *c == ':') c++;
            if (*c == 0) externHWND = GetForegroundWindow();
                //handle da usare per il dialog di configurazione
            else externHWND = reinterpret_cast<HWND> (atoi(c));
            res = SCR_CONFIG;
        } else if (*c == 'a' || *c == 'A') {
            //richiesta password (vecchie versioni Windows)
            c++;
            while (*c == ' ' || *c == ':') c++;
            externHWND = reinterpret_cast<HWND> (atoi(c));
            res = SCR_PASSWORD;
        }
    }

    return res;
}

/**
 * Program entry point
 * @param hThisInstance
 * @param hPrevInstance
 * @param lpszArgument
 * @param nCmdShow
 * @return
 */
int WINAPI WinMain(HINSTANCE hThisInstance, HINSTANCE hPrevInstance, LPSTR lpszArgument, int nCmdShow) {
    
    const bool loadSettings = true;
    const bool fullscreen=true;

    logger.SetLogFile("scrsave.log");
    logger << "start" << "\n";

    hInstance = hThisInstance;

    const char* cmd = ::GetCommandLine();

    logger << "command line:" << cmd << "\n";
    logger.flush();


    //modalità normale applicazione
#ifndef APPLICATION_MODE

    m_currentMode = getFromCommandLine(cmd, externHWND);
    //screen saver mode

    //modalità screen saver
#else

    //DEBUG   
    m_currentMode = SCR_SAVER;
    externHWND = ::GetDesktopWindow();

#endif

    switch (m_currentMode) {

        case SCR_SAVER:
        case SCR_NONE:
            //crea la finestra dello screen saver in modalità full screen e lo esegue
            demo.initialize();

            if (loadSettings) {

                SAVER_SETTINGS s = LoadSettings();

                demo.setDisplayNames(s.displayNames);

                switch (s.rotSpeed) {
                    case 0:
                        demo.setRotSpeed(1.8);
                        break;
                    case 1:
                        demo.setRotSpeed(2.5);
                        break;
                    case 3:
                        demo.setRotSpeed(5.6);
                        break;
                }

                switch (s.colorSpeed) {
                    case 0:
                        demo.setColorGradientSpeed(16);
                        break;
                    case 1:
                        demo.setColorGradientSpeed(32);
                        break;
                    case 2:
                        demo.setColorGradientSpeed(64);
                        break;

                }

                switch (s.transformSpeed) {
                    case 0:
                        demo.setPersistCycles(600);
                        break;
                    case 1:
                        demo.setPersistCycles(120);
                        break;
                    case 2:
                        demo.setPersistCycles(70);
                        break;
                }

                switch (s.screenRes) {
                    case SCREEN_RES_320_200_32:
                        demo.setDisplaySettings(320, 320, 32, fullscreen);
                        break;
                    case SCREEN_RES_640_480_32:
                        demo.setDisplaySettings(640, 480, 32, fullscreen);
                        break;
                    case SCREEN_RES_800_600_32:
                        demo.setDisplaySettings(800, 600, 32, fullscreen);
                        break;
                    case SCREEN_RES_1024_768_32:
                        demo.setDisplaySettings(1024, 768, 32, fullscreen);
                        break;
                    case SCREEN_RES_1152_864_32:
                        demo.setDisplaySettings(1152, 864, 32, fullscreen);
                        break;
                    case SCREEN_RES_1280_720_32:
                        demo.setDisplaySettings(1280, 720, 32, fullscreen);
                        break;
                    case SCREEN_RES_1280_768_32:
                        demo.setDisplaySettings(1280, 768, 32, fullscreen);
                        break;
                    case SCREEN_RES_1280_960_32:
                        demo.setDisplaySettings(1280, 960, 32, fullscreen);
                        break;
                    case SCREEN_RES_1280_1024_32:
                        demo.setDisplaySettings(1280, 960, 32, fullscreen);
                        break;
                    case SCREEN_RES_1360_768_32:
                        demo.setDisplaySettings(1360, 768, 32, fullscreen);
                        break;
                    case SCREEN_RES_1360_1024_32:
                        demo.setDisplaySettings(1360, 1024, 32, fullscreen);
                        break;
                    default:
                        demo.setDisplaySettings(1024, 768, 32, fullscreen);
                        break;

                }

            }
            try {

                demo.start();

            } catch (lwtk::Exception& ex) {

                ::MessageBox(externHWND, ex.GetMsg(), "Error", MB_ICONEXCLAMATION);
            }

            break;
        case SCR_CONFIG:

            ScreenSaverConfigureDialog(externHWND);
            break;

        case SCR_PREVIEW:

            //da fare:creare una child window per il preview
            break;

        case SCR_PASSWORD:

            //non implementato 
            break;
    }

    logger.Close();

    return 0;
}

/**
 * Verifica password (solo per Win9x)
 * @param hwnd
 * @return
 */
BOOL VerifyPassword(HWND hwnd) {

    //determina la versione di Windows
    OSVERSIONINFO osv;
    osv.dwOSVersionInfoSize = sizeof (osv);
    GetVersionEx(&osv);

    //non necessaria sui sistemi operativi succ. a Win98
    if (osv.dwPlatformId == VER_PLATFORM_WIN32_NT) return TRUE;

    HINSTANCE hpwdcpl = ::LoadLibrary(_T("PASSWORD.CPL"));
    if (hpwdcpl == NULL) {
        OutputDebugString("Unable to load PASSWORD.CPL. Aborting");
        return TRUE;
    }
    typedef BOOL(WINAPI * VERIFYSCREENSAVEPWD)(HWND hwnd);
    VERIFYSCREENSAVEPWD VerifyScreenSavePwd;
    VerifyScreenSavePwd = (VERIFYSCREENSAVEPWD) GetProcAddress(hpwdcpl, "VerifyScreenSavePwd");
    if (VerifyScreenSavePwd == NULL) {
        OutputDebugString("Unable to get VerifyPwProc address. Aborting");
        FreeLibrary(hpwdcpl);
        return TRUE;
    }
    OutputDebugString("About to call VerifyPwProc");
    BOOL bres = VerifyScreenSavePwd(hwnd);
    FreeLibrary(hpwdcpl);
    return bres;

}

/**
 * Registra sottoclassi dialog se necessario
 * @param hInst
 * @return
 */
BOOL WINAPI RegisterDialogClasses(HANDLE hInst) {
    //non usata
    return TRUE;
}

/**
 * Acquisisce il valore di un settaggio dal registry
 * @param key
 * @return 
 */
const char* GetSetting(const char* key) {

    HKEY k;
    DWORD valType, valSize, val;
    LONG r = ::RegOpenKey(HKEY_CURRENT_USER, BASE_KEY, &k);
    if (r != ERROR_SUCCESS) return NULL;
    memset(resBuff, 0, BUFF_SIZE);
    LONG res = RegQueryValueEx(k, (LPCSTR) key, 0, &valType, (LPBYTE) resBuff, &valSize);
    if (res != ERROR_SUCCESS) return 0;
    return resBuff;

}

/**
 * Scrive il valore di un settaggio nel registry
 * @param key
 * @param value
 * @return 
 */
bool SaveSetting(const char* key, const char* value) {

    LONG res;
    HKEY skey;
    DWORD val, disp;
    res = RegCreateKeyEx(HKEY_CURRENT_USER, BASE_KEY, 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &skey, &disp);
    if (res != ERROR_SUCCESS) return false;
    res = RegSetValueEx(skey, (LPCSTR) key, 0, REG_SZ, (CONST BYTE*) value, strlen(value) + 1);
    RegCloseKey(skey);
    return res == ERROR_SUCCESS;
}

/**
 *Carica un settaggio e setta il combo 
 */
int LoadComboSetting(ComboBox& cmb, const char* key, int defaultIndex) {

    const char* value = GetSetting(key);

    logger<<"load combo setting from key "<<key<<"=";

    if (value==0) {
        logger<<"null"<<"\n";
    }
    else {
        logger<<value<<"\n";
    }


    //chiave non settata
    if (value == 0) {
        cmb.SetSelectedIndex(defaultIndex);
        return defaultIndex;
    }

    int index = atoi(value);

    if (index >= 0 && index < cmb.GetSize()) {
        cmb.SetSelectedIndex(index);
        return index;
    } else {
        cmb.SetSelectedIndex(defaultIndex);
        return defaultIndex; //valore normale
    }
}

/**
 *Salva un settaggio leggendo il valore selezionato dal combo * 
 */
bool SaveComboSetting(ComboBox& cmb, const char* key) {

    memset(resBuff, 0, BUFF_SIZE);
    sprintf(resBuff, "%d", cmb.GetSelectedIndex());
    SaveSetting(key, resBuff);

}

/**
 *Salva i settaggi dello screen saver nel registry leggendoli dai controlli
 * del dialog di configurazione
 */
void SaveSettings() {

    //visualizza nomi superfici
    SaveSetting(SET_DISPLAY_NAMES, chkNames->IsSelected() ? "1" : "0");
    //screen res
    SaveComboSetting(*cmbRes, SET_SCRN_RES);
    //rot speed
    SaveComboSetting(*cmbRotSpeed, SET_ROT_SPEED);
    //valocità trasformazione
    SaveComboSetting(*cmbTransformSpeed, SET_TRANSFORM_SPEED);
    //velocità cambio colore
    SaveComboSetting(*cmbColorSpeed, SET_COLOR_SPEED);
}

/**
 *Carica i settaggi dello screen saver dal registry
 */
SAVER_SETTINGS LoadSettings() {

    SAVER_SETTINGS s;
    //setta i valori di default
    s.displayNames = false; //visualizza i nomi delle funzioni
    s.screenRes = SCREEN_RES_1024_768_32; //risoluzione in modalità full screen
    s.rotSpeed = 1; //celocità rotazione
    s.transformSpeed = 1; //velocità trasformazione
    s.colorSpeed = 1; //velocità variazione gradiente colore

    const char* value = GetSetting(SET_DISPLAY_NAMES);
    if (value) s.displayNames = (strcmp(value, "1") == 0);
    value = GetSetting(SET_SCRN_RES);
    if (value) s.screenRes = atoi(value);
    value = GetSetting(SET_ROT_SPEED);
    if (value) s.rotSpeed = atoi(value);
    value = GetSetting(SET_TRANSFORM_SPEED);
    if (value) s.transformSpeed = atoi(value);
    value = GetSetting(SET_COLOR_SPEED);
    if (value) s.colorSpeed = atoi(value);

    return s;
}

/**
 * Visualizza i settaggi sul dialog
 * @param s
 */
void ShowSettings(const SAVER_SETTINGS& s) {

    chkNames->SetSelected(s.displayNames);
    cmbRes->SetSelectedIndex(s.screenRes);
    cmbRotSpeed->SetSelectedIndex(s.rotSpeed);
    cmbColorSpeed->SetSelectedIndex(s.colorSpeed);
    cmbTransformSpeed->SetSelectedIndex(s.transformSpeed);

}

