// ��������������������������������������������������������������������������������������������������������������
// 
//  �m �N���X�� / �t�@�C���� �n
//     camera.cpp
// 
//  �m ����� �n
//     2025�N06��05��
// 
//  �m ����� �n
//     �i��`��
// 
//  �m �T�v �n
//  �J�����̊Ǘ��@�}�E�X����ɑΉ�����悤�ɂȂ��Ă�
// 
//  �m �X�V���� �n
//     - 2025/06/05 : �V�K�쐬
// 
// ��������������������������������������������������������������������������������������������������������������

#include	"camera.h"
#include	"Manager.h"
#include	"player.h"
#include	"input.h"

void	Camera::Init()
{
	//�J�����̏�����
	m_Position = Vector3(0.0f, 1.0f, -5.0f);	//�J������{���W
	m_UpVector = Vector3(0.0f, 1.0f, 0.0f);		//�J�����̏���x�N�g��
	m_AtPosition = Vector3(0.0f, 0.0f, 0.0f);	//�J�����̒����_���W
	m_Fov = 45.0f;								//��p
	m_nearClip = 1.0f;							//�ߖʃN���b�v
	m_farClip = 1000.0f;						//���ʃN���b�v
	m_rot = 0.0f;

	m_playerOffset = Vector3( 0.0f,3.0f,-10.0f);
}

void	Camera::Uninit()
{

}

void	Camera::Update()
{
    // �E�N���b�N�̓��͏�Ԏ擾
    bool isRightClick = (GetAsyncKeyState(VK_RBUTTON) & 0x8000) != 0;

    // �E�N���b�N���u�����ꂽ�u�ԁv�����o
    if (isRightClick && !m_PrevRightClick)
    {
        m_IsCameraControl = !m_IsCameraControl; // ���[�h�؂�ւ�
        ShowCursor(!m_IsCameraControl);         // �J�[�\���\���̐؂�ւ�
    }
    m_PrevRightClick = isRightClick;

    if (!m_IsCameraControl)
    {
        return; // �J�������샂�[�h�łȂ���Ή������Ȃ�
    }

    const float sensitivity = 0.005f; // �}�E�X���x

    // �}�E�X�ʒu�擾
    POINT mousePos;
    GetCursorPos(&mousePos);

    static bool firstMouse = true;
    if (firstMouse)
    {
        m_PrevMousePos = mousePos;
        firstMouse = false;
        return;
    }

    // �}�E�X�ړ��ʂ���Yaw��Pitch���X�V
    float dx = (float)(mousePos.x - m_PrevMousePos.x);
    float dy = (float)(mousePos.y - m_PrevMousePos.y);
    m_PrevMousePos = mousePos;

    m_Yaw += dx * sensitivity;
    m_Pitch += dy * sensitivity;

    // �s�b�`����
    if (m_Pitch > XM_PIDIV2 - 0.1f) m_Pitch = XM_PIDIV2 - 0.1f;
    if (m_Pitch < -XM_PIDIV2 + 0.1f) m_Pitch = -XM_PIDIV2 + 0.1f;

    // �v���C���[�ʒu�擾
    Player* player = Manager::GetGameObject<Player>();
    Vector3 playerPos = player->GetPosition() + Vector3(0.0f, 1.5f, 0.0f);

    m_AtPosition = playerPos;

    // �J�����ʒu�v�Z
    float distance = 5.0f;
    m_Position.x = m_AtPosition.x - distance * cosf(m_Pitch) * sinf(m_Yaw);
    m_Position.y = m_AtPosition.y + distance * sinf(m_Pitch);
    m_Position.z = m_AtPosition.z - distance * cosf(m_Pitch) * cosf(m_Yaw);

    // �J�[�\���𒆉��ɖ߂�
    SetCursorPos(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
    m_PrevMousePos.x = SCREEN_WIDTH / 2;
    m_PrevMousePos.y = SCREEN_HEIGHT / 2;

    // �v���C���[�̉�]���J�����ɓ���
    Vector3 playerRot = player->GetRotation();
    playerRot.y = m_Yaw;
    player->SetRotation(playerRot);
}

void	Camera::Draw()//3D�g�p��
{
	//�v���W�F�N�V�����s����쐬
	m_ProjectionMatrix =
		XMMatrixPerspectiveFovLH(
			XMConvertToRadians(m_Fov),
			(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,
			m_nearClip,
			m_farClip
		);

	//�v���W�F�N�V�����s����Z�b�g
	Renderer::SetProjectionMatrix(m_ProjectionMatrix);

	//�J�����s����쐬
	XMVECTOR	eyev = XMLoadFloat3((XMFLOAT3*)&m_AtPosition);
	XMVECTOR	pos = XMLoadFloat3((XMFLOAT3*)&m_Position);
	XMVECTOR	up = XMLoadFloat3((XMFLOAT3*)&m_UpVector);
	m_ViewMatrix = XMMatrixLookAtLH(pos, eyev, up);

	//�J�����s����Z�b�g
	Renderer::SetViewMatrix(m_ViewMatrix);
}