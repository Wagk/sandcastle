/*!************************************************************
	Created	:	2016/04/27
	Intent	:		
		
	Usage	:
		```
			
		```
	Note	:
		
**************************************************************/
#ifndef export_macros_h__
#define export_macros_h__

#ifdef SANDCASTLE_DLL
#define SANDCASTLE_API __declspec(dllexport) 
#else
#define SANDCASTLE_API __declspec(dllimport)
#endif

#endif // export_macros_h__
/*!************************************************************
	Todo:
			
	References:
		
**************************************************************/


