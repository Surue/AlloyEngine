#pragma once

#include <vulkan/vulkan.h>

#include <vector>

namespace alloy::vulkanwrapper {
class IVulkanWindow {
public:
	virtual void CreateVulkanSurface(const Instance& instance, Surface& surface_out) const = 0;

	virtual std::vector<const char*> GetVulkanExtensions() const = 0;
};
} //namespace alloy::vulkanwrapperVkSurfaceKHR*