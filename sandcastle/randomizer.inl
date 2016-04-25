/*!************************************************************
	Created:	2016/02/11
	Intent:		
			
	Note:
			
**************************************************************/
#ifndef randomizer_inl__
#define randomizer_inl__

#include <random>
#include <algorithm>

/*!************************************************************

**************************************************************/
template<typename T>
T Random(T r1, T r2)
{
  static std::default_random_engine rand;

  std::uniform_int_distribution<decltype(r1)> dist(std::min(r1, r2), std::max(r1, r2));

  return dist(rand);
}




#endif // randomizer_h__
/*!************************************************************
	Todo:
			
**************************************************************/


