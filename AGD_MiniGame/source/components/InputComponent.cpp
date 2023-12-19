#include "../../include/components/InputComponent.h"
#include "../../include/core/Game.h"
#include "../../include/core/InputHandler.h"
#include "../../include/core/Command.h"

#include <memory>


PlayerInputComponent::PlayerInputComponent()
{
	playerInput = std::make_shared<PlayerInputHandler>();
}