#include "PlayerCharacter.hpp"

PlayerCharacter::PlayerCharacter()
{
	shape.setSize(sf::Vector2f(20, 40));
	shape.setFillColor(sf::Color::White);

	shape.setOrigin(sf::Vector2f(shape.getSize().x / 2, shape.getSize().y / 2));
}

void PlayerCharacter::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(shape);
}

void PlayerCharacter::setPosition(const sf::Vector2f& newPosition)
{
	shape.setPosition(newPosition);
}

sf::Vector2f PlayerCharacter::getPosition() const
{
	return shape.getPosition();
}

void PlayerCharacter::move(const sf::Vector2f& positionOffset)
{
	shape.move(positionOffset);
}

