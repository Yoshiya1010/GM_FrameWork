#pragma once

#include <math.h>

class Vector3 {
public:
	float x, y, z;

	Vector3() = default;

	// コピーコンストラクタ
	Vector3(const Vector3& a) :x(a.x), y(a.y), z(a.z) {}

	// 3つの値で作成する
	Vector3(float nx, float ny, float nz) :x(nx), y(ny), z(nz) {}

	// 代入
	Vector3& operator=(const Vector3& a) {
		x = a.x;
		y = a.y;
		z = a.z;
		
		return *this;
	}


	// 等しさのチェック
	bool operator ==(const Vector3& a) const {
		return x == a.x && y == a.y && z == a.z;
	}

	bool operator !=(const Vector3& a) const {
		return x != a.x || y != a.y || z != a.z;
	}


	// ベクトル操作

	void Zero() {
		x = y = z = 0.0f;
	}

	// 単項式の-は反転ベクトルを返す
	Vector3 operator -() const { return Vector3(-x, -y, -z); }

	// 加算
	Vector3 operator +(const Vector3& a) const {
		return Vector3(x + a.x, y + a.y, z + a.z);
	}

	// 減算
	Vector3 operator -(const Vector3& a) const {
		return Vector3(x - a.x, y - a.y, z - a.z);
	}

	// 乗算
	Vector3 operator *(float a) const {
		return Vector3(x * a, y * a, z * a);
	}

	// 除算
	Vector3 operator /(float a) const {
		float oneOverA = 1.0f / a;
		return Vector3(x * oneOverA, y * oneOverA, z * oneOverA);
	}

	// ベクトルとの加算・
	Vector3& operator +=(const Vector3& a) {
		x += a.x; y += a.y; z += a.z;
		return *this;
	}


	// ベクトルとの減算
	Vector3& operator -=(const Vector3& a) {
		x -= a.x; y -= a.y; z -= a.z;
		return *this;
	}


	// スカラーとの乗算
	Vector3& operator*=(float a) {
		x *= a; y *= a; z *= a;
		return *this;
	}

	// スカラーとの除算
	Vector3& operator/=(float a) {
		float oneOverA = 1.0f / a;
		x *= oneOverA; y *= oneOverA; z *= oneOverA;
		return *this;
	}

	// 正規化
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


	// 内積
	//float operator *(const Vector3& a) const {
	//	return x * a.x + y * a.y + z * a.z;
	//}

};


// ベクトルの大きさを計算
inline float VectorMag(const Vector3& a) {
	return sqrt(a.x * a.x + a.y * a.y + a.z * a.z);
}

// 外積（クロス積）
inline Vector3 CrossProduct(const Vector3& a, const Vector3& b) {
	return Vector3(
		a.y * b.z - a.z * b.y,
		a.z * b.x - a.x * b.z,
		a.x * b.y - a.y * b.x
	);
}

// スカラーとの掛け算（左から）
inline Vector3 operator*(float k, const Vector3& v) {
	return Vector3(k * v.x, k * v.y, k * v.z);
}

// 2点間距離
inline float Distance(const Vector3& a, const Vector3& b) {
	float dx = a.x - b.x;
	float dy = a.y - b.y;
	float dz = a.z - b.z;
	return sqrt(dx * dx + dy * dy + dz * dz);
}

// グローバルなゼロベクトル
extern const Vector3 kZeroVector;