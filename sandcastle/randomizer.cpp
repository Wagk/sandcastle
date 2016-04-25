#include "randomizer.h"

template<>
float Random(float r1, float r2)
{
  static std::default_random_engine rand;

  std::uniform_real_distribution<float> dist(std::min(r1, r2), std::max(r1, r2));

  return dist(rand);
}

template<>
double Random(double r1, double r2)
{
  static std::default_random_engine rand;

  std::uniform_real_distribution<double> dist(std::min(r1, r2), std::max(r1, r2));

  return dist(rand);
}

template<>
long double Random(long double r1, long double r2)
{
  static std::default_random_engine rand;

  std::uniform_real_distribution<long double> dist(std::min(r1, r2), std::max(r1, r2));

  return dist(rand);
}

