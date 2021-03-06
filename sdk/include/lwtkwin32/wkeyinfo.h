#ifndef WKEYINFO_H_INCLUDED
#define WKEYINFO_H_INCLUDED

namespace lwtk {

#define WIN32_LEAN_AND_MEAN

#include "lwtk/lwtk.h"
#include "windows.h"

class Win32KeyInfo:public KeyInfo {
private:

        static const size_t str_size=32;
        TCHAR key_name[str_size];
        int key_code;
        LPARAM lParam;

public:

        Win32KeyInfo() {
            key_code=0;
            memset(key_name,0,str_size);
        }


        void Set(LPARAM lParam,WPARAM wParam) {
            key_code=wParam;
            GetKeyNameText(lParam,key_name,str_size);
            this->lParam=lParam;

        }

        /**acquisisce un flag esteso del tasto*/
        int GetExtendedKeyFlag() const
        {
            //if (lParam & 1<<24) return 1 non funziona
            //else return 0;
            //distingue fra tasto destro e sinistro (solo per shift e ctrl)
            if (lParam==(LPARAM)0xC0360001 || lParam==(LPARAM)0x360001 || lParam==(LPARAM)0xC11D0001 || lParam==(LPARAM)0x11D0001) return 1;
            else return 0;
        }

        int GetKeyCode() const {
            return key_code;
        }

        char GetKeyChar() const {
            return static_cast<char>(key_code);
        }

        const TCHAR* GetKeyName() const {
            return static_cast<const TCHAR*>(key_name);
        }
    };

};

#endif // WKEYINFO_H_INCLUDED
