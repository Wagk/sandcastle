/*!************************************************************
	Created	:	2016/03/08
	Intent	:		
		
	Usage	:
		
	Note	:
		
**************************************************************/
#ifndef multicore_hazard_inl__
#define multicore_hazard_inl__

#include "concurrent_hazard.h"
#include "concurrent_thread.h"

#include "include_assert.h"

namespace Concurrent
{
  /**************************************************************

  **************************************************************/
  template<unsigned HazardCount, ForHazard Type>
  std::atomic<void*>& HazardPackage<HazardCount, Type>::operator[](size_t index)
  {
    //find someway to guarantee that you'll never exceed the count
    auto& records = HazardManager<HazardCount, Type>::Get().m_record;

    return records[Thread::info.GetID() * HazardCount + index];
  }

  /**************************************************************

  **************************************************************/
  template<unsigned HazardCount, ForHazard Type>
  HazardPackage<HazardCount, Type>::HazardPackage()
    : m_retire_list()
  {

  }

  /**************************************************************

  **************************************************************/
  template<unsigned HazardCount, ForHazard Type>
  void HazardPackage<HazardCount, Type>::ResetHazardRecord()
  {
    for (unsigned i = 0; i < HazardCount; ++i)
    {
      operator[](i).store(nullptr);
    }
  }


  /**************************************************************
  how does this fight double deletion?

  It should be able to fight double deletion since each thread
  is responsible for resetting their hazard pointers when not
  in use.

  When juggling a pointer that is shared by multiple threads.
  It stands to reason that there will be a single thread where
  it holds the last reference to the pointer. When that
  **************************************************************/
  template<unsigned HazardCount, ForHazard Type>
  void HazardPackage<HazardCount, Type>::Cleanup()
  {
    std::vector<void*> prunelist;

    auto& hazardlist = HazardManager<HazardCount, Type>::Get().m_record;

    for (std::atomic<void*>& elem : hazardlist)
    {
      void* ptr = elem.load();

      if (ptr != nullptr)
      {
        prunelist.push_back(ptr);
      }
    }

    std::sort(prunelist.begin(), prunelist.end());

    std::vector<void*> purge_list = std::move(m_retire_list);
    m_retire_list.clear();

    while (purge_list.empty() == false)
    {
      void*& ptr_r = purge_list.back();
      if (std::binary_search(prunelist.begin(), prunelist.end(), ptr_r) == true)
      {
        m_retire_list.push_back(ptr_r);
      }
      else
      {
        delete ptr_r;
      }
      purge_list.pop_back();
    }
  }

  /**************************************************************

  **************************************************************/
  template<unsigned HazardCount, ForHazard Type>
  void HazardPackage<HazardCount, Type>::Retire(void* ptr)
  {
    m_retire_list.push_back(ptr);

    if (m_retire_list.size() > HazardCount << 1)
      Cleanup();
  }

  /**************************************************************

  **************************************************************/
  template<unsigned HazardCount, ForHazard Type>
  HazardManager<HazardCount, Type>::HazardManager(size_t num_threads)
    : m_record{} //generate those records and store them to nullptr
  {
    EXPECT(num_threads < Threads); //we're hacking and fixing an upper bound for threads

    for (std::atomic<void*>& elem : m_record)
    {
      elem.store(nullptr);
    }
  }



  /**************************************************************

  **************************************************************/
  template<unsigned HazardCount, ForHazard Type>
  HazardManager<HazardCount, Type>& HazardManager<HazardCount, Type>::Get()
  {
    static HazardManager<HazardCount, Type> singleton(HARDWARE_CONCURRENCY);

    return singleton;
  }


} //namespace Concurrent

#endif // multicore_hazard_h__
/*!************************************************************
	Todo:
			
	References:
		
**************************************************************/


