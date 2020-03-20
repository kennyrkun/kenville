#ifndef PLAYER_CHARACTER_HPP
#define PLAYER_CHARACTER_HPP

#include "BaseEntity.hpp"

class PlayerController : public EntityComponent
{
public:
	float baseMoveSpeed = 200;
	float fastMoveSpeed = 300;
	float slowMoveSpeed = 100;

	virtual void HandleEvents(const sf::Event& event, float delta);
};

class PlayerCharacter : public ComponentEntity
{
public:
	PlayerCharacter(int entityID, AppEngine* app);

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	void setPosition(const sf::Vector2f& newPosition) override;
	sf::Vector2f getPosition() const override;

	void move(const sf::Vector2f& positionOffset);

private:
	sf::RectangleShape shape;
};

#endif // !PLAYER_CHARACTER_HPP
