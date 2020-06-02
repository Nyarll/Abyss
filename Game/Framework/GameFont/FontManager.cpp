#include "FontManager.h"
#include "../Context/GameContext.h"

void FontManager::Register(GameContext & context, const wchar_t * file_name, const std::string & font_name)
{
	m_pools.push_back(std::move(Font(context.GetDR().GetD3DDevice(), file_name, font_name)));
}
