// □□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□
// 
//  ［ クラス名 / ファイル名 ］
//     camera.cpp
// 
//  ［ 制作日 ］
//     2025年06月05日
// 
//  ［ 制作者 ］
//     永野義也
// 
//  ［ 概要 ］
//  カメラの管理　マウス操作に対応するようになってる
// 
//  ［ 更新履歴 ］
//     - 2025/06/05 : 新規作成
// 
// □□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□

#include	"camera.h"
#include	"Manager.h"
#include	"player.h"
#include	"input.h"

void	Camera::Init()
{
	//カメラの初期化
	m_Position = Vector3(0.0f, 1.0f, -5.0f);	//カメラ基本座標
	m_UpVector = Vector3(0.0f, 1.0f, 0.0f);		//カメラの上方ベクトル
	m_AtPosition = Vector3(0.0f, 0.0f, 0.0f);	//カメラの注視点座標
	m_Fov = 45.0f;								//画角
	m_nearClip = 1.0f;							//近面クリップ
	m_farClip = 1000.0f;						//遠面クリップ
	m_rot = 0.0f;

	m_playerOffset = Vector3( 0.0f,3.0f,-10.0f);
}

void	Camera::Uninit()
{

}

void	Camera::Update()
{
    // 右クリックの入力状態取得
    bool isRightClick = (GetAsyncKeyState(VK_RBUTTON) & 0x8000) != 0;

    // 右クリックが「押された瞬間」を検出
    if (isRightClick && !m_PrevRightClick)
    {
        m_IsCameraControl = !m_IsCameraControl; // モード切り替え
        ShowCursor(!m_IsCameraControl);         // カーソル表示の切り替え
    }
    m_PrevRightClick = isRightClick;

    if (!m_IsCameraControl)
    {
        return; // カメラ操作モードでなければ何もしない
    }

    const float sensitivity = 0.005f; // マウス感度

    // マウス位置取得
    POINT mousePos;
    GetCursorPos(&mousePos);

    static bool firstMouse = true;
    if (firstMouse)
    {
        m_PrevMousePos = mousePos;
        firstMouse = false;
        return;
    }

    // マウス移動量からYawとPitchを更新
    float dx = (float)(mousePos.x - m_PrevMousePos.x);
    float dy = (float)(mousePos.y - m_PrevMousePos.y);
    m_PrevMousePos = mousePos;

    m_Yaw += dx * sensitivity;
    m_Pitch += dy * sensitivity;

    // ピッチ制限
    if (m_Pitch > XM_PIDIV2 - 0.1f) m_Pitch = XM_PIDIV2 - 0.1f;
    if (m_Pitch < -XM_PIDIV2 + 0.1f) m_Pitch = -XM_PIDIV2 + 0.1f;

    // プレイヤー位置取得
    Player* player = Manager::GetGameObject<Player>();
    Vector3 playerPos = player->GetPosition() + Vector3(0.0f, 1.5f, 0.0f);

    m_AtPosition = playerPos;

    // カメラ位置計算
    float distance = 5.0f;
    m_Position.x = m_AtPosition.x - distance * cosf(m_Pitch) * sinf(m_Yaw);
    m_Position.y = m_AtPosition.y + distance * sinf(m_Pitch);
    m_Position.z = m_AtPosition.z - distance * cosf(m_Pitch) * cosf(m_Yaw);

    // カーソルを中央に戻す
    SetCursorPos(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
    m_PrevMousePos.x = SCREEN_WIDTH / 2;
    m_PrevMousePos.y = SCREEN_HEIGHT / 2;

    // プレイヤーの回転をカメラに同期
    Vector3 playerRot = player->GetRotation();
    playerRot.y = m_Yaw;
    player->SetRotation(playerRot);
}

void	Camera::Draw()//3D使用時
{
	//プロジェクション行列を作成
	m_ProjectionMatrix =
		XMMatrixPerspectiveFovLH(
			XMConvertToRadians(m_Fov),
			(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,
			m_nearClip,
			m_farClip
		);

	//プロジェクション行列をセット
	Renderer::SetProjectionMatrix(m_ProjectionMatrix);

	//カメラ行列を作成
	XMVECTOR	eyev = XMLoadFloat3((XMFLOAT3*)&m_AtPosition);
	XMVECTOR	pos = XMLoadFloat3((XMFLOAT3*)&m_Position);
	XMVECTOR	up = XMLoadFloat3((XMFLOAT3*)&m_UpVector);
	m_ViewMatrix = XMMatrixLookAtLH(pos, eyev, up);

	//カメラ行列をセット
	Renderer::SetViewMatrix(m_ViewMatrix);
}