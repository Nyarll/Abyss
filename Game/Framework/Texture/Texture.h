#pragma once

// <class name		: Texture>
// <update date		: 2020 / 05 / 27>
// <author			: Nyarll>
// <GitHub			: https://github.com/Nyarll >

#ifndef TEXTURE_DEFINED
#define TEXTURE_DEFINED

class GameContext;

class Texture
{
private:
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_texture;

	DirectX::SimpleMath::Vector2 m_center;
	DirectX::SimpleMath::Vector2 m_textureSize;

public:

	void Load(GameContext& ctx, const wchar_t* file_name);

	ID3D11ShaderResourceView* Get()
	{
		return m_texture.Get();
	}

	DirectX::SimpleMath::Vector2& GetCenter()
	{
		return m_center;
	}

	DirectX::SimpleMath::Vector2& GetTextureSize()
	{
		return m_textureSize;
	}
};

#endif