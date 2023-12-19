#include "../../include/core/Game.h"
#include "../../include/entities/Fire.h"
#include "../../include/entities/StaticEntities.h"
#include "../../include/core/InputHandler.h"
#include "../../include/core/Command.h"
#include "../../include/components/GraphicsComponent.h"
#include "../../include/components/LogicComponent.h"
#include "../../include/systems/Systems.h"
#include "../../include/systems/Observer.h"
#include "../../include/components/InputComponent.h"
#include "../../include/utils/Locator.h"
#include <iostream>


Game::Game() : id{ 0 }, paused(false), drawDebug(true), ecsMethod(EcsMethod::archetypes)
{
	inputHandler = std::make_unique<InputHandler>();
	ecsManager.populateECS(*this);
	std::cout << "WASD Control" << std::endl;
	ServiceLocator::ServiceLocator();
}

Game::~Game()
{
	
}

void Game::toggleControl()
{
	switch (currentControl)
	{
		case WASD:
		{
			currentControl = ARROWS;
			std::cout << "Arrows Control" << std::endl;
			break;
		}
		case ARROWS:
		{
			currentControl = MOUSE;
			std::cout << "Mouse Control" << std::endl;
			break;
		}
		case MOUSE:
		{
			std::cout << "WASD Control" << std::endl;
			currentControl = WASD;
			break;
		}
	}
	getPlayer()->getInputComponent()->getPlayerInputHander()->updateKeys(currentControl);
}

template <typename T>
std::shared_ptr<T> Game::buildEntityAt(const std::string& filename, int col, int row, std::shared_ptr<GraphicsComponent> graphicsComponentPointer)
{
	auto ent = std::make_shared<T>();
	float x = col * spriteWH * tileScale;
	float y = row * spriteWH * tileScale;
	float cntrFactor = (tileScale - itemScale) * spriteWH * 0.5f;

	ent->init(filename, itemScale, graphicsComponentPointer);
	ent->setPosition(x + cntrFactor, y + cntrFactor);
	
	return ent;
}

void Game::buildBoard(size_t width, size_t height)
{
	board = std::make_unique<Board>(width, height);
}

void Game::initWindow(size_t width, size_t height)
{
	int wdt = static_cast<int>(width * spriteWH * tileScale);
	int hgt = static_cast<int>(height * spriteWH * tileScale);
	window.setSize(sf::Vector2u(wdt, hgt));
	window.redraw();
}

void Game::init(std::vector<std::string> lines)
{
	size_t h = lines.size() - 1;
	if (h < 0)
		throw std::exception("No data in level file");
	size_t w = -1;

	window.loadFont("font/AmaticSC-Regular.ttf");
	window.setTitle("Mini-Game");
	
	auto it = lines.cbegin();
	int row = 0;
	while (it != lines.cend())
	{
		int col = 0;
		if(w == -1)
		{
			w = it->size();
			buildBoard(w, h);
			initWindow(w, h);		
		}
		
		std::string::const_iterator is = it->cbegin();
		while (is != it->cend())
		{
			switch (*is)
			{
			case '.': // corriodor
			{
				board->addTile(col, row, tileScale, TileType::CORRIDOR);
				break;
			}
			case 'w': // wall
			{
				board->addTile(col, row, tileScale, TileType::WALL);
				break;
			}
			case 'x': // log
			{
				auto logEntity = buildEntityAt<Log>("./img/log.png", col, row, std::make_shared<SpriteGraphics>());
				addEntity(logEntity);	
				board->addTile(col, row, tileScale, TileType::CORRIDOR);
				break;
			}
			case 'p': // potion
			{
				auto potionEntity = buildEntityAt<Potion>("./img/potion.png", col, row, std::make_shared<SpriteGraphics>());
				addEntity(potionEntity);			
				board->addTile(col, row, tileScale, TileType::CORRIDOR);
				break;
			}
			case '*': // player
			{
				player = std::make_shared<Player>();
				achievementManager.init(player);
				player->setGraphicsPointer(std::make_shared<SpriteSheetGraphics>());
				player->initSpriteSheet("./img/DwarfSpriteSheet_data.txt");
				player->positionSprite(row,col,spriteWH,tileScale);
				addEntity(player);
				
				collisionCallbacks[EntityType::POTION] = std::bind(&Player::handlePotionCollision, player.get(), std::placeholders::_1);
				collisionCallbacks[EntityType::LOG] = std::bind(&Player::handleLogCollision, player.get(), std::placeholders::_1);

				board->addTile(col, row, tileScale, TileType::CORRIDOR);
				break;
			}
			}
			col++; is++;
		}
		row++; it++;
	}
}

void Game::addEntity(std::shared_ptr<Entity> newEntity)
{
	id++;
	newEntity->setID(id);
	entities.push_back(newEntity);
}

void Game::handleInput()
{
	auto command = inputHandler->handleInput();
	if (command) {
		command->execute(*this);
	}
}

void Game::update(float elapsed)
{
	if (!isPaused())
	{
		ecsManager.updateECS(elapsed, *this, SystemType::Logic);
		auto it = entities.begin();
		while (it != entities.end())
		{
			if ((*it) != player) {
				auto entType = (*it)->getEntityType();
				if (entType != EntityType::FIRE)
				{
					if (player->intersects(**it))
					{
						if (collisionCallbacks.count(entType) > 0)
						{
							collisionCallbacks[entType](*it);
						}
					}
				}
			}
			it++;
		}
		it = entities.begin();
		while (it != entities.end())
		{
			if ((*it)->isDeleted())
			{
				it = entities.erase(it);
			}
			else
			{
				++it;
			}
		}
	}
	window.update();
}

void Game::render(float elapsed)
{
	window.beginDraw();
	board->draw(&window);
	ecsManager.updateECS(elapsed, *this, SystemType::Graphics);
	window.drawGUI(*this);
	window.endDraw();
}

void Game::setFPS(int FPS)
{
	std::string text("FPS: " + std::to_string(FPS));
	window.getFPSText().setString(text);
}

EntityID Game::getIDCounter()
{
	return id;
}

std::shared_ptr<Entity> Game::getEntity(unsigned int idx)
{
	if (idx < 0 || idx >= entities.size()) {
		throw std::out_of_range("Index is out of bounds.");
	}
	return entities[idx];
}