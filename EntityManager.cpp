#include "EntityManager.hpp"

#include <iostream>

EntityManager::EntityManager()
{
	std::cout << "EntityManager constructed." << std::endl;
}

EntityManager::~EntityManager()
{
	for (size_t i = 0; i < entities.size(); i++)
		delete entities[i];

//	is this needed?
//	in theory, there can be no more selected entities than entities,
//	so deleting all entities will also delete all selected entities
//	thus rendering this code uselss and crash-creaty
//	for (size_t i = 0; i < selectedEnts.size(); i++)
//		delete selectedEnts[i];

	entities.clear();

	std::cout << "EntityManager deconstructed." << std::endl;
}

void EntityManager::add(BaseEntity* ent)
{
	entities.push_back(ent);
	count++;
}

void EntityManager::remove(BaseEntity* ent)
{
	entities.erase(std::remove(entities.begin(), entities.end(), ent), entities.end());
}

