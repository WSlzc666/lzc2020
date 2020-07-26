#ifndef glinclude_h
#define glinclude_h

#include <windows.h>		// Windows��ͷ�ļ�
#include <math.h>			// ��ѧ��ͷ�ļ�
#include <stdio.h>			// ��׼I / O���̵�ͷ�ļ�
#include <stdlib.h>			// ��׼���ͷ�ļ�
#include <gl\gl.h>			// OpenGL32���ͷ�ļ�
#include <gl\glu.h>			// GLu32���ͷ�ļ�
#include <mmsystem.h>
#include <vector>
#include "stb_image.h"
#include "tvector.h"
#include "tmatrix.h"
#include "tray.h"
#include "Image.h"

#pragma comment( lib, "winmm.lib" )

GLfloat spec[] = { 1.0, 1.0 ,1.0 ,1.0 };      //������ľ���߹�
GLfloat posl[] = { 0,400,0,1 };               //��Դλ��
GLfloat amb[] = { 0.2f, 0.2f, 0.2f ,1.0f };   //ȫ�ֻ���
GLfloat amb2[] = { 0.3f, 0.3f, 0.3f ,1.0f };  //��Դ����

TVector dir(0, 0, -10);                     //����ĳ�ʼ����
TVector pos(0, -50, 1000);                  //����ĳ�ʼλ��
float camera_rotation = 0;                  //������Y�����ת


TVector veloc(0.5, -0.1, 0.5);              //��ĳ�ʼ�ٶ�
TVector accel(0, -0.05, 0);                 //���ټ� �������

TVector ArrayVel[10];                     //��������ٶ�
TVector ArrayPos[10];                     //���λ��
TVector OldPos[10];                       //��ľ�λ��
int NrOfBalls;                            //��������
double Time = 0.6;                        //ģ���ʱ�䲽
int hook_toball1 = 0, sounds = 1;         //�����������������
//ǽ��ṹ
struct Plane {
	TVector _Position;
	TVector _Normal;
};
//Բ���ṹ
struct Cylinder {
	TVector _Position;
	TVector _Axis;
	double _Radius;
};
//"��ҫ"�ṹ                                      
struct Explosion {
	TVector _Position;
	float   _Alpha; //Alpha��Ϊ0����ըЧ�����ɼ�
	float   _Scale; //����
};

Plane pl1, pl2, pl3, pl4, pl5;            //�����5��ƽ��
Cylinder cyl1, cyl2, cyl3;                //�����3��Բ����
GLUquadricObj *cylinder_obj;              //��ȾԲ����Ķ��ζ���
GLuint texture[4], dlist;                 //�洢���������ʾ�б�
Explosion ExplosionArray[20];             //һ����������20�α�ը

HDC				hDC = NULL;			//ר��GDI�豸������
HGLRC			hRC = NULL;			//������Ⱦ������
HWND			hWnd = NULL;		//�������ھ��
HINSTANCE		hInstance;			//����Ӧ�ó����ʵ��

DEVMODE			DMsaved;			//������ǰ����Ļ���ã��£�

bool			keys[256];			//���ڼ����¼�������
bool			active = TRUE;		//Ĭ������£����ڻ��־����ΪTRUE
bool			fullscreen = TRUE;	//ȫ����־Ĭ������Ϊȫ��ģʽ
#endif //!glinclude_h