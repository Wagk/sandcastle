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

		static const int width = 800;
		static const int height = 600;

		void run()
		{

			init();
			initvulkan();
			main_loop();

		}

	private:

		GLFWwindow* _window;
		vkhandle<VkInstance> _instance{vkDestroyInstance};

		void init()
		{

			glfwInit();

			glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
			glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
			
			_window = glfwCreateWindow(width, height, "Vulkan", nullptr, nullptr);

		}

		void initvulkan()
		{
			createinstance();
		}

		void main_loop()
		{

			while (!glfwWindowShouldClose(_window)) 
			{
				glfwPollEvents();
			}

		}

		//assumes the instance is already initialized
		std::vector<VkExtensionProperties> enumerateExtensions() const
		{

			uint32_t extension_count = 0;
			vkEnumerateInstanceExtensionProperties(nullptr, &extension_count, nullptr);

			std::vector<VkExtensionProperties> extensions(extension_count);

			vkEnumerateInstanceExtensionProperties(nullptr, &extension_count, extensions.data());

			return extensions;

		}

		void createinstance()
		{

			VkApplicationInfo appinfo = {};
			appinfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
			appinfo.pApplicationName = "Hello Triangle";
			appinfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
			appinfo.pEngineName = "No Engine";
			appinfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
			appinfo.apiVersion = VK_API_VERSION_1_0;

			unsigned int glfw_extension_count = 0;
			const char** glfw_extensions = glfwGetRequiredInstanceExtensions(&glfw_extension_count);

			VkInstanceCreateInfo createinfo = {};
			createinfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
			createinfo.pApplicationInfo = &appinfo;
			createinfo.enabledExtensionCount = glfw_extension_count;
			createinfo.ppEnabledExtensionNames = glfw_extensions;
			createinfo.enabledLayerCount = 0;

			if (vkCreateInstance(&createinfo, nullptr, _instance.replace()) != VK_SUCCESS)
			{
				throw std::runtime_error("Failed to create instance!");
			}

			std::vector<VkExtensionProperties> extensions = enumerateExtensions();

			std::cout << "Available Extensions:" << std::endl;
			for (const auto& exts : extensions)
			{
				std::cout << "\t" << exts.extensionName << std::endl;
			}

		}

	};
}

#endif