/*!************************************************************
  Created:	2016/02/14
  Intent:
      Computes delta time for us
  Note:

**************************************************************/
#ifndef util_timestep_h__
#define util_timestep_h__

#include "export_macros.h"

namespace Utility
{

  /*!************************************************************
    FullName:	StartTimer
    Returns:	void
    Brief:
          starts the clock for timing
    Assumes:
    Consider:
    Note:
  **************************************************************/
  SANDCASTLE_API void StartTimer();

  /*!************************************************************
    FullName:	EndTimer
    Returns:	void
    Brief:
          ends the clock for timing, dt will be :

          (endtimer() - starttimer()) / 1 second;

    Assumes:
    Consider:
    Note:
  **************************************************************/
  SANDCASTLE_API void EndTimer();

  /*!************************************************************
    FullName:	GetTimeStep
    Returns:	float
    Brief:
          gets the dt this frame

          first frame dt is 1/60
    Assumes:
    Consider:
    Note:
  **************************************************************/
  SANDCASTLE_API float GetTimeStep();

} //namespace Utility

#endif // timestep_h__
/*!************************************************************
  Todo:

**************************************************************/


