#include "TextureManager.h"

#include "../Context/GameContext.h"

void TextureManager::Register(GameContext& ctx, const wchar_t* file_name, TextureID id)
{
	assert(id < TextureID::NUM && "Not Found ID");
	m_pools[id].Load(ctx, file_name);
}

Texture& TextureManager::Get(TextureID id)
{
	return m_pools[id];
}

ID3D11ShaderResourceView* TextureManager::GetTexture(TextureID id)
{
	return m_pools[id].Get();
}
