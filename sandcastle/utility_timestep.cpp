#include "utility_timestep.h"
#include <chrono>

namespace
{
  static float dt = 1 / 60.f;
  static std::chrono::system_clock::time_point s_timepoint;
}

/*!************************************************************

**************************************************************/
void Utility::StartTimer()
{
  s_timepoint = std::chrono::system_clock::now();
}

/*!************************************************************

**************************************************************/
void Utility::EndTimer()
{
  using namespace std::chrono;

  auto endpoint = system_clock::now();
  auto timestep = duration_cast<microseconds>(endpoint - s_timepoint);
  dt = timestep.count() / static_cast<float>(seconds(1).count());
  s_timepoint = endpoint;
}

/*!************************************************************

**************************************************************/
float Utility::GetTimeStep()
{
  return dt;
}
