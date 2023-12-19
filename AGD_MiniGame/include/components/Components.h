#pragma once

enum class ComponentID
{
	UNDEFINED = -1,
	INPUT = 0,
	STATE = 1,
	POSITION = 2,
	COLLIDER = 3,
	VELOCITY = 4,
	GRAPHICS = 5,
	HEALTH = 6,
	TTL = 7,
};

class Component
{
public:
	~Component() {};
	virtual ComponentID getID() = 0;
};