#include "hello_triangle.h"
#include <vector>
#include <string>

namespace sandcastle::graphics
{
	const int width = 800;
	const int height = 600;

	const std::vector<const char*> validationlayers = {
		"VK_LAYER_LUNARG_standard_validation"
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

		_window = glfwCreateWindow(width, height, "Vulkan", nullptr, nullptr);

	}

	void simpletriangle::init_vulkan()
	{
		create_instance();
		setup_debug_callback();
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
		for (const std::string& layer : validationlayers)
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
			createinfo.enabledLayerCount = (uint32_t)validationlayers.size();
			createinfo.ppEnabledLayerNames = validationlayers.data();
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

	bool simpletriangle::is_device_suitable(VkPhysicalDevice device)
	{
		////example of finding a card that has a geometry shader
		//VkPhysicalDeviceProperties device_properties;
		//VkPhysicalDeviceFeatures device_features;

		//vkGetPhysicalDeviceProperties(_physical_device, &device_properties);
		//vkGetPhysicalDeviceFeatures(_physical_device, &device_features);

		//return	device_properties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU &&
		//		device_features.geometryShader;

		return find_queue_families(device).is_complete();
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
		std::cerr << "validation layer" << msg << std::endl;

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
				indices.graphics_family = i;

			if (indices.is_complete())
				break;
		}

		return indices;
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