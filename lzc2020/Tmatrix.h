#ifndef tmatrix_h

#define tmatrix_h

#include <iostream>
#include "mathex.h"

using namespace std;

class TVector;

// 3x3矩阵
class TMatrix33
{
private:
	// 3x3矩阵
	double _Mx[3][3];

public:

	// 3x3矩阵构造函数
	TMatrix33();
	TMatrix33(double Phi, double Theta, double Psi);
	TMatrix33(double mx00, double mx01, double mx02, double mx10, double mx11, double mx12, double mx20, double mx21, double mx22);

	// 返回 矩阵第 Row 行第 Column 列的值
	double operator()(int Row, int Column) const { return _Mx[Row][Column]; }
	double &operator()(int Row, int Column) { return _Mx[Row][Column]; }

	// 矩阵运算函数
	// 矩阵 M1+矩阵M2
	static TMatrix33 &add(const TMatrix33 &m1, const TMatrix33 &m2, TMatrix33 &result);
	// 矩阵 M1-矩阵M2
	static TMatrix33 &subtract(const TMatrix33 &m1, const TMatrix33 &m2, TMatrix33 &result);
	// 矩阵 M1 x M2
	static TMatrix33 &multiply(const TMatrix33 &m1, const TMatrix33 &m2, TMatrix33 &result);
	// 矩阵放大 scale*M1   scale为放大倍数
	static TMatrix33 &multiply(const TMatrix33 &m1, const double &scale, TMatrix33 &result);
	// 矩阵M1 * 向量V ,返回一个向量
	static TVector &multiply(const TMatrix33 &m1, const TVector &v, TVector &result);

	// 运算符重载 矩阵运算
	TMatrix33 &operator+=(const TMatrix33 &m) { return add(*this, m, *this); }
	TMatrix33 &operator-=(const TMatrix33 &m) { return subtract(*this, m, *this); }
	TMatrix33 &operator*=(const TMatrix33 &m) { TMatrix33 tm(*this); return multiply(tm, m, *this); }
	TMatrix33 &operator*=(const double &scale) { return multiply(*this, scale, *this); }
	TMatrix33 operator+(const TMatrix33 &m) const { TMatrix33 tm; return add(*this, m, tm); }
	TMatrix33 operator-(const TMatrix33 &m) const { TMatrix33 tm; return subtract(*this, m, tm); }
	TMatrix33 operator*(const TMatrix33 &m) const { TMatrix33 tm; return multiply(*this, m, tm); }
	TMatrix33 operator*(const double &scale) const { TMatrix33 tm; return multiply(*this, scale, tm); }
	TVector operator*(const TVector &v) const;
	
	// 返回矩阵生成的行列式结果值
	double determinant() const;
	static double determinant(const TMatrix33 &m) { return m.determinant(); }

	// 矩阵转置  M^T
	TMatrix33 &transpose();
	static TMatrix33 &transpose(const TMatrix33 &m, TMatrix33 &result) { result = m; return result.transpose(); }
	static TMatrix33 transpose(const TMatrix33 &m) { return TMatrix33(m).transpose(); }

	// 原矩阵的逆矩阵
	TMatrix33 inverse() const { TMatrix33 tm; return inverse(*this, tm); }
	static TMatrix33 &inverse(const TMatrix33 &m1, TMatrix33 &result);
	static TMatrix33 inverse(const TMatrix33 &m1) { TMatrix33 tm; return inverse(m1, tm); }
};
#endif