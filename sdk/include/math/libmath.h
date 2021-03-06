/**************************************
parametri compilazione libreria LMath
***************************************/

#ifndef LIBMATH_H_INCLUDED
#define LIBMATH_H_INCLUDED
//----------------------------------------------------------------------

//definire questo flag quando si vuol esportare su DLL
#define CREATE_MATH_DLL
//#define CREATE_MATH_VB_EXPORT //funzioni esportate per Visual Basic

#ifdef CREATE_MATH_DLL
#include <windows.h>
#define MATH_EXPORT __declspec(dllexport)
#else
//compilato come eseguibile
#define MATH_EXPORT
#endif

#ifdef CREATE_MATH_VB_EXPORT
#undef MATH_EXPORT
#define MATH_EXPORT __stdcall __declspec(dllexport) //le funzioni esportabili per visual basic devono avere __stdcall
#endif

#endif // LIBMATH_H_INCLUDED
