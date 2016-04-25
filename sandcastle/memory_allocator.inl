/*!************************************************************
	Created	:	2016/04/25
	Intent	:		
		
	Usage	:
		```
			
		```
	Note	:
		
**************************************************************/
#ifndef memory_allocator_inl__
#define memory_allocator_inl__

#include <utility>
#include <cstdlib>

namespace Memory
{
  /*!************************************************************

  **************************************************************/
  template<typename T>
  template<typename U>
  void Allocator<T>::destroy(U* p)
  {
    p->~U();
  }

  /*!************************************************************

  **************************************************************/
  template<typename T>
  void Allocator<T>::destroy(pointer p)
  {
    ((T*)p)->~T();
  }

  /*!************************************************************

  **************************************************************/
  template<typename T>
  template<typename U, typename...Args>
  void Allocator<T>::construct(U* p, Args&&... args)
  {
    :: new((void*)p) U(std::forward<Args>(args)...);
  }

  /*!************************************************************

  **************************************************************/
  template<typename T>
  void Allocator<T>::construct(pointer p, const_reference val)
  {
    new((void*)p) T(val);
  }

  /*!************************************************************

  **************************************************************/
  template<typename T>
  void Allocator<T>::deallocate(pointer p, size_type n)
  {
    free(pointer);
  }

  /*!************************************************************

  **************************************************************/
  template<typename T>
  typename Allocator<T>::pointer Allocator<T>::allocate(size_type n, Allocator<void>::const_pointer hint /*= nullptr*/)
  {
    return (pointer)malloc(sizeof(T) * n);
  }

} //namespace Memory

#endif // memory_allocator_h__
/*!************************************************************
	Todo:
			
	References:
		
**************************************************************/


