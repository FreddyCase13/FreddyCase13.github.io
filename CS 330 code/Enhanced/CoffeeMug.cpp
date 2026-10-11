/*
 * File:     CoffeeMug.cpp
 * Author:   Freddy Case
 * Version:  1.0
 * Date:     September 2026 (CS 499 enhancement)
 * Original: CS 330 Computational Graphics and Visualization, February, 2026
 *
 * Purpose:  Draws the coffee mug using cylinder meshes for the body 
			 and a torus for the handle.
 */
# include "CoffeeMug.h"
# include "SceneManager.h"
# include <glm/glm.hpp>

/******************************************************************/
// OUTER MUG BODY CONSTANTS
/******************************************************************/
const glm::vec3 MUG_OUTER_BODY_SCALE(0.95f, 1.8f, 0.95f);
const glm::vec3 MUG_POSITION(0.0f, 0.0f, -0.8f);

/******************************************************************/
// INNER MUG BODY CONSTANTS
/******************************************************************/
const glm::vec3 MUG_INNER_BODY_SCALE(0.8f, 1.8005f, 0.8f);
const glm::vec3 MUG_INNER_POSITION(0.0f, 0.0f, -0.8f);

/******************************************************************/
// MUG HANDLE CONSTANTS
/******************************************************************/

const glm::vec3 MUG_HANDLE_SCALE(0.6f, 0.6f, 0.25f);
const glm::vec3 MUG_HANDLE_POSITION(0.7f, 0.8f, -0.1f);
const float MUG_HANDLE_ROTATION_Y = -20.0f;

/******************************************************************/
// NO ROTATION CONSTANTS
/******************************************************************/

const float NO_ROTATION_X = 0.0f;
const float NO_ROTATION_Y = 0.0f;
const float NO_ROTATION_Z = 0.0f;

CoffeeMug::CoffeeMug() {}
CoffeeMug::~CoffeeMug() {}

void CoffeeMug::Draw(SceneManager* scene)
{
	// Temporary variables for scale and position
	glm::vec3 scaleXYZ;
	glm::vec3 positionXYZ;
	/******************************************************************/
	// OUTER MUG BODY
	// This cylinder represents the main outer body of the mug.
	/******************************************************************/
	// Set transformations for the outer mug body
	scene->SetTransformations(MUG_OUTER_BODY_SCALE, NO_ROTATION_X, NO_ROTATION_Y, NO_ROTATION_Z, MUG_POSITION);

	// White color
	scene->SetShaderColor(1, 1, 1, 1);

	// UV scale tiling of the texture
	scene->SetTextureUVScale(2.0f, 1.0f);

	// Uses the stainless texture
	scene->SetShaderTexture("mug_texture");

	//// set shader material to ceramic
	scene->SetShaderMaterial("ceramic");

	// Draw the outer mug body
	scene->m_basicMeshes->DrawCylinderMesh();

	/******************************************************************/
	// INNER MUG BODY
	// This cylinder represents the inner body of the mug.
	// Gives the illusion of the hollow center of a mug
	// slightly taller and narrower than the outer mug body
	/******************************************************************/
	// set the transformations for the inner mug body
	scene->SetTransformations(MUG_INNER_BODY_SCALE, NO_ROTATION_X, NO_ROTATION_Y, NO_ROTATION_Z, MUG_POSITION);

	// Black color
	scene->SetShaderColor(0, 0, 0, 1);

	// Draw the inner mug body
	scene->m_basicMeshes->DrawCylinderMesh();

	/******************************************************************/
	// MUG HANDLE
	// The handle is created using a torus
	// The handle is rotated along the y axis to align to image
	// The handle is oriented on the side of the mug.
	// The handle has half of the shape exposed to represent the handle
	/******************************************************************/
	// set the transformations for the mug handle
	scene->SetTransformations(MUG_HANDLE_SCALE, NO_ROTATION_X, MUG_HANDLE_ROTATION_Y, NO_ROTATION_Z, MUG_HANDLE_POSITION);

	// White color
	scene->SetShaderColor(1, 1, 1, 1);

	// UV scale tiling of the texture
	scene->SetTextureUVScale(1.0f, 1.0f);

	// Uses the seamless gold texture
	scene->SetShaderTexture("mug_texture");

	// // set shader material to ceramic
	scene->SetShaderMaterial("ceramic");

	// Draw the mug handle
	scene->m_basicMeshes->DrawTorusMesh();

	// Reset UV scale
	scene->SetTextureUVScale(1.0f, 1.0f);
}
