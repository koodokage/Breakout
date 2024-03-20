#include "AObject.h"

#pragma once
class GameObject:AObject{

public:
	// Inherited via Gameobject
	void OnEnable() override;
	void Update(float deltaTime) override;
	void OnDisable() override;
};

