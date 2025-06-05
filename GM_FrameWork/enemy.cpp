#include "enemy.h"
#include "manager.h"
#include "modelRenderer.h"
#include "camera.h"
#include "input.h"

void Enemy::Init()
{
    m_ModelRenderer = new ModelRenderer();
    m_ModelRenderer->Load("asset\\model\\player.obj");

    // �V�F�[�_�[�ǂݍ���
    Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout,
        "shader\\unlitTextureVS.cso");

    Renderer::CreatePixelShader(&m_PixelShader,
        "shader\\unlitTexturePS.cso");

}

void Enemy::Uninit()
{
    delete m_ModelRenderer;
    if (m_VertexLayout)     m_VertexLayout->Release();
    if (m_VertexShader)     m_VertexShader->Release();
    if (m_PixelShader)      m_PixelShader->Release();
}

void Enemy::Update()
{
    
}

void Enemy::Draw()
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