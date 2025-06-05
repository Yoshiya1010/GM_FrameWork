#pragma once

#include "main.h"
#include "renderer.h"
#include "gameObject.h"

class Camera :public GameObject
{
private:
	XMMATRIX m_ProjectionMatrix;
	XMMATRIX m_ViewMatrix;

	//Vector3		m_Position;		//カメラの座標
	Vector3		m_AtPosition;	//カメラの注視点
	Vector3		m_UpVector;		//上方ベクトル
	float		m_Fov;			//視野角
	float		m_nearClip;		//どこまで近くが見えるか
	float		m_farClip;		//どこまで遠くが見えるか
	float		m_rot;

	Vector3		m_playerOffset; // プレイヤーからどれだけ離れた位置にいるか。
	


	float m_Yaw = 0.0f;
	float m_Pitch = 0.0f;
	POINT m_PrevMousePos = {};

	bool m_IsCameraControl = false; // カメラ操作モードかどうか
	bool m_PrevRightClick = false;  // 右クリックの前回状態

public:
	void	Init() override;
	void	Uninit() override;
	void	Update() override;
	void	Draw() override;

	float GetYaw() const { return m_Yaw; }
	float GetPitch()const { return m_Pitch; }
};