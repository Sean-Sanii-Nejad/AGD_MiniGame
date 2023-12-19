#include <memory>
#include "Components.h"

class Game;
class PlayerInputHandler;

class InputComponent : public Component
{
public:
	virtual ~InputComponent() {};
	virtual std::shared_ptr<PlayerInputHandler> getPlayerInputHander() = 0;

};

class PlayerInputComponent : public InputComponent
{
public:
	PlayerInputComponent();
	
	ComponentID getID() override { return ComponentID::INPUT; }

	std::shared_ptr<PlayerInputHandler> getPlayerInputHander() override { return playerInput; }

private:
	std::shared_ptr<PlayerInputHandler> playerInput;

};