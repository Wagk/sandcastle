/*!************************************************************
  Created	:	2016/05/25
  Note	:

**************************************************************/
#include "testing_concurrency.h"

#include "sandcastle/concurrent_dispatcher.h"
#include "sandcastle/concurrent_queue.h"
#include "sandcastle/concurrent_thread.h"
#include "sandcastle/concurrent_process_graph.h"
#include "sandcastle/concurrent_light_job.h"
#include "sandcastle/include_std.h"
#include "sandcastle/concurrent_worker.h"
#include "sandcastle/concurrent_worker_mutex.h"
#include "sandcastle/utility_timestep.h"

namespace Testing
{

  //atomic init
  size_t CounterJob::s_counter = 0;
  Mutex CounterJob::s_mutex;

  /*!************************************************************

  **************************************************************/
  void Concurrency()
  {
    Concurrent::SimpleDispatcher block;

    const size_t numjobs = 200;

    Vector<SharedPtr<Concurrent::Job>> counters;

    Atomic<int> atomic = 0;

    for (size_t i = 0; i < numjobs; ++i)
    {
      counters.push_back(std::make_shared<Concurrent::LightJob>([&atomic]() {++atomic; }));
      block.Insert(counters.back().get());
    }

    block.Run();

    std::cout << atomic << std::endl;

    block.Clear();

    std::cout << "I'm done" << std::endl;
  }

  /*!************************************************************

  **************************************************************/
  void ProcessChain()
  {
    using Concurrent::SimpleDispatcher;
    using Concurrent::ProcessGraphNode;
    using Concurrent::LightJob;
    using Concurrent::Job;

    const size_t numjobs = 10000;

    Vector<Job*> counter1;
    Vector<Job*> counter2;

    Atomic<int> atomic1 = 0;
    Atomic<int> atomic2 = 0;

    Mutex lock1;
    Mutex lock2;

    for (size_t i = 0; i < numjobs; ++i)
    {
      counter1.push_back(new LightJob([&atomic1, &lock1]() {
        std::lock_guard<Mutex> lock(lock1);
        ++atomic1;
        std::cout << "lock1 " << atomic1 
          << " " << Concurrent::Thread::GetInfo().GetID() << std::endl;
      }));
      counter2.push_back(new LightJob([&atomic2, &lock2]() {
        std::lock_guard<Mutex> lock(lock2);
        ++atomic2;
        std::cout << "lock2 " << atomic2 
          << " " << Concurrent::Thread::GetInfo().GetID() << std::endl;
      }));
    }

    ProcessGraphNode g1 = SimpleDispatcher(counter1);
    ProcessGraphNode g2 = SimpleDispatcher(counter2);

    g1.SetNextNode(&g2);

    Utility::StartTimer();
    g1.Run(); //not actually implemented

    while (atomic1.load() != numjobs || atomic2.load() != numjobs)
    {
      Concurrent::WorkSingleJob();
    } //loop
    Utility::EndTimer();

    std::cout << Utility::GetTimeStep() << std::endl;

    for (size_t i = 0; i < numjobs; ++i)
    {
      delete counter1[i];
      delete counter2[i];
    }

  }

  /*!************************************************************

  **************************************************************/
  CounterJob::CounterJob()
    : Concurrent::Job()
  {

  }

  /*!************************************************************

  **************************************************************/
  void CounterJob::JobDefinition()
  {
    std::lock_guard<Mutex> lock(s_mutex);

    ++s_counter;

    std::cout << s_counter << std::endl;
  }

  /*!************************************************************

  **************************************************************/
  void TestJob::JobDefinition()
  {
    //Concurrency();
    ProcessChain();
  }

  /*!************************************************************

  **************************************************************/
  TestJob::TestJob()
    : Concurrent::Job()
  {

  }

} //namespace Testing


/*!************************************************************
  Todo:

  References:

**************************************************************/
