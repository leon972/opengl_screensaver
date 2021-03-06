/***************************************
Alcune definizioni usate dal math engine
*****************************************/
/*!
 * \file mathdefs.h
 * \brief Math constants and global definitions.
 
 */

#ifndef MATHDEFS_H_INCLUDED
#define MATHDEFS_H_INCLUDED

#define _USEDEFAULT_

/**Default settings*/
#ifdef _USEDEFAULT_
#undef _USEDOUBLE_
#define _USENAMESPACE_
#endif

/**
 *Deg to Rad conversion factor
 */
#define DEG_TO_RAD_CONV 0.01745329251994329577

/**
 *Rad to Deg conversion factor
 */
#define RAD_TO_DEG_CONV 57.2957795130823208768

/**
 *Degrees to radians conversion
 */
#define DEG_TO_RAD(x) x*DEG_TO_RAD_CONV

/**
 *Radians to degrees conversion
 */
#define RAD_TO_DEG(x) x*RAD_TO_DEG_CONV

#define _USENAMESPACE_

#ifdef _USENAMESPACE_
namespace mathengine
{
#endif

/**
 * Real number
 */
#define REAL double

const double EPSILON=0.0000000001;

/**
 *Single variable function pointer  y=f(x)
 */
typedef REAL (*FUNCT_X)(REAL);

/**
 *Double variable function pointer  z=f(x,y)
 */
typedef REAL (*FUNCT_XY)(REAL,REAL);

/**
 *Triple variable function pointer v=f(x,y,z)
 */
typedef REAL (*FUNCT_XYZ)(REAL,REAL,REAL);

/**
 *Division by zero exception
 */
class DivideByZeroVideoException {};

/**
 *Generic invalid argument exception
 */
class InvalidArgumentException {};

/**
 *No solution exception
 */
class NoSolutionException {};

/**
 *Functor interface y=f(x)
 */
class IFunctionX
{
    public:
    virtual REAL operator()(REAL x)=0;
};

/**
 *Functor interface z=f(x,y)
 */
class IFunctionXY
{
    public:
    virtual REAL operator()(REAL x,REAL y)=0;
};

/**
 *Functor interface v=f(x,y,z)
 */
class IFunctionXYZ
{
    public:
    virtual REAL operator()(REAL x,REAL y,REAL z)=0;
};


/**
 *Template  based functor interface y=f(x)
 */
template <class T> class TFunctionX
{
    public:
    virtual T operator()(REAL x)=0;
};

/**
 *Template  based functor z=f(x,y)
 */
template <class T> class TFunctionXY
{
    public:
    virtual T operator()(REAL x,REAL y)=0;
};

/**
 *Template  based functor v=f(x,y,z)
 */
template <class T> class TFunctionXYZ
{
    public:
    virtual T operator()(REAL x,REAL y,REAL z)=0;
};


#ifdef _USENAMESPACE_
};
#endif

#endif // MATHDEFS_H_INCLUDED
