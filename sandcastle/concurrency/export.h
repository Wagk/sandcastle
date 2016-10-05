#ifndef export_h__
#define export_h__

#ifdef CONCURRENCY_EXPORTS

#define SANDCASTLE_CONCURRENCY_API __declspec(dllexport)

#else

#define SANDCASTLE_CONCURRENCY_API __declspec(dllimport)

#endif

#endif