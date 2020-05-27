
#include "TitleState.h"

#include "../../../Framework/Framework.h"

void TitleState::Initialize(GameContext & context)
{
	auto titleLogo = m_registry.create();
	//auto& titleSprite = m_registry.assign<GameSprite2D>(titleLogo);
	//titleSprite.Initialize();
	//auto& logoPos = m_registry.assign<DirectX::SimpleMath::Vector2>(titleLogo);
	//logoPos.x = System::GetWindowSize().x / 2;
	//logoPos.y = System::GetWindowSize().y / 2;
}

void TitleState::Update(GameContext& context)
{
}

void TitleState::Render(GameContext& context)
{
	//m_registry.view<GameSprite2D>().each(
	//	[&](auto entity, auto& sprite)
	//{
		//auto& manager = context.Get<TextureManager>();
		//sprite.Draw(context, pos - manager.Get(TextureID::Logo).GetCenter(), manager.GetTexture(TextureID::Logo);
	//});

	Sprite2DRenderer sprite;
	sprite.Initialize();
	sprite.Draw(context, DirectX::SimpleMath::Vector2(0, 0), context.Get<TextureManager>().GetTexture(TextureID::Logo));
}
