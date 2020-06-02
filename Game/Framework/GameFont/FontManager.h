#pragma once

// <class name		: FontManager>
// <update date		: 2020 / 06 / 01>
// <author			: Nyarll>
// <GitHub			: https://github.com/Nyarll >

#ifndef FONTMANAGER_DEFINED
#define FONTMANAGER_DEFINED

#include "Font.h"

class GameContext;

class FontManager final
{
private:
	std::vector<Font>	m_pools;

public:
	FontManager() = default;
	~FontManager() = default;

	void Register(GameContext& context, const wchar_t* file_name, const std::string& font_name);
	DirectX::SpriteFont* GetSpriteFont(const std::string& font_name)
	{
		for (auto& font : m_pools)
		{
			if (font.GetFontName() == font_name)
			{
				return font.GetFont();
			}
		}
		return nullptr;
	}
};

#endif