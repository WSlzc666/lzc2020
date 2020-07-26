#ifndef mathex_h

#define mathex_h

#include <math.h>

#define EPSILON 1.0e-8
#define ZERO EPSILON
#define M_PI 3.1415926535

#define VC 1

#if VC

	#define bool int
	#define false 0
	#define true !false

#endif

// 判断 x 是否在区间(lower,upper),并取区间最接近 x 的值
template <class T> inline T limit(const T &x, const T &lower, const T &upper)
{
	if (x < lower) return lower;
	if (x > upper) return upper;
	return x;
}

// 返回 x^2
template <class T> inline T sqr(const T &x)
{
	return x*x;
}

// 弧度转角度
template <class T> inline T RadToDeg(const T &rad)
{
	return (rad * 180.0) / M_PI;
}

// 角度转弧度
template <class T> inline T DegToRad(const T &deg)
{
	return (deg * M_PI) / 180.0;
}
#endif