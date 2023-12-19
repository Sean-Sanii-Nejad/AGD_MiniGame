#pragma once
#include "../graphics/Window.h"
#include "../utils/Rectangle.h"
#include "../../include/components/GraphicsComponent.h"
#include "../components/ColliderComponent.h"
#include "../utils/Bitmask.h"
#include "../components/TTLComponent.h"
#include <memory>

class PositionComponent;
class InputComponent;
class VelocityComponent;
class PlayerStateComponent;

enum class ArchetypeID;

using EntityID = unsigned int;
enum class EntityType
{
	UNDEFINED = -1,
	PLAYER = 0,
	POTION = 1,
	LOG = 2,
	FIRE = 3
};

class Game;

class Entity
{
public:
	Entity();
	Entity(EntityType et);
	~Entity();
	virtual void init(const std::string& textureFile, float scale, std::shared_ptr<GraphicsComponent> _graphics);
	void initSpriteSheet(const std::string& spriteSheetFile);
	void addComponent(std::shared_ptr<Component> c);
	std::shared_ptr<Component> getComponent(ComponentID id) { return mapComponent[id]; }
	void setID(EntityID entId) { id = entId; }
	EntityID getID() const { return id; }
	void setPosition(float x, float y) ;
	Vector2f getPosition();
	EntityType getEntityType() const { return type; }
	Bitmask getComponentSet() { return componentSet; }
	std::shared_ptr<PositionComponent> getPositionComponent() { return position; }
	std::shared_ptr<GraphicsComponent> getGraphicsComponent() { return graphics; }
	bool isDeleted() const { return deleted; }
	bool hasComponent(Bitmask mask) const { return componentSet.contains(mask); }
	void markDeleted() { deleted = true; }
	virtual std::shared_ptr<ColliderComponent> getColliderComponent();
	void setArchetypeID(ArchetypeID _archetypeID);
	ArchetypeID getArchetypeID() const;

protected:
	EntityType type;
	EntityID id;
	Bitmask componentSet;
	bool isSpriteSheet;
	bool deleted;
	std::map<ComponentID, std::shared_ptr<Component>> mapComponent;
	std::shared_ptr<PositionComponent> position;
	std::shared_ptr<GraphicsComponent> graphics;
	std::shared_ptr<ColliderComponent> collider;
	ArchetypeID archetypeID;
};