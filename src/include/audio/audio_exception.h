/* 
 * File:   AudioException.h
 * Author: Proprietario
 *
 * Created on 30 settembre 2010, 21.19
 */

#ifndef AUDIOVideoException_H
#define	AUDIOVideoException_H

#include <string>
#include <list>
#include <tchar.h>
#include "lwtk/libhead.h"

using namespace std;

namespace audio {

    class DLL_EXPORT AudioException {
    private:

        list<string> err_stack;
        int id;
        TCHAR* tmp_message;

    public:        
   
        AudioException(string msg);
        AudioException(const TCHAR* formatText ...);
        AudioException(AudioException* parent, const TCHAR* formatText ...);
        int SetErrId(int err_id);
        AudioException();
        virtual ~AudioException();
        const TCHAR* GetMsg() const;
        int GetId() const;
        const TCHAR* GetStackTrace() const;

    };

};

#endif	/* AUDIOVideoException_H */

