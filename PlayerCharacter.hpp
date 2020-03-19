#ifndef PLAYER_CHARACTER_HPP
#define PLAYER_CHARACTER_HPP

#include <SFML/Graphics.hpp>

class PlayerCharacter : public sf::Drawable
{
public:
	PlayerCharacter();

	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	void setPosition(const sf::Vector2f& newPosition);
	sf::Vector2f getPosition() const;

	void move(const sf::Vector2f& positionOffset);

private:
	sf::RectangleShape shape;
};

#endif // !PLAYER_CHARACTER_HPP
