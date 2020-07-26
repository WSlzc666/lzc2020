#ifndef tray_h

#define tray_h

#include <iostream>
#include "mathex.h"
#include "tvector.h"

// ����
class TRay
{
	private:
		TVector _P; //���ϵĵ�
		TVector _V; //�ߵķ���
	public:
		//���캯��
		TRay() {}
		// ���㹹�ɵ��߻����������ɵ���
		TRay(const TVector &point1, const TVector &point2);

		// ���ڵ�
		bool adjacentPoints(const TRay &ray, TVector &point1, TVector &point2) const;
		// ȡ��
		static TRay &invert(const TRay &r, TRay &result) { result._P = r._P; TVector::invert(r._V, result._V); return result; }
		// ���������
		TRay operator-() const { TRay cc; return invert(*this, cc); }

		TVector P() const { return _P; }//���ϵ��κε�
		TVector V() const { return _V; }//�ߵķ���

		// �Ƿ���Ч
		int isValid() const { return V().isUnit() && P().isValid(); }
		// �����֮��ľ���
		double dist(const TRay &ray) const;
		double dist(const TVector &point) const;
};
#endif

