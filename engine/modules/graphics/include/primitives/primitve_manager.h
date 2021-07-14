#pragma once
#include <vector>

#include <primitives/circle.h>
#include <primitives/polygon.h>
#include <primitives/rect.h>

namespace alloy::graphics {
class PrimitiveManager {
public:
	PrimitiveManager() {
		
	}

	void AddCircleToDraw() {
		
	}

	void Draw(sf::RenderTarget& target) {
		for (auto& circlePrimitive : circlePrimitives_) {
			circlePrimitive.Draw(target);
		}

		for (auto& rectPrimitive : rectPrimitives_) {
			rectPrimitive.Draw(target);
		}

		for (auto& polygonPrimitive : polygonPrimitives_) {
			polygonPrimitive.Draw(target);
		}
	}
private:
	std::vector<Circle> circlePrimitives_;
	std::vector<Rect> rectPrimitives_;
	std::vector<Polygon> polygonPrimitives_;
};
}
