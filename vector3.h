#pragma once

#include <math.h>

class Vector3 {
public:
	float x, y, z;

	Vector3() = default;

	// �R�s�[�R���X�g���N�^
	Vector3(const Vector3& a) :x(a.x), y(a.y), z(a.z) {}

	// 3�̒l�ō쐬����
	Vector3(float nx, float ny, float nz) :x(nx), y(ny), z(nz) {}

	// ���
	Vector3& operator=(const Vector3& a) {
		x = a.x;
		y = a.y;
		z = a.z;
		
		return *this;
	}


	// �������̃`�F�b�N
	bool operator ==(const Vector3& a) const {
		return x == a.x && y == a.y && z == a.z;
	}

	bool operator !=(const Vector3& a) const {
		return x != a.x || y != a.y || z != a.z;
	}


	// �x�N�g������

	void Zero() {
		x = y = z = 0.0f;
	}

	// �P������-�͔��]�x�N�g����Ԃ�
	Vector3 operator -() const { return Vector3(-x, -y, -z); }

	// ���Z
	Vector3 operator +(const Vector3& a) const {
		return Vector3(x + a.x, y + a.y, z + a.z);
	}

	// ���Z
	Vector3 operator -(const Vector3& a) const {
		return Vector3(x - a.x, y - a.y, z - a.z);
	}

	// ��Z
	Vector3 operator *(float a) const {
		return Vector3(x * a, y * a, z * a);
	}

	// ���Z
	Vector3 operator /(float a) const {
		float oneOverA = 1.0f / a;
		return Vector3(x * oneOverA, y * oneOverA, z * oneOverA);
	}

	// �x�N�g���Ƃ̉��Z�E
	Vector3& operator +=(const Vector3& a) {
		x += a.x; y += a.y; z += a.z;
		return *this;
	}


	// �x�N�g���Ƃ̌��Z
	Vector3& operator -=(const Vector3& a) {
		x -= a.x; y -= a.y; z -= a.z;
		return *this;
	}


	// �X�J���[�Ƃ̏�Z
	Vector3& operator*=(float a) {
		x *= a; y *= a; z *= a;
		return *this;
	}

	// �X�J���[�Ƃ̏��Z
	Vector3& operator/=(float a) {
		float oneOverA = 1.0f / a;
		x *= oneOverA; y *= oneOverA; z *= oneOverA;
		return *this;
	}

	// ���K��
	void Normalize() {
		float magSq = x * x + y * y + z * z;
		if (magSq > 0.0f) {
			float oneOverMag = 1.0f / sqrtf(magSq);
			x *= oneOverMag;
			y *= oneOverMag;
			z *= oneOverMag;
		}
	}

	float Length() const {
		return sqrtf(x * x + y * y+z*z);
	}


	// ����
	//float operator *(const Vector3& a) const {
	//	return x * a.x + y * a.y + z * a.z;
	//}

};


// �x�N�g���̑傫�����v�Z
inline float VectorMag(const Vector3& a) {
	return sqrt(a.x * a.x + a.y * a.y + a.z * a.z);
}

// �O�ρi�N���X�ρj
inline Vector3 CrossProduct(const Vector3& a, const Vector3& b) {
	return Vector3(
		a.y * b.z - a.z * b.y,
		a.z * b.x - a.x * b.z,
		a.x * b.y - a.y * b.x
	);
}

// �X�J���[�Ƃ̊|���Z�i������j
inline Vector3 operator*(float k, const Vector3& v) {
	return Vector3(k * v.x, k * v.y, k * v.z);
}

// 2�_�ԋ���
inline float Distance(const Vector3& a, const Vector3& b) {
	float dx = a.x - b.x;
	float dy = a.y - b.y;
	float dz = a.z - b.z;
	return sqrt(dx * dx + dy * dy + dz * dz);
}

// �O���[�o���ȃ[���x�N�g��
extern const Vector3 kZeroVector;