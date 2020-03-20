#ifndef OBJECT_HPP
#define OBJECT_HPP

#include "BaseEntity.hpp"

// A simple decorative entity.

class Object : public BaseEntity
{
public:
	Object(const std::string& texturePath, const int entityID, EntityType entityType = EntityType::Object);
	~Object();
};

#endif // !OBJECT_HPP

