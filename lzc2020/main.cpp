#include "GLinclude.h"

//������Ժ���
int TestIntersionPlane(const Plane& plane,const TVector& position,const TVector& direction, double& lamda, TVector& pNormal);
int TestIntersionCylinder(const Cylinder& cylinder,const TVector& position,const TVector& direction, double& lamda, TVector& pNormal,TVector& newposition);

void LoadGLTextures();                    //�����������
void InitVars();
void idle();

int ProcessKeys();
LRESULT	CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);	// WndProc������

GLvoid ReSizeGLScene(GLsizei width, GLsizei height)		//������С����ʼ��GL����
{
	if (height==0)	height = 1;							//��ֹ�����
	glViewport(0,0,width,height);						//����OpenGL��Ⱦ���ڵĳߴ��С
	glMatrixMode(GL_PROJECTION);						//ѡ��ͶӰ����
	glLoadIdentity();									//����ͶӰ����
	gluPerspective(50.0,(GLfloat)width/(GLfloat)height,10.0,1700.0);
	glMatrixMode(GL_MODELVIEW);							//ѡ��ģ����ͼ����
	glLoadIdentity();									//����ģ����ͼ����
}

// ��ʼ��OpenGL
int InitGL(GLvoid)										// OpenGL���������ö�������
{
   	float df=100.0;
	glClearDepth(1.0f);	//��Ȼ���������								
	glEnable(GL_DEPTH_TEST);//������Ȳ���
	glDepthFunc(GL_LEQUAL);//��Ȳ��Ե�����
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glClearColor(0,0,0,0);
  	glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
	glShadeModel(GL_SMOOTH);
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);//������Ȳ���
	//���ò���
	glMaterialfv(GL_FRONT,GL_SPECULAR,spec);
	glMaterialfv(GL_FRONT,GL_SHININESS,&df);
	glEnable(GL_LIGHTING);
	glLightfv(GL_LIGHT0,GL_POSITION,posl);
	glLightfv(GL_LIGHT0,GL_AMBIENT,amb2);
	glEnable(GL_LIGHT0);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT,amb);
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT,GL_AMBIENT_AND_DIFFUSE);
	glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	glEnable(GL_TEXTURE_2D);
    LoadGLTextures();
	//ǽ��
    glNewList(dlist=glGenLists(1), GL_COMPILE);
    glBegin(GL_QUADS);
	glRotatef(-45,0,1,0);
	glNormal3f(0,0,1);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-50,-40,0);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(50,-40,0);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(50,40,0);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-50,40,0);
    glNormal3f(0,0,-1);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-50,40,0);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(50,40,0);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(50,-40,0);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-50,-40,0);
	glNormal3f(1,0,0);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(0,-40,50);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(0,-40,-50);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(0,40,-50);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(0,40,50);
    glNormal3f(-1,0,0);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(0,40,50);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(0,40,-50);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(0,-40,-50);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(0,-40,50);
	glEnd();
    glEndList();
	return TRUE;										// ��ʼ���ɹ�
}

