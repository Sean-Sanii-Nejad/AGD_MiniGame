#pragma once
#include "Entity.h"
#include "../components/TTLComponent.h"
#include "../components/VelocityComponent.h"

class Fire : public Entity
{
public:
	const int startTimeToLive = 150; //frames

	Fire();
	~Fire();

	int getTTL() const { return ttlPtr->getTTL(); }

private:

	std::shared_ptr<TTLComponent> ttlPtr;
	std::shared_ptr<VelocityComponent> velocityPtr;
};

