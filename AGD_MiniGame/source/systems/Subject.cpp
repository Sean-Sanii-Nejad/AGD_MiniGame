#include "../../include/systems/Subject.h"
#include <vector>


void Subject::notify(Entity& entity, EventType event)
{
	for (Observer* o : observers)
	{
		o->onNotify(entity, event);
	}
}

void Subject::addObserver(Observer* observer)
{ 
	observers.push_back(observer);
}

void Subject::removeObserver(Observer* observer)
{
	auto index = std::find(observers.begin(), observers.end(), observer);
	if (index != observers.end()) {
		observers.erase(index);
	}
}