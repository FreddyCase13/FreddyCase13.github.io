/*
 * File:     SceneObject.h
 * Author:   Freddy Case
 * Version:  1.0
 * Date:     September 2026 (CS 499 enhancement)
 * Original: CS 330 Computational Graphics and Visualization, Februaryfdr fv, 2026
 *
 * Purpose:  Abstract base class for every object drawn in the 3D scene.
 *           Defines the Draw() function that each object must override.
 *
 * Changes:  New file in project. Allows SceneManager to store every object
 *           in one list and draw them with a single loop.
 */

#pragma once
// Call forward declaration of SceneManager
// Only a pointer to SceneManager, so we don't need to include the header file here
class SceneManager;

class SceneObject
{
public:
	// virtual destructor to ensure proper cleanup of derived classes
	// Will be deleting objects through a pointer
	// Without this, the base class destructor would run.
	virtual ~SceneObject() {}

	// pure virtual function to draw the object
	// Each derived class must implement this function to draw itself
	virtual void Draw(SceneManager* scene) = 0;
};
