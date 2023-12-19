#include "../../include/core/Command.h"
#include "../../include/core/Game.h"
#include "../../include/utils/ArchetypeManager.h"
#include <iostream>
#include <cmath>

void MoveRightCommand::execute(Game& game)
{
	//if (game.isMouse()) return;
	std::shared_ptr<VelocityComponent> velocity = std::dynamic_pointer_cast<VelocityComponent>(game.getPlayer()->getComponent(ComponentID::VELOCITY));
	velocity->setVelocityDirection(1.f, velocity->getVelocityDirection().y);
}

void MoveLeftCommand::execute(Game& game)
{
	//if (game.isMouse()) return;
	std::shared_ptr<VelocityComponent> velocity = std::dynamic_pointer_cast<VelocityComponent>(game.getPlayer()->getComponent(ComponentID::VELOCITY));
	velocity->setVelocityDirection(-1.f, velocity->getVelocityDirection().y);
}

void MoveUpCommand::execute(Game& game)
{
	//if (game.isMouse()) return;
	std::shared_ptr<VelocityComponent> velocity = std::dynamic_pointer_cast<VelocityComponent>(game.getPlayer()->getComponent(ComponentID::VELOCITY));
	velocity->setVelocityDirection(velocity->getVelocityDirection().x, -1.f);
}

void MoveDownCommand::execute(Game& game)
{
	//if (game.isMouse()) return;
	std::shared_ptr<VelocityComponent> velocity = std::dynamic_pointer_cast<VelocityComponent>(game.getPlayer()->getComponent(ComponentID::VELOCITY));
	velocity->setVelocityDirection(velocity->getVelocityDirection().x, 1.f);
}

void AttackCommand::execute(Game& game)
{
	std::shared_ptr<PlayerStateComponent> state = std::dynamic_pointer_cast<PlayerStateComponent>(game.getPlayer()->getComponent(ComponentID::STATE));
	state->setAttacking(true);
}

void FireCommand::execute(Game& game)
{
	std::shared_ptr<PlayerStateComponent> state = std::dynamic_pointer_cast<PlayerStateComponent>(game.getPlayer()->getComponent(ComponentID::STATE));
	state->setShouting(true);
}

void ClickCommand::execute(Game& game)
{
	if (game.getCurrentControl() == 2)
	{
		std::shared_ptr<PositionComponent> position = std::dynamic_pointer_cast<PositionComponent>(game.getPlayer()->getComponent(ComponentID::POSITION));
		std::shared_ptr<VelocityComponent> velocity = std::dynamic_pointer_cast<VelocityComponent>(game.getPlayer()->getComponent(ComponentID::VELOCITY));

		float target_x = sf::Mouse().getPosition(game.getWindow()->getWindow()).x - 50.f;
		float target_y = sf::Mouse().getPosition(game.getWindow()->getWindow()).y - 80.f;

		float player_x = position->getPosition().x;
		float player_y = position->getPosition().y;

		float movement_x = target_x - player_x;
		float movement_y = target_y - player_y;

		if (!movement)
		{
			switch (game.getEcsMethod())
			{
			case bigArray:
				movement = std::dynamic_pointer_cast<MovementSystem>(game.getEcsManager().getLogicSystems()[2]);
				break;
			case archetypes:
				movement = std::dynamic_pointer_cast<MovementSystem>(game.getEcsManager().getArchetypeManager()->getSystems(ArchetypeID::DwarfPlayer, SystemType::Logic)[1]);
				break;
			default:
				break;
			}
		}

		movement->setTargetX(target_x);
		movement->setTargetY(target_y);
		movement->setMovementX(movement_x);
		movement->setMovementY(movement_y);
	}
}
