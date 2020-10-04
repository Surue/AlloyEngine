#pragma once

#include <vulkan/vulkan.h>

#include <devices/vulkan_window.h>

namespace alloy::vulkanwrapper {
class Surface {
public:
	Surface() = default;
	~Surface() = default;

	const VkSurfaceKHR& operator&() const {
		return surface_;
	}
	
	void Init(const Instance& instance, const IVulkanWindow& vulkanWindow) {
		vulkanWindow.CreateVulkanSurface(instance, *this);
	}

	void Destroy(const VkInstance& instance) {
		vkDestroySurfaceKHR(instance, surface_, nullptr);
	}

	VkSurfaceKHR* GetSurface() {
		return &surface_;
	}
private:
	VkSurfaceKHR surface_;
};
}