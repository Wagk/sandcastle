/*!************************************************************
	Created	:	2016/04/25
	Intent	:		
		
	Usage	:
		```
			
		```
	Note	:
		
**************************************************************/
#ifndef memory_allocator_h__
#define memory_allocator_h__

#include <cstddef>

namespace Memory
{
  template<typename T>
  class Allocator
  {
  public:

    using value_type = T;
    using pointer = T*;
    using const_pointer = const T*;
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;
    using reference = T&;
    using const_reference = const T&;

    template<typename U>
    struct rebind
    {
      using other = Allocator<U>;
    };

    pointer allocate(size_type n, Allocator<void>::const_pointer hint = nullptr);
    void deallocate(pointer p, size_type n);

    void construct(pointer p, const_reference val);
    template<typename U, typename... Args>
    void construct(U* p, Args&&... args);
    
    void destroy(pointer p);
    template<typename U>
    void destroy(U* p);

  private:


  };



}

#endif // utility_allocator_h__
/*!************************************************************
	Todo:
			
	References:
		
**************************************************************/


