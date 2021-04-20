#include <gtest/gtest.h>

#include <entity_manager.h>
#include <components/Component.h>

#include <components/position_component_manager.h>

TEST(ECS, EntityManager_CreateEntity) {
	using namespace alloy;

	ecs::EntityManager entityManager;

	const auto entity0 = entityManager.CreateEntity();
	const auto entity1 = entityManager.CreateEntity();
	
	EXPECT_EQ(entity0, 0);
	EXPECT_EQ(entity1, 1);
}

TEST(ECS, EntityManager_DestroyEntity) {
	using namespace alloy;

	ecs::EntityManager entityManager;

	const auto entity = entityManager.CreateEntity();

	EXPECT_TRUE(entityManager.HasComponent(entity, static_cast<ecs::ComponentID>(ecs::CoreComponent::INSTANTIATED_FLAG)));
	
	entityManager.DestroyEntity(entity);

	EXPECT_FALSE(entityManager.HasComponent(entity, static_cast<ecs::ComponentID>(ecs::CoreComponent::INSTANTIATED_FLAG)));
}

TEST(ECS, EntityManager_AddAndDestroyEntity) {
	using namespace alloy;

	ecs::EntityManager entityManager;

	const auto entity0 = entityManager.CreateEntity();
	const auto entity1 = entityManager.CreateEntity();
	const auto entity2 = entityManager.CreateEntity();
	const auto entity3 = entityManager.CreateEntity();

	EXPECT_EQ(entity0, 0);
	EXPECT_EQ(entity1, 1);
	EXPECT_EQ(entity2, 2);
	EXPECT_EQ(entity3, 3);

	entityManager.DestroyEntity(entity0);

	const auto entity4 = entityManager.CreateEntity();
	EXPECT_EQ(entity4, entity0);
}

TEST(ECS, EntityManager_HasComponent) {
	using namespace alloy;

	ecs::EntityManager entityManager;

	const auto entity = entityManager.CreateEntity();

	entityManager.AddComponent(entity, static_cast<ecs::ComponentID>(ecs::CoreComponent::POSITION));

	EXPECT_TRUE(entityManager.HasComponent(entity, static_cast<ecs::ComponentID>(ecs::CoreComponent::POSITION)));
}

TEST(ECS, EntityManager_AddComponent) {
	using namespace alloy;

	ecs::EntityManager entityManager;

	const auto entity = entityManager.CreateEntity();

	entityManager.AddComponent(entity, static_cast<ecs::ComponentID>(ecs::CoreComponent::POSITION));

	EXPECT_TRUE(entityManager.HasComponent(entity, static_cast<ecs::ComponentID>(ecs::CoreComponent::POSITION)));
}

TEST(ECS, EntityManager_RemoveComponent) {
	using namespace alloy;

	ecs::EntityManager entityManager;

	const auto entity = entityManager.CreateEntity();

	entityManager.AddComponent(entity, static_cast<ecs::ComponentID>(ecs::CoreComponent::POSITION));

	EXPECT_TRUE(entityManager.HasComponent(entity, static_cast<ecs::ComponentID>(ecs::CoreComponent::POSITION)));

	entityManager.RemoveComponent(entity, static_cast<ecs::ComponentID>(ecs::CoreComponent::POSITION));

	EXPECT_FALSE(entityManager.HasComponent(entity, static_cast<ecs::ComponentID>(ecs::CoreComponent::POSITION)));
}

TEST(ECS, Component_Position_SetComponent) {
	using namespace alloy;

	ecs::EntityManager entityManager;

	const auto entity = entityManager.CreateEntity();

	ecs::Position position;

	position.position.x = 1;
	position.position.y = 1;

	entityManager.AddComponentData<ecs::Position>(entity, position);

	EXPECT_TRUE(entityManager.HasComponent(entity, static_cast<ecs::ComponentID>(ecs::CoreComponent::POSITION)));

	ecs::Position pos = entityManager.GetComponentData<ecs::Position>(entity);

	EXPECT_EQ(pos.position.x, 1);
	EXPECT_EQ(pos.position.y, 1);
}

TEST(ECS, System_SetComponent) {
	using namespace alloy;

	ecs::EntityManager entityManager;

	const auto entity = entityManager.CreateEntity();

	ecs::Position position;

	position.position.x = 1;
	position.position.y = 1;

	entityManager.AddComponentData<ecs::Position>(entity, position);

	EXPECT_TRUE(entityManager.HasComponent(entity, static_cast<ecs::ComponentID>(ecs::CoreComponent::POSITION)));

	ecs::Position pos = entityManager.GetComponentData<ecs::Position>(entity);

	EXPECT_EQ(pos.position.x, 1);
	EXPECT_EQ(pos.position.y, 1);
}