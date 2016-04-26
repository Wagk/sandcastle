/*!************************************************************
Created	:	2016/03/03
Intent	:

Usage	:

Note	:
Jobs, on completion, should tell all the triggers
that they are done. This is so that JobBlocks can
know when every job they are responsible for is
complete, and they can move on with their lives
**************************************************************/
#ifndef export_macros_h__
#define export_macros_h__

//I am defining the SANDCASTLE_DLL Macro for the sandcastle project.

#ifdef SANDCASTLE_DLL
#define SANDCASTLEAPI __declspec(dllexport) 
#else
#define SANDCASTLEAPI __declspec(dllimport)
#endif


#endif