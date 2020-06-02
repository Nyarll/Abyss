#pragma once

// <class name		: Font>
// <update date		: 2020 / 06 / 01>
// <author			: Nyarll>
// <GitHub			: https://github.com/Nyarll >

#ifndef FONT_DEFINED
#define FONT_DEFINED

class Font
{
private:
	std::unique_ptr<DirectX::SpriteFont>	m_font;
	std::string								m_fontName;

public:
	Font(ID3D11Device* device, const wchar_t* file_name, const std::string& font_name);

	DirectX::SpriteFont* GetFont()
	{
		return m_font.get();
	}

	const std::string& GetFontName()
	{
		return m_fontName;
	}
};

#endif