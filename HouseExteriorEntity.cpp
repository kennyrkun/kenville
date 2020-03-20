#include "HouseExteriorEntity.hpp"

#include <iostream>

HouseExteriorEntity::HouseExteriorEntity(const std::string& texturePath, const int id, EntityType entityType) : BaseEntity(id, entityType)
{
	std::cout << "created HouseExteriorEntity" << std::endl;

	texture.loadFromFile("./kenvillee/resources/textures/" + texturePath);
	sprite.setTexture(texture, true);
	sprite.setScale(sf::Vector2f(.25f, .25f));
}

HouseExteriorEntity::~HouseExteriorEntity()
{
	std::cout << "destroyed HouseExteriorEntity" << std::endl;
}

bool HouseExteriorEntity::onInteract(BaseEntity* entity)
{
	std::cout << "user should enter the house" << std::endl;
}

