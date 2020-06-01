#pragma once

// <class name		: GameSprite>
// <update date		: 2020 / 05 / 26>
// <author			: Nyarll>
// <GitHub			: https://github.com/Nyarll >

#ifndef GAMESPRITE_DEFINED
#define GAMESPRITE_DEFINED

#include <SimpleMath.h>
#include <Effects.h>
#include <PrimitiveBatch.h>
#include <VertexTypes.h>
#include <WICTextureLoader.h>
#include <CommonStates.h>

class GameContext;

// <GameSprite2D>
class Sprite2DRenderer
{
private:
	float m_scale;

public:
	Sprite2DRenderer() = default;
	~Sprite2DRenderer() = default;

	void Initialize(float scale = 1.f);
	void Draw(GameContext& context, const DirectX::SimpleMath::Vector2& pos, ID3D11ShaderResourceView* texture);
};

#endif
// GameSprite