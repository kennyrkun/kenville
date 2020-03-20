#ifndef DOOR_HPP
#define DOOR_HPP

#include "BaseEntity.hpp"

class Door : public BaseEntity
{
public:
	Door(int entityID);

	void setPosition(const sf::Vector2f& newPosition) override;
	sf::Vector2f getPosition() const override;

	bool onInteract(BaseEntity* interactingEntity) override;

	bool isOpen = false;

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
	sf::RectangleShape shape;
};

#endif // !DOOR_HPP

