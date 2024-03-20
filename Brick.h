#include "GameObject.h"
#include "ADrawable.h"
#include "ACollidable.h"

#pragma once
class Brick:public GameObject,public ADrawable,public ACollidable{

public:
	Brick(const sf::RectangleShape* shape, const sf::Color color, const sf::Vector2f location);

	// Inherited via ACollider
	sf::FloatRect GetBounds() override;

	// Inherited via ADrawable
	void Draw() override;

protected:
	std::shared_ptr<sf::RectangleShape> m_RectangleShape;
};

