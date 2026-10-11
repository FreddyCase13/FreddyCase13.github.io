/*
 * File:     MousePad.h
 * Author:   Freddy Case
 * Version:  1.0
 * Date:     September 2026 (CS 499 enhancement)
 * Original: CS 330 Computational Graphics and Visualization, September, 2026
 *
 * Purpose:  Declares the mouse pad object.
 * 
 * New File: Added as a 7th object to show that a new object can be added easily
 *			 without any changes to RenderScene.
 */
#pragma once

#include <glm/glm.hpp>
#include "SceneObject.h"

// Forward declaration of SceneManager
class SceneManager;

class MousePad : public SceneObject
{
public:
	// Constructor
	MousePad();
	// Destructor
	~MousePad();

	// Draw the mouse pad in the scene
	void Draw(SceneManager* scene) override;
};