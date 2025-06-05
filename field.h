#pragma once

#include "main.h"
#include "renderer.h"
#include "gameObject.h"

class Field :public GameObject {

private:
	ID3D11Buffer* m_VertexBuffer;

	ID3D11VertexShader* m_VertexShader;	// ���_�V�F�[�_�[�I�u�W�F�N�g
	ID3D11PixelShader* m_PixelShader;		// �s�N�Z���V�F�[�_�[�I�u�W�F�N�g
	ID3D11InputLayout* m_VertexLayout;	// ���_���C�A�E�g�I�u�W�F�N�g

	ID3D11ShaderResourceView* m_Texture; // �e�N�X�`��

public:
	void Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;
};