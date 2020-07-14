#pragma once

// <class name		: Grid>
// <update date		: 2020 / 06 / 11>
// <author			: Nyarll>
// <GitHub			: https://github.com/Nyarll >

#ifndef GRID_DEFINED
#define GRID_DEFINED

// <�f�o�b�O�p�O���b�h���N���X>
class GridFloor
{
	// <�G�t�F�N�g>
	std::unique_ptr<DirectX::BasicEffect> m_basicEffect;

	// <�v���~�e�B�u�o�b�`>
	std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionColor>> m_primitiveBatch;

	// <�C���v�b�g���C�A�E�g>
	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_pInputLayout;

	// <�R�����X�e�[�g�ւ̃|�C���^>
	DirectX::CommonStates* m_states;

	ID3D11DeviceContext* m_deviceContext;

	// <���̈�ӂ̃T�C�Y>
	float m_size;

	// <������>
	int m_divs;

public:
	// <�R���X�g���N�^>
	GridFloor(ID3D11Device* device, ID3D11DeviceContext* context, DirectX::CommonStates* states, float size, int divs);

	// <�f�X�g���N�^>
	~GridFloor();

	// <�`��>
	void draw(const DirectX::SimpleMath::Matrix& world, const DirectX::SimpleMath::Matrix& view,
		const DirectX::SimpleMath::Matrix& proj);
};

#endif