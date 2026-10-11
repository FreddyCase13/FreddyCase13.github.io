/*
 * File:     SceneManager.cpp
 * Author:   Brian Battersby and Freddy Case
 * Version:  3.0
 * Date:     September 2026 (CS 499 enhancement)
 * Original: CS 330 Computational Graphics and Visualization, November 1st, 2023.
 *
 * Purpose:  Loads textures, sets up lights, and draws the scene.
 *
 * Changes:  PrepareScene now creates each object and adds it to the list. 
			 RenderScene draws everything with one loop instead of needing
			 a separate call for each object.
 */

#include "SceneManager.h"
#include "CoffeeMug.h"
#include "Desk.h"
#include "Monitor.h"
#include "Laptop.h"
#include "Mouse.h"
#include "Notebook.h"
#include "MousePad.h" // New Object class for the mouse pad

#ifndef STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#endif

#include <glm/gtx/transform.hpp>

// declaration of global variables
namespace
{
	const char* g_ModelName = "model";
	const char* g_ColorValueName = "objectColor";
	const char* g_TextureValueName = "objectTexture";
	const char* g_UseTextureName = "bUseTexture";
	const char* g_UseLightingName = "bUseLighting";
}

/***********************************************************
 *  SceneManager() Constants
 ***********************************************************/

// ------------------------------------------------------------
// Material Constants
// ------------------------------------------------------------

// Plastic
const glm::vec3 PLASTIC_AMBIENT_COLOR(0.15f, 0.15f, 0.15f);
const float PLASTIC_AMBIENT_STRENGTH = 0.25f;
const glm::vec3 PLASTIC_DIFFUSE_COLOR(0.25f, 0.25f, 0.25f);
const glm::vec3 PLASTIC_SPECULAR_COLOR(0.25f, 0.25f, 0.25f);
const float PLASTIC_SHININESS = 18.0f;

// Metal
const glm::vec3 METAL_AMBIENT_COLOR(0.18f, 0.18f, 0.18f);
const float METAL_AMBIENT_STRENGTH = 0.22f;
const glm::vec3 METAL_DIFFUSE_COLOR(0.35f, 0.35f, 0.35f);
const glm::vec3 METAL_SPECULAR_COLOR(0.85f, 0.85f, 0.85f);
const float METAL_SHININESS = 96.0f;

// Wood
const glm::vec3 WOOD_AMBIENT_COLOR(0.10f, 0.10f, 0.10f);
const float WOOD_AMBIENT_STRENGTH = 0.30f;
const glm::vec3 WOOD_DIFFUSE_COLOR(0.30f, 0.30f, 0.30f);
const glm::vec3 WOOD_SPECULAR_COLOR(0.10f, 0.10f, 0.10f);
const float WOOD_SHININESS = 1.0f;

// Screen
const glm::vec3 SCREEN_AMBIENT_COLOR(0.30f, 0.30f, 0.30f);
const float SCREEN_AMBIENT_STRENGTH = 0.45f;
const glm::vec3 SCREEN_DIFFUSE_COLOR(0.25f, 0.25f, 0.25f);
const glm::vec3 SCREEN_SPECULAR_COLOR(0.67f, 0.67f, 0.67f);
const float SCREEN_SHININESS = 140.0f;

// Paper
const glm::vec3 PAPER_AMBIENT_COLOR(0.20f, 0.20f, 0.20f);
const float PAPER_AMBIENT_STRENGTH = 0.18f;
const glm::vec3 PAPER_DIFFUSE_COLOR(0.70f, 0.70f, 0.70f);
const glm::vec3 PAPER_SPECULAR_COLOR(0.05f, 0.05f, 0.05f);
const float PAPER_SHININESS = 6.0f;

// Cover
const glm::vec3 COVER_AMBIENT_COLOR(0.18f, 0.18f, 0.18f);
const float COVER_AMBIENT_STRENGTH = 0.22f;
const glm::vec3 COVER_DIFFUSE_COLOR(0.40f, 0.40f, 0.40f);
const glm::vec3 COVER_SPECULAR_COLOR(0.18f, 0.18f, 0.18f);
const float COVER_SHININESS = 14.0f;

