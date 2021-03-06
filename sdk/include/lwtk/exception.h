/**********************************
Eccezione generica base
Code by L.Berti (c) 2008
***********************************/

#ifndef VideoException_H_INCLUDED
#define VideoException_H_INCLUDED

#include "lwtk/libhead.h"
#include <string>
#include <list>
#include <tchar.h>

using namespace std;

namespace lwtk
{

class DLL_EXPORT Exception
{
    private:

    list<string> err_stack;
    int id;
    TCHAR* tmp_message;

    public:

    Exception(string msg);
    Exception(const TCHAR* formatText ...);
    Exception(Exception* parent,const TCHAR* formatText ...);
   // VideoException(string msg,VideoException* parent);//ambigua
    int SetErrId(int err_id);
    Exception();
    virtual ~Exception();
    const TCHAR* GetMsg() const;
    int GetId() const;
    const TCHAR* GetStackTrace() const;

};

};




#endif // VideoException_H_INCLUDED
