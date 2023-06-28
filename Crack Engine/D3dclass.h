#pragma once
#ifndef _D3DCLASS_H_
#define _D3DCLASS_H_

//These libraries contain all the Direct3D functionality for setting up and drawing 3D graphics in DirectX
//as well as tools to interface with the hardware on the computer to obtain information about the refresh rate of the monitor, the video card being used, and so forth.
//We use some DX10 libraries due they have not been upgraded for DX11
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3dcompiler.lib")

#include <d3d11.h>
#include <directxmath.h>

using namespace DirectX;
class D3DClass
{
public:
	D3DClass();
	D3DClass(const D3DClass&);
	~D3DClass();

	/// <summary>
	/// Does the entire setup of Direct3D for DirectX 11
	/// </summary>
	/// <param name="screenWidth"></param>
	/// <param name="screenHeight"></param>
	/// <param name="vsync"></param>
	/// <param name="hwnd"></param>
	/// <param name="fullscreen"></param>
	/// <param name="screenDepth"></param>
	/// <param name="screenNear"></param>
	/// <returns>Returns true if everything went ok</returns>
	bool Initialize(int screenWidth, int screenHeight, bool vsync, HWND hwnd, bool fullscreen,float screenDepth, float screenNear);

	/// <summary>
	/// Cleanups all pointers used in Initialize function
	/// </summary>
	void Shutdown();

	/// <summary>
	/// Initializes all buffers to be blank and ready to drawn to. Params are RGBA color to clear the buffer to
	/// </summary>
	/// <param name="red">R</param>
	/// <param name="green">G</param>
	/// <param name="blue">B</param>
	/// <param name="alpha">A</param>
	void BeginScene(float red, float green, float blue, float alpha);
	/// <summary>
	/// Tells swapchain to dispaly 3D scene once all the drawing has completed at the end of each frame
	/// </summary>
	void EndScene();

	//Helper functions

	/// <summary>
	/// Gets Direct3D device
	/// </summary>
	/// <returns>Direct3D device</returns>
	ID3D11Device* GetDevice();

	/// <summary>
	/// Gets Direct3D device context
	/// </summary>
	/// <returns>Direct3D device context</returns>
	ID3D11DeviceContext* GetDeviceContext();

	/// <summary>
	/// Returns projection matrix
	/// </summary>
	/// <param name="">Reference to variable to copy the matrix to</param>
	void GetProjectionMatrix(XMMATRIX&);
	/// <summary>
	/// Returns wolrd matix
	/// </summary>
	/// <param name="">Reference to variable to copy the matrix to</param>
	void GetWorldMatrix(XMMATRIX&);
	/// <summary>
	/// Returns orthographic matrix
	/// </summary>
	/// <param name="">Reference to variable to copy the matrix to</param>
	void GetOrthoMatrix(XMMATRIX&);

	/// <summary>
	/// Returns by reference Video Card name and amount of dedicated memory on the video card to the m_videoCardDescription and m_videoCardMemory;
	/// </summary>
	/// <param name="">Video Card name</param>
	/// <param name="">Video Card memory</param>
	void GetVideoCardInfo(char*, int&);

private:
	bool m_vsync_enabled;
	int m_videoCardMemory;
	char m_videoCardDescription[128];
	IDXGISwapChain* m_swapChain;
	ID3D11Device* m_device;
	ID3D11DeviceContext* m_deviceContext;
	ID3D11RenderTargetView* m_renderTargetView;
	ID3D11Texture2D* m_depthStencilBuffer;
	ID3D11DepthStencilState* m_depthStencilState;
	ID3D11DepthStencilView* m_depthStencilView;
	ID3D11RasterizerState* m_rasterState;
	XMMATRIX m_projectionMatrix;
	XMMATRIX m_worldMatrix;
	XMMATRIX m_orthoMatrix;

};

#endif
