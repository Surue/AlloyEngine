#include <devices/logical_device.h>

namespace alloy::vulkanwrapper {

void LogicalDevice::Init(const PhysicalDevice& physicalDevice) {
	//Get queue family
	QueueFamilyIndices indices = PhysicalDevice::FindQueueFamilies(physicalDevice.GetPhysicalDevice());

	//Device queue create info
	VkDeviceQueueCreateInfo queueCreateInfo{};
	queueCreateInfo.flags = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
	queueCreateInfo.queueCount = 1;
	queueCreateInfo.queueFamilyIndex = indices.graphicsFamily.value();
	float queuePriority = 1.0f;
	queueCreateInfo.pQueuePriorities = &queuePriority;

	//Physical device features
	VkPhysicalDeviceFeatures deviceFeatures{};

	//Device create infos
	VkDeviceCreateInfo deviceCreateInfo{};
	deviceCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
	deviceCreateInfo.queueCreateInfoCount = 1;
	deviceCreateInfo.pQueueCreateInfos = &queueCreateInfo;
	deviceCreateInfo.pEnabledFeatures = &deviceFeatures;
	deviceCreateInfo.enabledExtensionCount = 0;

	//Create logical device
	if(vkCreateDevice(physicalDevice.GetPhysicalDevice(), &deviceCreateInfo, nullptr, &device_)) {
		std::cerr << "Error while creating logical device\n";
	}

	//Get graphics queue
	vkGetDeviceQueue(device_, indices.graphicsFamily.value(), 0, &graphicsQueue_);
}
}
