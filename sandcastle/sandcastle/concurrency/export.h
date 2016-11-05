#ifndef export_h__
#define export_h__

#ifdef DLL_EXPORT
#ifdef CONCURRENCY_EXPORTS

#define SANDCASTLE_CONCURRENCY_API __declspec(dllexport)

#else

#define SANDCASTLE_CONCURRENCY_API __declspec(dllimport)

#endif
#else

#define SANDCASTLE_CONCURRENCY_API

#endif

#endif