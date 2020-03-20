#ifndef BASE_ENTITY_HPP
#define BASE_ENTITY_HPP

#include "AppEngine.hpp"

#include <SFML/Graphics.hpp>

#include <string>
#include <map>

// this is bad somebody fix

enum class EntityType
{
	BaseEntity,
	ComponentEntity,
	Player,
	Object,
	InteractableObject,
	House,
};

class BaseEntity : public sf::Drawable
{
public:
	BaseEntity(const int entityID, EntityType type, AppEngine* app = nullptr);
	~BaseEntity();

	const int entityID;

	AppEngine* app;

	float maxInteractDistance = 25.0f;

	bool isMoving;
	bool isMovable;

	const EntityType type = EntityType::BaseEntity;

	sf::Vector2f movePos;

	sf::Sprite sprite;
	sf::Texture texture;

	virtual void moveTo(const sf::Vector2f &dest);

	virtual void setPosition(const sf::Vector2f& pos);
	virtual sf::Vector2f getPosition() const;

	// returns: false if the interaction failed
	//			true if the interaction succeeded
	virtual bool onInteract(BaseEntity* entity) {}

	virtual void HandleEvents(const sf::Event& event, float delta);
	virtual void Update(); // if moveTo is overriden this should be too

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

class ComponentEntity;

class EntityComponent : public sf::Drawable
{
public:
	ComponentEntity* owner = nullptr;

	virtual void HandleEvents(const sf::Event& event, float delta) {}
	virtual void Update() {}
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const {}
};

class ComponentEntity : public BaseEntity
{
public:
	ComponentEntity(int entityID, AppEngine* app = nullptr) : BaseEntity(entityID, EntityType::ComponentEntity, app) {}
	~ComponentEntity() {}

	EntityComponent* addComponent(EntityComponent* component);
	EntityComponent* removeComponent(EntityComponent* component);

	// TODO: this doesn't work
	EntityComponent* hasComponent(EntityComponent* component);
	// TODO: this doesn't work
	EntityComponent* getComponent(EntityComponent* component);

	void HandleEvents(const sf::Event& event, float delta) override;
	void Update() override;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
	std::vector<EntityComponent*> components;
};

#endif // !BASE_ENTITY_HPP

