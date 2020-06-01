#pragma once

// <class name		: GameFont>
// <update date		: 2020 / 05 / 27>
// <author			: Nyarll>
// <GitHub			: https://github.com/Nyarll >

#ifndef GAMEFONT_DEFINED
#define GAMEFONT_DEFINED

#include "../Context/GameContext.h"
#include <string>

// <GameFont>
class GameFont
{
private:
	//std::unique_ptr<DirectX::SpriteFont> m_spriteFont;

	float m_scale;

public:
	GameFont() = default;
	~GameFont() = default;

	void Load(GameContext& ctx, const wchar_t* file_name, float scale = 0.75f);

	void Draw(GameContext& context, DirectX::SimpleMath::Vector2 pos,DirectX::FXMVECTOR color, std::string fmt_str, ...);

	void SetScale(float scale) { m_scale = scale; }
};

#endif