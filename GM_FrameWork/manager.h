#pragma once
#include <chrono>
#include <list>
#include<vector>
#include "gameObject.h"

class Manager
{
private:
	static std::list<GameObject*> m_GameObjects;
	static float m_deltaTime;

	static void UpdateDeltaTime();
public:
	static void Init();
	static void Uninit();
	static void Update();
	static void Draw();

	//template <typename T>
	//static void AddGameObject() {
	//	T* gameObject = new T();
	//	gameObject->Init();
	//	m_GameObjects.push_back(gameObject);
	//}


	//単数
	template <typename T>
	static T* GetGameObject() {
		for (auto gameObject : m_GameObjects) {

			T* find = dynamic_cast<T*>(gameObject); // T*型にあてはめられない場合、nullが入る

			if (find) {
				return find;
			}
		}

		return nullptr;
	}


	//複数
	template <typename T>
	static std::vector<T*> GetGameObjects()
	{
		std::vector<T*> finds;
		for (auto gameObject : m_GameObjects)
		{
			T* find = dynamic_cast<T*>(gameObject);
			if (find != nullptr)
				finds.push_back(find);
		}
		return finds;
	}

	static float GetDeltaTime() { return m_deltaTime; }

	template <typename T>
	static T* AddGameObject() {
		T* gameObject = new T();
		gameObject->Init();
		m_GameObjects.push_back(gameObject);

		return gameObject;
	}
};