#include "hello_triangle.h"
#include <vector>
#include <string>
#include <set>
#include <limits>
#include <algorithm>

namespace sandcastle::graphics
{
	const int g_width = 800;
	const int g_height = 600;

	const std::vector<const char*> validation_layers = {
		"VK_LAYER_LUNARG_standard_validation"
	};

	const std::vector<const char*> device_extensions = {
		VK_KHR_SWAPCHAIN_EXTENSION_NAME
	};

#ifdef NDEBUG
	const bool enablevalidationlayers = false;
#else
	const bool enable_validation_layers = true;
#endif

	void simpletriangle::run()
	{

		init();
		init_vulkan();
		main_loop();

	}
	void simpletriangle::init()
	{

		glfwInit();

		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
		glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

		_window = glfwCreateWindow(g_width, g_height, "Vulkan", nullptr, nullptr);

	}

	void simpletriangle::init_vulkan()
	{
		create_instance();
		setup_debug_callback();
		create_surface();
		pick_physical_device();
		create_logical_device();
		create_swap_chain();
		create_image_views();
	}

	void simpletriangle::main_loop()
	{

		while (!glfwWindowShouldClose(_window))
		{
			glfwPollEvents();
		}

	}

	//assumes the instance is already initialized
	std::vector<VkExtensionProperties> simpletriangle::enumerate_extensions() const
	{

		uint32_t extension_count = 0;
		vkEnumerateInstanceExtensionProperties(nullptr, &extension_count, nullptr);

		std::vector<VkExtensionProperties> extensions(extension_count);

		vkEnumerateInstanceExtensionProperties(nullptr, &extension_count, extensions.data());

		return extensions;

	}

	std::vector<const char*> simpletriangle::get_required_extensions()
	{
		std::vector<const char*> extensions;

		unsigned int glfw_extension_count = 0;
		const char** glfw_extensions = glfwGetRequiredInstanceExtensions(&glfw_extension_count);

		for (unsigned int i = 0; i < glfw_extension_count; ++i)
		{
			extensions.push_back(glfw_extensions[i]);
		}

		if (enable_validation_layers)
		{
			extensions.push_back(VK_EXT_DEBUG_REPORT_EXTENSION_NAME);
		}

		return extensions;
	}

	bool simpletriangle::check_validation_layer_support()
	{
		uint32_t layercount;

		vkEnumerateInstanceLayerProperties(&layercount, nullptr);

		std::vector<VkLayerProperties> availablelayers(layercount);
		vkEnumerateInstanceLayerProperties(&layercount, availablelayers.data());

		bool every_layer_supported = true;
		for (const std::string& layer : validation_layers)
		{
			bool this_layer_supported = false;

			for (const auto& avail : availablelayers)
			{
				if (std::strcmp(avail.layerName , layer.c_str()) == 0)
				{
					this_layer_supported = true;
					break;
				}
			}

			if (this_layer_supported == false)
				every_layer_supported = false;
		}

		return every_layer_supported;
	}

	void simpletriangle::create_instance()
	{
		if (enable_validation_layers && check_validation_layer_support() == false)
		{
			throw std::runtime_error("validation layers requested, but not available!~");
		}

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
		
		auto extensions = get_required_extensions();
		createinfo.enabledExtensionCount = (uint32_t)extensions.size();
		createinfo.ppEnabledExtensionNames = extensions.data();

		if(enable_validation_layers == false)
			createinfo.enabledLayerCount = 0;
		else
		{
			createinfo.enabledLayerCount = (uint32_t)validation_layers.size();
			createinfo.ppEnabledLayerNames = validation_layers.data();
		}

		if (vkCreateInstance(&createinfo, nullptr, _instance.replace()) != VK_SUCCESS)
		{
			throw std::runtime_error("Failed to create instance!");
		}

		std::vector<VkExtensionProperties> enumerate = enumerate_extensions();

		std::cout << "Available Extensions:" << std::endl;
		for (const auto& exts : enumerate)
		{
			std::cout << "\t" << exts.extensionName << std::endl;
		}

	}

	void simpletriangle::create_surface()
	{
		if (glfwCreateWindowSurface(_instance, _window, nullptr, _surface.replace()) != VK_SUCCESS)
		{
			throw std::runtime_error("failed to create window surface!");
		}
	}

