
#include "main.h"
#include "manager.h"
#include "renderer.h"

#include "Polygon.h"
#include "field.h"
#include "camera.h"
#include "player.h"
#include "enemy.h"
#include "input.h"

//GameObject* g_GameObjects[4]; //�O����3D�I�u�W�F�N�g�A�㔼��2D�I�u�W�F�N�g�ɂ���B�v����ɂ������蕪���邱��
std::list<GameObject*> Manager::m_GameObjects;
float Manager::m_deltaTime;

void Manager::Init()
{
	Renderer::Init();

	/// �J�������ŏ��ɓ����
	AddGameObject<Camera>();
	AddGameObject<Field>();
	AddGameObject<Player>();
	AddGameObject<Enemy>()->SetPosition({ -2.0f,0.0f,3.0f });
	AddGameObject<Enemy>()->SetPosition({ 0.0f,0.0f,3.0f });
	AddGameObject<Enemy>()->SetPosition({ 2.0f,0.0f,3.0f });

	// 3D��2D�Ń}�g���N�X���Ⴄ�̂Ń��X�g�𕪂���Ȃǂ��đΉ�����̂��ǂ����ȁH
	//AddGameObject<Polygon2D>(); 

	Input::Init();

	//m_GameObjects.push_back(new Camera());
	//m_GameObjects.back()->Init();

	//m_GameObjects.push_back(new Field());
	//m_GameObjects.back()->Init();

	//m_GameObjects.push_back(new Player());
	//m_GameObjects.back()->Init();

	//m_GameObjects.push_back(new Polygon2D());
	//m_GameObjects.back()->Init();
}


void Manager::Uninit()
{
	for (auto gameObject : m_GameObjects) {
		gameObject->Uninit();
		delete gameObject;
	}

	m_GameObjects.clear();

	Input::Uninit();

	Renderer::Uninit();
}

void Manager::Update()
{
	//for (int i = 0; i < 4; i++) {
	//	g_GameObjects[i]->Update();
	//}

	UpdateDeltaTime();
	Input::Update();

	for (auto gameObject : m_GameObjects) {
		gameObject->Update();
	}

	m_GameObjects.remove_if([](GameObject* object) {
		return object->Destroy();
		});
	
}

void Manager::Draw()
{
	Renderer::Begin();

	/// �J�������ŏ��ɕ`�悷�邱�ƁB
	for (auto gameObject : m_GameObjects) {
		gameObject->Draw();
	}

	Renderer::End();
}

void Manager::UpdateDeltaTime()
{
	static auto prevTime = std::chrono::high_resolution_clock::now();
	auto currentTime = std::chrono::high_resolution_clock::now();

	std::chrono::duration<float> delta = currentTime - prevTime;
	prevTime = currentTime;
	
	m_deltaTime = delta.count();
}