// Rubber
const glm::vec3 RUBBER_AMBIENT_COLOR(0.12f, 0.12f, 0.12f);
const float RUBBER_AMBIENT_STRENGTH = 0.20f;
const glm::vec3 RUBBER_DIFFUSE_COLOR(0.12f, 0.12f, 0.12f);
const glm::vec3 RUBBER_SPECULAR_COLOR(0.02f, 0.02f, 0.02f);
const float RUBBER_SHININESS = 4.0f;

// Ceramic
const glm::vec3 CERAMIC_AMBIENT_COLOR(0.20f, 0.20f, 0.20f);
const float CERAMIC_AMBIENT_STRENGTH = 0.25f;
const glm::vec3 CERAMIC_DIFFUSE_COLOR(0.35f, 0.35f, 0.35f);
const glm::vec3 CERAMIC_SPECULAR_COLOR(0.72f, 0.72f, 0.72f);
const float CERAMIC_SHININESS = 90.0f;

// ------------------------------------------------------------
// Scene Lighting Constants
// ------------------------------------------------------------

const glm::vec3 LIGHT1_POSITION = glm::vec3(0.0f, 6.0f, 0.0f);
const glm::vec3 LIGHT1_AMBIENT = glm::vec3(0.08f, 0.07f, 0.07f);
const glm::vec3 LIGHT1_DIFFUSE = glm::vec3(0.77f, 0.77f, 0.77f);
const glm::vec3 LIGHT1_SPECULAR = glm::vec3(0.25f, 0.25f, 0.25f);
const float LIGHT1_FOCAL = 20.0f;
const float LIGHT1_SPEC_INT = 0.12f;

const glm::vec3 LIGHT2_POSITION = glm::vec3(10.0f, 6.0f, 4.0f);
const glm::vec3 LIGHT2_AMBIENT = glm::vec3(0.03f, 0.03f, 0.03f);
const glm::vec3 LIGHT2_DIFFUSE = glm::vec3(0.18f, 0.17f, 0.16f);
const glm::vec3 LIGHT2_SPECULAR = glm::vec3(0.04f, 0.04f, 0.04f);
const float LIGHT2_FOCAL = 24.0f;
const float LIGHT2_SPEC_INT = 0.05f;

const glm::vec3 LIGHT3_POSITION = glm::vec3(0.0f, 4.5f, -8.0f);
const glm::vec3 LIGHT3_AMBIENT = glm::vec3(0.01f, 0.01f, 0.02f);
const glm::vec3 LIGHT3_DIFFUSE = glm::vec3(0.1f, 0.12f, 0.22f);
const glm::vec3 LIGHT3_SPECULAR = glm::vec3(0.03f, 0.04f, 0.06f);
const float LIGHT3_FOCAL = 26.0f;
const float LIGHT3_SPEC_INT = 0.06f;

// ------------------------------------------------------------
// Texture File Path Constant
// ------------------------------------------------------------

const std::string TEXTURE_PATH = "project_textures/";

/***********************************************************
 *  SceneManager()
 *
 *  The constructor for the class
 ***********************************************************/
SceneManager::SceneManager(ShaderManager *pShaderManager)
{
	m_pShaderManager = pShaderManager;
	m_basicMeshes = new ShapeMeshes();
}

/***********************************************************
 *  ~SceneManager()
 *
 *  The destructor for the class
 ***********************************************************/
SceneManager::~SceneManager()
{
	m_pShaderManager = NULL;
	delete m_basicMeshes;
	m_basicMeshes = NULL;
}

/***********************************************************
 *  CreateGLTexture()
 *
 *  This method is used for loading textures from image files,
 *  configuring the texture mapping parameters in OpenGL,
 *  generating the mipmaps, and loading the read texture into
 *  the next available texture slot in memory.
 ***********************************************************/
