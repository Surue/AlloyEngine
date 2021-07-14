#pragma once
#include <SFML/Graphics.hpp>

#include "drawing_instruction_2d.h"
#include <primitives/circle.h>
#include <primitives/rect.h>

namespace alloy::graphics {
class Renderer2D {
public:
	Renderer2D() {
		
	}

	void Init() {
		
	}

	void Draw(sf::RenderTarget& target) {
		//Draw Circles
		for(size_t i = 0; i < circlesCount_; i++) {
			circles_[i].Draw(target);
		}

		//Draw rects
		for(size_t i = 0; i < rectsCount_; i++) {
			rects_[i].Draw(target);
		}

		circlesCount_ = 0;
		rectsCount_ = 0;
	}

	void AddDrawingInstructions2d(const std::vector<DrawingInstruction2d>& drawingInstructions) {		
		for(size_t i = 0; i < drawingInstructions.size(); i++) {
			switch(drawingInstructions[i].type) {
			case PrimitiveType::CIRCLE:
				if(circles_.size() == circles_.capacity()) {
					circles_.reserve(circles_.size() * 2 + 1);
				}
				circles_.emplace_back(drawingInstructions[i].scale.x, drawingInstructions[i].position, drawingInstructions[i].color);
				circlesCount_++;
				break;
			case PrimitiveType::RECT:
				if (circles_.size() == circles_.capacity()) {
					circles_.reserve(circles_.size() * 2 + 1);
				}
				rects_.emplace_back(math::fvec2(drawingInstructions[i].scale.x, drawingInstructions[i].scale.x), drawingInstructions[i].position, drawingInstructions[i].color);
				rectsCount_++;
				break;
			case PrimitiveType::POLYGON:
				//debug::LogError("Renderer2D: PrimitiveType.Polygon not implemented yet", debug::LogType::GRAPHICS);
				break;
			default:
				break;
				//debug::LogError("Renderer2D: trying to draw an unknown PrimitiveType (" + std::to_string(static_cast<int>(drawingInstructions[i].type)) + ")", debug::LogType::GRAPHICS);
			}
		}
	}

private:
	std::vector<Circle> circles_;
	size_t circlesCount_ = 0;
	
	std::vector<Rect> rects_;
	size_t rectsCount_ = 0;
};
} // namespace alloy::graphics
