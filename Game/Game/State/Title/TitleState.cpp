
#include "TitleState.h"

#include "../../../Framework/Framework.h"

void TitleState::Initialize(GameContext & context)
{
	{
		auto titleLogo = m_registry.create();
		auto& titleSprite = m_registry.assign<Sprite2DRenderer>(titleLogo);
		titleSprite.Initialize();
		auto& logoPos = m_registry.assign<DirectX::SimpleMath::Vector2>(titleLogo);
		logoPos.x = 0;
		logoPos.y = 0;
	}
	{
		auto titleMessage = m_registry.create();
		auto& titlefont = m_registry.assign<FontRenderer>(titleMessage);
		auto& messagePos = m_registry.assign<DirectX::SimpleMath::Vector2>(titleMessage);
		messagePos.x = (System::GetWindowSize().x / 8) * 2.5f;
		messagePos.y = (System::GetWindowSize().y / 4) * 3;
	}
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

	m_registry.view<FontRenderer, DirectX::SimpleMath::Vector2>().each([&](auto entity, auto& gameFont, auto& pos)
	{
		auto font = context.Get<FontManager>().GetSpriteFont("Meiryo UI");
		gameFont.Draw(context, font, pos, DirectX::Colors::White, "push to [SPACE] key.");
	});
}