bool SceneManager::CreateGLTexture(const char* filename, std::string tag)
{
	int width = 0;
	int height = 0;
	int colorChannels = 0;
	GLuint textureID = 0;

	// indicate to always flip images vertically when loaded
	stbi_set_flip_vertically_on_load(true);

	// try to parse the image data from the specified image file
	unsigned char* image = stbi_load(
		filename,
		&width,
		&height,
		&colorChannels,
		0);

	// if the image was successfully read from the image file
	if (image)
	{
		std::cout << "Successfully loaded image:" << filename << ", width:" << width << ", height:" << height << ", channels:" << colorChannels << std::endl;

		glGenTextures(1, &textureID);
		glBindTexture(GL_TEXTURE_2D, textureID);

		// set the texture wrapping parameters
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		// set texture filtering parameters
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		// if the loaded image is in RGB format
		if (colorChannels == 3)
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
		// if the loaded image is in RGBA format - it supports transparency
		else if (colorChannels == 4)
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
		else
		{
			std::cout << "Not implemented to handle image with " << colorChannels << " channels" << std::endl;
			return false;
		}

		// generate the texture mipmaps for mapping textures to lower resolutions
		glGenerateMipmap(GL_TEXTURE_2D);

		// free the image data from local memory
		stbi_image_free(image);
		glBindTexture(GL_TEXTURE_2D, 0); // Unbind the texture

		// register the loaded texture and associate it with the special tag string
		m_textureIDs[m_loadedTextures].ID = textureID;
		m_textureIDs[m_loadedTextures].tag = tag;
		m_loadedTextures++;

		return true;
	}

	std::cout << "Could not load image:" << filename << std::endl;

	// Error loading the image
	return false;
}

/***********************************************************
 *  BindGLTextures()
 *
 *  This method is used for binding the loaded textures to
 *  OpenGL texture memory slots.  There are up to 16 slots.
 ***********************************************************/
void SceneManager::BindGLTextures()
{
	for (int i = 0; i < m_loadedTextures; i++)
	{
		// bind textures on corresponding texture units
		glActiveTexture(GL_TEXTURE0 + i);
		glBindTexture(GL_TEXTURE_2D, m_textureIDs[i].ID);
	}
}

/***********************************************************
 *  DestroyGLTextures()
 *
 *  This method is used for freeing the memory in all the
 *  used texture memory slots.
 ***********************************************************/
void SceneManager::DestroyGLTextures()
{
	for (int i = 0; i < m_loadedTextures; i++)
	{
		glGenTextures(1, &m_textureIDs[i].ID);
	}
}

/***********************************************************
 *  FindTextureID()
 *
 *  This method is used for getting an ID for the previously
 *  loaded texture bitmap associated with the passed in tag.
 ***********************************************************/
int SceneManager::FindTextureID(std::string tag)
{
	int textureID = -1;
	int index = 0;
	bool bFound = false;

	while ((index < m_loadedTextures) && (bFound == false))
	{
		if (m_textureIDs[index].tag.compare(tag) == 0)
		{
			textureID = m_textureIDs[index].ID;
			bFound = true;
		}
		else
			index++;
	}

	return(textureID);
}

/***********************************************************
 *  FindTextureSlot()
 *
 *  This method is used for getting a slot index for the previously
 *  loaded texture bitmap associated with the passed in tag.
 ***********************************************************/
int SceneManager::FindTextureSlot(std::string tag)
{
	int textureSlot = -1;
	int index = 0;
	bool bFound = false;

	while ((index < m_loadedTextures) && (bFound == false))
	{
		if (m_textureIDs[index].tag.compare(tag) == 0)
		{
			textureSlot = index;
			bFound = true;
		}
		else
			index++;
	}

	return(textureSlot);
}

/***********************************************************
 *  FindMaterial()
 *
 *  This method is used for getting a material from the previously
 *  defined materials list that is associated with the passed in tag.
 ***********************************************************/
