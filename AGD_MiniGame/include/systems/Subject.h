#pragma once
#include "Observer.h"

class Subject
{
public:
	void addObserver(Observer* observer);
	void removeObserver(Observer* observer);

	void notify(Entity& entity, EventType event);

	std::vector<Observer*> getObserversVector() { return observers; }

private:
	std::vector<Observer*> observers;
};