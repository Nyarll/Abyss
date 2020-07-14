#include "PrimitiveRenderer.h"

PrimitiveRenderer::PrimitiveRenderer()
	:m_modelPtr(nullptr)
	,m_color(DirectX::Colors::Red)
	,m_isWireframe(false)
	,texture(nullptr)
{
}

void PrimitiveRenderer::SetModel(PrimitiveModel* model)
{
	m_modelPtr = model;
}

void PrimitiveRenderer::SetModelOption(DirectX::XMVECTOR _color, bool _wireframe, ID3D11ShaderResourceView* _texture)
{
	SetColor(_color);
	SetIsWireframe(_wireframe);
	SetTexture(_texture);
}

void PrimitiveRenderer::SetColor(DirectX::XMVECTOR _color)
{
	m_color = _color;
}

void PrimitiveRenderer::SetIsWireframe(bool _wireframe)
{
	m_isWireframe = _wireframe;
}

void PrimitiveRenderer::SetTexture(ID3D11ShaderResourceView* _texture)
{
	texture = _texture;
}

void PrimitiveRenderer::Draw(const DirectX::SimpleMath::Matrix& world, const DirectX::SimpleMath::Matrix& view,
	const DirectX::SimpleMath::Matrix& projection)
{
	if (m_modelPtr)
	{
		m_modelPtr->Draw(world, view, projection, m_color, texture, m_isWireframe);
	}
}
