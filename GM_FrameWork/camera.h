#pragma once

#include "main.h"
#include "renderer.h"
#include "gameObject.h"

class Camera :public GameObject
{
private:
	XMMATRIX m_ProjectionMatrix;
	XMMATRIX m_ViewMatrix;

	//Vector3		m_Position;		//�J�����̍��W
	Vector3		m_AtPosition;	//�J�����̒����_
	Vector3		m_UpVector;		//����x�N�g��
	float		m_Fov;			//����p
	float		m_nearClip;		//�ǂ��܂ŋ߂��������邩
	float		m_farClip;		//�ǂ��܂ŉ����������邩
	float		m_rot;

	Vector3		m_playerOffset; // �v���C���[����ǂꂾ�����ꂽ�ʒu�ɂ��邩�B
	


	float m_Yaw = 0.0f;
	float m_Pitch = 0.0f;
	POINT m_PrevMousePos = {};

	bool m_IsCameraControl = false; // �J�������샂�[�h���ǂ���
	bool m_PrevRightClick = false;  // �E�N���b�N�̑O����

public:
	void	Init() override;
	void	Uninit() override;
	void	Update() override;
	void	Draw() override;

	float GetYaw() const { return m_Yaw; }
	float GetPitch()const { return m_Pitch; }
};