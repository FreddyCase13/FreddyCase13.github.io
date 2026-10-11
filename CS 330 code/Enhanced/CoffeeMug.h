/*
 * File:     CoffeeMug.h
 * Author:   Freddy Case
 * Version:  2.0
 * Date:     September 2026 (CS 499 enhancement)
 * Original: CS 330 Computational Graphics and Visualization, February, 2026
 *
 * Purpose:  Declares the coffee mug object.
 *
 * Changes:  Now inherits from SceneObject and overrides Draw().
 */

#pragma once

#include <glm/glm.hpp>
#include "SceneObject.h"

// Forward declaration of SceneManager
class SceneManager;

// Coffee mug object class that inherits from SceneObject.
// SceneManager can now draw a coffee mug through a SceneObject pointer.
class CoffeeMug : public SceneObject
{
public:
	// Constructor
	CoffeeMug();
	// Destructor
	~CoffeeMug();

	// Draw the coffee mug in the scene.
	//"override" means it is meant to replace SceneObjects version of Draw().
	void Draw(SceneManager* scene) override;
};
