#ifndef INPUT_EXCEPTION_H
#define	INPUT_EXCEPTION_H

#include "lwtk/libhead.h"
#include <string>
#include <list>
#include <tchar.h>

using namespace std;

namespace inputmanager {

    class DLL_EXPORT InputException {
    private:

        list<string> err_stack;
        int id;
        TCHAR* tmp_message;

    public:

        InputException(string msg);
        InputException(const TCHAR* formatText ...);
        InputException(InputException* parent, const TCHAR* formatText ...);
        int SetErrId(int err_id);
        InputException();
        virtual ~InputException();
        const TCHAR* GetMsg() const;
        int GetId() const;
        const TCHAR* GetStackTrace() const;

    };

};


#endif	/* VIDEO_VideoException_H */

