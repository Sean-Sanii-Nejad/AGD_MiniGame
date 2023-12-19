#include "../../include/core/Command.h"
#include "../../include/core/Game.h"

void PauseCommand::execute(Game& game)
{
	game.togglePause();
}

void SwitchCommand::execute(Game& game)
{
	game.toggleControl();
}