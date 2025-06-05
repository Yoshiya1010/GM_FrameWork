#pragma once

class GameObject {
private:

protected:
	Vector3 m_Position { 0.0f,0.0f,0.0f };
	Vector3 m_Rotation{ 0.0f,0.0f,0.0f };
	Vector3 m_Scale{ 1.0f,1.0f,1.0f };

	bool m_Destroy = false;
public:
	virtual void Init() {}
	virtual void Uninit() {}
	virtual void Update() {}
	virtual void Draw() {}

	void SetDestroy() { m_Destroy = true; }
	bool Destroy() {

		if (m_Destroy) {
			Uninit();
			delete this;

			return true;
		}
		else {
			return false;
		}
	}

	Vector3 GetPosition() { return m_Position; }
	void SetPosition(Vector3 Position) { m_Position = Position; }

	Vector3 GetRotation() { return m_Rotation; }
	void SetRotation(Vector3 Rotation) { m_Rotation = Rotation; }

	Vector3 GetScale() { return m_Scale; }
	void SetScale(Vector3 Scale) { m_Scale = Scale; }

	Vector3 GetRight() { 
		XMMATRIX matrix;
		matrix = XMMatrixRotationRollPitchYaw(m_Rotation.x, m_Rotation.y, m_Rotation.z);

		Vector3 right;
		XMStoreFloat3((XMFLOAT3*)&right, matrix.r[0]);

		return right;
	};

	Vector3 GetUp() { 
		XMMATRIX matrix;
		matrix = XMMatrixRotationRollPitchYaw(m_Rotation.x, m_Rotation.y, m_Rotation.z);

		Vector3 Up;
		XMStoreFloat3((XMFLOAT3*)&Up, matrix.r[1]);

		return Up;
	};

	Vector3 GetForward() { 
		XMMATRIX matrix;
		matrix = XMMatrixRotationRollPitchYaw(m_Rotation.x, m_Rotation.y, m_Rotation.z);

		Vector3 forward;
		XMStoreFloat3((XMFLOAT3*)&forward, matrix.r[2]);

		return forward;
	};
};