	//a swap chain is a queue of image buffers to be drawn onto the screen
	void simpletriangle::create_swap_chain()
	{
		swap_chain_support_details swap_chain_support = query_swap_chain_support(_physical_device);

		VkSurfaceFormatKHR surface_format = choose_swap_surface_format(swap_chain_support._formats);
		VkPresentModeKHR present_mode = choose_swap_present_mode(swap_chain_support._present_modes);
		VkExtent2D extent = choose_swap_extent(swap_chain_support._capabilities);

		uint32_t image_count = swap_chain_support._capabilities.minImageCount + 1;
		if (swap_chain_support._capabilities.maxImageCount > 0 && image_count > swap_chain_support._capabilities.maxImageCount) {
			image_count = swap_chain_support._capabilities.maxImageCount;
		}

		VkSwapchainCreateInfoKHR create_info = {};
		create_info.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
		create_info.surface = _surface;

		create_info.minImageCount = image_count;
		create_info.imageFormat = _swap_chain_image_format = surface_format.format;
		create_info.imageColorSpace = surface_format.colorSpace;
		create_info.imageExtent = _swap_chain_extent = extent;
		create_info.imageArrayLayers = 1;
		create_info.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT; //this will need to change when we draw to some separate buffer first

		queue_family_indices indices = find_queue_families(_physical_device);
		uint32_t queue_family_indice_array[] = { (uint32_t)indices._graphics_family, (uint32_t)indices._presentation_family };

		if (indices._graphics_family != indices._presentation_family)
		{
			//Images can be used across multiple queue families without explicit ownership transfers.
			create_info.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
			create_info.queueFamilyIndexCount = 2;
			create_info.pQueueFamilyIndices = queue_family_indice_array;
		}
		else
		{
			//An image is owned by one queue family at a time and ownership must be 
			//explicitly transfered before using it in another queue family. 
			//This option offers the best performance.
			create_info.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
			create_info.queueFamilyIndexCount = 0;
			create_info.pQueueFamilyIndices = nullptr;
		}

		create_info.preTransform = swap_chain_support._capabilities.currentTransform;
		create_info.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
		create_info.presentMode = present_mode;
		create_info.clipped = VK_TRUE;
		create_info.oldSwapchain = VK_NULL_HANDLE; //this might get iffy

		if (vkCreateSwapchainKHR(_device, &create_info, nullptr, _swap_chain.replace()) != VK_SUCCESS)
		{
			throw std::runtime_error("failed to create swap chain!");
		}

		//get swapchain image handles
		vkGetSwapchainImagesKHR(_device, _swap_chain, &image_count, nullptr);
		_swap_chain_images.resize(image_count);
		vkGetSwapchainImagesKHR(_device, _swap_chain, &image_count, _swap_chain_images.data());
	}


	void simpletriangle::pick_physical_device()
	{
		uint32_t device_count = 0;
		vkEnumeratePhysicalDevices(_instance, &device_count, nullptr);

		if (device_count == 0)
		{
			throw std::runtime_error("Failed to find GPU's with Vulkan Support!");
		}

		std::vector<VkPhysicalDevice> devices(device_count);
		vkEnumeratePhysicalDevices(_instance, &device_count, devices.data());

		for (const auto& device : devices)
		{
			if (is_device_suitable(device))
			{
				_physical_device = device;
				break;
			}
		}
		
		if (_physical_device == VK_NULL_HANDLE)
			throw std::runtime_error("failed to find a suitable GPU!");
	}

