#pragma once
#include <vulkan/vulkan.h>

#include <devices/physical_device.h>

namespace alloy::vulkanwrapper {
class LogicalDevice {
public:
	LogicalDevice() = default;
	~LogicalDevice() {
		vkDestroyDevice(device_, nullptr);
	}

	void Init(const PhysicalDevice& physicalDevice);
private:

	VkDevice device_;

	VkQueue graphicsQueue_;
};
}
