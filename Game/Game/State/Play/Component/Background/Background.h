#pragma once

// <class name		: Background>
// <update date		: 2020 / 07 / 20>
// <author			: Nyarll>
// <GitHub			: https://github.com/Nyarll >

#ifndef BACKGROUND_DEFINED
#define BACKGROUND_DEFINED

#include "../../../../../Framework/Context/GameContext.h"

class Background
{
private:
	ID3D11RasterizerState* m_pDefaultCulling;
	Microsoft::WRL::ComPtr<ID3D11PixelShader>	m_PixelShader;
	Microsoft::WRL::ComPtr<ID3D11VertexShader>	m_VertexShader;
	Microsoft::WRL::ComPtr<ID3D11InputLayout>	m_inputLayout;

	static const std::vector<D3D11_INPUT_ELEMENT_DESC>	INPUT_LAYOUT;

public:

	Background& operator=(Background&& back)noexcept;

	void Initialize(GameContext& context);

	void Begin(GameContext& context);
	void End(GameContext& context);
};

#endif