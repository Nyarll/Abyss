#include "Font.h"

Font::Font(ID3D11Device * device, const wchar_t * file_name, const std::string& font_name)
	:m_fontName(font_name)
{
	m_font = std::make_unique<DirectX::SpriteFont>(device, file_name);
}
