# include "Mouse.h"
# include "SceneManager.h"
# include <glm/glm.hpp>

/******************************************************************/
// MOUSE BODY CONSTANTS
/******************************************************************/
const glm::vec3 MOUSE_BODY_SCALE(0.7f, 0.28f, 0.9f);
const glm::vec3 MOUSE_BODY_POSITION(7.95f, 0.16f, 2.0f);

/******************************************************************/
// SCROLL WHEEL CONSTANTS
/******************************************************************/
const glm::vec3 MOUSE_WHEEL_SCALE(0.14f, 0.14f, 0.30f);
const glm::vec3 MOUSE_WHEEL_POSITION(7.9f, 0.2f, 1.5f);
const float MOUSE_WHEEL_ROTATION_X = 90.0f;

/******************************************************************/
// MOUSE ROTATION (YAW)
/******************************************************************/
const float MOUSE_ROTATION_Y = 22.0f;

/******************************************************************/
// NO ROTATION CONSTANTS
/******************************************************************/

const float NO_ROTATION_X = 0.0f;
const float NO_ROTATION_Y = 0.0f;
const float NO_ROTATION_Z = 0.0f;

Mouse::Mouse() {}
Mouse::~Mouse() {}

void Mouse::Draw(SceneManager* scene)
{
	// Temporary variables for scale and position
	glm::vec3 scaleXYZ;
	glm::vec3 positionXYZ;

	/******************************************************************/
	// MOUSE BODY
	/******************************************************************/
	// Set transformations for the mouse body.
	scene->SetTransformations(MOUSE_BODY_SCALE, NO_ROTATION_X, MOUSE_ROTATION_Y, NO_ROTATION_Z, MOUSE_BODY_POSITION);

	// set shader color to white
	scene->SetShaderColor(1, 1, 1, 1);

	// Draw the mouse body using the sphere mesh.
	scene->m_basicMeshes->DrawSphereMesh();

	// UV scale tiling of the texture
	scene->SetTextureUVScale(1.0f, 1.0f);

	// Uses the seamless gold texture
	scene->SetShaderTexture("plastic_texture");

	// Set shader material to plastic shader
	scene->SetShaderMaterial("plastic");

	/******************************************************************/
	// SCROLL WHEEL
	/******************************************************************/
	// Set transformations for the outer mug body.
	scene->SetTransformations(MOUSE_WHEEL_SCALE, MOUSE_WHEEL_ROTATION_X, MOUSE_ROTATION_Y, NO_ROTATION_Z, MOUSE_WHEEL_POSITION);

	// White color
	scene->SetShaderColor(1, 1, 1, 1);

	// UV scale tiling of the texture
	scene->SetTextureUVScale(1.0f, 1.0f);

	// Uses the seamless gold texture
	scene->SetShaderTexture("black_plastic_texture");

	// // Set shader material to rubber shader
	scene->SetShaderMaterial("rubber");

	// Draw the outer mug body
	scene->m_basicMeshes->DrawCylinderMesh();
}