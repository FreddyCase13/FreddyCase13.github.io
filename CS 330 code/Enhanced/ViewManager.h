/*
 * File:     ViewManager.h
 * Author:   Brian Battersby and Freddy Case
 * Version:  2.0
 * Date:     September 2026 (CS 499 enhancement)
 * Original: CS 330 Computational Graphics and Visualization, November 1st, 2023
 *
 * Purpose:  Declares the class that manages the camera, window, and projection.
 */

#pragma once

#include "ShaderManager.h"
#include "camera.h"

// GLFW library
#include "GLFW/glfw3.h" 

class ViewManager
{
public:
	// constructor
	ViewManager(
		ShaderManager* pShaderManager);
	// destructor
	~ViewManager();

	// mouse position callback for mouse interaction with the 3D scene
	static void Mouse_Position_Callback(GLFWwindow* window, double xMousePos, double yMousePos);

	// callback for mouse scroll wheel to adjust speed of camera movement
	static void Mouse_Scroll_Callback(GLFWwindow* window, double xOffset, double yOffset);

private:
	// pointer to shader manager object
	ShaderManager* m_pShaderManager;
	// active OpenGL display window
	GLFWwindow* m_pWindow;

	// process keyboard events for interaction with the 3D scene
	void ProcessKeyboardEvents();

public:
	// create the initial OpenGL display window
	GLFWwindow* CreateDisplayWindow(const char* windowTitle);
	
	// prepare the conversion from 3D object display to 2D scene display
	void PrepareSceneView();
};