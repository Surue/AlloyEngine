#include <devices/physical_device.h>

#include <set>

#include <devices/instance.h>
#include <devices/surface.h>

namespace alloy::vulkanwrapper {

void PhysicalDevice::Init(const Instance& instance, const Surface& surface) {
	uint32_t deviceCount = 0;
	vkEnumeratePhysicalDevices(instance.GetInstance(), &deviceCount, nullptr);

	if (deviceCount == 0) {
		std::cerr << "No device available\n";
	}

	std::vector<VkPhysicalDevice> devices(deviceCount);
	vkEnumeratePhysicalDevices(instance.GetInstance(), &deviceCount, devices.data());

	for (const auto& device : devices) {
		if (IsDeviceSuitable(device, surface)) {
			device_ = device;
			break;
		}
	}

	if (device_ == VK_NULL_HANDLE) {
		std::cerr << "No suitable physical device found\n";
	}
}

void PhysicalDevice::Destroy() { }


bool PhysicalDevice::IsDeviceSuitable(const VkPhysicalDevice& physicalDevice, const Surface& surface) {
	VkPhysicalDeviceProperties deviceProperties;
	vkGetPhysicalDeviceProperties(physicalDevice, &deviceProperties);

	VkPhysicalDeviceFeatures deviceFeatures;
	vkGetPhysicalDeviceFeatures(physicalDevice, &deviceFeatures);

	QueueFamilyIndices indices = FindQueueFamilies(physicalDevice, surface);

	bool extensionsSupported = CheckDeviceExtensionSupport(physicalDevice);

	return indices.IsComplete() && extensionsSupported;
}

bool PhysicalDevice::CheckDeviceExtensionSupport(const VkPhysicalDevice& device) {
	uint32_t extensionCount;
	vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, nullptr);

	std::vector<VkExtensionProperties> availableExtensions(extensionCount);
	vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, availableExtensions.data());

	std::set<std::string> requiredExtensions(deviceExtensions.begin(), deviceExtensions.end());

	for (const auto& extension : availableExtensions) {
		requiredExtensions.erase(extension.extensionName);
	}

	return requiredExtensions.empty();
}

QueueFamilyIndices PhysicalDevice::FindQueueFamilies(const VkPhysicalDevice& physicalDevice, const Surface& surface) {
	QueueFamilyIndices indices;

	uint32_t queueFamilyCount = 0;
	vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &queueFamilyCount, nullptr);

	std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
	vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &queueFamilyCount, queueFamilies.data());

	for (uint32_t i = 0; i < queueFamilyCount; i++) {
		//Check for presentation queue
		VkBool32 presentationSupport = false;
		vkGetPhysicalDeviceSurfaceSupportKHR(physicalDevice, i, &surface, &presentationSupport);

		if(presentationSupport) {
			indices.presentFamily = i;
		}
		
		//Check for drawing queue
		if (queueFamilies[i].queueFlags & VK_QUEUE_GRAPHICS_BIT) {
			indices.graphicsFamily = i;
		}

		if (indices.IsComplete()) {
			break;
		}
	}

	return indices;
}
}
