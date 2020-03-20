#ifndef ENTITY_MANAGER_HPP
#define ENTITY_MANAGER_HPP

#include "BaseEntity.hpp"
//#include "InteractableObject.hpp"
//#include "LivingEntity.hpp"

#include <vector>

class EntityManager
{
public:
	EntityManager();
	~EntityManager();

	std::vector<BaseEntity*> entities;

	void add(BaseEntity *entity);
	void remove(BaseEntity *entity);

	unsigned long long int physicalMaxEnts = std::numeric_limits<unsigned long long int>::max();
	unsigned long long int count = 0;
};

#endif // ENTITY_MANAGER_HPP
