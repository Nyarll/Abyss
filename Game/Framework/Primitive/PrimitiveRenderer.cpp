#include "PrimitiveRenderer.h"

void PrimitiveRenderer::SetModel(PrimitiveModel * model)
{
	m_modelPtr = model;
}

void PrimitiveRenderer::Draw(const DirectX::SimpleMath::Matrix& world, const DirectX::SimpleMath::Matrix& view,
	const DirectX::SimpleMath::Matrix& projection, DirectX::XMVECTORF32 color)
{
	m_modelPtr->Draw(world, view, projection, color);
}
