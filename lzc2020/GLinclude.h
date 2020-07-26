#ifndef glinclude_h
#define glinclude_h

#include <windows.h>		// Windows的头文件
#include <math.h>			// 数学库头文件
#include <stdio.h>			// 标准I / O例程的头文件
#include <stdlib.h>			// 标准库的头文件
#include <gl\gl.h>			// OpenGL32库的头文件
#include <gl\glu.h>			// GLu32库的头文件
#include <mmsystem.h>
#include <vector>
#include "stb_image.h"
#include "tvector.h"
#include "tmatrix.h"
#include "tray.h"
#include "Image.h"

#pragma comment( lib, "winmm.lib" )

GLfloat spec[] = { 1.0, 1.0 ,1.0 ,1.0 };      //设置球的镜面高光
GLfloat posl[] = { 0,400,0,1 };               //光源位置
GLfloat amb[] = { 0.2f, 0.2f, 0.2f ,1.0f };   //全局环境
GLfloat amb2[] = { 0.3f, 0.3f, 0.3f ,1.0f };  //光源环境

TVector dir(0, 0, -10);                     //相机的初始方向
TVector pos(0, -50, 1000);                  //相机的初始位置
float camera_rotation = 0;                  //保持绕Y轴的旋转


TVector veloc(0.5, -0.1, 0.5);              //球的初始速度
TVector accel(0, -0.05, 0);                 //加速即 球的重力

TVector ArrayVel[10];                     //保持球的速度
TVector ArrayPos[10];                     //球的位置
TVector OldPos[10];                       //球的旧位置
int NrOfBalls;                            //设置球数
double Time = 0.6;                        //模拟的时间步
int hook_toball1 = 0, sounds = 1;         //挂载相机，声音开关
//墙面结构
struct Plane {
	TVector _Position;
	TVector _Normal;
};
//圆柱结构
struct Cylinder {
	TVector _Position;
	TVector _Axis;
	double _Radius;
};
//"闪耀"结构                                      
struct Explosion {
	TVector _Position;
	float   _Alpha; //Alpha变为0，则爆炸效果不可见
	float   _Scale; //缩放
};

Plane pl1, pl2, pl3, pl4, pl5;            //房间的5个平面
Cylinder cyl1, cyl2, cyl3;                //房间的3个圆柱体
GLUquadricObj *cylinder_obj;              //渲染圆柱体的二次对象
GLuint texture[4], dlist;                 //存储纹理对象并显示列表
Explosion ExplosionArray[20];             //一次最多可容纳20次爆炸

HDC				hDC = NULL;			//专用GDI设备上下文
HGLRC			hRC = NULL;			//永久渲染上下文
HWND			hWnd = NULL;		//保留窗口句柄
HINSTANCE		hInstance;			//保存应用程序的实例

DEVMODE			DMsaved;			//保存以前的屏幕设置（新）

bool			keys[256];			//用于键盘事件的数组
bool			active = TRUE;		//默认情况下，窗口活动标志设置为TRUE
bool			fullscreen = TRUE;	//全屏标志默认设置为全屏模式
#endif //!glinclude_h