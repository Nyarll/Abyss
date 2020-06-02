#pragma once

// <class name		: PrimitiveRenderer>
// <update date		: 2020 / 06 / 02>
// <author			: Nyarll>
// <GitHub			: https://github.com/Nyarll >

#ifndef PRIMITIVERENDERER_DEFINED
#define PRIMITIVERENDERER_DEFINED

// <PrimitiveRenderer>
class PrimitiveRenderer
{
private:
	using PrimitiveModel = DirectX::GeometricPrimitive;
	PrimitiveModel* m_modelPtr;

public:
	void SetModel(PrimitiveModel* model);

	void Draw(const DirectX::SimpleMath::Matrix& world, const DirectX::SimpleMath::Matrix& view,
		const DirectX::SimpleMath::Matrix& projection, DirectX::XMVECTORF32 color);
};

#endif