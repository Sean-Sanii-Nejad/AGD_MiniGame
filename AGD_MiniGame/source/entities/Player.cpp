#include "../../include/entities/Player.h"
#include "../../include/graphics/AnimBase.h"
#include "../../include/entities/Fire.h"
#include "../../include/core/Game.h"
#include "../../include/core/InputHandler.h"
#include "../../include/core/Command.h"
#include "../../include/components/InputComponent.h"
#include "../../include/components/PositionComponent.h"
#include "../../include/components/GraphicsComponent.h"
#include "../../include/components/LogicComponent.h"
#include "../../include/entities/StaticEntities.h"
#include "../../include/utils/Locator.h"
#include <iostream>



Player::Player() : Entity(EntityType::PLAYER), attacking(false), shouting(false), wood(0), shootCooldown(0)
{
	playerInput = std::make_shared<PlayerInputComponent>();
	addComponent(playerInput);
	healthComponent = std::make_shared<HealthComponent>(startingHealth, maxHealth);
	addComponent(healthComponent);
	velocity = std::make_shared<VelocityComponent>(playerSpeed);
	addComponent(velocity);
	state = std::make_shared<PlayerStateComponent>(attacking, shouting, maxWood, wood, shootingCost, shootCooldown, shootCooldownTime, fireSpeed, velocity);
	addComponent(state);
	archetypeID = ArchetypeID::DwarfPlayer;
}

Player::~Player() {}

void Player::positionSprite(int row, int col, int spriteWH, float tileScale)
{
	sf::Vector2f scaleV2f = getGraphicsComponent()->getSpriteScale();
	sf::Vector2i textureSize = getGraphicsComponent()->getTextureSize();

	float x = col * spriteWH * tileScale;
	float y = (row)*spriteWH * tileScale;
	float spriteSizeY = scaleV2f.y * textureSize.y;
	float cntrFactorY = ((spriteWH * tileScale) - spriteSizeY);	
	float cntrFactorX = cntrFactorY * 0.5f;						

	setPosition(x + cntrFactorX, y + cntrFactorY);
	velocity->setVelocityDirection(0.f, 0.f);
}

bool Player::intersects(Entity& other)
{
	if (!getColliderComponent()) return false;
	std::shared_ptr<ColliderComponent> otherCollider = std::dynamic_pointer_cast<ColliderComponent>(other.getComponent(ComponentID::COLLIDER));
	return getColliderComponent()->intersects(otherCollider->getBoundingBox());
}

void Player::collectPotion()
{
	potionCollected.notify(*this, EventType::COLLECT_POTION);
}

void Player::shoutTrigger()
{
	shoutTriggered.notify(*this, EventType::SHOUT);
}

void Player::handlePotionCollision(std::shared_ptr<Entity> _entity)
{
	std::shared_ptr<Potion> potion = std::dynamic_pointer_cast<Potion>(_entity);
	int	healthRestore = potion->getHealth();
	getHealthComp()->changeHealth(healthRestore);
	_entity->markDeleted();
	collectPotion();
	ServiceLocator::getAudioManager()->playSound("CollectItemAudio.wav");
	std::cout << "Collide with potion (health restored: " << healthRestore << ", player health: " << getHealthComp()->getHealth() << ")" << std::endl;
}

void Player::handleLogCollision(std::shared_ptr<Entity> _entity)
{
	if (state->isAttacking() && getGraphicsComponent()->getSpriteSheet()->getCurrentAnim()->isInAction()) // check this
	{
		std::shared_ptr<Log> log = std::dynamic_pointer_cast<Log>(_entity);
		state->addWood(log->getWood());
		_entity->markDeleted();
	}
}