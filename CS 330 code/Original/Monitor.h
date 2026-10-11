#pragma once

#include <glm/glm.hpp>

// Forward declaration of SceneManager
class SceneManager;

class Monitor
{
public:
	// Constructor
	Monitor();
	// Destructor
	~Monitor();

	// Draw the Monitor in the scene
	void Draw(SceneManager* scene);
};
