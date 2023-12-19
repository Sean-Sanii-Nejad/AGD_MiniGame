#include "../../include/systems/Observer.h"
#include "../../include/core/Game.h"
#include "../../include/entities/Player.h"


void AchievementManager::init(std::shared_ptr<Entity> entity)
{
	std::shared_ptr<Player> player = std::dynamic_pointer_cast<Player>(entity);
	player->getPotionCollected().addObserver(this);
	player->getShoutTriggered().addObserver(this);
}


bool AchievementManager::onNotify(Entity& entity, EventType event)
{
	switch (event)
	{
	case EventType::COLLECT_POTION:
	{
		potionCounter++;
		return (potionCounter >= potionGoal) ? unlockAchievement(entity, AchievementType::COLLECTED_ALL_POTIONS), true : false;
		break;
	}
	case EventType::SHOUT:
	{
		shoutCounter++;
		return (shoutCounter >= shoutGoal) ? unlockAchievement(entity, AchievementType::SHOUT_5_TIMES), true : false;
		break;
	}
	default:
		return false;
	}
}

void AchievementManager::unlockAchievement(Entity& entity, AchievementType achievement)
{
	switch (achievement)
	{
	case AchievementType::COLLECTED_ALL_POTIONS:
	{
		std::cout << "Achievement Unlocked: Collected All Potions" << std::endl;
		Player* player = dynamic_cast<Player*>(&entity);
		player->getPotionCollected().removeObserver(this);
		break;
	}
	case AchievementType::SHOUT_5_TIMES:
	{
		std::cout << "Achievement Unlocked: Successfully shot 5 fireballs" << std::endl;
		Player* player = dynamic_cast<Player*>(&entity);
		player->getShoutTriggered().removeObserver(this);
		break;
	}
	default:
		break;
	}
}


	
