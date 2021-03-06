#ifndef FONT_H_INCLUDED
#define FONT_H_INCLUDED

#include "videodef.h"
#include <tchar.h>

#ifdef _USEVIDEONAMESPACE_
namespace video
{
#endif

/**Font*/
    class Font
    {
        public:

        static const int ATTR_NONE=0x0;
        static const int ATTR_BOLD=0x1;
        static const int ATTR_ITALIC=0x2;
        static const int ATTR_UNDERLINE=0x4;
        static const int ATTR_STRIKE_OUT=0x8;

        virtual ~Font() {}
        virtual const TCHAR* GetFontName()=0;
        /**Restituisce la dimensione in punti del font*/
        virtual int GetSize()=0;
        virtual bool IsBold()=0;
        virtual bool IsItalic()=0;
        virtual bool IsUnderline()=0;
        virtual bool IsStrikeout()=0;
        virtual int GetAttributes()=0;
    };

#ifdef _USEVIDEONAMESPACE_
};
#endif

#endif // FONT_H_INCLUDED
