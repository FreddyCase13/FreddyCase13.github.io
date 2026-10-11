#pragma once

#include <glm/glm.hpp>

// Forward declaration of SceneManager
class SceneManager;

class Mouse
{
public:
	// Constructor
	Mouse();
	// Destructor
	~Mouse();

	// Draw the Mouse in the scene
	void Draw(SceneManager* scene);
};
