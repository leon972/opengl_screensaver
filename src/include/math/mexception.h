/*!
 \file mexception.h
 \brief Generic math exception class.
 */

#ifndef MVideoException_H_INCLUDED
#define MVideoException_H_INCLUDED

#include "mathdefs.h"
#include "libmath.h"
#include <list>
#include <string>

#ifdef _USENAMESPACE_
namespace mathengine {
#endif

    using namespace std;

class MATH_EXPORT MathException
{
    private:

    list<string> err_stack;
    int id;
    TCHAR* tmp_message;

    public:

    MathException(const string &msg);
    MathException(const TCHAR* formatText ...);
    MathException(MathException* parent,const TCHAR* formatText ...);
   // VideoException(string msg,VideoException* parent);//ambigua
    int SetErrId(int err_id);
    MathException();
    virtual ~MathException();
    const TCHAR* GetMessage() const;
    int GetId() const;
    const TCHAR* GetStackTrace() const;

};


#ifdef _USENAMESPACE_
};
#endif

#endif // MVideoException_H_INCLUDED
