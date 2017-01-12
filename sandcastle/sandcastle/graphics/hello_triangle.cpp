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

		glfwSetWindowUserPointer(_window, this);
		glfwSetWindowSizeCallback(_window, simpletriangle::on_window_resize);

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
		create_render_pass();
		create_graphics_pipeline();
		create_frame_buffers();
		create_command_pool();
		create_command_buffers();
		create_semaphores();
	}

	void simpletriangle::main_loop()
	{

		while (!glfwWindowShouldClose(_window))
		{
			glfwPollEvents();
			draw_frame();
		}

		vkDeviceWaitIdle(_device);
	}

	void simpletriangle::draw_frame()
	{
		uint32_t image_index;

		VkResult result = vkAcquireNextImageKHR(_device, _swap_chain, std::numeric_limits<uint32_t>::max(), 
			_image_available_semaphore, VK_NULL_HANDLE, &image_index);

		if (result == VK_ERROR_OUT_OF_DATE_KHR)
		{
			recreate_swap_chain();
			return;
		}
		else if (result != VK_SUCCESS && result != VK_SUBOPTIMAL_KHR)
		{
			throw std::runtime_error("failed to acquire swap chain image!");
		}

		VkSubmitInfo submit_info = {};

		VkSemaphore wait_semaphores[] = { _image_available_semaphore };
		VkPipelineStageFlags wait_stages[] = { VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT };
		submit_info.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
		submit_info.waitSemaphoreCount = 1;
		submit_info.pWaitSemaphores = wait_semaphores;
		submit_info.pWaitDstStageMask = wait_stages;
		submit_info.commandBufferCount = 1;
		submit_info.pCommandBuffers = &_command_buffers[image_index];

		VkSemaphore signal_semaphores[] = { _render_finished_semaphore };
		submit_info.signalSemaphoreCount = 1;
		submit_info.pSignalSemaphores = signal_semaphores;

		if (vkQueueSubmit(_graphics_queue, 1, &submit_info, VK_NULL_HANDLE) != VK_SUCCESS)
		{
			throw std::runtime_error("failed to submit draw command buffer!");
		}

		VkPresentInfoKHR present_info = {};
		present_info.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
		present_info.waitSemaphoreCount = 1;
		present_info.pWaitSemaphores = signal_semaphores;
		
		VkSwapchainKHR swap_chains[] = { _swap_chain };
		present_info.swapchainCount = 1;
		present_info.pSwapchains = swap_chains;
		present_info.pImageIndices = &image_index;

		present_info.pResults = nullptr;

		result = vkQueuePresentKHR(_presentation_queue, &present_info);

		if (result == VK_ERROR_OUT_OF_DATE_KHR || result == VK_SUBOPTIMAL_KHR)
			recreate_swap_chain();
		else if (result != VK_SUCCESS)
			throw std::runtime_error("failed to present swap chain image!");
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

		VkSwapchainKHR old_swap_chain = _swap_chain;
		create_info.oldSwapchain = old_swap_chain;

		VkSwapchainKHR new_swap_chain;
		if (vkCreateSwapchainKHR(_device, &create_info, nullptr, &new_swap_chain) != VK_SUCCESS)
		{
			throw std::runtime_error("failed to create swap chain!");
		}

		_swap_chain = new_swap_chain;

		//get swapchain image handles
		vkGetSwapchainImagesKHR(_device, _swap_chain, &image_count, nullptr);
		_swap_chain_images.resize(image_count);
		vkGetSwapchainImagesKHR(_device, _swap_chain, &image_count, _swap_chain_images.data());
	}

	void simpletriangle::recreate_swap_chain()
	{
		vkDeviceWaitIdle(_device);

		create_swap_chain();
		create_image_views();
		create_render_pass();
		create_graphics_pipeline();
		create_frame_buffers();
		create_command_buffers();
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
		auto func = (PFN_vkDestroyDebugReportCallbackEXT) vkGetInstanceProcAddr(instance, "vkDestroyDebugReportCallbackEXT");

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

	void simpletriangle::create_graphics_pipeline()
	{
		//these are generated via glslangValidator.exe with the V flag
		auto vert_spv = read_binary("graphics/shaders/vert.spv");
		auto frag_spv = read_binary("graphics/shaders/frag.spv");

		vkhandle<VkShaderModule> vert_shader_module{ _device, vkDestroyShaderModule };
		vkhandle<VkShaderModule> frag_shader_module{ _device, vkDestroyShaderModule };

		create_shader_module(vert_spv, vert_shader_module);
		create_shader_module(frag_spv, frag_shader_module);

		VkPipelineShaderStageCreateInfo vert_shader_stage_info = {};
		vert_shader_stage_info.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
		vert_shader_stage_info.stage = VK_SHADER_STAGE_VERTEX_BIT;
		vert_shader_stage_info.module = vert_shader_module;
		vert_shader_stage_info.pName = "main"; //shaders can choose which shader to pipe to now. what?

		VkPipelineShaderStageCreateInfo frag_shader_stage_info = {};
		frag_shader_stage_info.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
		frag_shader_stage_info.stage = VK_SHADER_STAGE_FRAGMENT_BIT;
		frag_shader_stage_info.module = frag_shader_module;
		frag_shader_stage_info.pName = "main"; //shaders can choose which shader to pipe to now. what?

		VkPipelineShaderStageCreateInfo shader_stages[] = {vert_shader_stage_info, frag_shader_stage_info};

		VkPipelineVertexInputStateCreateInfo vertex_input_info = {};
		vertex_input_info.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
		vertex_input_info.vertexBindingDescriptionCount = 0;
		vertex_input_info.pVertexBindingDescriptions = nullptr;
		vertex_input_info.vertexAttributeDescriptionCount = 0;
		vertex_input_info.pVertexAttributeDescriptions = nullptr;

		VkPipelineInputAssemblyStateCreateInfo input_assembly_info = {};
		input_assembly_info.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
		input_assembly_info.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
		input_assembly_info.primitiveRestartEnable = VK_FALSE;

		VkViewport viewport = {};
		viewport.x = viewport.y = 0.f;
		viewport.width = (float)_swap_chain_extent.width;
		viewport.height = (float)_swap_chain_extent.height;
		viewport.minDepth = 0.f;
		viewport.maxDepth = 1.f;

		VkRect2D scissor = {};
		scissor.offset = { 0, 0 };
		scissor.extent = _swap_chain_extent;

		VkPipelineViewportStateCreateInfo viewport_state = {};
		viewport_state.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
		viewport_state.viewportCount = 1;
		viewport_state.pViewports = &viewport;
		viewport_state.scissorCount = 1;
		viewport_state.pScissors = &scissor;
		
		VkPipelineRasterizationStateCreateInfo rasterizer = {};
		rasterizer.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
		rasterizer.depthClampEnable = VK_FALSE;
		rasterizer.rasterizerDiscardEnable = VK_FALSE;
		rasterizer.polygonMode = VK_POLYGON_MODE_FILL;
		rasterizer.lineWidth = 1.f;
		rasterizer.cullMode = VK_CULL_MODE_BACK_BIT;
		rasterizer.frontFace = VK_FRONT_FACE_CLOCKWISE;
		rasterizer.depthBiasEnable = VK_FALSE;
		rasterizer.depthBiasConstantFactor = 0.f;
		rasterizer.depthBiasClamp = 0.f;
		rasterizer.depthBiasSlopeFactor = 0.f;

		//not used, but look anyway
		VkPipelineMultisampleStateCreateInfo multisampling = {};
		multisampling.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
		multisampling.sampleShadingEnable = VK_FALSE;
		multisampling.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;
		multisampling.minSampleShading = 1.f;
		multisampling.pSampleMask = nullptr;
		multisampling.alphaToCoverageEnable = VK_FALSE;
		multisampling.alphaToOneEnable = VK_FALSE;

		//depth and stencil testing

		//color blending
		VkPipelineColorBlendAttachmentState color_blend_attachment = {};
		color_blend_attachment.colorWriteMask = VK_COLOR_COMPONENT_R_BIT | 
			VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;
		color_blend_attachment.blendEnable = VK_FALSE;
		color_blend_attachment.srcColorBlendFactor = VK_BLEND_FACTOR_ONE;
		color_blend_attachment.dstColorBlendFactor = VK_BLEND_FACTOR_ZERO;
		color_blend_attachment.colorBlendOp = VK_BLEND_OP_ADD;
		color_blend_attachment.srcAlphaBlendFactor = VK_BLEND_FACTOR_ONE;
		color_blend_attachment.dstAlphaBlendFactor = VK_BLEND_FACTOR_ZERO;
		color_blend_attachment.alphaBlendOp = VK_BLEND_OP_ADD;

		VkPipelineColorBlendStateCreateInfo color_blending = {};
		color_blending.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
		color_blending.logicOpEnable = VK_FALSE;
		color_blending.logicOp = VK_LOGIC_OP_COPY;
		color_blending.attachmentCount = 1;
		color_blending.pAttachments = &color_blend_attachment;
		color_blending.blendConstants[0] = 0.f;
		color_blending.blendConstants[1] = 0.f;
		color_blending.blendConstants[2] = 0.f;
		color_blending.blendConstants[3] = 0.f;

		VkDynamicState dynamic_states[] = {
			VK_DYNAMIC_STATE_VIEWPORT,
			VK_DYNAMIC_STATE_LINE_WIDTH
		};

		//not used...yet
		VkPipelineDynamicStateCreateInfo dynamic_state = {};
		dynamic_state.sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
		dynamic_state.dynamicStateCount = 2;
		dynamic_state.pDynamicStates = dynamic_states;

		VkPipelineLayoutCreateInfo pipeline_layout_info = {};
		pipeline_layout_info.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
		pipeline_layout_info.setLayoutCount = 0;
		pipeline_layout_info.pSetLayouts = nullptr;
		pipeline_layout_info.pushConstantRangeCount = 0;
		pipeline_layout_info.pPushConstantRanges = nullptr;

		if (vkCreatePipelineLayout(_device, &pipeline_layout_info, nullptr, _pipeline_layout.replace()) != VK_SUCCESS)
		{
			throw std::runtime_error("failed to create pipeline layout!");
		}

		VkGraphicsPipelineCreateInfo pipeline_info = {};
		pipeline_info.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
		pipeline_info.stageCount = 2;
		pipeline_info.pStages = shader_stages;

		pipeline_info.pVertexInputState = &vertex_input_info;
		pipeline_info.pInputAssemblyState = &input_assembly_info;
		pipeline_info.pViewportState = &viewport_state;
		pipeline_info.pRasterizationState = &rasterizer;
		pipeline_info.pMultisampleState = &multisampling;
		pipeline_info.pDepthStencilState = nullptr;
		pipeline_info.pColorBlendState = &color_blending;
		pipeline_info.pDynamicState = nullptr;

		pipeline_info.layout = _pipeline_layout;
		pipeline_info.renderPass = _render_pass;
		pipeline_info.subpass = 0;

		pipeline_info.basePipelineHandle = VK_NULL_HANDLE;
		pipeline_info.basePipelineIndex = -1;

		if (vkCreateGraphicsPipelines(_device, VK_NULL_HANDLE, 1, &pipeline_info, nullptr,
			_graphics_pipeline.replace()) != VK_SUCCESS)
		{
			throw std::runtime_error("failed to create graphics pipeline!");
		}
	}

	void simpletriangle::create_render_pass()
	{
		VkAttachmentDescription color_attachment = {};
		color_attachment.format = _swap_chain_image_format;
		color_attachment.samples = VK_SAMPLE_COUNT_1_BIT;
		color_attachment.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
		color_attachment.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
		color_attachment.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
		color_attachment.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
		color_attachment.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
		color_attachment.finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;

		VkAttachmentReference color_attachment_ref = {};
		color_attachment_ref.attachment = 0;
		color_attachment_ref.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

		VkSubpassDescription subpass = {};
		subpass.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
		subpass.colorAttachmentCount = 1;
		subpass.pColorAttachments = &color_attachment_ref;

		VkSubpassDependency dependencies = {};
		dependencies.srcSubpass = VK_SUBPASS_EXTERNAL;
		dependencies.dstSubpass = 0;
		dependencies.srcStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
		dependencies.srcAccessMask = 0;
		dependencies.dstStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
		dependencies.dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_READ_BIT | VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;

		VkRenderPassCreateInfo render_pass_info = {};
		render_pass_info.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
		render_pass_info.attachmentCount = 1;
		render_pass_info.pAttachments = &color_attachment;
		render_pass_info.subpassCount = 1;
		render_pass_info.pSubpasses = &subpass;
		render_pass_info.dependencyCount = 1;
		render_pass_info.pDependencies = &dependencies;

		if (vkCreateRenderPass(_device, &render_pass_info, nullptr, _render_pass.replace()) != VK_SUCCESS)
		{
			throw std::runtime_error("failed to create render pass!");
		}
	}

	void simpletriangle::create_frame_buffers()
	{
		_swap_chain_frame_buffers.resize(_swap_chain_image_views.size(), vkhandle<VkFramebuffer>{_device, vkDestroyFramebuffer});

		for (size_t i = 0; i < _swap_chain_image_views.size(); ++i)
		{
			VkImageView attachments[] = {
				_swap_chain_image_views[i]
			};

			VkFramebufferCreateInfo frame_buffer_info = {};
			frame_buffer_info.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
			frame_buffer_info.renderPass = _render_pass;
			frame_buffer_info.attachmentCount = 1;
			frame_buffer_info.pAttachments = attachments;
			frame_buffer_info.width = _swap_chain_extent.width;
			frame_buffer_info.height = _swap_chain_extent.height;
			frame_buffer_info.layers = 1;

			if (vkCreateFramebuffer(_device, &frame_buffer_info, nullptr, _swap_chain_frame_buffers[i].replace()) != VK_SUCCESS)
			{
				throw std::runtime_error("failed to create framebuffer!");
			}
		}
	}

	void simpletriangle::on_window_resize(GLFWwindow * window, int width, int height)
	{
		if (width == 0 || height == 0) return;

		simpletriangle* app = reinterpret_cast<simpletriangle*>(glfwGetWindowUserPointer(window));
		app->recreate_swap_chain();
	}

	void simpletriangle::create_image_views()
	{
		_swap_chain_image_views.resize(_swap_chain_images.size(), vkhandle<VkImageView>{_device, vkDestroyImageView});

		for (uint32_t i = 0; i < _swap_chain_images.size(); ++i)
		{
			VkImageViewCreateInfo create_info = {};
			create_info.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
			create_info.image = _swap_chain_images[i];
			create_info.viewType = VK_IMAGE_VIEW_TYPE_2D;
			create_info.format = _swap_chain_image_format;
			create_info.components.r = create_info.components.g 
				= create_info.components.b = create_info.components.a 
				= VK_COMPONENT_SWIZZLE_IDENTITY;
			create_info.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
			create_info.subresourceRange.baseMipLevel = 0;
			create_info.subresourceRange.levelCount = 1;
			create_info.subresourceRange.baseArrayLayer = 0;
			create_info.subresourceRange.layerCount = 1;

			if (vkCreateImageView(_device, &create_info, nullptr, _swap_chain_image_views[i].replace()) != VK_SUCCESS)
			{
				throw std::runtime_error("failed to create image views!");
			}
		}
	}

	std::vector<char> simpletriangle::read_binary(const std::string & file)
	{
		std::ifstream ifs(file, std::ios::ate | std::ios::binary);

		if (ifs.is_open() == false)
		{
			throw std::runtime_error("failed to open file");
		}

		size_t file_size = (size_t)ifs.tellg();
		std::vector<char> buffer(file_size);

		ifs.seekg(0);
		ifs.read(buffer.data(), file_size);

		return buffer;
	}

	void simpletriangle::create_shader_module(const std::vector<char>& code, vkhandle<VkShaderModule>& shader)
	{
		VkShaderModuleCreateInfo create_info = {};
		create_info.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
		create_info.codeSize = code.size();
		create_info.pCode = (uint32_t*)code.data();

		if (vkCreateShaderModule(_device, &create_info, nullptr, shader.replace()) != VK_SUCCESS)
		{
			throw std::runtime_error("failed to create shader module!");
		}
	}

	void simpletriangle::create_command_pool()
	{
		queue_family_indices queue_family_indices = find_queue_families(_physical_device);

		VkCommandPoolCreateInfo pool_info = {};
		pool_info.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
		pool_info.queueFamilyIndex = queue_family_indices._graphics_family;
		pool_info.flags = 0;

		if (vkCreateCommandPool(_device, &pool_info, nullptr, _command_pool.replace()) != VK_SUCCESS)
		{
			throw std::runtime_error("failed to create command pool!");
		}
	}

	void simpletriangle::create_command_buffers()
	{
		if (_command_buffers.empty() == false)
		{
			vkFreeCommandBuffers(_device, _command_pool, _command_buffers.size(), _command_buffers.data());
		}

		_command_buffers.resize(_swap_chain_frame_buffers.size());

		VkCommandBufferAllocateInfo alloc_info = {};
		alloc_info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
		alloc_info.commandPool = _command_pool;
		alloc_info.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
		alloc_info.commandBufferCount = (uint32_t) _command_buffers.size();

		if (vkAllocateCommandBuffers(_device, &alloc_info, _command_buffers.data()) != VK_SUCCESS)
		{
			throw std::runtime_error("failed to allocate command buffers!");
		}

		for (size_t i = 0; i < _command_buffers.size(); ++i)
		{
			VkCommandBufferBeginInfo begin_info = {};
			begin_info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
			begin_info.flags = VK_COMMAND_BUFFER_USAGE_SIMULTANEOUS_USE_BIT;
			begin_info.pInheritanceInfo = nullptr;

			vkBeginCommandBuffer(_command_buffers[i], &begin_info);

			VkRenderPassBeginInfo render_pass_info = {};
			render_pass_info.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
			render_pass_info.renderPass = _render_pass;
			render_pass_info.framebuffer = _swap_chain_frame_buffers[i];
			render_pass_info.renderArea.offset = { 0, 0 };
			render_pass_info.renderArea.extent = _swap_chain_extent;

			VkClearValue clear_color = { 0.f, 0.f, 0.f, 1.f };
			render_pass_info.clearValueCount = 1;
			render_pass_info.pClearValues = &clear_color;

			vkCmdBeginRenderPass(_command_buffers[i], &render_pass_info, VK_SUBPASS_CONTENTS_INLINE);
			vkCmdBindPipeline(_command_buffers[i], VK_PIPELINE_BIND_POINT_GRAPHICS, _graphics_pipeline);

			vkCmdDraw(_command_buffers[i], 3, 1, 0, 0);

			vkCmdEndRenderPass(_command_buffers[i]);

			if (vkEndCommandBuffer(_command_buffers[i]) != VK_SUCCESS)
			{
				throw std::runtime_error("failed to record command buffer!");
			}
		}
	}

	void simpletriangle::create_semaphores()
	{
		VkSemaphoreCreateInfo semaphore_info = {};
		semaphore_info.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;

		if (vkCreateSemaphore(_device, &semaphore_info, nullptr, _image_available_semaphore.replace()) != VK_SUCCESS ||
			vkCreateSemaphore(_device, &semaphore_info, nullptr, _render_finished_semaphore.replace()) != VK_SUCCESS)
		{
			throw std::runtime_error("failed to create semaphores!");
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