	void simpletriangle::create_logical_device()
	{
		//get all the queue families
		queue_family_indices indices = find_queue_families(_physical_device);

		std::vector<VkDeviceQueueCreateInfo> queue_create_infos = {};
		std::set<int> unique_queue_families = { indices._graphics_family, 
												indices._presentation_family };

		float queue_priority = 1.f;
		for (int queue_family : unique_queue_families) {
			
			//for each of them generate a queue_create_info struct
			VkDeviceQueueCreateInfo queue_create_info = {};
			queue_create_info.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
			queue_create_info.queueFamilyIndex = queue_family;
			queue_create_info.queueCount = 1;
			queue_create_info.pQueuePriorities = &queue_priority;

			queue_create_infos.push_back(queue_create_info);
		}

		VkPhysicalDeviceFeatures device_features = {};

		//create the device with all the queue_create_infos
		VkDeviceCreateInfo device_create_info = {};
		device_create_info.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
		device_create_info.pQueueCreateInfos = queue_create_infos.data();
		device_create_info.queueCreateInfoCount = static_cast<uint32_t>(queue_create_infos.size());
		device_create_info.pEnabledFeatures = &device_features;
		device_create_info.enabledExtensionCount = device_extensions.size();
		device_create_info.ppEnabledExtensionNames = device_extensions.data();

		if (enable_validation_layers) {
			device_create_info.enabledLayerCount = validation_layers.size();
			device_create_info.ppEnabledLayerNames = validation_layers.data();
		}
		else {
			device_create_info.enabledLayerCount = 0;
		}

		//call the thing and pray
		if (vkCreateDevice(_physical_device, &device_create_info, nullptr, _device.replace()) 
			!= VK_SUCCESS) {
			throw std::runtime_error("failed to create logical device!");
		}

		//once we initialised and set it up, grab the needed handles
		vkGetDeviceQueue(_device, indices._graphics_family, 0, &_graphics_queue);
		vkGetDeviceQueue(_device, indices._presentation_family, 0, &_presentation_queue);
	}

	bool simpletriangle::is_device_suitable(VkPhysicalDevice device)
	{
		////example of finding a card that has a geometry shader
		//VkPhysicalDeviceProperties device_properties;
		//VkPhysicalDeviceFeatures device_features;

		//vkGetPhysicalDeviceProperties(_physical_device, &device_properties);
		//vkGetPhysicalDeviceFeatures(_physical_device, &device_features);

		//return	device_properties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU &&
		//		device_features.geometryShader;

		queue_family_indices indices = find_queue_families(device);

		bool extensions_supported = check_device_extension_support(device);

		bool swap_chain_adequate = false;
		if (extensions_supported)
		{
			swap_chain_support_details swap_chain_support = query_swap_chain_support(device);
			swap_chain_adequate = swap_chain_support._formats.empty() == false &&
								  swap_chain_support._present_modes.empty() == false;
		}

		return indices.is_complete() && extensions_supported && swap_chain_adequate;
	}

	bool simpletriangle::check_device_extension_support(VkPhysicalDevice device)
	{
		uint32_t extension_count;
		vkEnumerateDeviceExtensionProperties(device, nullptr, &extension_count, nullptr);

		std::vector<VkExtensionProperties> available_extensions(extension_count);
		vkEnumerateDeviceExtensionProperties(device, nullptr, &extension_count, available_extensions.data());
		
		std::set<std::string> required_extensions(device_extensions.begin(), device_extensions.end());

		//match available extensions with required extensions. make sure everything is there
		for (const VkExtensionProperties& extension : available_extensions) {
			required_extensions.erase(extension.extensionName);
		}

		return required_extensions.empty() == true;
	}

	VKAPI_ATTR VkBool32 VKAPI_CALL simpletriangle::debugcallback_fn(
		VkDebugReportFlagsEXT flags, 
		VkDebugReportObjectTypeEXT objtype, 
		uint64_t obj, 
		size_t location, 
		int32_t code, 
		const char * layerprefix, 
		const char * msg, 
		void * userdata)
	{
		std::cerr << "validation layer " << msg << std::endl;

		return VK_FALSE;
	}

	VkResult simpletriangle::CreateDebugReportCallbackEXT(
		VkInstance instance, 
		const VkDebugReportCallbackCreateInfoEXT* pcreateinfo,
		const VkAllocationCallbacks* palloc, 
		VkDebugReportCallbackEXT* pcallback
		)
	{
		auto func = (PFN_vkCreateDebugReportCallbackEXT)vkGetInstanceProcAddr(_instance,
																			"vkCreateDebugReportCallbackEXT");
		if (func)
		{
			return func(instance, pcreateinfo, palloc, pcallback);
		}
		else
		{
			return VK_ERROR_EXTENSION_NOT_PRESENT;
		}

	}

	void simpletriangle::DestroyDebugReportCallbackEXT(
		VkInstance instance, 
		VkDebugReportCallbackEXT callback, 
		const VkAllocationCallbacks * palloc)
	{
		auto func = (PFN_vkDestroyDebugReportCallbackEXT) vkGetInstanceProcAddr(instance,
			"vkDestroyDebugReportCallbackEXT");

		if (func)
		{
			func(instance, callback, palloc);
		}
	}

