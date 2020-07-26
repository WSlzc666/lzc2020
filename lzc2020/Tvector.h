#ifndef tvector_h

#define tvector_h

#include <iostream>
using namespace std;
#include <math.h>
#include "mathex.h"

class TRay;


//��ά����
class TVector {
	public:
		// ״̬����ö��
		enum TStatus { INVALID, DEFAULT, UNIT };

	private:
		double _x, _y, _z; //���� { x, y, z }
		TStatus _Status;  //����״̬

		// ���캯��
		TVector(double x, double y, double z, TStatus s) : _x(x), _y(y), _z(z), _Status(s) {}

	public:

		// ���캯��
		TVector() : _x(0.0), _y(0.0), _z(0.0), _Status(INVALID) {}
		TVector(double x, double y, double z) : _x(x), _y(y), _z(z), _Status(DEFAULT) {}

		// ������֮����е�
		TVector(const TRay &line1, const TRay &line2);

		double X() const { return _x; }  //�������� x ֵ
		double Y() const { return _y; }  //�������� y ֵ
		double Z() const { return _z; }  //�������� z ֵ
		int isUnit() const { return _Status==UNIT; }          //�ж�����״̬
		int isDefault() const { return _Status==DEFAULT; }    //�ж�����״̬
		int isValid() const { return _Status!=INVALID; }      //�ж�����״̬

		// ��������״̬
		TVector &unit();
		static TVector &unit(const TVector &v, TVector &result) { result = v; return result.unit(); }
		static TVector unit(const TVector &v) { return TVector(v).unit(); }

		TVector &Default();
		static TVector Default(const TVector &v, TVector &result) { result = v; return result.Default(); }
		static TVector Default(const TVector &v) { return TVector(v).Default(); }

		// ��С
		double mag() const { return (isValid() ? (isUnit() ? 1.0 : sqrt(sqr(X()) + sqr(Y()) + sqr(Z()))) : 0.0); }
		double magSqr() const { return (isValid() ? (isUnit() ? 1.0 : sqr(X()) + sqr(Y()) + sqr(Z())) : 0.0); }

		// �������
		double dot(const TVector &v) const { return ((isValid() && v.isValid()) ? (X()*v.X() + Y()*v.Y() + Z()*v.Z()) : 0.0); }
		static double dot(const TVector &v1, const TVector &v2) { return v1.dot(v2); }
		
		// �����������֮��ľ���
		double dist(const TVector &v) const { return (*this-v).mag(); }
		double distSqr(const TVector &v) const { return (*this-v).magSqr(); }

		// �������㣺�ӡ�������ˡ�ȡ�����Ŵ�
		static TVector &add(const TVector &v1, const TVector &v2, TVector &result);
		static TVector &subtract(const TVector &v1, const TVector &v2, TVector &result);
		static TVector &cross(const TVector &v1, const TVector &v2, TVector &result);
		static TVector &invert(const TVector &v1, TVector &result);
		static TVector &multiply(const TVector &v1, const double &scale, TVector &result);
		
		// ��������֮���������
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

