/*!************************************************************
	Created	:	2016/04/27
	Intent	:		
		
    A renderer that lets you render things onto the screen

	Usage	:
		```
			
		```
	Note	:
		
**************************************************************/
#ifndef renderer_h__
#define renderer_h__

#include "glfw/glfw3.h"

#include "drawrequest.h"

namespace Graphics
{

  class Renderer
  {
  public:

    void Request(const Drawrequest& request);

  private:


  };

} //namespace Graphics

#endif // renderer_h__
/*!************************************************************
	Todo:
			
	References:
		
**************************************************************/


