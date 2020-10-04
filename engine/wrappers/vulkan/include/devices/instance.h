#pragma once

#include <iostream>
#include <vector>

#include <vulkan/vulkan.h>

namespace alloy::vulkanwrapper {
const std::vector<const char*> validationLayers = {
	"VK_LAYER_KHRONOS_validation"
};

#ifdef NDEBUG
	constexpr bool enableValidationLayers = false;
#else
	constexpr bool enableValidationLayers = true;
#endif

class Instance {
public:
	Instance() = default;
	~Instance() = default;

	const VkInstance& operator&() const {
		return instance_;
	}

	/**
	 * \param windowExtensions The required list of extension specific to the window
	 */
	void Init(const std::vector<const char*>& windowExtensions);

	void Destroy();

	const VkInstance& GetInstance() const { return instance_; }
private:
	void CreateInstance(const std::vector<const char*>& windowExtensions);

	std::vector<const char*> GetRequiredExtensions(const std::vector<const char*>& windowExtensions);

	bool CheckValidationLayerSupport();

	void SetupDebugMessenger();

	VkInstance instance_;
	VkDebugUtilsMessengerEXT debugMessenger_;
};
} //namespace alloy::vulkanwrapper