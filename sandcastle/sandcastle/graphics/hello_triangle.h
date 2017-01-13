#ifndef graphics_hello_triangle_h__
#define graphics_hello_triangle_h__

#include <vector>
#include <array>
#include <iostream>
#include <fstream>

#include <glm/glm.hpp>

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include "vkhandle.h"

namespace sandcastle::graphics
{
	
	struct vertex
	{
		glm::vec2 _pos;
		glm::vec3 _color;

		static VkVertexInputBindingDescription get_binding_description();
		static std::array<VkVertexInputAttributeDescription, 2> get_attribute_descriptions();
	};

	class simpletriangle
	{
	public:

		void run();

	private:

		void init();
		void init_vulkan();
		void main_loop();
		void draw_frame();
		std::vector<VkExtensionProperties> enumerate_extensions() const;

		std::vector<const char*> get_required_extensions();

		bool check_validation_layer_support();

		void create_instance();
		void create_surface();
		void create_swap_chain();
		void recreate_swap_chain();

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

		struct swap_chain_support_details {
			VkSurfaceCapabilitiesKHR _capabilities;
			std::vector<VkSurfaceFormatKHR> _formats;
			std::vector<VkPresentModeKHR> _present_modes;
		};

		swap_chain_support_details query_swap_chain_support(VkPhysicalDevice device);

		VkSurfaceFormatKHR choose_swap_surface_format(const std::vector<VkSurfaceFormatKHR>& available_formats);
		VkPresentModeKHR choose_swap_present_mode(const std::vector<VkPresentModeKHR>& avaiable_presents);
		VkExtent2D choose_swap_extent(const VkSurfaceCapabilitiesKHR& capabilities);

		void create_graphics_pipeline();
		void create_render_pass();
		void create_frame_buffers();

		GLFWwindow* _window; //glfw object

		static void on_window_resize(GLFWwindow* window, int width, int height);

		VkPhysicalDevice _physical_device = VK_NULL_HANDLE; //the physical device
		vkhandle<VkInstance> _instance{vkDestroyInstance}; //this is the vulkan instance, we need to boot one everytime we start
		vkhandle<VkDevice> _device{ vkDestroyDevice }; //this is the logical device
		vkhandle<VkDebugReportCallbackEXT> _debug_callback{ _instance, DestroyDebugReportCallbackEXT }; //this is the validation layer callback:w
		vkhandle<VkSurfaceKHR> _surface{ _instance, vkDestroySurfaceKHR }; //the surface to draw onto
		vkhandle<VkSwapchainKHR> _swap_chain{ _device, vkDestroySwapchainKHR };

		std::vector<VkImage> _swap_chain_images;
		VkFormat _swap_chain_image_format;
		VkExtent2D _swap_chain_extent;

		std::vector<vkhandle<VkImageView>> _swap_chain_image_views;
		void create_image_views();

		//apparently being able to handle draw commands doesn't mean you can render to screen
		VkQueue _graphics_queue; 
		VkQueue _presentation_queue;

		static std::vector<char> read_binary(const std::string& file);
		void create_shader_module(const std::vector<char>& code, vkhandle<VkShaderModule>& shader);

		vkhandle<VkPipelineLayout> _pipeline_layout{ _device, vkDestroyPipelineLayout };
		vkhandle<VkRenderPass> _render_pass{ _device, vkDestroyRenderPass };
		vkhandle<VkPipeline> _graphics_pipeline{ _device, vkDestroyPipeline };
		std::vector<vkhandle<VkFramebuffer>> _swap_chain_frame_buffers;

		void create_command_pool();
		void create_command_buffers();

		vkhandle<VkCommandPool> _command_pool{ _device, vkDestroyCommandPool };
		std::vector<VkCommandBuffer> _command_buffers;

		void create_semaphores();

		vkhandle<VkSemaphore> _image_available_semaphore{ _device, vkDestroySemaphore };
		vkhandle<VkSemaphore> _render_finished_semaphore{ _device, vkDestroySemaphore };
	};
}

#endif