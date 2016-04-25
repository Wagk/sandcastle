/*!************************************************************
Created	:	2016/03/03
Intent	:

Usage	:

Note	:

**************************************************************/
#ifndef hazardptr_h__
#define hazardptr_h__

#include <vector>
#include <array>
#include <atomic>

#include "include_assert.h"

namespace Concurrent
{

  enum ForHazard
  {
    SCHEDULING
  };

  //used per thread
  template<unsigned HazardCount, ForHazard Type>
  class HazardPackage
  {
  public:

    HazardPackage();

    void Retire(void* ptr);
    void ResetHazardRecord();

    std::atomic<void*>& operator[](size_t index);

    void Cleanup();

  private:

    std::vector<void*> m_retire_list;

  };

  //used across all threads
  //number of threads is declared when constructing
  template<unsigned HazardCount, ForHazard Type>
  class HazardManager
  {
  public:

    template<unsigned HazardCount, ForHazard Type>
    friend class HazardPackage;

    static HazardManager& Get();


  private:

    static const size_t Threads = 20; //this is a hardcoded value

    HazardManager(size_t num_threads); //typically std::thread::hardware_concurrency

    std::array<std::atomic<void*>, Threads * HazardCount> m_record;
    //std::vector<std::atomic<void*>> m_record;


  };

  

} //namespace Concurrent

#include "concurrent_hazard.inl"

#endif
/*!************************************************************
Todo:

**************************************************************/