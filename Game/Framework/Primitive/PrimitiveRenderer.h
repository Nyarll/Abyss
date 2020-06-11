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

	DirectX::XMVECTOR m_color;
	bool m_isWireframe;
	ID3D11ShaderResourceView* texture;

public:
	PrimitiveRenderer();

	void SetModel(PrimitiveModel* model);
	void SetModelOption(DirectX::XMVECTOR _color = DirectX::Colors::Blue,
		bool _wireframe = false, ID3D11ShaderResourceView* _texture = nullptr);

	void SetColor(DirectX::XMVECTOR _color);
	void SetIsWireframe(bool _wireframe);
	void SetTexture(ID3D11ShaderResourceView* _texture);

	void Draw(const DirectX::SimpleMath::Matrix& world, const DirectX::SimpleMath::Matrix& view,
		const DirectX::SimpleMath::Matrix& projection);
};

#endif