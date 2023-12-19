#pragma once
#include "../entities/Entity.h"

class Game;

enum class EventType
{
	UNDEFINED = -1,
	COLLECT_POTION = 0,
	SHOUT = 1
};

enum class AchievementType
{
	UNDEFINED = -1,
	COLLECTED_ALL_POTIONS = 0,
	SHOUT_5_TIMES = 1
};

class Observer
{
public:
	virtual ~Observer() {}
	virtual bool onNotify(Entity& entity, EventType event) = 0;
};

class AchievementManager : public Observer
{
public:

	bool onNotify(Entity& entity, EventType event) override;
	void init(std::shared_ptr<Entity>);

private:
	void unlockAchievement(Entity& entity, AchievementType achievement);

	int potionCounter = 0;
	int shoutCounter = 0;

	const int potionGoal = 6;
	const int shoutGoal = 5;
};