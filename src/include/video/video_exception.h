/* 
 * File:   video_VideoException.h
 * Author: Leonardo Berti (c) 2011
 *
 * Created on 18 marzo 2011, 18.49
 */

#ifndef VIDEO_VideoException_H
#define	VIDEO_VideoException_H


#include "lwtk/libhead.h"
#include <string>
#include <list>
#include <tchar.h>

using namespace std;

namespace video {

    class DLL_EXPORT VideoException {
    private:

        list<string> err_stack;
        int id;
        TCHAR* tmp_message;

    public:

        VideoException(string msg);
        VideoException(const TCHAR* formatText ...);
        VideoException(VideoException* parent, const TCHAR* formatText ...);
        int SetErrId(int err_id);
        VideoException();
        virtual ~VideoException();
        const TCHAR* GetMsg() const;
        int GetId() const;
        const TCHAR* GetStackTrace() const;

    };

};


#endif	/* VIDEO_VideoException_H */

