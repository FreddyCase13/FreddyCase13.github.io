#pragma once

#include <glm/glm.hpp>

// Forward declaration of SceneManager
class SceneManager;

class Desk
{
public:
	// Constructor
	Desk();
	// Destructor
	~Desk();

	// Draw the Desk in the scene
	void Draw(SceneManager* scene);
};
