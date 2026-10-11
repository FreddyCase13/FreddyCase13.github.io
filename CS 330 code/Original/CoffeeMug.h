#pragma once

#include <glm/glm.hpp>

// Forward declaration of SceneManager
class SceneManager;

class CoffeeMug
{
public:
	// Constructor
	CoffeeMug();
	// Destructor
	~CoffeeMug();

	// Draw the coffee mug in the scene
	void Draw(SceneManager* scene);
};
