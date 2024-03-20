#include "SFML/Graphics.hpp"

#pragma once

class AObject{
public:
	virtual void OnEnable() = 0;
	virtual void Update(float deltaTime) = 0;
	virtual void OnDisable() = 0;
};

