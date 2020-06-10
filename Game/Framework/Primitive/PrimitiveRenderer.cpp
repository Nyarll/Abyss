#include "PrimitiveRenderer.h"

void PrimitiveRenderer::SetModel(PrimitiveModel * model)
{
	m_modelPtr = model;
}

void PrimitiveRenderer::Draw(const DirectX::SimpleMath::Matrix& world, const DirectX::SimpleMath::Matrix& view,
	const DirectX::SimpleMath::Matrix& projection, DirectX::XMVECTOR color,
	ID3D11ShaderResourceView* texture,
	bool wireframe)
{
	if (m_modelPtr)
	{
		m_modelPtr->Draw(world, view, projection, color, texture, wireframe);
	}
}
