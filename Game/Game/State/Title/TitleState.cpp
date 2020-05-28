
#include "TitleState.h"

#include "../../../Framework/Framework.h"

void TitleState::Initialize(GameContext & context)
{
	auto titleLogo = m_registry.create();
	auto& titleSprite = m_registry.assign<Sprite2DRenderer>(titleLogo);
	titleSprite.Initialize();
	auto& logoPos = m_registry.assign<DirectX::SimpleMath::Vector2>(titleLogo);
	logoPos.x = 0;
	logoPos.y = 0;
}

void TitleState::Update(GameContext& context)
{
}

void TitleState::Render(GameContext& context)
{
	m_registry.view<Sprite2DRenderer, DirectX::SimpleMath::Vector2>().each([&](auto entity, auto& renderer, auto& pos)
	{
		renderer.Draw(context, pos, context.Get<TextureManager>().GetTexture(TextureID::Logo));
	});

	/*Sprite2DRenderer sprite;
	sprite.Initialize();
	sprite.Draw(context, DirectX::SimpleMath::Vector2(0, 0), context.Get<TextureManager>().GetTexture(TextureID::Logo));*/
}
