#pragma once

#ifndef _GRAPHICSCLASS_H_
#define _GRAPHICSCLASS_H_

#include "D3dclass.h"
#include "cameraclass.h"
#include "modelclass.h"
#include "colorshaderclass.h"


//globals
const bool FULL_SCREEN = true;
const bool VSYNC_ENABLED = true;
const float SCREEN_DEPTH = 1000.0f;
const float SCREEN_NEAR = 0.1f;

/// <summary>
/// Base class for handling all graphic componets of DirectX
/// </summary>
class GraphicsClass
{
public:
	GraphicsClass();
	GraphicsClass(const GraphicsClass&);
	~GraphicsClass();

	//HWND is window object
    
	/// <summary>
	/// Initializes new Graphics class with all needed components
	/// </summary>
	/// <param name="width">Window width</param>
	/// <param name="height">Window height</param>
	/// <param name="window">window object</param>
	/// <returns>return true if everything went ok</returns>
	bool Initialize(int width, int height, HWND window);
	/// <summary>
	/// Shutdowns graphics class objects and all other componets related to it
	/// </summary>
	void Shutdown();
	/// <summary>
	/// Basic frame, that renders the graphics
	/// </summary>
	/// <returns>returns true if frame was rendered properly</returns>
	bool Frame();

private:
	bool Render();

	D3DClass* m_D3D;
	CameraClass* m_Camera;
	ModelClass* m_Model;
	ColorShaderClass* m_ColorShader;

};

#endif

