#pragma once
#include <optional>
#include <vulkan/vulkan.h>

#include <devices/instance.h>

namespace alloy::vulkanwrapper {
struct QueueFamilyIndices {
	std::optional<uint32_t> graphicsFamily;

	bool IsComplete() {
		return graphicsFamily.has_value();
	}
};

class PhysicalDevice {
public:
	PhysicalDevice() = default;

	void Init(const Instance& instance);

	void Destroy();

	const VkPhysicalDevice& GetPhysicalDevice() const { return device_; }

	static QueueFamilyIndices FindQueueFamilies(const VkPhysicalDevice& physicalDevice);
private:

	bool IsDeviceSuitable(const VkPhysicalDevice& physicalDevice);

	VkPhysicalDevice device_;
};
}
