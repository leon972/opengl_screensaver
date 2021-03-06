/*******************************
Utilit� di formattazione
implementazione Win32
Code by L.Berti 2009
********************************/

#ifndef FORMATW32_H_INCLUDED
#define FORMATW32_H_INCLUDED

#include "util/format.h"


namespace util
{
    class NumberFormatWin32:public NumberFormat
    {
        public:

        virtual int ParseInt(const TCHAR* text) throw (ParseVideoException);
        virtual float ParseFloat(const TCHAR* text) throw (ParseVideoException);
        virtual double ParseDouble(const TCHAR* text) throw (ParseVideoException);
        virtual const TCHAR* format(int n);
        virtual const TCHAR* format(float n);
        virtual const TCHAR* format(double n);
    };
};

#endif // FORMATW32_H_INCLUDED
