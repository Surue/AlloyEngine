#pragma once
#include <vulkan/vulkan.h>

#include <devices/physical_device.h>

namespace alloy::vulkanwrapper {
class LogicalDevice {
public:
	LogicalDevice() = default;
	~LogicalDevice() = default;

	void Init(const PhysicalDevice& physicalDevice);

	void Destroy() const;
private:

	VkDevice device_;

	VkQueue graphicsQueue_;
};
}
