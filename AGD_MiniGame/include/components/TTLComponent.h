#pragma once
#include "Components.h"


class TTLComponent : public Component
{
public:

	TTLComponent(int _ttl) : ttl{ _ttl } {}

	int getTTL() { return ttl; }
	ComponentID getID() { return ComponentID::TTL; }

	void decrementTTL() 
	{ 
		--ttl; 
	}

private:

	int ttl;

};