bool SceneManager::FindMaterial(std::string tag, OBJECT_MATERIAL& material)
{
	if (m_objectMaterials.size() == 0)
	{
		return(false);
	}

	int index = 0;
	bool bFound = false;
	while ((index < m_objectMaterials.size()) && (bFound == false))
	{
		if (m_objectMaterials[index].tag.compare(tag) == 0)
		{
			bFound = true;
			material.ambientColor = m_objectMaterials[index].ambientColor;
			material.ambientStrength = m_objectMaterials[index].ambientStrength;
			material.diffuseColor = m_objectMaterials[index].diffuseColor;
			material.specularColor = m_objectMaterials[index].specularColor;
			material.shininess = m_objectMaterials[index].shininess;
		}
		else
		{
			index++;
		}
	}

	return(true);
}

/***********************************************************
 *  SetTransformations()
 *
 *  This method is used for setting the transform buffer
 *  using the passed in transformation values.
 ***********************************************************/
void SceneManager::SetTransformations(
	glm::vec3 scaleXYZ,
	float XrotationDegrees,
	float YrotationDegrees,
	float ZrotationDegrees,
	glm::vec3 positionXYZ)
{
	// variables for this method
	glm::mat4 modelView;
	glm::mat4 scale;
	glm::mat4 rotationX;
	glm::mat4 rotationY;
	glm::mat4 rotationZ;
	glm::mat4 translation;

	// set the scale value in the transform buffer
	scale = glm::scale(scaleXYZ);
	// set the rotation values in the transform buffer
	rotationX = glm::rotate(glm::radians(XrotationDegrees), glm::vec3(1.0f, 0.0f, 0.0f));
	rotationY = glm::rotate(glm::radians(YrotationDegrees), glm::vec3(0.0f, 1.0f, 0.0f));
	rotationZ = glm::rotate(glm::radians(ZrotationDegrees), glm::vec3(0.0f, 0.0f, 1.0f));
	// set the translation value in the transform buffer
	translation = glm::translate(positionXYZ);

	modelView = translation * rotationX * rotationY * rotationZ * scale;

	if (NULL != m_pShaderManager)
	{
		m_pShaderManager->setMat4Value(g_ModelName, modelView);
	}
}

/***********************************************************
 *  SetShaderColor()
 *
 *  This method is used for setting the passed in color
 *  into the shader for the next draw command
 ***********************************************************/
void SceneManager::SetShaderColor(
	float redColorValue,
	float greenColorValue,
	float blueColorValue,
	float alphaValue)
{
	// variables for this method
	glm::vec4 currentColor;

	currentColor.r = redColorValue;
	currentColor.g = greenColorValue;
	currentColor.b = blueColorValue;
	currentColor.a = alphaValue;

	if (NULL != m_pShaderManager)
	{
		m_pShaderManager->setIntValue(g_UseTextureName, false);
		m_pShaderManager->setVec4Value(g_ColorValueName, currentColor);
	}
}

/***********************************************************
 *  SetShaderTexture()
 *
 *  This method is used for setting the texture data
 *  associated with the passed in ID into the shader.
 ***********************************************************/
void SceneManager::SetShaderTexture(
	std::string textureTag)
{
	if (NULL != m_pShaderManager)
	{
		m_pShaderManager->setIntValue(g_UseTextureName, true);

		int textureID = -1;
		textureID = FindTextureSlot(textureTag);
		m_pShaderManager->setSampler2DValue(g_TextureValueName, textureID);
	}
}

/***********************************************************
 *  SetTextureUVScale()
 *
 *  This method is used for setting the texture UV scale
 *  values into the shader.
 ***********************************************************/
void SceneManager::SetTextureUVScale(float u, float v)
{
	if (NULL != m_pShaderManager)
	{
		m_pShaderManager->setVec2Value("UVscale", glm::vec2(u, v));
	}
}

