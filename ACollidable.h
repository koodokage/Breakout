#include "SFML/Graphics.hpp"

#pragma once
class ACollidable{

public:
	virtual sf::FloatRect GetBounds() = 0;
public:
	inline bool IsCollide(ACollidable* collidable) {
		return GetBounds().intersects(collidable->GetBounds());
	}
};

