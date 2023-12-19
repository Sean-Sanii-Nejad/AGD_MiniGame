#pragma once
#include "../../include/utils/Vector2.h"
#include "Components.h"


class PositionComponent : public Component
{
public:
	const Vector2f& getPosition() const { return position; }
	void setPosition(float x, float y)
	{
		position.x = x; position.y = y;
	}

	ComponentID getID() { return ComponentID::POSITION; }

private:
	Vector2f position;

};