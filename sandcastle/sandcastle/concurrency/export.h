#ifndef export_h__
#define export_h__

#ifdef CONCURRENCY_EXPORTS

#define CONCURRENCY_API __declspec(dllexport)

#else

#define CONCURRENCY_API __declspec(dllimport)

#endif

#endif