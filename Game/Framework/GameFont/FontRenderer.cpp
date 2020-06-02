
#include "FontRenderer.h"

void FontRenderer::Draw(GameContext& context, DirectX::SpriteFont* font, DirectX::SimpleMath::Vector2 pos, DirectX::FXMVECTOR color, std::string fmt_str, ...)
{
	int final_n, n = ((int)fmt_str.size()) * 2;
	std::unique_ptr<char[]> formatted;
	va_list ap;
	while (1)
	{
		formatted.reset(new char[n]);
		strcpy(&formatted[0], fmt_str.c_str());
		va_start(ap, fmt_str);
		final_n = vsnprintf(&formatted[0], n, fmt_str.c_str(), ap);
		va_end(ap);
		if (final_n < 0 || final_n >= n)
			n += abs(final_n - n + 1);
		else
			break;
	}
	std::string result = std::string(formatted.get());

	auto& batch = context.Get<DirectX::SpriteBatch>();

	DirectX::SimpleMath::Vector2 position = pos;

	batch.Begin(DirectX::SpriteSortMode_Deferred, context.Get<DirectX::CommonStates>().NonPremultiplied());
	font->DrawString(&batch, result.c_str(),
		position, color,
		0, DirectX::SimpleMath::Vector3::Zero, m_scale);
	batch.End();
}
