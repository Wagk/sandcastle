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
	const bool enablevalidationlayers = true;
#endif

	void simpletriangle::run()
	{

		init();
		initvulkan();
		main_loop();

	}

	void simpletriangle::init()
	{

		glfwInit();

		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
		glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

		_window = glfwCreateWindow(width, height, "Vulkan", nullptr, nullptr);

	}

	void simpletriangle::initvulkan()
	{
		createinstance();
	}

	void simpletriangle::main_loop()
	{

		while (!glfwWindowShouldClose(_window))
		{
			glfwPollEvents();
		}

	}

	//assumes the instance is already initialized
	std::vector<VkExtensionProperties> simpletriangle::enumerateExtensions() const
	{

		uint32_t extension_count = 0;
		vkEnumerateInstanceExtensionProperties(nullptr, &extension_count, nullptr);

		std::vector<VkExtensionProperties> extensions(extension_count);

		vkEnumerateInstanceExtensionProperties(nullptr, &extension_count, extensions.data());

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

	void simpletriangle::createinstance()
	{
		if (enablevalidationlayers && check_validation_layer_support() == false)
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
		
		if(enablevalidationlayers == false)
			createinfo.enabledLayerCount = 0;
		else
		{
			createinfo.enabledLayerCount = validationlayers.size();
			createinfo.ppEnabledLayerNames = validationlayers.data();
		}

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

	VKAPI_ATTR VkBool32 VKAPI_CALL simpletriangle::debugcallback(
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
}