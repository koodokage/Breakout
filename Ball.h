#include "GameObject.h"
#include "ACollidable.h"
#include "ADrawable.h"


#pragma once
class Ball :public GameObject, public ADrawable, public ACollidable {

public:
	Ball(const sf::CircleShape* shape, const sf::Color color, const sf::Vector2f startLocation,const float ballSpeed);
	// Inherited via GameObject
	void Update(float deltaTime) override;
	// Inherited via ACollider
	sf::FloatRect GetBounds() override;
	// Inherited via ADrawable
	void Draw() override;


	inline void SetVelocity(const sf::Vector2f velocity) {
		M_BallVelocity = velocity;
	}

	inline void ReflectMovement() {
		M_BallVelocity.y *= -1;
	}


protected:
	std::shared_ptr<sf::CircleShape> m_CircleShape;
	sf::Vector2f M_BallVelocity;
	float m_BallSpeed = 1600.0f;



};

