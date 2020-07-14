#pragma once

// <class name		: Grid>
// <update date		: 2020 / 06 / 11>
// <author			: Nyarll>
// <GitHub			: https://github.com/Nyarll >

#ifndef GRID_DEFINED
#define GRID_DEFINED

// <デバッグ用グリッド床クラス>
class GridFloor
{
	// <エフェクト>
	std::unique_ptr<DirectX::BasicEffect> m_basicEffect;

	// <プリミティブバッチ>
	std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionColor>> m_primitiveBatch;

	// <インプットレイアウト>
	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_pInputLayout;

	// <コモンステートへのポインタ>
	DirectX::CommonStates* m_states;

	ID3D11DeviceContext* m_deviceContext;

	// <床の一辺のサイズ>
	float m_size;

	// <分割数>
	int m_divs;

public:
	// <コンストラクタ>
	GridFloor(ID3D11Device* device, ID3D11DeviceContext* context, DirectX::CommonStates* states, float size, int divs);

	// <デストラクタ>
	~GridFloor();

	// <描画>
	void draw(const DirectX::SimpleMath::Matrix& world, const DirectX::SimpleMath::Matrix& view,
		const DirectX::SimpleMath::Matrix& proj);
};

#endif