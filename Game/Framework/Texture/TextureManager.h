#pragma once

// <class name		: TextureManager>
// <update date		: 2020 / 05 / 27>
// <author			: Nyarll>
// <GitHub			: https://github.com/Nyarll >

#ifndef TEXTUREMANAGER_DEFINED
#define TEXTUREMANAGER_DEFINED

#include "Texture.h"

class GameContext;

enum TextureID
{
	Logo,

	Floor,

	NUM
};

class TextureManager final
{
private:
	Texture	m_pools[TextureID::NUM];

public:
	TextureManager() = default;
	~TextureManager() = default;

	void Register(GameContext& ctx, const wchar_t* file_name, TextureID id);
	Texture& Get(TextureID id);
	ID3D11ShaderResourceView* GetTexture(TextureID id);
};

#endif