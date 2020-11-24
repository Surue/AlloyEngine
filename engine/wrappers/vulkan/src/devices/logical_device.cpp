#include <devices/logical_device.h>

#include <set>
#include <iostream>

#include <devices/instance.h>

namespace alloy::vulkanwrapper {

void LogicalDevice::Init(const PhysicalDevice& physicalDevice, const Surface& surface) {
	//Get queue family
	QueueFamilyIndices indices = PhysicalDevice::FindQueueFamilies(physicalDevice.GetPhysicalDevice(), surface);

	//Device queue create info
	std::vector<VkDeviceQueueCreateInfo> queueCreateInfos{};
	std::set<uint32_t> uniqueQueueFamilies = { indices.graphicsFamily.value(), indices.presentFamily.value() };

	float queuePriority = 1.0f;
	for(uint32_t queueFamily : uniqueQueueFamilies) {
		VkDeviceQueueCreateInfo queueCreateInfo{};
		queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
		queueCreateInfo.queueFamilyIndex = queueFamily;
		queueCreateInfo.queueCount = 1;
		queueCreateInfo.pQueuePriorities = &queuePriority;

		queueCreateInfos.push_back(queueCreateInfo);
	}

	//Physical device features
	VkPhysicalDeviceFeatures deviceFeatures{};

	//Device create infos
	VkDeviceCreateInfo deviceCreateInfo{};
	deviceCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
	deviceCreateInfo.queueCreateInfoCount = static_cast<uint32_t>(queueCreateInfos.size());
	deviceCreateInfo.pQueueCreateInfos = queueCreateInfos.data();
	deviceCreateInfo.pEnabledFeatures = &deviceFeatures;
	deviceCreateInfo.enabledExtensionCount = static_cast<uint32_t>(PhysicalDevice::deviceExtensions.size());
	deviceCreateInfo.ppEnabledExtensionNames = PhysicalDevice::deviceExtensions.data();
	
	//If validation layers is active => add validation layer extensions
	if (enableValidationLayers) {
		deviceCreateInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
		deviceCreateInfo.ppEnabledLayerNames = validationLayers.data();
	}
	else {
		deviceCreateInfo.enabledLayerCount = 0;
	}

	//Create logical device
	if(vkCreateDevice(physicalDevice.GetPhysicalDevice(), &deviceCreateInfo, nullptr, &device_)) {
		std::cerr << "Error while creating logical device\n";
	}

	//Get graphics queue
	vkGetDeviceQueue(device_, indices.graphicsFamily.value(), 0, &graphicsQueue_);
	vkGetDeviceQueue(device_, indices.presentFamily.value(), 0, &presentQueue_);
}

void LogicalDevice::Destroy() const {
	vkDestroyDevice(device_, nullptr);
}
}
