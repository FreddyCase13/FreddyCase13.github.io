/*
 * File:     Laptop.h
 * Author:   Freddy Case
 * Version:  2.0
 * Date:     September 2026 (CS 499 enhancement)
 * Original: CS 330 Computational Graphics and Visualization, February, 2026
 *
 * Purpose:  Declares the laptop object.
 *
 * Changes:  Now inherits from SceneObject and overrides Draw().
 */

#pragma once

#include <glm/glm.hpp>
#include "SceneObject.h"

// Forward declaration of SceneManager
class SceneManager;

class Laptop : public SceneObject
{
public:
	// Constructor
	Laptop();
	// Destructor
	~Laptop();

	// Draw the Laptop in the scene
	void Draw(SceneManager* scene) override;
};
