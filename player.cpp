// □□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□
// 
//  ［ クラス名 / ファイル名 ］
//     player.cpp
// 
//  ［ 制作日 ］
//     2025年06月05日
// 
//  ［ 制作者 ］
//     永野義也
// 
//  ［ 概要 ］
//  プレイヤーの管理
// 
//  ［ 更新履歴 ］
//     - 2025/06/05 : 新規作成
// 
// □□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□


#include "player.h"
#include "manager.h"
#include "modelRenderer.h"
#include "camera.h"
#include "input.h"
#include "bullet.h"

void Player::Init()
{
    m_ModelRenderer = new ModelRenderer();
    m_ModelRenderer->Load("asset\\model\\player.obj");

    // シェーダー読み込み
    Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout,
        "shader\\unlitTextureVS.cso");

    Renderer::CreatePixelShader(&m_PixelShader,
        "shader\\unlitTexturePS.cso");

}

void Player::Uninit()
{
    delete m_ModelRenderer;
    if (m_VertexLayout)     m_VertexLayout->Release();
    if (m_VertexShader)     m_VertexShader->Release();
    if (m_PixelShader)      m_PixelShader->Release();
}

void Player::Update()
{
    Camera* camera = Manager::GetGameObject<Camera>();
    

    // 1. カメラの Yaw を取得
    float yaw = Manager::GetGameObject<Camera>()->GetYaw();  // ★Camera に GetYaw() を追加してください

    // 2. カメラ向きから前方・右方向ベクトルを計算
    Vector3 forward = Vector3(
        sinf(yaw), 0.0f,
        cosf(yaw)
    );

    Vector3 right = Vector3(
        cosf(yaw), 0.0f,
        -sinf(yaw)
    );


    // 3. 入力による移動方向を合成
    Vector3 moveDir = { 0.0f, 0.0f, 0.0f };
    const float speed = 0.1f;

    if (Input::GetKeyPress(KK_A)) {
        moveDir -= right;
    }

    if (Input::GetKeyPress(KK_D)) {
        moveDir += right;
    }

    if (Input::GetKeyPress(KK_W)) {
        moveDir += forward;
    }

    if (Input::GetKeyPress(KK_S)) {
        moveDir -= forward;
    }


    // 4. 移動と回転更新
    if (moveDir.Length() > 0.0f)
    {
        moveDir.Normalize();
        m_Position += moveDir * speed;

        // 進行方向に体を向ける
        m_Rotation.y = atan2f(moveDir.x, moveDir.z);
    }
    
    // 弾を発射する
    if (Input::GetKeyTrigger(KK_SPACE)) {
        Bullet* bullet = Manager::AddGameObject<Bullet>();
        bullet->SetPosition(m_Position);
        bullet->SetVelocity(Vector3(GetForward().x, -camera->GetPitch()+0.2f, GetForward().z)*bullet->bulletspeed);
    }

    //Vector3 rotation = camera->GetRotation();
    //m_Rotation.y = rotation.y;
}

void Player::Draw()
{
    // 入力レイアウト設定
    Renderer::GetDeviceContext()->IASetInputLayout(m_VertexLayout);

    // シェーダー設定
    Renderer::GetDeviceContext()->VSSetShader(m_VertexShader, NULL, 0);
    Renderer::GetDeviceContext()->PSSetShader(m_PixelShader, NULL, 0);

    // マトリクス設定
    XMMATRIX world, scale, rot, trans;
    scale = XMMatrixScaling(m_Scale.x, m_Scale.y, m_Scale.z);
    rot = XMMatrixRotationRollPitchYaw(m_Rotation.x, m_Rotation.y + XM_PI, m_Rotation.z);
    trans = XMMatrixTranslation(m_Position.x, m_Position.y, m_Position.z);
    world = scale * rot * trans;
    Renderer::SetWorldMatrix(world);

    // モデルの描画
    m_ModelRenderer->Draw();

}