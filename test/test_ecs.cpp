#include <gtest/gtest.h>

#include <entity_manager.h>
#include <component.h>

TEST(ECS, EntityManager_CreateEntity) {
	using namespace alloy;

	ecs::EntityManager entityManager;

	auto entityHandle = entityManager.CreateEntity();
	auto entityHandle2 = entityManager.CreateEntity();
	
	EXPECT_EQ(entityHandle.GetEntityIndex(), 0);
	EXPECT_EQ(entityHandle2.GetEntityIndex(), 1);
}

TEST(ECS, Entityhandle_AddComponent) {
	using namespace alloy;

	ecs::EntityManager entityManager;

	auto entityHandle = entityManager.CreateEntity();

	entityHandle.AddComponent(static_cast<ecs::Component>(ecs::CoreComponent::POSITION));

	const auto entity = entityHandle.GetEntity();

	EXPECT_TRUE(entity.test(static_cast<ecs::Component>(ecs::CoreComponent::POSITION)));
}

TEST(ECS, EntityHandle_HasComponent) {
	using namespace alloy;

	ecs::EntityManager entityManager;

	auto entityHandle = entityManager.CreateEntity();

	entityHandle.AddComponent(static_cast<ecs::Component>(ecs::CoreComponent::POSITION));

	const auto entity = entityHandle.GetEntity();

	EXPECT_TRUE(entityHandle.HasComponent(static_cast<ecs::Component>(ecs::CoreComponent::POSITION)));
}