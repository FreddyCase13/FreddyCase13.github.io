# include "Laptop.h"
# include "SceneManager.h"
# include <glm/glm.hpp>

/******************************************************************/
// LAPTOP BASE CONSTANTS
/******************************************************************/
const glm::vec3 LAPTOP_BASE_SCALE(4.8f, 0.25f, 2.4f);
const glm::vec3 LAPTOP_BASE_POSITION(5.5f, 0.25f, -2.75f);

/******************************************************************/
// LAPTOP SCREEN BEZEL CONSTANTS
/******************************************************************/
const glm::vec3 LAPTOP_SCREEN_BEZEL_SCALE(4.8f, 2.8f, 0.15f);
const glm::vec3 LAPTOP_SCREEN_BEZEL_POSITION(5.5f, 1.6f, -4.2f);

/******************************************************************/
// LAPTOP SCREEN CONSTANTS
/******************************************************************/
const glm::vec3 LAPTOP_SCREEN_SCALE(4.6f, 2.4f, 0.05f);
const glm::vec3 LAPTOP_SCREEN_POSITION(5.5f, 1.7f, -4.13f);

/******************************************************************/
// LAPTOP KEYBOARD CONSTANTS
/******************************************************************/
const glm::vec3 LAPTOP_KEYBOARD_SCALE(4.5f, 0.08f, 1.15f);
const glm::vec3 LAPTOP_KEYBOARD_POSITION(5.5f, 0.35f, -3.0f);

/******************************************************************/
// MOUSEPAD CONSTANTS
/******************************************************************/
const glm::vec3 MOUSEPAD_SCALE(1.5f, 0.08f, 0.7f);
const glm::vec3 MOUSEPAD_POSITION(5.5f, 0.35f, -1.9f);

/******************************************************************/
// ROTATION CONSTANTS
/******************************************************************/
const float MONITOR_ROTATION_X = -15.0f;

/******************************************************************/
// NO ROTATION CONSTANTS
/******************************************************************/

const float NO_ROTATION_X = 0.0f;
const float NO_ROTATION_Y = 0.0f;
const float NO_ROTATION_Z = 0.0f;

Laptop::Laptop() {}
Laptop::~Laptop() {}

void Laptop::Draw(SceneManager* scene)
{
	// Temporary variables for scale and position
	glm::vec3 scaleXYZ;
	glm::vec3 positionXYZ;

	/******************************************************************/
	// Laptop Base
	/******************************************************************/
	scene->SetTransformations(LAPTOP_BASE_SCALE, NO_ROTATION_X, NO_ROTATION_Y, NO_ROTATION_Z, LAPTOP_BASE_POSITION);

	// White color
	scene->SetShaderColor(1, 1, 1, 1);

	// UV scale tiling of the texture
	scene->SetTextureUVScale(1.0f, 1.0f);

	// Bind the plastic texture to the shader for the laptop base
	scene->SetShaderTexture("laptop_texture");

	// set shader material to plastic
	scene->SetShaderMaterial("plastic");

	// Draw the laptop base using a box mesh
	scene->m_basicMeshes->DrawBoxMesh();

	/******************************************************************/
	// Laptop Screen Bezel
	/******************************************************************/
	scene->SetTransformations(LAPTOP_SCREEN_BEZEL_SCALE, MONITOR_ROTATION_X, NO_ROTATION_Y,NO_ROTATION_Z,LAPTOP_SCREEN_BEZEL_POSITION
	);

	// White color
	scene->SetShaderColor(1, 1, 1, 1);

	// UV scale tiling of the texture
	scene->SetTextureUVScale(0.5f, 0.5f);

	// Bind the plastic texture to the shader for the laptop base
	scene->SetShaderTexture("laptop_texture");

	// set shader material to plastic
	scene->SetShaderMaterial("plastic");

	// Draw the laptop screen using a box mesh
	scene->m_basicMeshes->DrawBoxMesh();

	/******************************************************************/
	// LAPTOP SCREEN
	/******************************************************************/
	scene->SetTransformations(LAPTOP_SCREEN_SCALE, MONITOR_ROTATION_X, NO_ROTATION_Y, NO_ROTATION_Z, LAPTOP_SCREEN_POSITION);

	// White color
	scene->SetShaderColor(1, 1, 1, 1);

	// UV scale tiling of the texture
	scene->SetTextureUVScale(1.0f, 1.0f);

	// Bind the screen texture to the shader
	scene->SetShaderTexture("screen_texture");

	// set shader material to screen
	scene->SetShaderMaterial("screen");

	// Draw screen
	scene->m_basicMeshes->DrawBoxMesh();

/******************************************************************/
// LAPTOP KEYBOARD
/******************************************************************/
	scene->SetTransformations(LAPTOP_KEYBOARD_SCALE, NO_ROTATION_X, NO_ROTATION_Y, NO_ROTATION_Z, LAPTOP_KEYBOARD_POSITION);

	// White color
	scene->SetShaderColor(1, 1, 1, 1);

	// UV scale tiling of the texture
	scene->SetTextureUVScale(1.0f, 1.0f);

	// Bind the plastic texture to the shader for the laptop keyboard
	scene->SetShaderTexture("black_plastic_texture");

	// set shader material to rubber
	scene->SetShaderMaterial("rubber");

	// draw keyboard
	scene->m_basicMeshes->DrawBoxMesh();

/******************************************************************/
// MOUSEPAD
/******************************************************************/
	scene->SetTransformations(MOUSEPAD_SCALE, NO_ROTATION_X, NO_ROTATION_Y, NO_ROTATION_Z, MOUSEPAD_POSITION);

	// White color
	scene->SetShaderColor(1, 1, 1, 1);

	// UV scale tiling of the texture
	scene->SetTextureUVScale(1.0f, 1.0f);

	// Bind the plastic texture to the shader for the laptop keyboard
	scene->SetShaderTexture("black_plastic_texture");

	// set shader material to rubber
	scene->SetShaderMaterial("rubber");

	// Draw mousepad
	scene->m_basicMeshes->DrawBoxMesh();
}