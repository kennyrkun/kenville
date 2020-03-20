#include "PlayerCharacter.hpp"

#include <iostream>

void PlayerController::HandleEvents(const sf::Event& event, float delta)
{
	if (owner->app->window.hasFocus())
	{
		int moveX = 0, moveY = 0;
		int moveAmount = baseMoveSpeed * delta;

		// keyboard based camera movement
		if (sf::Keyboard::isKeyPressed(owner->app->keys.movePlayerUp))
			moveY -= moveAmount;
		if (sf::Keyboard::isKeyPressed(owner->app->keys.movePlayerDown))
			moveY += moveAmount;
		if (sf::Keyboard::isKeyPressed(owner->app->keys.movePlayerLeft))
			moveX -= moveAmount;
		if (sf::Keyboard::isKeyPressed(owner->app->keys.movePlayerRight))
			moveX += moveAmount;

		sf::Vector2f newPosition = owner->getPosition() + sf::Vector2f(moveX, moveY);

		newPosition.x = std::clamp(newPosition.x, -400.f, 400.f);
		newPosition.y = std::clamp(newPosition.y, -300.f, 300.f);

		owner->setPosition(newPosition);
	}
}

PlayerCharacter::PlayerCharacter(int entityID, AppEngine* app) : ComponentEntity(entityID, app)
{
	shape.setSize(sf::Vector2f(20, 40));
	shape.setFillColor(sf::Color::White);

	shape.setOrigin(sf::Vector2f(shape.getSize().x / 2, shape.getSize().y / 2));

	addComponent(new PlayerController);
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

