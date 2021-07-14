#include <systems/renderer_2d_system.h>

#include <entity_manager.h>
#include <renderer_2d/drawing_instruction_2d.h>
#include <components/renderer_2d_component_manager.h>

namespace alloy {
void Renderer2DSystem::OnInit() {}

void Renderer2DSystem::OnUpdate() {
	auto& entityManager = ServiceLocator::Get<ecs::EntityManager>();
	auto entities = entityManager.GetEntities({ 
		static_cast<ecs::ComponentID>(ecs::CoreComponentID::POSITION),
		static_cast<ecs::ComponentID>(ecs::CoreComponentID::RENDERER_2D)});

	std::vector<graphics::DrawingInstruction2d> drawingInstructions;
	drawingInstructions.reserve(entities.size());
	
	for(size_t i = 0; i < entities.size(); i++) {
		const auto entityIndex = entities[i];

		const auto& position = entityManager.GetComponentData<ecs::Position>(entityIndex);
		const auto& renderer2D = entityManager.GetComponentData<ecs::Renderer2D>(entityIndex);

		graphics::PrimitiveType primitiveType = graphics::PrimitiveType::RECT;

		if(renderer2D.shape == ecs::Renderer2DShape::SQUARE) {
			primitiveType = graphics::PrimitiveType::RECT;
		}else if(renderer2D.shape == ecs::Renderer2DShape::CIRCLE) {
			primitiveType = graphics::PrimitiveType::CIRCLE;
		}

		graphics::DrawingInstruction2d drawingInstruction{
			position.position,
			math::fvec2(10.0f, 10.0f),
			renderer2D.color,
			primitiveType
		};

		drawingInstructions.emplace_back(drawingInstruction);
	}

	renderer2d_.AddDrawingInstructions2d(drawingInstructions);
}
} // namespace alloy
