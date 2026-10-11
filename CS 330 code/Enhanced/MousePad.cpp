/*
 * File:     MousePad.cpp
 * Author:   Freddy Case
 * Version:  1.0
 * Date:     September 2026 (CS 499 enhancement)
 * New File: Added as a 7th object to show that a new object can be added easily
 *			 without any changes to RenderScene.
 * 
 * Purpose:  Draws the mouse pad under the mouse using a box mesh and a solid color.
 */
# include "MousePad.h"
# include "SceneManager.h"
# include <glm/glm.hpp>

/******************************************************************/
// MOUSEPAD BODY CONSTANTS
/******************************************************************/
const glm::vec3 MOUSEPAD_BODY_SCALE(2.0f, 0.03f, 2.5f);
const glm::vec3 MOUSEPAD_BODY_POSITION(7.95f, 0.02f, 2.0f);

/******************************************************************/
// NO ROTATION CONSTANTS
/******************************************************************/

const float NO_ROTATION_X = 0.0f;
const float NO_ROTATION_Y = 0.0f;
const float NO_ROTATION_Z = 0.0f;

MousePad::MousePad() {}
MousePad::~MousePad() {}

void MousePad::Draw(SceneManager* scene)
{

	/******************************************************************/
	// MOUSEPAD BODY
	/******************************************************************/
	// Set transformations for the mouse pad body.
	scene->SetTransformations(MOUSEPAD_BODY_SCALE, NO_ROTATION_X, NO_ROTATION_Y, NO_ROTATION_Z, MOUSEPAD_BODY_POSITION);

	// set shader color to white
	scene->SetShaderColor(1, 1, 1, 1);

	// Set shader material to rubber shader
	scene->SetShaderMaterial("rubber");

	// Draw the mouse pad body using the box mesh.
	scene->m_basicMeshes->DrawBoxMesh();

}
