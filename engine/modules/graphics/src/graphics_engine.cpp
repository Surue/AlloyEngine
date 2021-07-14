#include <graphics_engine.h>

namespace alloy::graphics {

void GraphicsEngine::Init() {
	window_.Init();
	tilemapManager_.Init();
	renderer2d_.Init();
}

void GraphicsEngine::Update() {
	//Clear windows
	window_.Clear();

	//Draw everything
	auto& renderTarget = window_.GetRenderTarget();
	//tilemapManager_.Draw(renderTarget);
	renderer2d_.Draw(renderTarget);
	lightManager_.Draw(renderTarget);

	//Display
	window_.Display();
}
}
