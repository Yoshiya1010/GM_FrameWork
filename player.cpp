// ��������������������������������������������������������������������������������������������������������������
// 
//  �m �N���X�� / �t�@�C���� �n
//     player.cpp
// 
//  �m ����� �n
//     2025�N06��05��
// 
//  �m ����� �n
//     �i��`��
// 
//  �m �T�v �n
//  �v���C���[�̊Ǘ�
// 
//  �m �X�V���� �n
//     - 2025/06/05 : �V�K�쐬
// 
// ��������������������������������������������������������������������������������������������������������������


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

    // �V�F�[�_�[�ǂݍ���
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
    

    // 1. �J������ Yaw ���擾
    float yaw = Manager::GetGameObject<Camera>()->GetYaw();  // ��Camera �� GetYaw() ��ǉ����Ă�������

    // 2. �J������������O���E�E�����x�N�g�����v�Z
    Vector3 forward = Vector3(
        sinf(yaw), 0.0f,
        cosf(yaw)
    );

    Vector3 right = Vector3(
        cosf(yaw), 0.0f,
        -sinf(yaw)
    );


    // 3. ���͂ɂ��ړ�����������
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


    // 4. �ړ��Ɖ�]�X�V
    if (moveDir.Length() > 0.0f)
    {
        moveDir.Normalize();
        m_Position += moveDir * speed;

        // �i�s�����ɑ̂�������
        m_Rotation.y = atan2f(moveDir.x, moveDir.z);
    }
    
    // �e�𔭎˂���
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
    // ���̓��C�A�E�g�ݒ�
    Renderer::GetDeviceContext()->IASetInputLayout(m_VertexLayout);

    // �V�F�[�_�[�ݒ�
    Renderer::GetDeviceContext()->VSSetShader(m_VertexShader, NULL, 0);
    Renderer::GetDeviceContext()->PSSetShader(m_PixelShader, NULL, 0);

    // �}�g���N�X�ݒ�
    XMMATRIX world, scale, rot, trans;
    scale = XMMatrixScaling(m_Scale.x, m_Scale.y, m_Scale.z);
    rot = XMMatrixRotationRollPitchYaw(m_Rotation.x, m_Rotation.y + XM_PI, m_Rotation.z);
    trans = XMMatrixTranslation(m_Position.x, m_Position.y, m_Position.z);
    world = scale * rot * trans;
    Renderer::SetWorldMatrix(world);

    // ���f���̕`��
    m_ModelRenderer->Draw();

}