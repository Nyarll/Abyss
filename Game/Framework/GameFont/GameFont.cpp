
#include "GameFont.h"


void GameFont::Load(GameContext & ctx, const wchar_t * file_name, float scale)
{
	auto device = ctx.GetDR().GetD3DDevice();
	auto context = ctx.GetDR().GetD3DDeviceContext();

	ctx.Register(std::make_unique<DirectX::SpriteFont>(device, file_name));

	m_scale = scale;
}

void GameFont::Draw(GameContext& context, DirectX::SimpleMath::Vector2 pos, DirectX::FXMVECTOR color, std::string fmt_str, ...)
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
	auto& font = context.Get<DirectX::SpriteFont>();

	batch.Begin(DirectX::SpriteSortMode_Deferred, context.Get<DirectX::CommonStates>().NonPremultiplied());
	font.DrawString(&batch, result.c_str(),
		pos, color,
		0, DirectX::SimpleMath::Vector3::Zero, m_scale);
	batch.End();
}