/***********************************************************
 *  SetShaderMaterial()
 *
 *  This method is used for passing the material values
 *  into the shader.
 ***********************************************************/
void SceneManager::SetShaderMaterial(
	std::string materialTag)
{
	if (m_objectMaterials.size() > 0)
	{
		OBJECT_MATERIAL material;
		bool bReturn = false;

		bReturn = FindMaterial(materialTag, material);
		if (bReturn == true)
		{
			m_pShaderManager->setVec3Value("material.ambientColor", material.ambientColor);
			m_pShaderManager->setFloatValue("material.ambientStrength", material.ambientStrength);
			m_pShaderManager->setVec3Value("material.diffuseColor", material.diffuseColor);
			m_pShaderManager->setVec3Value("material.specularColor", material.specularColor);
			m_pShaderManager->setFloatValue("material.shininess", material.shininess);
		}
	}
}

/**************************************************************/
/*** STUDENTS CAN MODIFY the code in the methods BELOW for  ***/
/*** preparing and rendering their own 3D replicated scenes.***/
/*** Please refer to the code in the OpenGL sample project  ***/
/*** for assistance.                                        ***/
/**************************************************************/

/***********************************************************
 *  DefineObjectMaterials()
 *
 *  This method is used for configuring the various material
 *  settings for all of the objects within the 3D scene.
 ***********************************************************/
void SceneManager::DefineObjectMaterials()
{
	OBJECT_MATERIAL plasticMaterial;
	plasticMaterial.ambientColor = PLASTIC_AMBIENT_COLOR;
	plasticMaterial.ambientStrength = PLASTIC_AMBIENT_STRENGTH;
	plasticMaterial.diffuseColor = PLASTIC_DIFFUSE_COLOR;
	plasticMaterial.specularColor = PLASTIC_SPECULAR_COLOR;
	plasticMaterial.shininess = PLASTIC_SHININESS;
	plasticMaterial.tag = "plastic";
	m_objectMaterials.push_back(plasticMaterial);

	OBJECT_MATERIAL metalMaterial;
	metalMaterial.ambientColor = METAL_AMBIENT_COLOR;
	metalMaterial.ambientStrength = METAL_AMBIENT_STRENGTH;
	metalMaterial.diffuseColor = METAL_DIFFUSE_COLOR;
	metalMaterial.specularColor = METAL_SPECULAR_COLOR;
	metalMaterial.shininess = METAL_SHININESS;
	metalMaterial.tag = "metal";
	m_objectMaterials.push_back(metalMaterial);

	OBJECT_MATERIAL woodMaterial;
	woodMaterial.ambientColor = WOOD_AMBIENT_COLOR;
	woodMaterial.ambientStrength = WOOD_AMBIENT_STRENGTH;
	woodMaterial.diffuseColor = WOOD_DIFFUSE_COLOR;
	woodMaterial.specularColor = WOOD_SPECULAR_COLOR;
	woodMaterial.shininess = WOOD_SHININESS;
	woodMaterial.tag = "wood";
	m_objectMaterials.push_back(woodMaterial);

	OBJECT_MATERIAL screenMaterial;
	screenMaterial.ambientColor = SCREEN_AMBIENT_COLOR;
	screenMaterial.ambientStrength = SCREEN_AMBIENT_STRENGTH;
	screenMaterial.diffuseColor = SCREEN_DIFFUSE_COLOR;
	screenMaterial.specularColor = SCREEN_SPECULAR_COLOR;
	screenMaterial.shininess = SCREEN_SHININESS;
	screenMaterial.tag = "screen";
	m_objectMaterials.push_back(screenMaterial);

	OBJECT_MATERIAL paperMaterial;
	paperMaterial.ambientColor = PAPER_AMBIENT_COLOR;
	paperMaterial.ambientStrength = PAPER_AMBIENT_STRENGTH;
	paperMaterial.diffuseColor = PAPER_DIFFUSE_COLOR;
	paperMaterial.specularColor = PAPER_SPECULAR_COLOR;
	paperMaterial.shininess = PAPER_SHININESS;
	paperMaterial.tag = "paper";
	m_objectMaterials.push_back(paperMaterial);

	OBJECT_MATERIAL coverMaterial;
	coverMaterial.ambientColor = COVER_AMBIENT_COLOR;
	coverMaterial.ambientStrength = COVER_AMBIENT_STRENGTH;
	coverMaterial.diffuseColor = COVER_DIFFUSE_COLOR;
	coverMaterial.specularColor = COVER_SPECULAR_COLOR;
	coverMaterial.shininess = COVER_SHININESS;
	coverMaterial.tag = "cover";
	m_objectMaterials.push_back(coverMaterial);

	OBJECT_MATERIAL rubberMaterial;
	rubberMaterial.ambientColor = RUBBER_AMBIENT_COLOR;
	rubberMaterial.ambientStrength = RUBBER_AMBIENT_STRENGTH;
	rubberMaterial.diffuseColor = RUBBER_DIFFUSE_COLOR;
	rubberMaterial.specularColor = RUBBER_SPECULAR_COLOR;
	rubberMaterial.shininess = RUBBER_SHININESS;
	rubberMaterial.tag = "rubber";
	m_objectMaterials.push_back(rubberMaterial);

	OBJECT_MATERIAL ceramicMaterial;
	ceramicMaterial.ambientColor = CERAMIC_AMBIENT_COLOR;
	ceramicMaterial.ambientStrength = CERAMIC_AMBIENT_STRENGTH;
	ceramicMaterial.diffuseColor = CERAMIC_DIFFUSE_COLOR;
	ceramicMaterial.specularColor = CERAMIC_SPECULAR_COLOR;
	ceramicMaterial.shininess = CERAMIC_SHININESS;
	ceramicMaterial.tag = "ceramic";
	m_objectMaterials.push_back(ceramicMaterial);
}


