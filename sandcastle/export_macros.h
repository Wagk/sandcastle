/*!************************************************************
Created	:	2016/03/03
Intent	:

Usage	:

Note	:

**************************************************************/
#ifndef export_macros_h__
#define export_macros_h__

//I am defining the SANDCASTLE_DLL Macro for the sandcastle project.

#ifdef SANDCASTLE_DLL
#define SANDCASTLE_API __declspec(dllexport) 
#else
#define SANDCASTLE_API __declspec(dllimport)
#endif


#endif