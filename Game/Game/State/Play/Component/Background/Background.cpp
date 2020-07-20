#include "Background.h"

#include "../../../../../Framework/Framework.h"

const std::vector<D3D11_INPUT_ELEMENT_DESC>	Background::INPUT_LAYOUT = 
{
	{ "POSITION",	0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "COLOR",		0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, sizeof(DirectX::SimpleMath::Vector3), D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "TEXCOORD",	0, DXGI_FORMAT_R32G32_FLOAT, 0, sizeof(DirectX::SimpleMath::Vector3) + sizeof(DirectX::SimpleMath::Vector4), D3D11_INPUT_PER_VERTEX_DATA, 0 },
};

Background& Background::operator=(Background && back) noexcept
{
	m_PixelShader = std::move(back.m_PixelShader);
	m_VertexShader = std::move(back.m_VertexShader);
	m_inputLayout = std::move(back.m_inputLayout);
	m_pDefaultCulling = back.m_pDefaultCulling;
}

void Background::Initialize(GameContext& context)
{
	//ShaderFileImporter VS = ShaderFileImporter::LoadFile(L"");
	ShaderFileImporter PS = ShaderFileImporter::LoadFile(L"Resources/Shader/backgroundPS.cso");
}

void Background::Begin(GameContext& context)
{
	auto deviceContext = context.GetDR().GetD3DDeviceContext();
	auto& state = context.Get<DirectX::CommonStates>();

	// <透明判定処理>
	ID3D11BlendState* blendstate = state.NonPremultiplied();
	deviceContext->OMSetBlendState(blendstate, nullptr, 0xFFFFFFFF);
	// <深度バッファに書き込み参照する>
	deviceContext->OMSetDepthStencilState(state.DepthDefault(), 0);
	
	deviceContext->RSGetState(&m_pDefaultCulling);
	// <カリング設定>
	deviceContext->RSSetState(state.CullNone());
}

void Background::End(GameContext& context)
{
	auto deviceContext = context.GetDR().GetD3DDeviceContext();

	deviceContext->RSSetState(m_pDefaultCulling);

	deviceContext->VSSetShader(nullptr, nullptr, 0);
	deviceContext->PSSetShader(nullptr, nullptr, 0);
	deviceContext->GSSetShader(nullptr, nullptr, 0);
}