/***********************************************************
 *  SetupSceneLights()
 *
 *	Configures lighting for the scene
 *	Uses Phong ambient, diffuse, and specular components.
 ***********************************************************/
void SceneManager::SetupSceneLights()
{
	// set up the light sources for the 3D scene rendering with lighting calculations
	m_pShaderManager->setBoolValue(g_UseLightingName, true);

	// ------------------------------------------------------------
	// Light 1: Primary light for overall visibility
	// ------------------------------------------------------------
	m_pShaderManager->setVec3Value("lightSources[0].position", LIGHT1_POSITION);
	m_pShaderManager->setVec3Value("lightSources[0].ambientColor", LIGHT1_AMBIENT);
	m_pShaderManager->setVec3Value("lightSources[0].diffuseColor", LIGHT1_DIFFUSE);
	m_pShaderManager->setVec3Value("lightSources[0].specularColor", LIGHT1_SPECULAR);
	m_pShaderManager->setFloatValue("lightSources[0].focalStrength", LIGHT1_FOCAL);
	m_pShaderManager->setFloatValue("lightSources[0].specularIntensity", LIGHT1_SPEC_INT);

	// ------------------------------------------------------------
	// Light 2: Fill light to fill shadows and balance scene
	// ------------------------------------------------------------
	m_pShaderManager->setVec3Value("lightSources[1].position", LIGHT2_POSITION);
	m_pShaderManager->setVec3Value("lightSources[1].ambientColor", LIGHT2_AMBIENT);
	m_pShaderManager->setVec3Value("lightSources[1].diffuseColor", LIGHT2_DIFFUSE);
	m_pShaderManager->setVec3Value("lightSources[1].specularColor", LIGHT2_SPECULAR);
	m_pShaderManager->setFloatValue("lightSources[1].focalStrength", LIGHT2_FOCAL);
	m_pShaderManager->setFloatValue("lightSources[1].specularIntensity", LIGHT2_SPEC_INT);

	// ------------------------------------------------------------
	// Light 3: Cool colored rim light for separation and depth.
	//			Prevents dark objects from blending to the background.
	// ------------------------------------------------------------
	m_pShaderManager->setVec3Value("lightSources[2].position", LIGHT3_POSITION);
	m_pShaderManager->setVec3Value("lightSources[2].ambientColor", LIGHT3_AMBIENT);
	m_pShaderManager->setVec3Value("lightSources[2].diffuseColor", LIGHT3_DIFFUSE);
	m_pShaderManager->setVec3Value("lightSources[2].specularColor", LIGHT3_SPECULAR);
	m_pShaderManager->setFloatValue("lightSources[2].focalStrength", LIGHT3_FOCAL);
	m_pShaderManager->setFloatValue("lightSources[2].specularIntensity", LIGHT3_SPEC_INT);
}

