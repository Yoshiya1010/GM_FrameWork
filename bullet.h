#pragma once

#include "main.h"
#include "renderer.h"
#include "gameObject.h"

class Bullet :public GameObject {
private:
	ID3D11VertexShader* m_VertexShader;	// ���_�V�F�[�_�[�I�u�W�F�N�g
	ID3D11PixelShader* m_PixelShader;		// �s�N�Z���V�F�[�_�[�I�u�W�F�N�g
	ID3D11InputLayout* m_VertexLayout;	// ���_���C�A�E�g�I�u�W�F�N�g

	class ModelRenderer* m_ModelRenderer; // �O���錾

	Vector3 m_Velocity{};

public:
	void Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;

	void SetVelocity(Vector3 Velocity) { m_Velocity = Velocity; }


	static constexpr float bulletspeed = 0.25f;
};