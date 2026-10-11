#pragma once

#include <glm/glm.hpp>

// Forward declaration of SceneManager
class SceneManager;

class Notebook
{
public:
	// Constructor
	Notebook();
	// Destructor
	~Notebook();

	// Draw the Notebook in the scene
	void Draw(SceneManager* scene);
};