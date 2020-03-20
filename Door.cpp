#include "Door.hpp"

#include <iostream>

Door::Door(int entityID) : BaseEntity(entityID, EntityType::InteractableObject)
{
	shape.setSize(sf::Vector2f(25, 45));
	shape.setFillColor(sf::Color::Black);
}

void Door::setPosition(const sf::Vector2f& newPosition)
{
	shape.setPosition(newPosition);
}

sf::Vector2f Door::getPosition() const
{
	return shape.getPosition();
}

bool Door::onInteract(BaseEntity* interactingEntity)
{
	isOpen = !isOpen;

	if (isOpen)
		shape.setSize(sf::Vector2f(5, 45));
	else
		shape.setSize(sf::Vector2f(25, 45));

	std::cout << "door is " << (isOpen ? "open" : "closed") << std::endl;
}

void Door::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(shape, states);
}

