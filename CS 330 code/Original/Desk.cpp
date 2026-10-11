# include "Desk.h"
# include "SceneManager.h"
# include <glm/glm.hpp>

/******************************************************************/
// DESK CONSTANTS
/******************************************************************/
const glm::vec3 DESK_BODY_SCALE(10.0f, 1.0f, 5.0f);
const glm::vec3 DESK_POSITION(0.0f, 0.0f, 0.0f);

/******************************************************************/
// NO ROTATION CONSTANTS
/******************************************************************/

const float NO_ROTATION_X = 0.0f;
const float NO_ROTATION_Y = 0.0f;
const float NO_ROTATION_Z = 0.0f;

Desk::Desk() {}
Desk::~Desk() {}

void Desk::Draw(SceneManager* scene)
{
	// Temporary variables for scale and position
	glm::vec3 scaleXYZ;
	glm::vec3 positionXYZ;

	/******************************************************************/
	// DESK BODY
	// This plane represents the desk.
	/******************************************************************/
	// Set transformations for the outer mug body.
	scene->SetTransformations(DESK_BODY_SCALE, NO_ROTATION_X, NO_ROTATION_Y, NO_ROTATION_Z, DESK_POSITION);

	// White color
	scene->SetShaderColor(1, 1, 1, 1);

	// UV scale tiling of the texture
	scene->SetTextureUVScale(1.0f, 1.0f);

	// Wood texture
	scene->SetShaderTexture("wood_table_texture");

	// // set shader material to wood
	scene->SetShaderMaterial("wood");

	// Draw the outer mug body
	scene->m_basicMeshes->DrawPlaneMesh();
}