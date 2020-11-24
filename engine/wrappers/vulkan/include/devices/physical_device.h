#pragma once
#include <optional>
#include <vulkan/vulkan.h>

namespace alloy::vulkanwrapper {
class Surface;
class Instance;

struct QueueFamilyIndices {
	std::optional<uint32_t> graphicsFamily;
	std::optional<uint32_t> presentFamily;

	bool IsComplete() {
		return graphicsFamily.has_value() && presentFamily.has_value();
	}
};

class PhysicalDevice {
public:
	PhysicalDevice() = default;

	void Init(const Instance& instance, const Surface& surface);

	void Destroy();

	const VkPhysicalDevice& GetPhysicalDevice() const { return device_; }

	static QueueFamilyIndices FindQueueFamilies(const VkPhysicalDevice& physicalDevice, const Surface& surface);

	inline const static std::vector<const char*> deviceExtensions = {
		VK_KHR_SWAPCHAIN_EXTENSION_NAME
	};
private:

	bool IsDeviceSuitable(const VkPhysicalDevice& physicalDevice, const Surface& surface);

	bool CheckDeviceExtensionSupport(const VkPhysicalDevice& device);

	VkPhysicalDevice device_;
};
}
