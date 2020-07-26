#ifndef tvector_h

#define tvector_h

#include <iostream>
using namespace std;
#include <math.h>
#include "mathex.h"

class TRay;


//三维向量
class TVector {
	public:
		// 状态类型枚举
		enum TStatus { INVALID, DEFAULT, UNIT };

	private:
		double _x, _y, _z; //向量 { x, y, z }
		TStatus _Status;  //向量状态

		// 构造函数
		TVector(double x, double y, double z, TStatus s) : _x(x), _y(y), _z(z), _Status(s) {}

	public:

		// 构造函数
		TVector() : _x(0.0), _y(0.0), _z(0.0), _Status(INVALID) {}
		TVector(double x, double y, double z) : _x(x), _y(y), _z(z), _Status(DEFAULT) {}

		// 两条线之间的中点
		TVector(const TRay &line1, const TRay &line2);

		double X() const { return _x; }  //返回向量 x 值
		double Y() const { return _y; }  //返回向量 y 值
		double Z() const { return _z; }  //返回向量 z 值
		int isUnit() const { return _Status==UNIT; }          //判断向量状态
		int isDefault() const { return _Status==DEFAULT; }    //判断向量状态
		int isValid() const { return _Status!=INVALID; }      //判断向量状态

		// 更改向量状态
		TVector &unit();
		static TVector &unit(const TVector &v, TVector &result) { result = v; return result.unit(); }
		static TVector unit(const TVector &v) { return TVector(v).unit(); }

		TVector &Default();
		static TVector Default(const TVector &v, TVector &result) { result = v; return result.Default(); }
		static TVector Default(const TVector &v) { return TVector(v).Default(); }

		// 大小
		double mag() const { return (isValid() ? (isUnit() ? 1.0 : sqrt(sqr(X()) + sqr(Y()) + sqr(Z()))) : 0.0); }
		double magSqr() const { return (isValid() ? (isUnit() ? 1.0 : sqr(X()) + sqr(Y()) + sqr(Z())) : 0.0); }

		// 向量点乘
		double dot(const TVector &v) const { return ((isValid() && v.isValid()) ? (X()*v.X() + Y()*v.Y() + Z()*v.Z()) : 0.0); }
		static double dot(const TVector &v1, const TVector &v2) { return v1.dot(v2); }
		
		// 两个向量或点之间的距离
		double dist(const TVector &v) const { return (*this-v).mag(); }
		double distSqr(const TVector &v) const { return (*this-v).magSqr(); }

		// 向量运算：加、减、叉乘、取反、放大
		static TVector &add(const TVector &v1, const TVector &v2, TVector &result);
		static TVector &subtract(const TVector &v1, const TVector &v2, TVector &result);
		static TVector &cross(const TVector &v1, const TVector &v2, TVector &result);
		static TVector &invert(const TVector &v1, TVector &result);
		static TVector &multiply(const TVector &v1, const double &scale, TVector &result);
		
		// 向量运算之运算符重载
		TVector operator-() const { TVector uu;return invert(*this, uu);}
		TVector &operator+=(const TVector &v) { return add(*this, v, *this); }
		TVector &operator-=(const TVector &v) { return subtract(*this, v, *this); }
		TVector &operator*=(const TVector &v) { TVector tv(*this); return cross(tv, v, *this); }
		TVector &operator*=(const double &scale) { return multiply(*this, scale, *this); }
		TVector operator+(const TVector &v) const { TVector tv; return add(*this, v, tv); }
		TVector operator-(const TVector &v) const { TVector tv; return subtract(*this, v, tv); }
		TVector operator*(const TVector &v) const { TVector tv; return cross(*this, v, tv); }
		TVector operator*(const double &scale) const { TVector tv; return multiply(*this, scale, tv); }
};
#endif

