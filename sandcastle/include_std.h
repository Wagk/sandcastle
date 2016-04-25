/*!************************************************************
	Created	:	2016/03/21
	Intent	:		
		
	Usage	:
		
	Note	:
		
**************************************************************/
#ifndef util_std_h__
#define util_std_h__

#include <iostream>
#include <type_traits>

#include <utility>
template<typename T, typename Q>
using Pair = std::pair<T, Q>;

#include <string>
using String = std::string;

#include <vector>
template<typename T>
using Vector = std::vector<T>;

#include <array>
template<typename T, size_t N>
using Array = std::array<T, N>;

#include <list>
template<typename T>
using List = std::list<T>;

#include <forward_list>
template<typename T>
using ForwardList = std::forward_list<T>;

#include <map>
template<typename Key, typename Value>
using Map = std::map<Key, Value>;

#include <set>
template<typename Value, typename Comp = std::less<Value>>
using Set = std::set<Value, Comp>;

#include <unordered_map>
template<typename Key, typename Value>
using HashMap = std::unordered_map<Key, Value>;

#include <unordered_set>
template<typename Key, typename Value>
using HashSet = std::unordered_set<Key, Value>;

#include <functional>
template<typename Func>
using Function = std::function<Func>;

#include <atomic>
template<typename T>
using Atomic = std::atomic<T>;

#include <mutex>
#include "concurrent_worker_mutex.h"
//using Mutex = Concurrent::WorkerMutex;
using Mutex = std::mutex; //we'll stick to this for performance reasons

#include <thread>
using Thread = std::thread;

#include <condition_variable>
using ConditionVariable = std::condition_variable;

#include <sstream>
using OutStream = std::ostream;
using InStream = std::istream;

#include <algorithm>

#include <memory>
template<typename T>
using SharedPtr = std::shared_ptr<T>;
template<typename T>
using UniquePtr = std::unique_ptr<T>;








#endif // util_stl_h__
/*!************************************************************
	Todo:
			
	References:
		
**************************************************************/


