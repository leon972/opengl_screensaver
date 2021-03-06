#include "lwtk/exception.h"
#include <tchar.h>
#include <cstdio>
#include <stdarg.h>
#include <mem.h>
#include <string>

namespace lwtk {

    using namespace std;

    //costruttore protetto usato dalla classi derivate
    Exception::Exception():err_stack()
    {
        tmp_message=0;
        id=0;
    }

    Exception::Exception(string msg):err_stack()
    {
        id=0;
        err_stack.push_back(msg);
    }

    Exception::Exception(const TCHAR* formatText ...):err_stack() {

        const unsigned msg_size=1024;

        tmp_message=new TCHAR[msg_size];
        memset(tmp_message,0,msg_size*sizeof(TCHAR));

        va_list		argumentPtr; //punta alla lista degli argomenti opzionali

        if (formatText == NULL) return;

        va_start(argumentPtr, formatText);

        vsprintf(tmp_message, formatText, argumentPtr);

        va_end(argumentPtr);

        err_stack.push_back(tmp_message);

        id=0;

    }

    Exception::Exception(Exception* parent,const TCHAR* formatText ...):err_stack()
    {
        const unsigned msg_size=1024;

        if (parent)
        {
            list<string>::iterator it=err_stack.begin();
            err_stack.insert(it,parent->err_stack.begin(),parent->err_stack.end());
        }

        tmp_message=new TCHAR[msg_size];
        
        memset(tmp_message,0,msg_size*sizeof(TCHAR));

        va_list		argumentPtr; //punta alla lista degli argomenti opzionali

        if (formatText == NULL) return;

        va_start(argumentPtr, formatText);

        vsprintf(tmp_message, formatText, argumentPtr);

        va_end(argumentPtr);

        err_stack.push_back(tmp_message);

        id=0;
    }
  
    int Exception::SetErrId(int err_id)
    {
        id=err_id;
        return id;
    }

    Exception::~Exception() {

        if (tmp_message)
        {
            delete[] tmp_message;
            tmp_message=0;
        }
    }

    const TCHAR* Exception::GetMsg() const {
        return err_stack.back().c_str();

    }

    int Exception::GetId() const {
        return id;
    }

    const TCHAR* Exception::GetStackTrace() const
    {
        string res="";

        if (err_stack.size()) res.reserve(30*err_stack.size());

        for (list<string>::const_reverse_iterator it=err_stack.rbegin();it!=err_stack.rend();it++)
        {
            res+=(*it);
            res+="\n";
        }

        return res.c_str();
    }

};

