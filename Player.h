#include "GameObject.h"
#include "ACollidable.h"
#include "ADrawable.h"

#pragma once
class Player:public GameObject,public ADrawable, public ACollidable {

public:
	Player(const sf::RectangleShape* shape, const sf::Color color, const sf::Vector2f startLocation);

	// Inherited via GameObject
	virtual void Update(float deltaTime) override;

	// Inherited via ACollider
	sf::FloatRect GetBounds() override;

	// Inherited via ADrawable
	void Draw() override;

protected:
	std::shared_ptr<sf::RectangleShape> m_RectangleShape;
	float m_PlayerHorizontalVelocity;
	float m_PlayerSpeed = 400.0f;



};

