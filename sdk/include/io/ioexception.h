/* 
 * File:   ioexception.h
 * Author: Proprietario
 *
 * Created on 18 marzo 2011, 19.04
 */

#ifndef IOEXCEPTION_H
#define	IOEXCEPTION_H

#include "lwtk/libhead.h"
#include <string>
#include <list>
#include <tchar.h>

using namespace std;

namespace io {   

    class DLL_EXPORT IOException {
    private:

        list<string> err_stack;
        int id;
        TCHAR* tmp_message;

    public:

        IOException(string msg);
        IOException(const TCHAR* formatText ...);
        IOException(IOException* parent, const TCHAR* formatText ...);
        int SetErrId(int err_id);
        IOException();
        virtual ~IOException();
        const TCHAR* GetMsg() const;
        int GetId() const;
        const TCHAR* GetStackTrace() const;

    };

};


#endif	/* IOEXCEPTION_H */