// ��������ͼ�εĺ���
int DrawGLScene(GLvoid)
{								
	int i;
	glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    ////���������Ϊhookmode 
	if (hook_toball1){
		TVector unit_followvector=ArrayVel[0];
		unit_followvector.unit();
 		gluLookAt(ArrayPos[0].X()+250,ArrayPos[0].Y()+250 ,ArrayPos[0].Z(), ArrayPos[0].X()+ArrayVel[0].X() ,ArrayPos[0].Y()+ArrayVel[0].Y() ,ArrayPos[0].Z()+ArrayVel[0].Z() ,0,1,0);  
    }
	else
	    gluLookAt(pos.X(),pos.Y(),pos.Z(), pos.X()+dir.X(),pos.Y()+dir.Y(),pos.Z()+dir.Z(), 0,1.0,0.0);
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glRotatef(camera_rotation,0,1,0);
	//��Ⱦ��
	for (i=0;i<NrOfBalls;i++){
		switch(i){
        case 1: glColor3f(1.0f,1.0f,1.0f);break;
		case 2: glColor3f(1.0f,1.0f,0.0f);break;
		case 3: glColor3f(0.0f,1.0f,1.0f);break;
		case 4: glColor3f(0.0f,1.0f,0.0f);break;
		case 5: glColor3f(0.0f,0.0f,1.0f);break;
		case 6: glColor3f(0.65f,0.2f,0.3f);break;
		case 7: glColor3f(1.0f,0.0f,1.0f);break;
		case 8: glColor3f(0.0f,0.7f,0.4f);break;
		default: glColor3f(1.0f,0.0f,0.0f);
		}
		glPushMatrix();
		glTranslated(ArrayPos[i].X(),ArrayPos[i].Y(),ArrayPos[i].Z());
		gluSphere(cylinder_obj,20,20,20);
		glPopMatrix();
	}
	glEnable(GL_TEXTURE_2D);
	//ʹ��������Ⱦǽ��
	glBindTexture(GL_TEXTURE_2D, texture[3]); 
	glColor3f(1, 1, 1);
	glBegin(GL_QUADS);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(320,320,320);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(320,-320,320);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-320,-320,320);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-320,320,320);
        
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-320,320,-320);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-320,-320,-320);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(320,-320,-320);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(320,320,-320);
    
	glTexCoord2f(1.0f, 0.0f); glVertex3f(320,320,-320);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(320,-320,-320);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(320,-320,320);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(320,320,320);
	
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-320,320,320);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-320,-320,320);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-320,-320,-320);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-320,320,-320);
	glEnd();

	//����ɫ��Ⱦ�ذ�ƽ��
	glBindTexture(GL_TEXTURE_2D, texture[2]); 
    glBegin(GL_QUADS);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-320,-320,320);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(320,-320,320);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(320,-320,-320);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-320,-320,-320);
	glEnd();

	//��ȾԲ��
	glBindTexture(GL_TEXTURE_2D, texture[0]);
	glColor3f(0.5,0.5,0.5);
    glPushMatrix();
	glRotatef(90, 1,0,0);
	glTranslatef(0,0,-500);
	gluCylinder(cylinder_obj, 60, 60, 1000, 20, 2);
	glPopMatrix();

  	glPushMatrix();
  	glTranslatef(200,-300,-500);
	gluCylinder(cylinder_obj, 60, 60, 1000, 20, 2);
	glPopMatrix();

	glPushMatrix();
    glTranslatef(-200,0,0);
	glRotatef(135, 1,0,0);
	glTranslatef(0,0,-500);
	gluCylinder(cylinder_obj, 30, 30, 1000, 20, 2);
	glPopMatrix();
	
	//��Ⱦ��ײЧ��
	glEnable(GL_BLEND);//ʹ�û��
	glDepthMask(GL_FALSE);//������Ȼ���
    glBindTexture(GL_TEXTURE_2D, texture[1]);//��������   
	for(i=0; i<20; i++)//��Ⱦ20����ըЧ��
	{
		if(ExplosionArray[i]._Alpha>=0)
		{
		   glPushMatrix();
           ExplosionArray[i]._Alpha-=0.01f; //����alpha
		   ExplosionArray[i]._Scale+=0.03f; //��������
		   //������ɫ
		   glColor4f(1,1,0,ExplosionArray[i]._Alpha);	 
		   glScalef(ExplosionArray[i]._Scale,ExplosionArray[i]._Scale,ExplosionArray[i]._Scale);
           //����λ��
		   glTranslatef((float)ExplosionArray[i]._Position.X()/ExplosionArray[i]._Scale, (float)ExplosionArray[i]._Position.Y()/ExplosionArray[i]._Scale, (float)ExplosionArray[i]._Position.Z()/ExplosionArray[i]._Scale);
           glCallList(dlist);//������ʾ�б���Ʊ�ըЧ��
	       glPopMatrix();
		}
	}
	glDepthMask(GL_TRUE);
	glDisable(GL_BLEND);
    glDisable(GL_TEXTURE_2D);
	return TRUE;										// ����
}

GLvoid KillGLWindow(GLvoid)//�رմ���
{
	if (fullscreen){ //�ж��Ƿ���ȫ��ģʽ
		if (!ChangeDisplaySettings(NULL,CDS_TEST)) { 
			ChangeDisplaySettings(NULL,CDS_RESET);
			ChangeDisplaySettings(&DMsaved,CDS_RESET);	// ���Ĳ�����
		} else {
			ChangeDisplaySettings(NULL,CDS_RESET);
		}
		ShowCursor(TRUE);//��ʾ���ָ��	
	}

	if (hRC) {
		if (!wglMakeCurrent(NULL,NULL))	
			MessageBox(NULL,"�ͷ�DC��RCʧ��", "3D-Collision��ʾ:",MB_OK | MB_ICONINFORMATION);

		if (!wglDeleteContext(hRC))//ɾ��RC
			MessageBox(NULL,"������Ⱦ������ʧ�ܡ�", "3D-Collision��ʾ:",MB_OK | MB_ICONINFORMATION);
		hRC=NULL;
	}
	if (hDC && !ReleaseDC(hWnd,hDC)) {	
		MessageBox(NULL,"�ͷ��豸������ʧ��", "3D-Collision��ʾ:",MB_OK | MB_ICONINFORMATION);
		hDC=NULL;
	}
	if (hWnd && !DestroyWindow(hWnd))//���ٴ���
	{
		MessageBox(NULL,"�޷��ͷ�hWnd", "3D-Collision��ʾ:",MB_OK | MB_ICONINFORMATION);
		hWnd=NULL;	
	}
	if (!UnregisterClass("OpenGL",hInstance))//ȡ��������
	{
		MessageBox(NULL,"�޷�ȡ��������", "3D-Collision��ʾ:",MB_OK | MB_ICONINFORMATION);
		hInstance=NULL;	
	}
}

