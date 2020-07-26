#ifndef tray_h

#define tray_h

#include <iostream>
#include "mathex.h"
#include "tvector.h"

// 射线
class TRay
{
	private:
		TVector _P; //线上的点
		TVector _V; //线的方向
	public:
		//构造函数
		TRay() {}
		// 两点构成的线或点和向量构成的线
		TRay(const TVector &point1, const TVector &point2);

		// 相邻点
		bool adjacentPoints(const TRay &ray, TVector &point1, TVector &point2) const;
		// 取反
		static TRay &invert(const TRay &r, TRay &result) { result._P = r._P; TVector::invert(r._V, result._V); return result; }
		// 运算符重载
		TRay operator-() const { TRay cc; return invert(*this, cc); }

		TVector P() const { return _P; }//线上的任何点
		TVector V() const { return _V; }//线的方向

		// 是否有效
		int isValid() const { return V().isUnit() && P().isValid(); }
		// 点和线之间的距离
		double dist(const TRay &ray) const;
		double dist(const TVector &point) const;
};
#endif

