#include "../../include/utils/Rectangle.h"
#include "../../include/graphics/Window.h"
#include "Components.h"

class Entity;


class ColliderComponent : public Component
{
public:
	Rectangle& getBoundingBox() { return boundingBox; }
	Vector2f getBboxSize() { return bboxSize; }
	void setBboxSize(Vector2f _bboxSize) { bboxSize = _bboxSize; }
	void setBoundingBoxLocation(Vector2f position);
	void draw(Window* window) { window->draw(boundingBox.getDrawableRect()); }
	bool intersects(Rectangle& otherBbox) { return boundingBox.intersects(otherBbox); }

	ComponentID getID() { return ComponentID::COLLIDER; }

private:
	Rectangle boundingBox;
	Vector2f bboxSize;
};