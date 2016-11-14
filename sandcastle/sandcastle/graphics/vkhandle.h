#ifndef graphics_vkdeleter_h__
#define graphics_vkdeleter_h__

#include <functional>
#include <vulkan/vulkan.h>

namespace sandcastle::graphics
{

	template<typename T>
	class vkhandle
	{
	public:
		
		vkhandle() : vkhandle([](T, VkAllocationCallbacks*) {}) {}
		vkhandle(const vkhandle<VkInstance>& instance,
			std::function<void(VkInstance, T, VkAllocationCallbacks*)> deletef)
			: _deleter([&instance, deletef](T obj) {deletef(instance, obj, nullptr); }) {}
		vkhandle(const vkhandle<VkDevice>& device, 
			std::function<void(VkDevice, T, VkAllocationCallbacks*)> deletef)
			: _deleter([&device, deletef](T obj) {deletef(device, obj, nullptr); }) {}

		~vkhandle() { cleanup(); }

		T* operator&() { return &_object; }
		const T* operator&() const { return &_object; }

		T* replace() {
			cleanup();
			return &_object;
		}

		void operator=(T rhs) {
			if (rhs != _object) {
				cleanup();
				_object = rhs;
			}
		}

		operator T() const {
			return _object;
		}

		template<typename V>
		bool operator==(V rhs) {
			return _object == T(rhs);
		}

	private:

		T _object = VK_NULL_HANDLE;

		std::function<void(T)> _deleter;

		void cleanup()
		{
			if (_object != VK_NULL_HANDLE)
			{
				_deleter(_object);
				_object = VK_NULL_HANDLE;
			}
		}

	}

}

#endif