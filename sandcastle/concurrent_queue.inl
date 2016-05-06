/*!************************************************************
	Created	:	2016/03/08
	Intent	:		
		
	Usage	:
		
	Note	:
		
**************************************************************/
#ifndef multicore_lockless_queue_inl__
#define multicore_lockless_queue_inl__

#include "concurrent_queue.h"
#include "concurrent_thread.h"
#include "include_std.h"

namespace Concurrent
{

  /**************************************************************

  **************************************************************/
  template<typename T>
  Node<T>::Node(const T& obj, Node<T>* ptr)
    : m_val(obj)
    , m_next(ptr)
  {

  }

  /*!************************************************************

  **************************************************************/
  template<typename T>
  LockFreeQueue<T>::~LockFreeQueue()
  {
    T temp;
    while (Dequeue(temp) == true); //force the system to end everything
  }

  /**************************************************************

  **************************************************************/
  template<typename T>
  int LockFreeQueue<T>::RecountSize() const
  {
    int size = 0;

    const auto& head = m_head;
    const auto& tail = m_tail;

    Node<T>* ptr = m_head.load()->m_next;
    Thread::hazardous[0] = ptr;

    while (ptr != nullptr)
    {
      Thread::hazardous[1] = ptr->m_next.load();

      ++size;
      ptr = ptr->m_next;

      if (size > m_count)// + COUNT_EPSILON)
        return -1;

      Thread::hazardous[1].exchange(Thread::hazardous[0].exchange(Thread::hazardous[1]));
    }

    Thread::hazardous.ResetHazardRecord();

    return size;
  }

  /**************************************************************

  **************************************************************/
  template<typename T>
  Node<T>* LockFreeQueue<T>::MakeNode(const T& obj)
  {
    Node<T>* ptr = new Node<T>(obj);
    return ptr;
  }

  /**************************************************************

  [m_front_guard]->[m_rear_guard]->[NULL]

  We will want to insert between front and rear guards

  **************************************************************/
  template<typename T>
  LockFreeQueue<T>::LockFreeQueue()
    : m_rear_guard(T{}, nullptr)
    , m_front_guard(T{}, nullptr)
    , m_head(const_cast<Node<T>*>(&m_front_guard))
    , m_tail(const_cast<Node<T>*>(&m_front_guard))
    , m_count(0)
  {
  }

  /**************************************************************

  **************************************************************/
  template<typename T>
  int LockFreeQueue<T>::Size() const
  {
    return m_count;
  }

  /**************************************************************
  it goes something like this:

  We start at the tail
  - The tail should point to the sentinel node.
  - if it does not, we try again, from the tail
  - if it does, we try to atomically set the current tail to point to us instead of the sentinel
  - this means that the node must already point to the sentinel, so we don't have to do 2 atomics and fuck it up
  Once we do that we can increment the size count and return from the infinite loop;

  We must always guarantee progress, meaning we can't rely on other threads
  to update the nodes

  ABA problem?
  **************************************************************/
  template<typename T>
  void LockFreeQueue<T>::Enqueue(const T& obj)
  {
    Node<T>* ptr = MakeNode(obj);
    ptr->m_next.store(nullptr);

    const auto& front = m_head;

    Node<T>* tail = nullptr;

    while (true)
    {
      //As a thread, I expect these to be the most updated pointers
      tail = m_tail;
      Thread::hazardous[0].store(tail);

      if (tail != m_tail)
        continue;

      Node<T>* tail_next = tail->m_next; //this should point to m_rear_guard

                                         //if after grabbing them, they changed, someone must have done something
      if (tail != m_tail)
        continue;

      if (tail_next != nullptr)
      {
        //SLEEP_THREAD;
        m_tail.compare_exchange_weak(tail, tail_next);
        continue;
      }

      //if nobody changed it, I atomically append the new node to the back
      //spurious failure is acceptable here, since I'm looping infinitely
      Node<T>* back = nullptr;

      //SLEEP_THREAD;
      if (tail->m_next.compare_exchange_weak(back, ptr))
      {
        //and then update the tail, so it's now accurate.
        //Everyone else starting at the tail would now break at line 118
        //even if they are past line 118, they will fail the compare_exchange
        //so I have all the time in the world to update the tail

        //SLEEP_THREAD;
        m_tail.compare_exchange_weak(tail, ptr);

        Thread::hazardous.ResetHazardRecord();
        ++m_count;
        return;
      }
    }
  }

  /**************************************************************
  Similar to the enqueue function

  We start from the head
  - If the head is pointing to the sentinel node, the queue is technically empty and we just stop.
  - Otherwise we attempt to atomically point the head to the next item in the list.
  - We keep trying until we get it done, then mark the pointer for retirement
  **************************************************************/
  template<typename T>
  bool LockFreeQueue<T>::Dequeue(T& obj)
  {
    while (true)
    {
      //the thread expects the head to look like this
      Node<T>* head = m_head;                      //should be front_guard
      Thread::hazardous[0].store(head);
      if (head != m_head)
        continue;

      Node<T>* tail = m_tail;

      Node<T>* head_next = head->m_next;           //could be m_rear_guard
      Thread::hazardous[1].store(head_next);
      if (head != m_head)
        continue;

      if (head_next == nullptr)
      {
        Thread::hazardous.ResetHazardRecord();
        return false;
      }

      if (head == tail)
      {
        //SLEEP_THREAD;
        m_tail.compare_exchange_weak(tail, head_next);
        continue;
      }

      //why this again? I mean getting the value *before* popping it off the list
      T val = head_next->m_val;

      //SLEEP_THREAD;
      if (m_head.compare_exchange_weak(head, head_next))
      {
        obj = std::move(val);

        Thread::hazardous.ResetHazardRecord();

        if (head != &m_front_guard && head != &m_rear_guard)
        {
          Thread::hazardous.Retire(head);
        }

        --m_count;
        return true;
      }
    }
  }

} //namespace Concurrent

#endif // multicore_lockless_queue_h__
/*!************************************************************
	Todo:
			
	References:
		
**************************************************************/


