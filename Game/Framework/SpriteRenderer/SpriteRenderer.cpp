
#include "SpriteRenderer.h"
#include "../Context/GameContext.h"

void Sprite2DRenderer::Initialize(float scale)
{
	m_scale = scale;
}

void Sprite2DRenderer::Draw(GameContext& context, const DirectX::SimpleMath::Vector2& pos, ID3D11ShaderResourceView* texture)
{
	auto& batch = context.Get<DirectX::SpriteBatch>();
	batch.Begin(DirectX::SpriteSortMode_Deferred, context.Get<DirectX::CommonStates>().NonPremultiplied());
	batch.Draw(texture, pos, nullptr, DirectX::Colors::White, 0.f, { 0.f,0.f }, m_scale);
	batch.End();
}

