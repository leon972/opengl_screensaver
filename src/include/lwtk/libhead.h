#ifndef LIBHEAD_H_INCLUDED
#define LIBHEAD_H_INCLUDED

#define CREATE_DLL
//#define CREATE_VB_EXPORT //funzioni esportate per Visual Basic

#ifdef CREATE_DLL
#define DLL_EXPORT __declspec(dllexport)
#else
//compilato come eseguibile o come libreria statica
#define DLL_EXPORT
#endif

#ifdef CREATE_VB_EXPORT
#undef DLL_EXPORT
#define DLL_EXPORT __stdcall __declspec(dllexport) //le funzioni esportabili per visual basic devono avere __stdcall
#endif

#endif // LIBHEAD_H_INCLUDED
