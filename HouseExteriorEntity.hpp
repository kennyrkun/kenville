#ifndef HOUSE_EXTERIOR_ENTITY_HPP
#define HOUSE_EXTERIOR_ENTITY_HPP

#include "BaseEntity.hpp"

// HouseExteriorEntity

class HouseExteriorEntity : public BaseEntity
{
public:
	HouseExteriorEntity(const std::string& texturePath, const int entityID, EntityType entityType = EntityType::Object);
	~HouseExteriorEntity();

	bool onInteract(BaseEntity* entity) override;
};

#endif // !HOUSE_EXTERIOR_ENTITY_HPP

