#include <iostream>
#include <vector>
#include <vector.h>

#define SDL_MAIN_HANDLED
#include <SDL.h>
#include <SDL_vulkan.h>
#include <vulkan/vulkan.h>

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
			std::cout << "SDL_CreateWindow Error : " << SDL_GetError() << "\n";
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



void InitVulkan() {

}

void Cleanup() {
	SDL_Quit();
}

class Engine {
public:
	void Init() {
		if (SDL_Init(SDL_INIT_VIDEO) != 0) {
			std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
		}

		window_.Init();

		InitVulkan();
	}

	void InitVulkan() {
		CreateInstance();
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

		//Get SDL extension
		uint32_t extensionCount;
		vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);
		std::vector<VkExtensionProperties> extensions(extensionCount);
		vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, extensions.data());

		SDL_Vulkan_GetInstanceExtensions(window_.GetWindow(), &extensionCount, nullptr);
		std::vector<const char*> extensionNames;
		extensionNames.resize(extensionCount);
		SDL_Vulkan_GetInstanceExtensions(window_.GetWindow(), &extensionCount, extensionNames.data());
		extensionNames.push_back(VK_KHR_SURFACE_EXTENSION_NAME);

		//Create infos
		VkInstanceCreateInfo instanceCreateInfo{};
		instanceCreateInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
		instanceCreateInfo.pApplicationInfo = &applicationInfo;
		instanceCreateInfo.enabledExtensionCount = extensionNames.size();
		instanceCreateInfo.ppEnabledExtensionNames = extensionNames.data();
		instanceCreateInfo.enabledLayerCount = 0;

		//Create vulkan's instance
		if (vkCreateInstance(&instanceCreateInfo, nullptr, &instance_) != VK_SUCCESS) {
			std::cout << "Error\n";
		}
	}

	void Destroy() {
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
};


int main() {

	Engine engine;
	engine.Init();
	engine.Run();

    return 0;
}
