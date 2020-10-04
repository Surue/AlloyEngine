#pragma once

#include <vulkan/vulkan.h>

namespace alloy::vulkanwrapper {
class Surface {
public:
	Surface() = default;
	~Surface() = default;
	
	void Init() {
		
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