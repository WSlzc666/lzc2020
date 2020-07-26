#include "tvector.h"

#include "tray.h"

// 两条线之间的中点
TVector::TVector(const TRay &ray1, const TRay &ray2) {
	TVector point1, point2;
	if (ray1.adjacentPoints(ray2, point1, point2)) {
		*this = (point1 + point2)*0.5;
	}
	else {
		*this = TVector();
	}
}

// 生成一个UNIT状态向量
TVector &TVector::unit() {
	if (isDefault()) {
		double rep = mag();
		if (rep < EPSILON) {
			_x = 0.0; _y = 0.0; _z = 0.0;
		} else {
			double temp = 1.0 / rep;
			_x *= temp; _y *= temp; _z *= temp;
		}
		_Status = UNIT;
	}
	return *this;
}

// 生成一个DEFAULT状态向量
TVector &TVector::Default() {
	if (isUnit()) {
		_Status = DEFAULT;
	}
	return *this;
}

// 向量V1取反
TVector &TVector::invert(const TVector &v1, TVector &result) {
	if (v1.isValid()) {
		result._x = -v1._x;
		result._y = -v1._y;
		result._z = -v1._z;
		result._Status = v1._Status;
	}
	else {
		result = TVector();
	}
	return result;
}

// 向量V1+向量V2
TVector &TVector::add(const TVector &v1, const TVector &v2, TVector &result) {
	if (v1.isValid() && v2.isValid()) {
		result._x = v1._x + v2._x;
		result._y = v1._y + v2._y;
		result._z = v1._z + v2._z;
		result._Status = DEFAULT;
	}
	else {
		result = TVector();
	}
	return result;
}

// 向量V1-向量V2
TVector &TVector::subtract(const TVector &v1, const TVector &v2, TVector &result) {
	if (v1.isValid() && v2.isValid()) {
		result._x = v1._x - v2._x;
		result._y = v1._y - v2._y;
		result._z = v1._z - v2._z;
		result._Status = DEFAULT;
	}
	else {
		result = TVector();
	}
	return result;
}

// 向量V1叉乘向量V2
TVector &TVector::cross(const TVector &v1, const TVector &v2, TVector &result) {
	if (v1.isValid() && v2.isValid()) {
		result._x = v1._y * v2._z - v1._z * v2._y;
		result._y = v1._z * v2._x - v1._x * v2._z;
		result._z = v1._x * v2._y - v1._y * v2._x;
		result._Status = DEFAULT;
	}
	else {
		result = TVector();
	}
	return result;
}

// 向量V1扩大scale倍
TVector &TVector::multiply(const TVector &v1, const double &scale, TVector &result) {
	if (v1.isValid()) {
		result._x = v1._x * scale;
		result._y = v1._y * scale;
		result._z = v1._z * scale;
		result._Status = DEFAULT;
	}
	else {
		result = TVector();
	}
	return result;
}