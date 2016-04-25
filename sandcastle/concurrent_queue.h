/*!************************************************************
Created	:	2016/03/03
Intent	:

Usage	:

Note	:

**************************************************************/
#ifndef locklessqueue_h__
#define locklessqueue_h__

#include "include_std.h"

namespace Concurrent
{
  template<typename T>
  struct Node
  {
    Node(const T& obj = T(), Node<T>* ptr = nullptr);

    T m_val;
    std::atomic<Node<T>*> m_next;
  };

  template<typename T>
  class LockFreeQueue
  {
  public:

    LockFreeQueue();
    ~LockFreeQueue();

    void Enqueue(const T& obj);
    bool Dequeue(T& obj);
    int Size() const;

    int RecountSize() const;

  private:

    Node<T>* MakeNode(const T& obj);

    const Node<T> m_rear_guard; //note that this isn't a point. It's also assumed to be default constructible
    const Node<T> m_front_guard;

    std::atomic<Node<T>*> m_head;
    std::atomic<Node<T>*> m_tail;

    std::atomic<int> m_count;

  };

} //namespace Concurrent

#include "concurrent_queue.inl"

#endif
/*!************************************************************
Todo:

**************************************************************/

