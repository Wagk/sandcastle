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

		void init();
		void init_vulkan();
		void main_loop();
		std::vector<VkExtensionProperties> enumerate_extensions() const;

		std::vector<const char*> get_required_extensions();

		bool check_validation_layer_support();

		void create_instance();
		void create_surface();

		void pick_physical_device();
		void create_logical_device();
		bool is_device_suitable(VkPhysicalDevice device);
		bool check_device_extension_support(VkPhysicalDevice device);

		static VKAPI_ATTR VkBool32 VKAPI_CALL debugcallback_fn(
			VkDebugReportFlagsEXT flags,
			VkDebugReportObjectTypeEXT objtype,
			uint64_t obj,
			size_t location,
			int32_t code,
			const char* layerprefix,
			const char* msg,
			void* userdata);

		void setup_debug_callback();
		VkResult CreateDebugReportCallbackEXT(
			VkInstance instance,
			const VkDebugReportCallbackCreateInfoEXT* pcreateinfo,
			const VkAllocationCallbacks* palloc,
			VkDebugReportCallbackEXT* pcallback);
		
		static void DestroyDebugReportCallbackEXT(
			VkInstance instance,
			VkDebugReportCallbackEXT callback, 
			const VkAllocationCallbacks* palloc);

		struct queue_family_indices {
			int _graphics_family = -1;
			int _presentation_family = -1;
			bool is_complete() {
				return _graphics_family >= 0 && _presentation_family >= 0;
			}
		};

		queue_family_indices find_queue_families(VkPhysicalDevice device);

		GLFWwindow* _window; //glfw object
		vkhandle<VkInstance> _instance{vkDestroyInstance}; //this is the vulkan instance, we need to boot one everytime we start
		vkhandle<VkDevice> _device{ vkDestroyDevice }; //this is the logical device
		vkhandle<VkDebugReportCallbackEXT> _debug_callback{ _instance, DestroyDebugReportCallbackEXT }; //this is the validation layer callback:w
		vkhandle<VkSurfaceKHR> _surface{ _instance, vkDestroySurfaceKHR }; //the surface to draw onto
		VkPhysicalDevice _physical_device = VK_NULL_HANDLE; //the physical device

		//apparently being able to handle draw commands doesn't mean you can render to screen
		VkQueue _graphics_queue; 
		VkQueue _presentation_queue;
	};
}

#endif