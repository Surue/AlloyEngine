#include <devices/physical_device.h>

namespace alloy::vulkanwrapper {
void PhysicalDevice::Init(const Instance& instance) {
	uint32_t deviceCount = 0;
	vkEnumeratePhysicalDevices(instance.GetInstance(), &deviceCount, nullptr);

	if (deviceCount == 0) {
		std::cerr << "No device available\n";
	}

	std::vector<VkPhysicalDevice> devices(deviceCount);
	vkEnumeratePhysicalDevices(instance.GetInstance(), &deviceCount, devices.data());

	for (const auto& device : devices) {
		if (IsDeviceSuitable(device)) {
			device_ = device;
			break;
		}
	}

	if (device_ == VK_NULL_HANDLE) {
		std::cerr << "No suitable physical device found\n";
	}
}

void PhysicalDevice::Destroy() { }

bool PhysicalDevice::IsDeviceSuitable(const VkPhysicalDevice& physicalDevice) {
	VkPhysicalDeviceProperties deviceProperties;
	vkGetPhysicalDeviceProperties(physicalDevice, &deviceProperties);

	VkPhysicalDeviceFeatures deviceFeatures;
	vkGetPhysicalDeviceFeatures(physicalDevice, &deviceFeatures);

	QueueFamilyIndices indices = FindQueueFamilies(physicalDevice);

	return indices.IsComplete();
}

QueueFamilyIndices PhysicalDevice::FindQueueFamilies(const VkPhysicalDevice& physicalDevice) {
	QueueFamilyIndices indices;

	uint32_t queueFamilyCount = 0;
	vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &queueFamilyCount, nullptr);

	std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
	vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &queueFamilyCount, queueFamilies.data());

	for (uint32_t i = 0; i < queueFamilyCount; i++) {
		if (queueFamilies[i].queueFlags & VK_QUEUE_GRAPHICS_BIT) {
			indices.graphicsFamily = i;

			if (indices.IsComplete()) {
				break;
			}
		}
	}

	return indices;
}
}
