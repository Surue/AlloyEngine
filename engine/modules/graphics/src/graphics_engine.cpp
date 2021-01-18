#include <graphics_engine.h>

namespace alloy::graphics {

void GraphicsEngine::Init() {
	window_.Init();
	tilemapManager_.Init();
}

void GraphicsEngine::Update() {
	//Clear windows
	window_.Clear();

	//Draw everything

	//window_.Draw(sprite);
	tilemapManager_.Draw(window_.GetRenderTarget());

	//Display
	window_.Display();
}
}
