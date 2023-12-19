#pragma once
#include "Entity.h"
#include "../components/HealthComponent.h"
#include "../components/VelocityComponent.h"
#include "../components/LogicComponent.h"
#include "../systems/Subject.h"

class Fire;
class InputComponent;
class LogicComponent;
class PlayerInputHandler;

class Player :  public Entity
{
public:

	const float playerSpeed = 100.f;
	const int startingHealth = 60;
	const int maxHealth = 100;
	const int maxWood = 100;
	const int shootingCost = 20;
	const float fireSpeed = 200.f;
	const float shootCooldownTime = 3.f; //in seconds

	Player();
	~Player();

	std::shared_ptr<InputComponent> getInputComponent() 
	{
		return playerInput;
	}

	bool isAttacking() const { return attacking; }
	void setAttacking(bool at) { attacking = at; }

	bool isShouting() const { return shouting; }
	void setShouting(bool sh) { shouting = sh; }

	std::shared_ptr<HealthComponent> getHealthComp() { return healthComponent; }

	int getWood() const { return wood; }

	bool hasSpriteSheet() const { return isSpriteSheet; }

	void positionSprite(int row, int col, int spriteWH, float tileScale);

	void setGraphicsPointer(std::shared_ptr<GraphicsComponent> _graphics) { 
		addComponent(_graphics);
		graphics = _graphics;
	}

	bool intersects(Entity& other);

	std::shared_ptr<ColliderComponent> getColliderComponent() override { return collider; }

	Subject& getPotionCollected() { return potionCollected; }
	Subject& getShoutTriggered() { return shoutTriggered; }
	void collectPotion();
	void shoutTrigger();

	void handlePotionCollision(std::shared_ptr<Entity> _entity);
	void handleLogCollision(std::shared_ptr<Entity> _entity);



private:

	bool attacking;
	bool shouting;
	int wood;
	float shootCooldown;

	std::shared_ptr<InputComponent> playerInput;
	std::shared_ptr<HealthComponent> healthComponent;
	std::shared_ptr<VelocityComponent> velocity;
	std::shared_ptr<PlayerStateComponent> state;

	Subject potionCollected;
	Subject shoutTriggered;
};

