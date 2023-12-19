#include "../../include/core/InputHandler.h"
#include "../../include/core/Command.h"
#include <iostream>

InputHandler::InputHandler()
{
	pause = std::make_shared<PauseCommand>();
    enter = std::make_shared<SwitchCommand>();
}

PlayerInputHandler::PlayerInputHandler()
{ 
    right = std::make_shared<MoveRightCommand>();
    left = std::make_shared<MoveLeftCommand>();
    up = std::make_shared<MoveUpCommand>();
    down = std::make_shared<MoveDownCommand>();
    attack = std::make_shared<AttackCommand>();
    fire = std::make_shared<FireCommand>();
    click = std::make_shared <ClickCommand>();  

    activeCommands.insert(std::make_pair(sf::Keyboard::W, up));
    activeCommands.insert(std::make_pair(sf::Keyboard::A, left));
    activeCommands.insert(std::make_pair(sf::Keyboard::S, down));
    activeCommands.insert(std::make_pair(sf::Keyboard::D, right));

}

std::shared_ptr<Command> InputHandler::handleInput()
{
    static bool isEscapePressed = false;
    static bool isEnterPressed = false;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
    {
        if (!isEscapePressed)
        {
            isEscapePressed = true;
            return pause;
        }
    }
    else
    {
        isEscapePressed = false;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
    {
        if (!isEnterPressed)
        {
            isEnterPressed = true;
            return enter;
        }
    }
    else
    {
        isEnterPressed = false;
    }
    
    return nullptr;
}

std::vector <std::shared_ptr<Command>> PlayerInputHandler::handleInput()
{
    arrayCommand.clear();

    for (auto const& command : activeCommands)
    {
        if (sf::Keyboard::isKeyPressed(command.first))
        {
            arrayCommand.push_back(command.second);
        }
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
    {
        arrayCommand.push_back(attack);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
    {
        arrayCommand.push_back(fire);
    }
    if (sf::Mouse::isButtonPressed(sf::Mouse::Right) && mouse)
    {
        arrayCommand.push_back(click);
    }
    return arrayCommand;
}

void PlayerInputHandler::updateKeys(int currentControl)
{
    activeCommands.clear();
    mouse = false;
    if (currentControl == 0)
    {
        activeCommands.insert(std::make_pair(sf::Keyboard::W, up));
        activeCommands.insert(std::make_pair(sf::Keyboard::A, left));
        activeCommands.insert(std::make_pair(sf::Keyboard::S, down));
        activeCommands.insert(std::make_pair(sf::Keyboard::D, right));
    }
    else if(currentControl == 1)
    {
        activeCommands.insert(std::make_pair(sf::Keyboard::Up, up));
        activeCommands.insert(std::make_pair(sf::Keyboard::Left, left));
        activeCommands.insert(std::make_pair(sf::Keyboard::Down, down));
        activeCommands.insert(std::make_pair(sf::Keyboard::Right, right));
    }
    else if (currentControl == 2)
    {
        mouse = true;
    }
}