/*  ����OpenGL����->����Ϊ��                    *
 *  title - �����ڴ��ڶ����ı���                             *
 *  width - GL���ڻ�ȫ��ģʽ�Ŀ��                           *
 *  height - GL���ڻ�ȫ��ģʽ�ĸ߶�                          *
 *  bits - ������ɫ��λ����8 / 16 / 24 / 32��                *
 *  fullscreenflag - ʹ��ȫ��ģʽ��TRUE���򴰿�ģʽ��FALSE�� */
BOOL CreateGLWindow(const char* title, int width, int height, int bits, bool fullscreenflag)
{
	int wx = 360, wy = 160;
	if (fullscreenflag) {
		width = 1366;
		height = 768;
		wx = 0, wy = 0;
	}
	GLuint		PixelFormat;			// Holds The Results After Searching For A Match
	WNDCLASS	wc;						// Windows Class Structure
	DWORD		dwExStyle;				// Window Extended Style
	DWORD		dwStyle;				// Window Style
	RECT		WindowRect;				// Grabs Rectangle Upper Left / Lower Right Values
	WindowRect.left=(long)0;			// Set Left Value To 0
	WindowRect.right=(long)width;		// Set Right Value To Requested Width
	WindowRect.top=(long)0;				// Set Top Value To 0
	WindowRect.bottom=(long)height;		// Set Bottom Value To Requested Height

	fullscreen=fullscreenflag;			// Set The Global Fullscreen Flag

	hInstance			= GetModuleHandle(NULL);				// Grab An Instance For Our Window
	wc.style			= CS_HREDRAW | CS_VREDRAW | CS_OWNDC;	// Redraw On Size, And Own DC For Window.
	wc.lpfnWndProc		= (WNDPROC) WndProc;					// WndProc Handles Messages
	wc.cbClsExtra		= 0;									// No Extra Window Data
	wc.cbWndExtra		= 0;									// No Extra Window Data
	wc.hInstance		= hInstance;							// Set The Instance
	wc.hIcon			= LoadIcon(NULL, IDI_WINLOGO);			// Load The Default Icon
	wc.hCursor			= LoadCursor(NULL, IDC_ARROW);			// Load The Arrow Pointer
	wc.hbrBackground	= NULL;									// No Background Required For GL
	wc.lpszMenuName		= NULL;									// We Don't Want A Menu
	wc.lpszClassName	= "OpenGL";								// Set The Class Name
	
	EnumDisplaySettings(NULL, ENUM_CURRENT_SETTINGS, &DMsaved); // save the current display state (NEW)

	if (fullscreen)												// Attempt Fullscreen Mode?
	{
		DEVMODE dmScreenSettings;								// Device Mode
		memset(&dmScreenSettings,0,sizeof(dmScreenSettings));	// Makes Sure Memory's Cleared
		dmScreenSettings.dmSize=sizeof(dmScreenSettings);		// Size Of The Devmode Structure
		dmScreenSettings.dmPelsWidth	= width;				// Selected Screen Width
		dmScreenSettings.dmPelsHeight	= height;				// Selected Screen Height
		dmScreenSettings.dmBitsPerPel	= bits;					// Selected Bits Per Pixel
		dmScreenSettings.dmFields=DM_BITSPERPEL|DM_PELSWIDTH|DM_PELSHEIGHT;

		//����������ѡģʽ����ȡ���
		if (ChangeDisplaySettings(&dmScreenSettings,CDS_FULLSCREEN)==DISP_CHANGE_SUCCESSFUL)
		{
			if (MessageBox(NULL,"PC��֧�ֳ���ȫ��ģʽ�����ô���ģʽ��","3D-Collision��ʾ:",MB_YESNO|MB_ICONEXCLAMATION)==IDYES)
				fullscreen=FALSE;
			else
			{
				MessageBox(NULL,"���д��󣬳���Ҫ�ر�","3D-Collision��ʾ:",MB_OK|MB_ICONSTOP);
				return FALSE;									// Return FALSE
			}
		}
	}

	if (!RegisterClass(&wc))
	{   MessageBox(NULL,"���д����޷�ע�ᴰ����", "3D-Collision��ʾ:",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;
	}

	if (fullscreen)	//ȫ��ģʽ
	{
		dwExStyle=WS_EX_APPWINDOW;//������չ��ʽ
		dwStyle=WS_POPUP;// Windows Style
		ShowCursor(FALSE);//�������ָ��
	}
	else
	{   dwExStyle=WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;
		dwStyle=WS_OVERLAPPEDWINDOW;
	}
	//�����ڵ���Ϊ�����������С
	AdjustWindowRectEx(&WindowRect, dwStyle, FALSE, dwExStyle);
	// Create The Window
	if (!(hWnd=CreateWindowEx(	dwExStyle,//���ڵ���չ��ʽ
								"OpenGL",//����
								title,
								dwStyle | //����Ĵ�����ʽ
								WS_CLIPSIBLINGS | 
								WS_CLIPCHILDREN,
								wx, wy,//����λ��
								WindowRect.right-WindowRect.left,
								WindowRect.bottom-WindowRect.top,
								NULL,//û�и�����
								NULL,//û�в˵�	
								hInstance,
								NULL)))	//not -> WM_CREATE
	{
		KillGLWindow();
		MessageBox(NULL,"���д��󣬴��ڴ���ʧ��", "3D-Collision��ʾ:",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;
	}

	static	PIXELFORMATDESCRIPTOR pfd=	// pfd��֪������ʲô
	{
		sizeof(PIXELFORMATDESCRIPTOR),	// Size
		1,								// �汾��
		PFD_DRAW_TO_WINDOW |			// ��ʽ����֧�ִ���
		PFD_SUPPORT_OPENGL |			
		PFD_DOUBLEBUFFER,				//����֧��˫����
		PFD_TYPE_RGBA,					//����RGBA��ʽ
		bits,							// ��ɫ���
		0, 0, 0, 0, 0, 0,				//������ɫλ
		0,								//û��Alpha������
		0,						//������λλ
		0,						//û���ۻ�������
		0, 0, 0, 0,				//�����ۻ�λ
		16,						// 16Bit Z����������Ȼ�������
		0,						//û��ģ�建����
		0,						//û�и���������
		PFD_MAIN_PLANE,			//����ͼ��
		0,						// Reserved
		0, 0, 0	
	};
	
	if (!(hDC=GetDC(hWnd)))
	{   KillGLWindow();
		MessageBox(NULL,"���д����޷�����GL�豸������", "3D-Collision��ʾ:",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;
	}

	if (!(PixelFormat=ChoosePixelFormat(hDC,&pfd)))	
	{
		KillGLWindow();
		MessageBox(NULL,"���д����Ҳ������ʵ����ظ�ʽ", "3D-Collision��ʾ:",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;
	}

	if(!SetPixelFormat(hDC,PixelFormat,&pfd))
	{
		KillGLWindow();	
		MessageBox(NULL,"���д����޷�����PixelFormat", "3D-Collision��ʾ:",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;
	}

	if (!(hRC=wglCreateContext(hDC)))
	{
		KillGLWindow();
		MessageBox(NULL,"���д����޷�����GL��Ⱦ������", "3D-Collision��ʾ:",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;
	}

	if(!wglMakeCurrent(hDC,hRC))
	{   KillGLWindow();
		MessageBox(NULL,"���д����޷�����GL��Ⱦ������", "3D-Collision��ʾ:",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;
	}

	ShowWindow(hWnd,SW_SHOW);//��ʾ����
	SetForegroundWindow(hWnd);
	SetFocus(hWnd);
	ReSizeGLScene(width, height);					// Set Up Our Perspective GL Screen

    if (!InitGL())
	{   KillGLWindow();	
		MessageBox(NULL,"��ʼ��ʧ��", "3D-Collision��ʾ:",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;}
	return TRUE;									// �ɹ�
}

//wParam��ֵΪ���°�����������룬lParam��洢���������״̬��Ϣ��
LRESULT CALLBACK WndProc(	HWND	hWnd,			// ���ڵľ��
							UINT	uMsg,			// ������ϢID
							WPARAM	wParam,			// ������Ϣ��Ϣ
							LPARAM	lParam)			// ������Ϣ��Ϣ
{
	switch (uMsg)									//��鴰����Ϣ
	{
		case WM_ACTIVATE:							//ע�ⴰ�ڼ�����Ϣ
		{
			if (!HIWORD(wParam))					// Check Minimization State
				active=TRUE;						// Program Is Active
			else
				active=FALSE;						// Program Is No Longer Active
			return 0;								// Return To The Message Loop
		}
		case WM_SYSCOMMAND:							//����ϵͳ����
		{
			switch (wParam)							// Check System Calls
			{
				case SC_SCREENSAVE:					// Screensaver Trying To Start?
				case SC_MONITORPOWER:				// Monitor Trying To Enter Powersave?
				return 0;							// Prevent From Happening
			}
			break;
		}
		case WM_CLOSE:{PostQuitMessage(0);return 0;}
		case WM_KEYDOWN:   //����
		{keys[wParam] = TRUE;return 0;}
		case WM_KEYUP://�ͷ�
		{keys[wParam] = FALSE;return 0;}
		case WM_SIZE:	//����OpenGL���ڵĴ�С
		{ReSizeGLScene(LOWORD(lParam),HIWORD(lParam));  // LoWord=Width, HiWord=Height
			return 0;}
	}
	//������δ�������Ϣ���ݸ�DefWindowProc
	return DefWindowProc(hWnd,uMsg,wParam,lParam);
}

/*
�������ں���
*/
int WINAPI WinMain(	HINSTANCE	hInstance,			// ʵ��
					HINSTANCE	hPrevInstance,		// ��ǰʵ��
					LPSTR		lpCmdLine,			// �����в���
					int			nCmdShow)			// ������ʾ״̬
{
	MSG		msg;									// ������Ϣ�ṹ
	BOOL	done=FALSE;								// �Ƿ��˳�ѭ���ı���

	// ѯ�ʴ���ģʽ
	if (MessageBox(NULL,"�Ƿ�Ҫ��ȫ��ģʽ������?", "3D-Collision��ʾ:",MB_YESNO|MB_ICONQUESTION)==IDNO)
	{
		fullscreen=FALSE;							//����ģʽ
	}

	InitVars();                                     // ��ʼ������
	
	// ����OpenGL����
	if (!CreateGLWindow("3D-Collision",640,480,16,fullscreen))
	{
		return 0;									//��������ʧ�ܣ��˳�Ӧ�ó���
	}

	while(!done)									// �� done = FALSE ��ʼѭ��
	{
		if (PeekMessage(&msg,NULL,0,0,PM_REMOVE))	// ����Ϣ�ȴ�
		{
			/*
			WM_CLOSE���ر�Ӧ�ó��򴰿�
			WM_DESTROY���ر�Ӧ�ó���
			WM_QUIT���ر���Ϣѭ��
			*/
			// �յ��˳���Ϣ
			if (msg.message==WM_QUIT) done=TRUE;	// ���� done=TRUE
			else									// ���򣬴�������Ϣ
			{
				TranslateMessage(&msg);				// ���������Ϣת��Ϊ�ַ���Ϣ
				DispatchMessage(&msg);				// ����Ϣ���͸�����
			}
		}
		else										// û����Ϣ
		    if (active)
			{
				// ���Ƴ��� 
				// ����ESC �˳��滭�ر���Ϣѭ��
				if (keys[VK_ESCAPE]) done=TRUE;							
				else
				{
					idle();
					DrawGLScene();
					SwapBuffers(hDC);
				}
				if (!ProcessKeys()) return 0;
			}
	}
	KillGLWindow();	
    glDeleteTextures(4,texture);
	return (msg.wParam);
}


/*���ҵ�ǰʱ�䲽�У��������Ƿ�˴��ཻ����������������������������Լ�ʱ��*/
int FindBallCol(TVector& point, double& TimePoint, double Time2, int& BallNr1, int& BallNr2)
{
	TVector RelativeV;
	TRay rays;
	// Time2��ʱ��Ĳ�����Add��һ��ʱ�䲽���ֳ���150��СƬ
	double MyTime=0.0, Add=Time2/150.0, Timedummy=10000, Timedummy2=-1;
	TVector posi;
	
	//��150��С���в���������˴�֮������λ��
	for (int i=0;i<NrOfBalls-1;i++)
	{
	 for (int j=i+1;j<NrOfBalls;j++)
	 {	
		    RelativeV=ArrayVel[i]-ArrayVel[j];//��������ľ���
			rays=TRay(OldPos[i],TVector::unit(RelativeV));
			MyTime=0.0;

			// ����������ĵľ������������İ뾶��
			// ����û����ײ��ֱ�ӷ��أ���İ뾶Ӧ����20��
			// �����ײ�������Ļ����������ȷ��ײ����
			if ( (rays.dist(OldPos[j])) > 40) continue; 

			while (MyTime<Time2)// ѭ��������ҵ���ȷ��ײ����
			{
			   MyTime+=Add;// ��һ��ʱ��Ƭ�ֳ�150��
			   posi=OldPos[i]+RelativeV*MyTime;// ��������ÿ��ʱ��Ƭ�ϵ�λ��
			   if (posi.dist(OldPos[j])<=40) {
				   // ����������ĵľ���С��40�����ڸ�ʱ��Ƭ�Ϸ�������ײ
					point=posi;// �����λ�ø���Ϊײ�����λ��
					if (Timedummy>(MyTime-Add)) Timedummy=MyTime-Add;
					BallNr1=i;// ��¼��������������ײ
					BallNr2=j;
					break;
				}
			}
	 }
	}
	if (Timedummy!=10000) { 
		// ���Timedummy<10000��������������ײ��
		// ��¼����ײ������ʱ��
		TimePoint=Timedummy;
	    return 1;
	}
	return 0;
}

/*ģ�����ѭ���ƶ����ҵ���ǰʱ�䲽�ж������ײ����Ӧ��
ģ�⺯����������ײ��������ģ��
*/
void idle()
{
	double rt,rt2,rt4,lamda;
	TVector norm,uveloc;
	TVector normal,point,time;
	double RestTime,BallTime;
	TVector Pos2;
	int BallNr = 0, BallColNr1, BallColNr2;
	TVector Nc;
	//���û�����������ϣ���ת�����
	if (!hook_toball1)
	{
		camera_rotation+=0.1f;
		if (camera_rotation>360)
			camera_rotation=0;
	}
 
	RestTime=Time;
	lamda=1000;
	//�����������ٶ�
	//ʹ��ŷ�����̼�����һ��ʱ�䲽���ٶ�
	for (int j=0;j<NrOfBalls;j++)
	  ArrayVel[j]+=accel*RestTime;

	//�����һ����ģ��ʱ����(������������㣬����������)
	while (RestTime>ZERO)
	{
	   lamda=10000;   //��ʼ��Ϊ�ǳ����ֵ
	
	   //�����������ҵ�����ƽ��/Բ����֮����ӽ��Ľ���
   	   for (int i=0;i<NrOfBalls;i++)
	   {
		      //�����µ�λ�ú��ƶ��ľ���
			  OldPos[i]=ArrayPos[i];
			  TVector::unit(ArrayVel[i],uveloc);
			  ArrayPos[i]=ArrayPos[i]+ArrayVel[i]*RestTime;
			  rt2=OldPos[i].dist(ArrayPos[i]);
			  //�����Ƿ��ǽ����ײ
			  if (TestIntersionPlane(pl1,OldPos[i],uveloc,rt,norm))
			  {  
				  //������ײ��ʱ��
				  rt4=rt*RestTime/rt2;

				  //���С�ڵ�ǰ�������ײʱ�䣬�������
				  if (rt4<=lamda)
				  { 
				    if (rt4<=RestTime+ZERO)
						if (! ((rt<=ZERO)&&(uveloc.dot(norm)>ZERO)) )
						{
						normal=norm;
						point=OldPos[i]+uveloc*rt;
						lamda=rt4;
						BallNr=i;
						}
				  }
			  }
			  
			  if (TestIntersionPlane(pl2,OldPos[i],uveloc,rt,norm))
			  {
				   rt4=rt*RestTime/rt2;

				  if (rt4<=lamda)
				  { 
				    if (rt4<=RestTime+ZERO)
						if (! ((rt<=ZERO)&&(uveloc.dot(norm)>ZERO)) )
						 {
							normal=norm;
							point=OldPos[i]+uveloc*rt;
							lamda=rt4;
							BallNr=i;
						 }
				  }
				 
			  }

			  if (TestIntersionPlane(pl3,OldPos[i],uveloc,rt,norm))
			  {
			      rt4=rt*RestTime/rt2;

				  if (rt4<=lamda)
				  { 
				    if (rt4<=RestTime+ZERO)
						if (! ((rt<=ZERO)&&(uveloc.dot(norm)>ZERO)) )
						 {
							normal=norm;
							point=OldPos[i]+uveloc*rt;
							lamda=rt4;
							BallNr=i;
						 }
				  }
			  }

			  if (TestIntersionPlane(pl4,OldPos[i],uveloc,rt,norm))
			  {
				  rt4=rt*RestTime/rt2;

				  if (rt4<=lamda)
				  { 
				    if (rt4<=RestTime+ZERO)
						if (! ((rt<=ZERO)&&(uveloc.dot(norm)>ZERO)) )
						 {
							normal=norm;
							point=OldPos[i]+uveloc*rt;
							lamda=rt4;
							BallNr=i;
						 }
				  }
			  }

			  if (TestIntersionPlane(pl5,OldPos[i],uveloc,rt,norm))
			  {
				  rt4=rt*RestTime/rt2;
				  if (rt4<=lamda)
				  {  if (rt4<=RestTime+ZERO)
						if (! ((rt<=ZERO)&&(uveloc.dot(norm)>ZERO)) )
						 {
							normal=norm;
							point=OldPos[i]+uveloc*rt;
							lamda=rt4;
							BallNr=i;
						 }
				  }
			  }

              //�����Ƿ�������Բ����ײ
			  if (TestIntersionCylinder(cyl1,OldPos[i],uveloc,rt,norm,Nc))
			  {   //������ײ��ʱ��
				  rt4=rt*RestTime/rt2;
				  //���С�ڵ�ǰ�������ײʱ�䣬�������
				  if (rt4<=lamda)
				  { 
				    if (rt4<=RestTime+ZERO)
						if (! ((rt<=ZERO)&&(uveloc.dot(norm)>ZERO)) )
						 {
							normal=norm;
							point=Nc;
							lamda=rt4;
							BallNr=i;
						 }
				  }
				 
			  }
			  if (TestIntersionCylinder(cyl2,OldPos[i],uveloc,rt,norm,Nc))
			  {
				  rt4=rt*RestTime/rt2;

				  if (rt4<=lamda)
				  { 
				    if (rt4<=RestTime+ZERO)
						if (! ((rt<=ZERO)&&(uveloc.dot(norm)>ZERO)) )
						 {
							normal=norm;
							point=Nc;
							lamda=rt4;
							BallNr=i;
						 }
				  }
				 
			  }
			  if (TestIntersionCylinder(cyl3,OldPos[i],uveloc,rt,norm,Nc))
			  {
				  rt4=rt*RestTime/rt2;

				  if (rt4<=lamda)
				  { 
				    if (rt4<=RestTime+ZERO)
						if (! ((rt<=ZERO)&&(uveloc.dot(norm)>ZERO)) )
						 {
							normal=norm;
							point=Nc;
							lamda=rt4;
							BallNr=i;
						 }
				  }
				 
			  }
	   }

	   //����ÿ����֮�����ײ�������ײʱ��С�����������ײ�����滻����
	   if (FindBallCol(Pos2,BallTime,RestTime,BallColNr1,BallColNr2))
			  {
				  //������غ�����������
				  if (sounds)
					  PlaySound("Data/Explode.wav",NULL,SND_FILENAME|SND_ASYNC);
			      
				  if ( (lamda==10000) || (lamda>BallTime) )
				  {
					  RestTime=RestTime-BallTime;
					  //����֮�����ײ
					  TVector pb1,pb2,xaxis,U1x,U1y,U2x,U2y,V1x,V1y,V2x,V2y;
					  double a,b;

					  pb1=OldPos[BallColNr1]+ArrayVel[BallColNr1]*BallTime;//��1��λ��
					  pb2=OldPos[BallColNr2]+ArrayVel[BallColNr2]*BallTime;//��2��λ��
					  xaxis=(pb2-pb1).unit();//X_Axis��

					  a=xaxis.dot(ArrayVel[BallColNr1]);//X_AxisͶӰϵ��
					  U1x=xaxis*a;//������X_Axis���ϵ��ٶ�
					  U1y=ArrayVel[BallColNr1]-U1x;//�����ڴ�ֱ���ϵ��ٶ�

					  xaxis=(pb1-pb2).unit();
					  b=xaxis.dot(ArrayVel[BallColNr2]);
      				  U2x=xaxis*b;
					  U2y=ArrayVel[BallColNr2]-U2x;

					  V1x=(U1x+U2x-(U1x-U2x))*0.5;//�����µ��ٶ�
					  V2x=(U1x+U2x-(U2x-U1x))*0.5;
					  V1y=U1y;
					  V2y=U2y;

					  for (int j=0;j<NrOfBalls;j++)//�����������λ��
					  ArrayPos[j]=OldPos[j]+ArrayVel[j]*BallTime;

					  ArrayVel[BallColNr1]=V1x+V1y;//�����µ��ٶ�
					  ArrayVel[BallColNr2]=V2x+V2y;
                      
					  for(int j=0;j<20;j++)
					  {
						  if (ExplosionArray[j]._Alpha<=0)
						  {
							  ExplosionArray[j]._Alpha=1;
                              ExplosionArray[j]._Position=ArrayPos[BallColNr1];
							  ExplosionArray[j]._Scale=1;
							  break;
						  }
					  }
					  continue;
				  }
			  }
			//���Ĳ��ԣ��滻�´���ײ��ʱ�䣬�����±�ըЧ��������
			if (lamda!=10000)
			{		 
				      RestTime-=lamda;

					  for (int j=0;j<NrOfBalls;j++)
					  ArrayPos[j]=OldPos[j]+ArrayVel[j]*lamda;

					  rt2=ArrayVel[BallNr].mag();//�����ٶ�������ģ
					  ArrayVel[BallNr].unit();//��һ���ٶ�����
					  //���㷴������
					  ArrayVel[BallNr]=TVector::unit( (normal*(2*normal.dot(-ArrayVel[BallNr]))) + ArrayVel[BallNr] );
					  ArrayVel[BallNr]=ArrayVel[BallNr]*rt2;
							
					  //���±�ը����
					  for(int j=0;j<20;j++)
					  {
						  if (ExplosionArray[j]._Alpha<=0)
						  {
							  ExplosionArray[j]._Alpha=1;
                              ExplosionArray[j]._Position=point;
							  ExplosionArray[j]._Scale=1;
							  break;
						  }
					  }
			}
			else RestTime=0;

	}

}

// ��ʼ������
void InitVars()
{
	 // 5��ǽ��
	pl1._Position=TVector(0,-300,0);
	pl1._Normal=TVector(0,1,0);
	pl2._Position=TVector(300,0,0);
	pl2._Normal=TVector(-1,0,0);
	pl3._Position=TVector(-300,0,0);
	pl3._Normal=TVector(1,0,0);
	pl4._Position=TVector(0,0,300);
	pl4._Normal=TVector(0,0,-1);
	pl5._Position=TVector(0,0,-300);
	pl5._Normal=TVector(0,0,1);

	// 3��Բ��
	cyl1._Position=TVector(0,0,0);
	cyl1._Axis=TVector(0,1,0);
	cyl1._Radius=60+20;
	cyl2._Position=TVector(200,-300,0);
	cyl2._Axis=TVector(0,0,1);
	cyl2._Radius=60+20;
	cyl3._Position=TVector(-200,0,0);
	cyl3._Axis=TVector(0,1,1);
    cyl3._Axis.unit();
	cyl3._Radius=30+20;
	//�������ζ�������ȾԲ����
	cylinder_obj= gluNewQuadric();
	gluQuadricTexture(cylinder_obj, GL_TRUE);

	//������ĳ�ʼλ�ú��ٶ�
    //����ʼ�����汬ը������
	NrOfBalls=10;//10����
	ArrayVel[0]=veloc;
	ArrayPos[0]=TVector(199,180,10);
	ExplosionArray[0]._Alpha=0;
	ExplosionArray[0]._Scale=1;
	ArrayVel[1]=veloc;
	ArrayPos[1]=TVector(0,150,100);
	ExplosionArray[1]._Alpha=0;
	ExplosionArray[1]._Scale=1;
	ArrayVel[2]=veloc;
	ArrayPos[2]=TVector(-100,180,-100);
	ExplosionArray[2]._Alpha=0;
	ExplosionArray[2]._Scale=1;
	for (int i=3; i<10; i++)
	{
         ArrayVel[i]=veloc;
	     ArrayPos[i]=TVector(-500+i*75, 300, -500+i*50);
		 ExplosionArray[i]._Alpha=0;
	     ExplosionArray[i]._Scale=1;
	}
	for (int i=10; i<20; i++)
	{
         ExplosionArray[i]._Alpha=0;
	     ExplosionArray[i]._Scale=1;
	}
}

//�ж��Ƿ��ƽ���ཻ�����򷵻�1�����򷵻�0
int TestIntersionPlane(const Plane& plane,const TVector& position,const TVector& direction, double& lamda, TVector& pNormal)
{
    double DotProduct=direction.dot(plane._Normal);
	double l2;

	//ȷ�����Ƿ�ƽ����ƽ��
    if ((DotProduct<ZERO)&&(DotProduct>-ZERO)) return 0;
    l2=(plane._Normal.dot(plane._Position-position))/DotProduct;
    if (l2<-ZERO) return 0;
    pNormal=plane._Normal;
	lamda=l2;
    return 1;
}

//�ж��Ƿ��Բ���ཻ�����򷵻�1�����򷵻�0
int TestIntersionCylinder(const Cylinder& cylinder,const TVector& position,const TVector& direction, double& lamda, TVector& pNormal,TVector& newposition)
{
	TVector RC, n, D, O;
	double d, t, s, ln, in, out;
	
	TVector::subtract(position,cylinder._Position,RC);
	TVector::cross(direction,cylinder._Axis,n);
    ln=n.mag();
	if ( (ln<ZERO)&&(ln>-ZERO) ) return 0;
	n.unit();
	d= fabs( RC.dot(n) );

    if (d<=cylinder._Radius)
	{
		TVector::cross(RC,cylinder._Axis,O);
		t= - O.dot(n)/ln;
		TVector::cross(n,cylinder._Axis,O);
		O.unit();
		s= fabs( sqrt(cylinder._Radius*cylinder._Radius - d*d) / direction.dot(O) );

		in=t-s;
		out=t+s;

		if (in<-ZERO){
			if (out<-ZERO) return 0;
			else lamda=out;
		}
		else
        if (out<-ZERO) {
			      lamda=in;
		}
		else
		if (in<out) lamda=in;
		else lamda=out;

    	newposition=position+direction*lamda;
		TVector HB=newposition-cylinder._Position;
		pNormal=HB - cylinder._Axis*(HB.dot(cylinder._Axis));
		pNormal.unit();

		return 1;
	}
    
	return 0;
}

//����λͼ��ת��Ϊ����       
void LoadGLTextures() {	
	LoadTextureFromFile(texture[0],"Data/marble.bmp", true);
	LoadTextureFromFile(texture[1],"Data/spark.bmp", false);
	LoadTextureFromFile(texture[2],"Data/boden.bmp", true);
	LoadTextureFromFile(texture[3],"Data/wand.bmp", false);
};

// ������Ӧ
int ProcessKeys()
{
	// Up Arrow
	if (keys[VK_UP])    pos+=TVector(0,0,-10);
	// Down Arrow
	if (keys[VK_DOWN])  pos+=TVector(0,0,10);
	// Left Arrow
	if (keys[VK_LEFT])  camera_rotation+=10;
	// Right Arrow
	if (keys[VK_RIGHT]) camera_rotation-=10;
	// F5 ��   �����˶�
	if (keys[VK_F5])
	{
		Time+=0.1;keys[VK_F5]=FALSE;
	}
	// F4 ��   ����
	if (keys[VK_F4])
	{
		Time-=0.1;keys[VK_F4]=FALSE;
	}
	// F3 ��  ��������
	if (keys[VK_F3]) 
	{   
		sounds^=1;  //1->0   0->1
        keys[VK_F3]=FALSE;
	}
	// F2 ��  �ӽǸ������˶�
	if (keys[VK_F2])
	{
	    hook_toball1^=1;
	    camera_rotation=0;
		keys[VK_F2]=FALSE;
	}
	// F1 ��
	if (keys[VK_F1])						
	{
		keys[VK_F1]=FALSE;
		KillGLWindow();	
		fullscreen=!fullscreen;
		// �ؽ�OpenGL����
		if (!CreateGLWindow("3D-Collision",640,480,16,fullscreen)){
			return 0;
		}
	}
	return 1;
}