/***********************************************************
 *  PrepareScene()
 *
 *  This method is used for preparing the 3D scene by loading
 *  the shapes, textures in memory to support the 3D scene 
 *  rendering
 ***********************************************************/
void SceneManager::PrepareScene()
{
	// set up the light sources for the 3D scene rendering with lighting calculations
	SetupSceneLights();

	// set up the preset material list into the 3D scene.
	DefineObjectMaterials();

	// only one instance of a particular mesh needs to be
	// loaded in memory no matter how many times it is drawn
	// in the rendered 3D scene

	m_basicMeshes->LoadPlaneMesh();
	m_basicMeshes->LoadCylinderMesh();
	m_basicMeshes->LoadTorusMesh();
	m_basicMeshes->LoadBoxMesh();
	m_basicMeshes->LoadSphereMesh();

	// load the textures used in the 3D scene
	bool res;

	// Textures for objects
    // Update the CreateGLTexture call to explicitly convert std::string to const char* using c_str()
	res = CreateGLTexture((TEXTURE_PATH + "ceramic.jpg").c_str(), "mug_texture");
	res = CreateGLTexture((TEXTURE_PATH + "table.jpg").c_str(), "wood_table_texture");
	res = CreateGLTexture((TEXTURE_PATH + "monitor_screen.jpg").c_str(), "screen_texture");
	res = CreateGLTexture((TEXTURE_PATH + "notebook_rings.jpg").c_str(), "notebook_ring_texture");
	res = CreateGLTexture((TEXTURE_PATH + "Paper.jpg").c_str(), "paper_texture");
	res = CreateGLTexture((TEXTURE_PATH + "Notebook Cover.jpg").c_str(), "notebook_cover_texture");
	res = CreateGLTexture((TEXTURE_PATH + "plastic.jpg").c_str(), "plastic_texture");
	res = CreateGLTexture((TEXTURE_PATH + "black_plastic.jpg").c_str(), "black_plastic_texture");
	res = CreateGLTexture((TEXTURE_PATH + "laptop.jpg").c_str(), "laptop_texture");


	BindGLTextures();

	// Create instances of each object and add them to the scene
	m_sceneObjects.push_back(std::make_unique<Desk>());
	m_sceneObjects.push_back(std::make_unique<CoffeeMug>());
	m_sceneObjects.push_back(std::make_unique<Monitor>());
	m_sceneObjects.push_back(std::make_unique<Laptop>());
	m_sceneObjects.push_back(std::make_unique<Mouse>());
	m_sceneObjects.push_back(std::make_unique<Notebook>());
	m_sceneObjects.push_back(std::make_unique<MousePad>()); // New Object added to scene to show modularity.
}

/***********************************************************
 *  RenderScene()
 *
 *  This method is used for rendering the 3D scene by 
 *  transforming and drawing the basic 3D shapes
 ***********************************************************/
void SceneManager::RenderScene()
{

	// Re-apply lights every frame so uniforms are correct right before drawing
	SetupSceneLights();

	// Loop through all scene objects and call their Draw method
	for (const auto& sceneObject : m_sceneObjects) {
		sceneObject->Draw(this);
	}

}