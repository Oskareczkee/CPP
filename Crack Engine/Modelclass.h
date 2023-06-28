#pragma once
#ifndef _MODELCLASS_H_
#define _MODELCLASS_H_

#include <d3d11.h>
#include <DirectXMath.h>

using namespace DirectX;


class ModelClass
{
private:
	struct VertexType
	{
		XMFLOAT3 position;
		XMFLOAT4 color;
	};

public:
	ModelClass();
	ModelClass(const ModelClass&);
	~ModelClass();

	/// <summary>
	/// Initializes model's vertex and index buffers
	/// </summary>
	/// <param name=""> </param>
	/// <returns>Returns true if everything went ok</returns>
	bool Initialize(ID3D11Device*);
	/// <summary>
	/// Shutdowns model's vertex and index buffers
	/// </summary>
	void Shutdown();
	/// <summary>
	/// puts the model geometry on the video card to prepare it for drawing by the color shader
	/// </summary>
	/// <param name=""></param>
	void Render(ID3D11DeviceContext*);

	/// <summary>
	/// </summary>
	/// <returns>Returns index buffer count</returns>
	int GetIndexCount();

private:
	bool InitializeBuffers(ID3D11Device*);
	void ShutdownBuffers();
	void RenderBuffers(ID3D11DeviceContext*);

private:
	ID3D11Buffer* m_vertexBuffer, * m_indexBuffer;
	int m_vertexCount, m_indexCount;
};

#endif