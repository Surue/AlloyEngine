#pragma once

namespace sf {
class RenderTarget;
}

namespace alloy::graphics {
class IDrawable {
public:
	virtual ~IDrawable() = default;
	virtual void Draw(sf::RenderTarget& renderTarget) = 0;
};
}
