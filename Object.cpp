#include "Object.hpp"

#include <iostream>

Object::Object(const std::string& texturePath, const int id, EntityType entityType) : BaseEntity(id, entityType)
{
	std::cout << "created object" << std::endl;

	texture.loadFromFile("./kenvillee/resources/textures/" + texturePath);
	sprite.setTexture(texture, true);
}

Object::~Object()
{
	std::cout << "destroyed object" << std::endl;
}

