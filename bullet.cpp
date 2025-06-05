#include "bullet.h"
#include "manager.h"
#include "modelRenderer.h"
#include "camera.h"
#include "input.h"
#include"enemy.h"

void Bullet::Init()
{
    m_ModelRenderer = new ModelRenderer();
    m_ModelRenderer->Load("asset\\model\\bullet.obj");

    // �V�F�[�_�[�ǂݍ���
    Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout,
        "shader\\unlitTextureVS.cso");

    Renderer::CreatePixelShader(&m_PixelShader,
        "shader\\unlitTexturePS.cso");

}

void Bullet::Uninit()
{
    delete m_ModelRenderer;
    if (m_VertexLayout)     m_VertexLayout->Release();
    if (m_VertexShader)     m_VertexShader->Release();
    if (m_PixelShader)      m_PixelShader->Release();
}

void Bullet::Update()
{
    m_Position += m_Velocity;

    //�i�݉߂�����j��
    if (m_Position.Length() > 15.0f)
    {
        SetDestroy();
    }

    // �G�Ƃ̏Փ˔���
    auto enemies = Manager::GetGameObjects<Enemy>();

    for (auto enemy : enemies)
    {
        Vector3 d = enemy->GetPosition() - m_Position;
        float length = d.Length();
        if (length < 1.0f)
        {
            enemy->SetDestroy();
            SetDestroy();
        }
    }
  

}

void Bullet::Draw()
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