	simpletriangle::queue_family_indices simpletriangle::find_queue_families(VkPhysicalDevice device)
	{
		queue_family_indices indices;

		uint32_t queue_family_count = 0;
		vkGetPhysicalDeviceQueueFamilyProperties(device, &queue_family_count, nullptr);

		std::vector<VkQueueFamilyProperties> queue_families(queue_family_count);
		vkGetPhysicalDeviceQueueFamilyProperties(device, &queue_family_count, queue_families.data());

		for (int i = 0, s = (int)queue_families.size(); i < s; ++i)
		{
			if (queue_families[i].queueCount > 0 && 
				queue_families[i].queueFlags & VK_QUEUE_GRAPHICS_BIT)
			{ 
				indices._graphics_family = i;
			}

			VkBool32 presentation_support = false;
			vkGetPhysicalDeviceSurfaceSupportKHR(device, i, _surface, &presentation_support);

			if (queue_families[i].queueCount > 0 && presentation_support) 
			{
				indices._presentation_family = i;
			}

			if (indices.is_complete())
				break;
		}

		return indices;
	}

	simpletriangle::swap_chain_support_details simpletriangle::query_swap_chain_support(VkPhysicalDevice device)
	{
		swap_chain_support_details details;
		vkGetPhysicalDeviceSurfaceCapabilitiesKHR(device, _surface, &details._capabilities);

		uint32_t format_count;
		vkGetPhysicalDeviceSurfaceFormatsKHR(device, _surface, &format_count, nullptr);

		if (format_count != 0) {
			details._formats.resize(format_count);
			vkGetPhysicalDeviceSurfaceFormatsKHR(device, _surface, &format_count, details._formats.data());
		}

		uint32_t present_mode_count;
		vkGetPhysicalDeviceSurfacePresentModesKHR(device, _surface, &present_mode_count, nullptr);

		if (present_mode_count != 0) {
			details._present_modes.resize(present_mode_count);
			vkGetPhysicalDeviceSurfacePresentModesKHR(device, _surface, &present_mode_count, details._present_modes.data());
		}

		return details;
	}

	VkSurfaceFormatKHR simpletriangle::choose_swap_surface_format(const std::vector<VkSurfaceFormatKHR>& available_formats)
	{
		if (available_formats.size() == 1 && available_formats.front().format == VK_FORMAT_UNDEFINED)
			return{ VK_FORMAT_B8G8R8A8_UNORM, VK_COLOR_SPACE_SRGB_NONLINEAR_KHR };

		for (const auto& available_format : available_formats)
		{
			if (available_format.format == VK_FORMAT_B8G8R8A8_UNORM &&
				available_format.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR)
			{
				return available_format;
			}
		}

		return available_formats.front();
	}

	VkPresentModeKHR simpletriangle::choose_swap_present_mode(const std::vector<VkPresentModeKHR>& available_presents)
	{
		for (const auto& available_mode : available_presents)
		{
			if (available_mode == VK_PRESENT_MODE_MAILBOX_KHR)
			{
				return available_mode;
			}
		}

		return VK_PRESENT_MODE_FIFO_KHR;
	}

	VkExtent2D simpletriangle::choose_swap_extent(const VkSurfaceCapabilitiesKHR & capabilities)
	{
		if (capabilities.currentExtent.width != std::numeric_limits<uint32_t>::max())
			return capabilities.currentExtent;
		else
		{
			VkExtent2D actual_extent = { g_width, g_height };

			actual_extent.width = std::max(capabilities.minImageExtent.width, 
				std::min(capabilities.maxImageExtent.width, actual_extent.width));
			actual_extent.height = std::max(capabilities.minImageExtent.height, 
				std::min(capabilities.maxImageExtent.height, actual_extent.height));

			return actual_extent;
		}
	}

	void simpletriangle::setup_debug_callback()
	{
		if (!enable_validation_layers)
			return;

		VkDebugReportCallbackCreateInfoEXT createinfo = {};
		createinfo.sType = VK_STRUCTURE_TYPE_DEBUG_REPORT_CALLBACK_CREATE_INFO_EXT;
		createinfo.flags = VK_DEBUG_REPORT_ERROR_BIT_EXT | VK_DEBUG_REPORT_WARNING_BIT_EXT;
		createinfo.pfnCallback = debugcallback_fn;

		if (CreateDebugReportCallbackEXT(_instance, &createinfo, nullptr, _debug_callback.replace()) != VK_SUCCESS)
		{
			throw std::runtime_error("failed to set up debug callback!");
		}

	}
}