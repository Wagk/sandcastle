#ifndef graphics_hello_triangle_h__
#define graphics_hello_triangle_h__

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

namespace sandcastle::graphics
{
	class simpletriangle
	{
	public:

		static const int width = 800;
		static const int height = 600;

		void run()
		{

			init();
			main_loop();

		}

	private:

		GLFWwindow* _window;

		void init()
		{

			glfwInit();

			glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
			glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
			
			_window = glfwCreateWindow(width, height, "Vulkan", nullptr, nullptr);

		}

		void main_loop()
		{

			while (!glfwWindowShouldClose(_window)) {
				glfwPollEvents();
			}

		}

	};
}

#endif