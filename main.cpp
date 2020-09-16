#include <iostream>
#include <vector>
#include <vector.h>
#include <log.h>

#define SDL_MAIN_HANDLED
#include <SDL.h>
#include <SDL_vulkan.h>
#include <vulkan/vulkan.h>

const std::vector<const char*> validationLayers = {
	"VK_LAYER_KHRONOS_validation"
};

#ifdef NDEBUG
constexpr bool enableValidationLayers = false;
#else
constexpr bool enableValidationLayers = true;
#endif

//VKAPI_ATTR & VKAPI_CALL ensure that the function has the right signature
static VKAPI_ATTR VkBool32 VKAPI_CALL DebugCallback(
	VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
	VkDebugUtilsMessageTypeFlagsEXT messageType,
	const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
	void* pUserData) {

	LogError(pCallbackData->pMessage);

	return VK_FALSE;
}

VkResult CreateDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* pDebugMessenger) {
	auto func = (PFN_vkCreateDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance, "vkCreateDebugUtilsMessengerEXT");
	if (func != nullptr) {
		return func(instance, pCreateInfo, pAllocator, pDebugMessenger);
	}
	else {
		return VK_ERROR_EXTENSION_NOT_PRESENT;
	}
}

void DestroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger, const VkAllocationCallbacks* pAllocator) {
	auto func = (PFN_vkDestroyDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance, "vkDestroyDebugUtilsMessengerEXT");
	if (func != nullptr) {
		func(instance, debugMessenger, pAllocator);
	}
}

class Window {
public:
	Window() = default;

	~Window() {
		SDL_DestroyWindow(window_);
	}

	SDL_Window* operator &() const {
		return window_;
	}

	bool Init() {
		window_ = SDL_CreateWindow("Alloy Engine", 100, 100, width_, height_, SDL_WINDOW_VULKAN);
		if (window_ == nullptr) {
			LogError("SDL_CreateWindow Error : " + static_cast<std::string>(SDL_GetError()));
			return false;
		}

		return true;
	}

	SDL_Window* GetWindow() {
		return window_;
	}

private:
	SDL_Window* window_ = nullptr;

	int width_ = 720;
	int height_ = 640;
};


class Engine {
public:
	void Init() {
		if (SDL_Init(SDL_INIT_VIDEO) != 0) {
			LogError("SDL_Init Error: " + static_cast<std::string>(SDL_GetError()));
		}

		window_.Init();

		InitVulkan();
	}

	void InitVulkan() {
		CreateInstance();
	}

	void SetupDebugMessenger() {
		if constexpr (!enableValidationLayers) return;

		VkDebugUtilsMessengerCreateInfoEXT debugMessengerCreateInfo{};
		debugMessengerCreateInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
		debugMessengerCreateInfo.messageSeverity =
			VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT |
			VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT |
			VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
		debugMessengerCreateInfo.messageType =
			VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT |
			VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT |
			VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
		debugMessengerCreateInfo.pfnUserCallback = DebugCallback;
		debugMessengerCreateInfo.pUserData = nullptr;

		if (CreateDebugUtilsMessengerEXT(instance_, &debugMessengerCreateInfo, nullptr, &debugMessenger_) != VK_SUCCESS) {
			LogError("Failed to setup debug messenger");
		}
	}

	std::vector<const char*> GetRequiredExtensions() {
		//SDL extensions
		uint32_t sdlExtensionCount = 0;
		SDL_Vulkan_GetInstanceExtensions(window_.GetWindow(), &sdlExtensionCount, nullptr);
		std::vector<const char*> sdlExtension(sdlExtensionCount);
		SDL_Vulkan_GetInstanceExtensions(window_.GetWindow(), &sdlExtensionCount, sdlExtension.data());

		//Required extensions
		std::vector<const char*> extensions(sdlExtension.data(), sdlExtension.data() + sdlExtensionCount);
		//Validation layers extension
		if constexpr (enableValidationLayers) {
			extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
		}

		return extensions;
	}

	void CreateInstance() {
		//Application informations
		VkApplicationInfo applicationInfo{};
		applicationInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
		applicationInfo.pApplicationName = "Vulkan Test";
		applicationInfo.applicationVersion = VK_MAKE_VERSION(0, 0, 0);
		applicationInfo.pEngineName = "Alloy Engine";
		applicationInfo.engineVersion = VK_MAKE_VERSION(0, 0, 0);
		applicationInfo.apiVersion = VK_API_VERSION_1_2;

		//Instance's create infos
		VkInstanceCreateInfo instanceCreateInfo{};
		instanceCreateInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
		instanceCreateInfo.pApplicationInfo = &applicationInfo;
		//Extensions
		std::vector<const char*> extensions = GetRequiredExtensions();
		instanceCreateInfo.enabledExtensionCount = extensions.size();
		instanceCreateInfo.ppEnabledExtensionNames = extensions.data();
		//Check layers
		VkDebugUtilsMessengerCreateInfoEXT debugCreateInfo{};
		if constexpr (enableValidationLayers) {
			instanceCreateInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
			instanceCreateInfo.ppEnabledLayerNames = validationLayers.data();
			instanceCreateInfo.pNext = (VkDebugUtilsMessengerCreateInfoEXT*)&debugCreateInfo;
		}
		else {
			instanceCreateInfo.enabledLayerCount = 0u;

			instanceCreateInfo.pNext = nullptr;
		}

		//Create vulkan's instance
		if (vkCreateInstance(&instanceCreateInfo, nullptr, &instance_) != VK_SUCCESS) {
			LogError("Failed to create vulkan instance");
		}
	}

	bool CheckValidationLayerSupport() {
		uint32_t layerCount;
		vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

		std::vector<VkLayerProperties> availableLayers(layerCount);
		vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());

		for (const char* layerName : validationLayers) {
			bool layerFound = false;

			for (const auto& layerProperties : availableLayers) {
				if (strcmp(layerName, layerProperties.layerName) == 0) {
					layerFound = true;
					break;
				}
			}

			if (!layerFound) {
				return false;
			}
		}

		return true;
	}

	void Destroy() {
		//Destroy debug messenger
		if (enableValidationLayers) {
			DestroyDebugUtilsMessengerEXT(instance_, debugMessenger_, nullptr);
		}

		vkDestroyInstance(instance_, nullptr);
	}

	void Run() {
		SDL_Event e;
		bool quit = false;
		while (!quit) {
			while (SDL_PollEvent(&e)) {
				if (e.type == SDL_QUIT) {
					quit = true;
				}
				if (e.type == SDL_KEYDOWN) {
					quit = true;
				}
				if (e.type == SDL_MOUSEBUTTONDOWN) {
					quit = true;
				}
			}
		}

		SDL_Quit();
	}
private:

	Window window_;

	VkInstance instance_ = VK_NULL_HANDLE;
	VkDebugUtilsMessengerEXT debugMessenger_;
};


int main() {
	Engine engine;
	engine.Init();
	engine.Run();
	engine.Destroy();

    return 0;
}
