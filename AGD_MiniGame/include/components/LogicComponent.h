#pragma once
#include <memory>
#include "Components.h"

class VelocityComponent;
class Entity;
class Game;
class Fire;

class LogicComponent : public Component
{
public:
	~LogicComponent() {};
	virtual void update(Entity& entity, Game* game, float elapsed) = 0;
};

class PlayerStateComponent : public LogicComponent
{
public:
	PlayerStateComponent(
		bool _attacking,
		bool _shouting,
		int _maxWood,
		int _wood,
		int _shootingCost,
		float _shootCooldown,
		float _shootCooldownTime,
		float _fireSpeed,
		std::shared_ptr<VelocityComponent> _velocity) : 
		attacking{ _attacking }, 
		shouting{ _shouting },  
		maxWood { _maxWood }, 
		wood{ _wood }, 
		fireSpeed{ _fireSpeed }, 
		shootingCost{ _shootingCost },
		shootCooldown{ _shootCooldown },
		shootCooldownTime{ _shootCooldownTime },
		velocity{ _velocity } {};

	void update(Entity& entity, Game* game, float elapsed) override;

	void addWood(int w);

	std::shared_ptr<Fire> createFire(Entity*) const;
	ComponentID getID() { return ComponentID::STATE; }

	bool isAttacking() const { return attacking; }
	void setAttacking(bool at) { attacking = at; }

	bool isShouting() const { return shouting; }
	void setShouting(bool sh) { shouting = sh; }

private:

	std::shared_ptr<VelocityComponent> velocity;

	bool attacking;
	bool shouting;
	int wood;
	int maxWood;
	int shootingCost;
	float shootCooldown;
	float shootCooldownTime;
	float fireSpeed;

	bool axeAudio = false;
};