#pragma once

#include <glm/glm.hpp>

// Forward declaration of SceneManager
class SceneManager;

class Laptop
{
public:
	// Constructor
	Laptop();
	// Destructor
	~Laptop();

	// Draw the Laptop in the scene
	void Draw(SceneManager* scene);
};
