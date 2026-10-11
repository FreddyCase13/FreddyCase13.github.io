# include "Notebook.h"
# include "SceneManager.h"
# include <glm/glm.hpp>

/******************************************************************/
// NOTEBOOK COVER CONSTANTS
/******************************************************************/
const glm::vec3 NOTEBOOK_COVER_SCALE(3.6f, 0.10f, 2.6f);
const glm::vec3 NOTEBOOK_COVER_POSITION(-6.0f, 0.08f, 2.0f);

/******************************************************************/
// NOTEBOOK PAGES CONSTANTS
/******************************************************************/
const glm::vec3 NOTEBOOK_PAGES_SCALE(3.4f, 0.06f, 2.4f);
const glm::vec3 NOTEBOOK_PAGES_POSITION(-6.0f, 0.14f, 2.0);

/******************************************************************/
// NOTEBOOK SPIRAL RINGS CONSTANTS
/******************************************************************/

const glm::vec3 NOTEBOOK_RING_SCALE(0.08f, 0.08f, 0.08f);
const float NOTEBOOK_RING_ROTATION_X = 90.0f;

// Spiral placement settings (left edge of notebook)
const float NOTEBOOK_SPIRAL_X_OFFSET = -1.75f;     // left edge relative to cover center
const float NOTEBOOK_SPIRAL_Y_OFFSET = 0.16f;      // slightly above pages
const float NOTEBOOK_SPIRAL_Z_START = -3.0f;      // near top of notebook
const float NOTEBOOK_SPIRAL_Z_STEP = 0.15f;        // spacing between rings
const int NOTEBOOK_RING_COUNT = 9;

/******************************************************************/
// NO ROTATION CONSTANTS
/******************************************************************/

const float NO_ROTATION_X = 0.0f;
const float NO_ROTATION_Y = 0.0f;
const float NO_ROTATION_Z = 0.0f;

Notebook::Notebook() {}
Notebook::~Notebook() {}

void Notebook::Draw(SceneManager* scene)
{
	// Temporary variables for scale and position
	glm::vec3 scaleXYZ;
	glm::vec3 positionXYZ;

	/******************************************************************/
	// NOTEBOOK COVER
	/******************************************************************/
	// Set transformations for the Notebook cover
	scene->SetTransformations(NOTEBOOK_COVER_SCALE, NO_ROTATION_X, NO_ROTATION_Y, NO_ROTATION_Z, NOTEBOOK_COVER_POSITION);

	// Dark gray color for the notebook cover
	scene->SetShaderColor(0.10f, 0.10f, 0.10f, 1.0f);

	// UV scale tiling of the texture
	scene->SetTextureUVScale(1.0f, 1.0f);

	// Set the texture for the spiral rings
	scene->SetShaderTexture("notebook_cover_texture");

	// // set shader material to cover
	scene->SetShaderMaterial("cover");

	// Draw the notebook cover using the box mesh
	scene->m_basicMeshes->DrawBoxMesh();

	/******************************************************************/
	// NOTEBOOK PAGES
	/******************************************************************/
	// set the transformations for the Notebook pages
	scene->SetTransformations(NOTEBOOK_PAGES_SCALE, NO_ROTATION_X, NO_ROTATION_Y, NO_ROTATION_Z, NOTEBOOK_PAGES_POSITION);

	// Light gray color for the notebook pages
	scene->SetShaderColor(0.92f, 0.92f, 0.88f, 1.0f);

	// UV scale tiling of the texture
	scene->SetTextureUVScale(1.0f, 1.0f);

	// Set the texture for the spiral rings
	scene->SetShaderTexture("paper_texture");

	// set shader material to paper
	scene->SetShaderMaterial("paper");

	// Draw the notebook pages using the box mesh
	scene->m_basicMeshes->DrawBoxMesh();

	/******************************************************************/
	// NOTEBOOK SPIRAL RINGS
	/******************************************************************/

	// Medium gray color for the spiral rings
	scene->SetShaderColor(0.35f, 0.35f, 0.35f, 1.0f);

	for (int i = 0; i < NOTEBOOK_RING_COUNT; i++)
	{
		glm::vec3 ringPosition;

		// Offset to the left edge of the notebook cover for spiral placement
		ringPosition.x = NOTEBOOK_COVER_POSITION.x - 1.7f;

		// Offset upwards to position the rings above the pages
		ringPosition.y = NOTEBOOK_COVER_POSITION.y + 0.11f;

		// Offset in the z-axis to create a spiral effect, with each ring slightly further down the notebook
		ringPosition.z = NOTEBOOK_COVER_POSITION.z + 1.15f - (i * 0.28f);

		// Set transformations for the current spiral ring
		scene->SetTransformations(NOTEBOOK_RING_SCALE, NOTEBOOK_RING_ROTATION_X, NO_ROTATION_Y, NO_ROTATION_Z, ringPosition);

		// UV scale tiling of the texture
		scene->SetTextureUVScale(1.0f, 1.0f);

		// Set the texture for the spiral rings
		scene->SetShaderTexture("notebook_ring_texture");

		// set shader material to metal
		scene->SetShaderMaterial("metal");

		// Draw the current spiral ring using the cylinder mesh
		scene->m_basicMeshes->DrawCylinderMesh();
	}
}