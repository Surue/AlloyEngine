#include <iostream>
#include <vector.h>

#define SDL_MAIN_HANDLED
#include <SDL.h>

int main() {

	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
		return 1;
	}
	
	SDL_Window* window = SDL_CreateWindow("Alloy Engine", 100, 100, 640, 720, SDL_WINDOW_SHOWN);


	if (window == nullptr) {
		std::cout << "SDL_CreateWindow Error : " << SDL_GetError() << "\n";
		SDL_Quit();
		return 1;
	}

	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (renderer == nullptr) {
		SDL_DestroyWindow(window);
		std::cout << "SDL_CreateRenderer Error : " << SDL_GetError() << "\n";
		SDL_Quit();
		return 1;
	}
	
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
		//Render the scene
		SDL_RenderClear(renderer);
		SDL_RenderPresent(renderer);
	}

    return 0;
}
