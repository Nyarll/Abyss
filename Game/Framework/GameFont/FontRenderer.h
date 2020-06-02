#pragma once

// <class name		: GameFont>
// <update date		: 2020 / 05 / 27>
// <author			: Nyarll>
// <GitHub			: https://github.com/Nyarll >

#ifndef FONTRENDERER_DEFINED
#define FONTRENDERER_DEFINED

#include "../Context/GameContext.h"
#include <string>

// <GameFont>
class FontRenderer
{
private:
	float m_scale = 1.f;

public:
	FontRenderer() = default;
	~FontRenderer() = default;

	void Draw(GameContext& context, DirectX::SpriteFont* font, DirectX::SimpleMath::Vector2 pos,
		DirectX::FXMVECTOR color, std::string fmt_str, ...);
};

#endif