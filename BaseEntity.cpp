#include "BaseEntity.hpp"

#include <iostream>

BaseEntity::BaseEntity(const int entityID, EntityType type, AppEngine* app) : entityID(entityID), type(type), app(app)
{
	std::cout << "Entity base class constructed." << std::endl;
}

BaseEntity::~BaseEntity()
{
	std::cout << "Entity base class deconstructed." << std::endl;
}

void BaseEntity::moveTo(const sf::Vector2f &pos)
{
	if (isMovable)
	{
		std::cout << "Moving to X: " << pos.x << ", Y: " << pos.y << ". (" << entityID << ")" << std::endl;
		movePos = pos;
		isMoving = true;
	}
	else
	{
		std::cout << "This entity is not moveable! (" << static_cast<int>(type) << ")" << std::endl;
	}
}

void BaseEntity::HandleEvents(const sf::Event& event, float delta)
{
}

void BaseEntity::Update()
{
	// TODO: stop entities from isMoving into each other

	if (isMoving)
	{
		int sX = static_cast<int>(sprite.getPosition().x);
		int sY = static_cast<int>(sprite.getPosition().y);
		int gX = static_cast<int>(movePos.x);
		int gY = static_cast<int>(movePos.y);

		if (sX > gX)
			sprite.move(-1.f, 0);
		else if (sX < gX)
			sprite.move(1.f, 0);

		if (sY > gY)
			sprite.move(0, -1.f);
		else if (sY < gY)
			sprite.move(0, 1.f);

		if (sX == gX && sY == gY)
		{
			std::cout << "Done moving! (" << entityID << ")" << std::endl;

			isMoving = false;
		}
		else
		{
			//line.setPoints(sprite.getPosition(), moveDest.getPosition());
		}
	}
}

void BaseEntity::setPosition(const sf::Vector2f& pos)
{
	sprite.setPosition(pos);
}

sf::Vector2f BaseEntity::getPosition() const
{
	return sprite.getPosition();
}

void BaseEntity::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(sprite);
}

// EntityComponent

EntityComponent* ComponentEntity::addComponent(EntityComponent* component)
{
	component->owner = this;
	components.push_back(component);
}

EntityComponent* ComponentEntity::removeComponent(EntityComponent* component)
{
	component->owner = nullptr;
	components.erase(std::remove(components.begin(), components.end(), component), components.end());
	return component;
}

EntityComponent* ComponentEntity::hasComponent(EntityComponent* component)
{
	auto it = std::find(components.begin(), components.end(), component);
	if (it == components.end())
		return nullptr;
	else
		return components[std::distance(components.begin(), it)];
}

EntityComponent* ComponentEntity::getComponent(EntityComponent* component)
{
	return hasComponent(component);
}

void ComponentEntity::HandleEvents(const sf::Event& event, float delta)
{
	for (auto component : components)
		component->HandleEvents(event, delta);
}

void ComponentEntity::Update()
{
	for (auto component : components)
		component->Update();
}

void ComponentEntity::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (auto component : components)
		target.draw(*component);
}
