#ifndef graphics_hello_triangle_h__
#define graphics_hello_triangle_h__

#include <vector>
#include <iostream>

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include "vkhandle.h"

namespace sandcastle::graphics
{
	class simpletriangle
	{
	public:

		void run();

	private:

		GLFWwindow* _window;
		vkhandle<VkInstance> _instance{vkDestroyInstance};

		void init();
		void initvulkan();
		void main_loop();
		std::vector<VkExtensionProperties> enumerateExtensions() const;

		bool check_validation_layer_support();

		void createinstance();

	};
}

#endif