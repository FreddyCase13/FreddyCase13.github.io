/*
 * File:     Monitor.cpp
 * Author:   Freddy Case
 * Version:  1.0
 * Date:     September 2026 (CS 499 enhancement)
 * Original: CS 330 Computational Graphics and Visualization, February, 2026
 *
 * Purpose:  Draws the monitor bezel, screen, and stand using box meshes.
 */
# include "Monitor.h"
# include "SceneManager.h"
# include <glm/glm.hpp>

/******************************************************************/
// MONITOR MAIN BODY (BEZEL) CONSTANTS
/******************************************************************/
const glm::vec3 MONITOR_BEZEL_SCALE(12.5f, 6.5f, 0.25f);
const glm::vec3 MONITOR_BEZEL_POSITION(-7.8f, 3.7f, -2.95f);

/******************************************************************/
// MONITOR SCREEN CONSTANTS
/******************************************************************/
const glm::vec3 MONITOR_SCREEN_SCALE(12.0f, 6.0f, 0.05f);
const glm::vec3 MONITOR_SCREEN_POSITION(-7.76f, 3.7f, -2.82f);

/******************************************************************/
// MONITOR STAND CONSTANTS
/******************************************************************/
const glm::vec3 MONITOR_STAND_SCALE(0.65f, 2.2f, 0.35f);
const glm::vec3 MONITOR_STAND_POSITION(-7.8f, 1.05f, -3.1f);

/******************************************************************/
// MONITOR BASE CONSTANTS
/******************************************************************/
const glm::vec3 MONITOR_BASE_SCALE(2.9f, 0.18f, 1.6f);
const glm::vec3 MONITOR_BASE_POSITION(-7.8f, 0.10f, -2.85f);

/******************************************************************/
// ROTATION CONSTANTS
/******************************************************************/
const float MONITOR_ROTATION_Y = 35.0f;

/******************************************************************/
// NO ROTATION CONSTANTS
/******************************************************************/

const float NO_ROTATION_X = 0.0f;
const float NO_ROTATION_Y = 0.0f;
const float NO_ROTATION_Z = 0.0f;

Monitor::Monitor() {}
Monitor::~Monitor() {}

void Monitor::Draw(SceneManager* scene)
{
	// Temporary variables for scale and position
	glm::vec3 scaleXYZ;
	glm::vec3 positionXYZ;

	/******************************************************************/
	// MONITOR BEZEL / BODY
	/******************************************************************/
	scene->SetTransformations(MONITOR_BEZEL_SCALE, NO_ROTATION_X, MONITOR_ROTATION_Y, NO_ROTATION_Z, MONITOR_BEZEL_POSITION);

	// White color
	scene->SetShaderColor(1, 1, 1, 1);

	// Bind the plastic texture to the shader for the bezel/body
	scene->SetShaderTexture("black_plastic_texture");

	// UV scale tiling of the texture
	scene->SetTextureUVScale(1.0f, 1.0f);

	//// Set shader material to plastic shader
	scene->SetShaderMaterial("plastic");

	// Draw bezel/body
	scene->m_basicMeshes->DrawBoxMesh();

	/******************************************************************/
	// MONITOR SCREEN
	/******************************************************************/
	scene->SetTransformations(MONITOR_SCREEN_SCALE, NO_ROTATION_X, MONITOR_ROTATION_Y, NO_ROTATION_Z, MONITOR_SCREEN_POSITION);

	// White color
	scene->SetShaderColor(1, 1, 1, 1);

	// Bind the screen texture to the shader
	scene->SetShaderTexture("screen_texture");

	// UV scale tiling of the texture
	scene->SetTextureUVScale(0.5f, 0.5f);

	// // Set shader material to screen shader
	scene->SetShaderMaterial("screen");

	// Draw screen
	scene->m_basicMeshes->DrawBoxMesh();

	/******************************************************************/
	// MONITOR STAND
	/******************************************************************/
	scene->SetTransformations(MONITOR_STAND_SCALE, NO_ROTATION_X, MONITOR_ROTATION_Y, NO_ROTATION_Z, MONITOR_STAND_POSITION);

	// White color
	scene->SetShaderColor(1, 1, 1, 1);

	// Bind the plastic texture to the shader for the stand
	scene->SetShaderTexture("black_plastic_texture");

	// UV scale tiling of the texture
	scene->SetTextureUVScale(1.0f, 1.0f);

	// // Set shader material to plastic shader
	scene->SetShaderMaterial("plastic");

	// Draw stand
	scene->m_basicMeshes->DrawBoxMesh();

	/******************************************************************/
	// MONITOR BASE
	/******************************************************************/
	scene->SetTransformations(MONITOR_BASE_SCALE, NO_ROTATION_X, MONITOR_ROTATION_Y, NO_ROTATION_Z, MONITOR_BASE_POSITION);

	// White color
	scene->SetShaderColor(1, 1, 1, 1);

	// Bind the plastic texture to the shader for the base
	scene->SetShaderTexture("black_plastic_texture");

	// UV scale tiling of the texture
	scene->SetTextureUVScale(1.0f, 1.0f);

	// // Set shader material to plastic shader
	scene->SetShaderMaterial("plastic");

	// Draw base
	scene->m_basicMeshes->DrawBoxMesh();
}