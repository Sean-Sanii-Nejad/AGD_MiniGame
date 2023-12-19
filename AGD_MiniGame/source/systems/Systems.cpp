#include "../../include/systems/Systems.h"
#include "../../include/core/Game.h"
#include "../../include/entities/Player.h"
#include "../../include/components/InputComponent.h"
#include "../../include/core/InputHandler.h"
#include "../../include/core/Command.h"
#include <stdexcept>
#include <iostream>
#include <cmath>

void TTLSystem::update(Entity* entity, Game* game, float elapsedTime)
{
	if (entity->getComponent(ComponentID::TTL))
	{
		std::shared_ptr<TTLComponent> ttl = std::dynamic_pointer_cast<TTLComponent>(entity->getComponent(ComponentID::TTL));

		ttl->decrementTTL();
		if (ttl->getTTL() <= 0)
		{
			entity->markDeleted();
		}
	}
}

void InputSystem::update(Entity* entity, Game* game, float elapsedTime)
{	
	if (entity->getComponent(ComponentID::INPUT))
	{	
		std::shared_ptr<VelocityComponent> velocity = std::dynamic_pointer_cast<VelocityComponent>(entity->getComponent(ComponentID::VELOCITY));
		std::shared_ptr<InputComponent> input = std::dynamic_pointer_cast<InputComponent>(entity->getComponent(ComponentID::INPUT));

		velocity->setVelocityDirection(0.f, 0.f);
		
		for (auto inputHandler : input->getPlayerInputHander()->handleInput())
		{
			inputHandler->execute(*game);
		}
	}
}

void MovementSystem::update(Entity* entity, Game* game, float elapsedTime)
{
	std::shared_ptr<VelocityComponent> velocity = std::dynamic_pointer_cast<VelocityComponent>(entity->getComponent(ComponentID::VELOCITY));
	std::shared_ptr<PositionComponent> position = std::dynamic_pointer_cast<PositionComponent>(entity->getComponent(ComponentID::POSITION));
	if (entity->getEntityType() == EntityType::FIRE)
	{
		position->setPosition(
			position->getPosition().x + (velocity->getVelocityDirection().x * velocity->getSpeed() * elapsedTime),
			position->getPosition().y + (velocity->getVelocityDirection().y * velocity->getSpeed() * elapsedTime)
		);	
	}
	else
	{
		if (game->getCurrentControl() == MOUSE || entity->getEntityType() == EntityType::FIRE)
		{
			if ((movement_x != 0 || movement_y != 0))
			{
				int positionIntX = static_cast<int>(position->getPosition().x);
				int positionIntY = static_cast<int>(position->getPosition().y);

				if (positionIntX == (int)target_x || positionIntY == (int)target_y)
				{
					movement_x = 0;
					movement_y = 0;
					return;
				}

				float magnitude = (float)sqrt(pow(movement_x, 2) + pow(movement_y, 2));
				float normalised_x = movement_x / magnitude;
				float normalised_y = movement_y / magnitude;

				velocity->setVelocityDirection(normalised_x, normalised_y);
				position->setPosition(
					position->getPosition().x + (velocity->getVelocityDirection().x * velocity->getSpeed() * elapsedTime),
					position->getPosition().y + (velocity->getVelocityDirection().y * velocity->getSpeed() * elapsedTime)
				);
			}
		}
		else
		{
			if (velocity)
			{
				position->setPosition(
					position->getPosition().x + (velocity->getVelocityDirection().x * velocity->getSpeed() * elapsedTime),
					position->getPosition().y + (velocity->getVelocityDirection().y * velocity->getSpeed() * elapsedTime)
				);
			}
		}
	}
}

void GraphicsSystem::update(Entity* entity, Game* game, float elapsedTime)
{
	std::shared_ptr<GraphicsComponent> graphics = std::dynamic_pointer_cast<GraphicsComponent>(entity->getComponent(ComponentID::GRAPHICS));
	std::shared_ptr<PositionComponent> position = std::dynamic_pointer_cast<PositionComponent>(entity->getComponent(ComponentID::POSITION));

	if (!game->isPaused()) { graphics->update(game, elapsedTime, position->getPosition()); }
	graphics->draw(game->getWindow());
}

void ColliderSystem::update(Entity* entity, Game* game, float elapsedTime)
{
	std::shared_ptr<ColliderComponent> collider = std::dynamic_pointer_cast<ColliderComponent>(entity->getComponent(ComponentID::COLLIDER));

	collider->getBoundingBox().setTopLeft(entity->getPosition());
	collider->getBoundingBox().setBottomRight(Vector2f((entity->getPosition().x + collider->getBboxSize().x), (entity->getPosition().y + collider->getBboxSize().y)));
}

void PrintDebugSystem::update(Entity* entity, Game* game, float elapsedTime)
{
	std::shared_ptr<ColliderComponent> collider = std::dynamic_pointer_cast<ColliderComponent>(entity->getComponent(ComponentID::COLLIDER));
	collider->draw(game->getWindow());
}

void GameplaySystem::update(Entity* entity, Game* game, float elapsedTime)
{
	std::shared_ptr<PlayerStateComponent> state = std::dynamic_pointer_cast<PlayerStateComponent>(entity->getComponent(ComponentID::STATE));

	state->update(*entity, game, elapsedTime);
}
