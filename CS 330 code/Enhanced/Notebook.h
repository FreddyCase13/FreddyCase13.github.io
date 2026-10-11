/*
 * File:     Notebook.h
 * Author:   Freddy Case
 * Version:  2.0
 * Date:     September 2026 (CS 499 enhancement)
 * Original: CS 330 Computational Graphics and Visualization, February, 2026
 *
 * Purpose:  Declares the notebook object.
 *
 * Changes:  Now inherits from SceneObject and overrides Draw().
 */
#pragma once

#include <glm/glm.hpp>
#include "SceneObject.h"

// Forward declaration of SceneManager
class SceneManager;

class Notebook : public SceneObject
{
public:
	// Constructor
	Notebook();
	// Destructor
	~Notebook();

	// Draw the Notebook in the scene
	void Draw(SceneManager* scene) override;
};