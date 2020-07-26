#include "GLinclude.h"

//交叉测试函数
int TestIntersionPlane(const Plane& plane,const TVector& position,const TVector& direction, double& lamda, TVector& pNormal);
int TestIntersionCylinder(const Cylinder& cylinder,const TVector& position,const TVector& direction, double& lamda, TVector& pNormal,TVector& newposition);

void LoadGLTextures();                    //加载纹理对象
void InitVars();
void idle();

int ProcessKeys();
LRESULT	CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);	// WndProc的声明

GLvoid ReSizeGLScene(GLsizei width, GLsizei height)		//调整大小并初始化GL窗口
{
	if (height==0)	height = 1;							//防止被零除
	glViewport(0,0,width,height);						//设置OpenGL渲染窗口的尺寸大小
	glMatrixMode(GL_PROJECTION);						//选择投影矩阵
	glLoadIdentity();									//重置投影矩阵
	gluPerspective(50.0,(GLfloat)width/(GLfloat)height,10.0,1700.0);
	glMatrixMode(GL_MODELVIEW);							//选择模型视图矩阵
	glLoadIdentity();									//重置模型视图矩阵
}

// 初始化OpenGL
int InitGL(GLvoid)										// OpenGL的所有设置都在这里
{
   	float df=100.0;
	glClearDepth(1.0f);	//深度缓冲区设置								
	glEnable(GL_DEPTH_TEST);//启用深度测试
	glDepthFunc(GL_LEQUAL);//深度测试的类型
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glClearColor(0,0,0,0);
  	glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
	glShadeModel(GL_SMOOTH);
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);//启用深度测试
	//设置材质
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
	//墙面
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
	return TRUE;										// 初始化成功
}

// 绘制所有图形的函数
int DrawGLScene(GLvoid)
{								
	int i;
	glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    ////将相机设置为hookmode 
	if (hook_toball1){
		TVector unit_followvector=ArrayVel[0];
		unit_followvector.unit();
 		gluLookAt(ArrayPos[0].X()+250,ArrayPos[0].Y()+250 ,ArrayPos[0].Z(), ArrayPos[0].X()+ArrayVel[0].X() ,ArrayPos[0].Y()+ArrayVel[0].Y() ,ArrayPos[0].Z()+ArrayVel[0].Z() ,0,1,0);  
    }
	else
	    gluLookAt(pos.X(),pos.Y(),pos.Z(), pos.X()+dir.X(),pos.Y()+dir.Y(),pos.Z()+dir.Z(), 0,1.0,0.0);
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glRotatef(camera_rotation,0,1,0);
	//渲染球
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
	//使用纹理渲染墙面
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

	//用颜色渲染地板平面
	glBindTexture(GL_TEXTURE_2D, texture[2]); 
    glBegin(GL_QUADS);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-320,-320,320);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(320,-320,320);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(320,-320,-320);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-320,-320,-320);
	glEnd();

	//渲染圆柱
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
	
	//渲染碰撞效果
	glEnable(GL_BLEND);//使用混合
	glDepthMask(GL_FALSE);//禁用深度缓存
    glBindTexture(GL_TEXTURE_2D, texture[1]);//设置纹理   
	for(i=0; i<20; i++)//渲染20个爆炸效果
	{
		if(ExplosionArray[i]._Alpha>=0)
		{
		   glPushMatrix();
           ExplosionArray[i]._Alpha-=0.01f; //设置alpha
		   ExplosionArray[i]._Scale+=0.03f; //设置缩放
		   //设置颜色
		   glColor4f(1,1,0,ExplosionArray[i]._Alpha);	 
		   glScalef(ExplosionArray[i]._Scale,ExplosionArray[i]._Scale,ExplosionArray[i]._Scale);
           //设置位置
		   glTranslatef((float)ExplosionArray[i]._Position.X()/ExplosionArray[i]._Scale, (float)ExplosionArray[i]._Position.Y()/ExplosionArray[i]._Scale, (float)ExplosionArray[i]._Position.Z()/ExplosionArray[i]._Scale);
           glCallList(dlist);//调用显示列表绘制爆炸效果
	       glPopMatrix();
		}
	}
	glDepthMask(GL_TRUE);
	glDisable(GL_BLEND);
    glDisable(GL_TEXTURE_2D);
	return TRUE;										// 继续
}

GLvoid KillGLWindow(GLvoid)//关闭窗口
{
	if (fullscreen){ //判断是否处于全屏模式
		if (!ChangeDisplaySettings(NULL,CDS_TEST)) { 
			ChangeDisplaySettings(NULL,CDS_RESET);
			ChangeDisplaySettings(&DMsaved,CDS_RESET);	// 更改并保存
		} else {
			ChangeDisplaySettings(NULL,CDS_RESET);
		}
		ShowCursor(TRUE);//显示鼠标指针	
	}

	if (hRC) {
		if (!wglMakeCurrent(NULL,NULL))	
			MessageBox(NULL,"释放DC和RC失败", "3D-Collision提示:",MB_OK | MB_ICONINFORMATION);

		if (!wglDeleteContext(hRC))//删除RC
			MessageBox(NULL,"发布渲染上下文失败。", "3D-Collision提示:",MB_OK | MB_ICONINFORMATION);
		hRC=NULL;
	}
	if (hDC && !ReleaseDC(hWnd,hDC)) {	
		MessageBox(NULL,"释放设备上下文失败", "3D-Collision提示:",MB_OK | MB_ICONINFORMATION);
		hDC=NULL;
	}
	if (hWnd && !DestroyWindow(hWnd))//销毁窗口
	{
		MessageBox(NULL,"无法释放hWnd", "3D-Collision提示:",MB_OK | MB_ICONINFORMATION);
		hWnd=NULL;	
	}
	if (!UnregisterClass("OpenGL",hInstance))//取消窗口类
	{
		MessageBox(NULL,"无法取消窗口类", "3D-Collision提示:",MB_OK | MB_ICONINFORMATION);
		hInstance=NULL;	
	}
}

/*  创建OpenGL窗口->参数为：                    *
 *  title - 出现在窗口顶部的标题                             *
 *  width - GL窗口或全屏模式的宽度                           *
 *  height - GL窗口或全屏模式的高度                          *
 *  bits - 用于颜色的位数（8 / 16 / 24 / 32）                *
 *  fullscreenflag - 使用全屏模式（TRUE）或窗口模式（FALSE） */
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

		//尝试设置所选模式并获取结果
		if (ChangeDisplaySettings(&dmScreenSettings,CDS_FULLSCREEN)==DISP_CHANGE_SUCCESSFUL)
		{
			if (MessageBox(NULL,"PC不支持程序全屏模式，改用窗口模式？","3D-Collision提示:",MB_YESNO|MB_ICONEXCLAMATION)==IDYES)
				fullscreen=FALSE;
			else
			{
				MessageBox(NULL,"运行错误，程序将要关闭","3D-Collision提示:",MB_OK|MB_ICONSTOP);
				return FALSE;									// Return FALSE
			}
		}
	}

	if (!RegisterClass(&wc))
	{   MessageBox(NULL,"运行错误，无法注册窗口类", "3D-Collision提示:",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;
	}

	if (fullscreen)	//全屏模式
	{
		dwExStyle=WS_EX_APPWINDOW;//窗口扩展样式
		dwStyle=WS_POPUP;// Windows Style
		ShowCursor(FALSE);//隐藏鼠标指针
	}
	else
	{   dwExStyle=WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;
		dwStyle=WS_OVERLAPPEDWINDOW;
	}
	//将窗口调整为真正的请求大小
	AdjustWindowRectEx(&WindowRect, dwStyle, FALSE, dwExStyle);
	// Create The Window
	if (!(hWnd=CreateWindowEx(	dwExStyle,//窗口的扩展样式
								"OpenGL",//类名
								title,
								dwStyle | //定义的窗口样式
								WS_CLIPSIBLINGS | 
								WS_CLIPCHILDREN,
								wx, wy,//窗口位置
								WindowRect.right-WindowRect.left,
								WindowRect.bottom-WindowRect.top,
								NULL,//没有父窗口
								NULL,//没有菜单	
								hInstance,
								NULL)))	//not -> WM_CREATE
	{
		KillGLWindow();
		MessageBox(NULL,"运行错误，窗口创建失败", "3D-Collision提示:",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;
	}

	static	PIXELFORMATDESCRIPTOR pfd=	// pfd告知窗口做什么
	{
		sizeof(PIXELFORMATDESCRIPTOR),	// Size
		1,								// 版本号
		PFD_DRAW_TO_WINDOW |			// 格式必须支持窗口
		PFD_SUPPORT_OPENGL |			
		PFD_DOUBLEBUFFER,				//必须支持双缓冲
		PFD_TYPE_RGBA,					//请求RGBA格式
		bits,							// 颜色深度
		0, 0, 0, 0, 0, 0,				//忽略颜色位
		0,								//没有Alpha缓冲区
		0,						//忽略移位位
		0,						//没有累积缓冲区
		0, 0, 0, 0,				//忽略累积位
		16,						// 16Bit Z缓冲区（深度缓冲区）
		0,						//没有模板缓冲区
		0,						//没有辅助缓冲区
		PFD_MAIN_PLANE,			//主绘图层
		0,						// Reserved
		0, 0, 0	
	};
	
	if (!(hDC=GetDC(hWnd)))
	{   KillGLWindow();
		MessageBox(NULL,"运行错误，无法创建GL设备上下文", "3D-Collision提示:",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;
	}

	if (!(PixelFormat=ChoosePixelFormat(hDC,&pfd)))	
	{
		KillGLWindow();
		MessageBox(NULL,"运行错误，找不到合适的像素格式", "3D-Collision提示:",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;
	}

	if(!SetPixelFormat(hDC,PixelFormat,&pfd))
	{
		KillGLWindow();	
		MessageBox(NULL,"运行错误，无法设置PixelFormat", "3D-Collision提示:",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;
	}

	if (!(hRC=wglCreateContext(hDC)))
	{
		KillGLWindow();
		MessageBox(NULL,"运行错误，无法创建GL渲染上下文", "3D-Collision提示:",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;
	}

	if(!wglMakeCurrent(hDC,hRC))
	{   KillGLWindow();
		MessageBox(NULL,"运行错误，无法激活GL渲染上下文", "3D-Collision提示:",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;
	}

	ShowWindow(hWnd,SW_SHOW);//显示窗口
	SetForegroundWindow(hWnd);
	SetFocus(hWnd);
	ReSizeGLScene(width, height);					// Set Up Our Perspective GL Screen

    if (!InitGL())
	{   KillGLWindow();	
		MessageBox(NULL,"初始化失败", "3D-Collision提示:",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;}
	return TRUE;									// 成功
}

//wParam的值为按下按键的虚拟键码，lParam则存储按键的相关状态信息。
LRESULT CALLBACK WndProc(	HWND	hWnd,			// 窗口的句柄
							UINT	uMsg,			// 窗口消息ID
							WPARAM	wParam,			// 附加消息信息
							LPARAM	lParam)			// 附加消息信息
{
	switch (uMsg)									//检查窗口消息
	{
		case WM_ACTIVATE:							//注意窗口激活消息
		{
			if (!HIWORD(wParam))					// Check Minimization State
				active=TRUE;						// Program Is Active
			else
				active=FALSE;						// Program Is No Longer Active
			return 0;								// Return To The Message Loop
		}
		case WM_SYSCOMMAND:							//拦截系统命令
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
		case WM_KEYDOWN:   //按键
		{keys[wParam] = TRUE;return 0;}
		case WM_KEYUP://释放
		{keys[wParam] = FALSE;return 0;}
		case WM_SIZE:	//调整OpenGL窗口的大小
		{ReSizeGLScene(LOWORD(lParam),HIWORD(lParam));  // LoWord=Width, HiWord=Height
			return 0;}
	}
	//将所有未处理的消息传递给DefWindowProc
	return DefWindowProc(hWnd,uMsg,wParam,lParam);
}

/*
程序的入口函数
*/
int WINAPI WinMain(	HINSTANCE	hInstance,			// 实例
					HINSTANCE	hPrevInstance,		// 先前实例
					LPSTR		lpCmdLine,			// 命令行参数
					int			nCmdShow)			// 窗口显示状态
{
	MSG		msg;									// 窗口消息结构
	BOOL	done=FALSE;								// 是否退出循环的变量

	// 询问窗口模式
	if (MessageBox(NULL,"是否要在全屏模式下运行?", "3D-Collision提示:",MB_YESNO|MB_ICONQUESTION)==IDNO)
	{
		fullscreen=FALSE;							//窗口模式
	}

	InitVars();                                     // 初始化变量
	
	// 创建OpenGL窗口
	if (!CreateGLWindow("3D-Collision",640,480,16,fullscreen))
	{
		return 0;									//创建窗口失败，退出应用程序
	}

	while(!done)									// 当 done = FALSE 开始循环
	{
		if (PeekMessage(&msg,NULL,0,0,PM_REMOVE))	// 有消息等待
		{
			/*
			WM_CLOSE：关闭应用程序窗口
			WM_DESTROY：关闭应用程序
			WM_QUIT：关闭消息循环
			*/
			// 收到退出消息
			if (msg.message==WM_QUIT) done=TRUE;	// 设置 done=TRUE
			else									// 否则，处理窗口信息
			{
				TranslateMessage(&msg);				// 将虚拟键消息转换为字符消息
				DispatchMessage(&msg);				// 将消息派送给窗口
			}
		}
		else										// 没有消息
		    if (active)
			{
				// 绘制场景 
				// 按键ESC 退出绘画关闭消息循环
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


/*查找当前时间步中，两个球是否彼此相交，返回两个迭代球的索引、交点以及时间*/
int FindBallCol(TVector& point, double& TimePoint, double Time2, int& BallNr1, int& BallNr2)
{
	TVector RelativeV;
	TRay rays;
	// Time2是时间的步长，Add将一个时间步长分成了150个小片
	double MyTime=0.0, Add=Time2/150.0, Timedummy=10000, Timedummy2=-1;
	TVector posi;
	
	//在150个小步中测试所有球彼此之间的相对位置
	for (int i=0;i<NrOfBalls-1;i++)
	{
	 for (int j=i+1;j<NrOfBalls;j++)
	 {	
		    RelativeV=ArrayVel[i]-ArrayVel[j];//计算两球的距离
			rays=TRay(OldPos[i],TVector::unit(RelativeV));
			MyTime=0.0;

			// 如果两个球心的距离大于两个球的半径，
			// 表明没有相撞，直接返回（球的半径应该是20）
			// 如果有撞击发生的话，计算出精确的撞击点
			if ( (rays.dist(OldPos[j])) > 40) continue; 

			while (MyTime<Time2)// 循环检测以找到精确的撞击点
			{
			   MyTime+=Add;// 将一个时间片分成150份
			   posi=OldPos[i]+RelativeV*MyTime;// 计算球在每个时间片断的位置
			   if (posi.dist(OldPos[j])<=40) {
				   // 如果两个球心的距离小于40表明在该时间片断发生了碰撞
					point=posi;// 将球的位置更新为撞击点的位置
					if (Timedummy>(MyTime-Add)) Timedummy=MyTime-Add;
					BallNr1=i;// 记录哪两个球发生了碰撞
					BallNr2=j;
					break;
				}
			}
	 }
	}
	if (Timedummy!=10000) { 
		// 如果Timedummy<10000，表明发生了碰撞，
		// 记录下碰撞发生的时间
		TimePoint=Timedummy;
	    return 1;
	}
	return 0;
}

/*模拟的主循环移动，找到当前时间步中对象的碰撞和响应。
模拟函数，计算碰撞检测和物理模拟
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
	//如果没有锁定到球上，旋转摄像机
	if (!hook_toball1)
	{
		camera_rotation+=0.1f;
		if (camera_rotation>360)
			camera_rotation=0;
	}
 
	RestTime=Time;
	lamda=1000;
	//计算重力加速度
	//使用欧拉方程计算下一个时间步的速度
	for (int j=0;j<NrOfBalls;j++)
	  ArrayVel[j]+=accel*RestTime;

	//如果在一步的模拟时间内(如果来不及计算，则跳过几步)
	while (RestTime>ZERO)
	{
	   lamda=10000;   //初始化为非常大的值
	
	   //对于所有球，找到球与平面/圆柱体之间最接近的交点
   	   for (int i=0;i<NrOfBalls;i++)
	   {
		      //计算新的位置和移动的距离
			  OldPos[i]=ArrayPos[i];
			  TVector::unit(ArrayVel[i],uveloc);
			  ArrayPos[i]=ArrayPos[i]+ArrayVel[i]*RestTime;
			  rt2=OldPos[i].dist(ArrayPos[i]);
			  //测试是否和墙面碰撞
			  if (TestIntersionPlane(pl1,OldPos[i],uveloc,rt,norm))
			  {  
				  //计算碰撞的时间
				  rt4=rt*RestTime/rt2;

				  //如果小于当前保存的碰撞时间，则更新它
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

              //测试是否与三个圆柱碰撞
			  if (TestIntersionCylinder(cyl1,OldPos[i],uveloc,rt,norm,Nc))
			  {   //计算碰撞的时间
				  rt4=rt*RestTime/rt2;
				  //如果小于当前保存的碰撞时间，则更新它
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

	   //计算每个球之间的碰撞，如果碰撞时间小于与上面的碰撞，则替换它们
	   if (FindBallCol(Pos2,BallTime,RestTime,BallColNr1,BallColNr2))
			  {
				  //调用相关函数播放声音
				  if (sounds)
					  PlaySound("Data/Explode.wav",NULL,SND_FILENAME|SND_ASYNC);
			      
				  if ( (lamda==10000) || (lamda>BallTime) )
				  {
					  RestTime=RestTime-BallTime;
					  //球体之间的碰撞
					  TVector pb1,pb2,xaxis,U1x,U1y,U2x,U2y,V1x,V1y,V2x,V2y;
					  double a,b;

					  pb1=OldPos[BallColNr1]+ArrayVel[BallColNr1]*BallTime;//球1的位置
					  pb2=OldPos[BallColNr2]+ArrayVel[BallColNr2]*BallTime;//球2的位置
					  xaxis=(pb2-pb1).unit();//X_Axis轴

					  a=xaxis.dot(ArrayVel[BallColNr1]);//X_Axis投影系数
					  U1x=xaxis*a;//计算在X_Axis轴上的速度
					  U1y=ArrayVel[BallColNr1]-U1x;//计算在垂直轴上的速度

					  xaxis=(pb1-pb2).unit();
					  b=xaxis.dot(ArrayVel[BallColNr2]);
      				  U2x=xaxis*b;
					  U2y=ArrayVel[BallColNr2]-U2x;

					  V1x=(U1x+U2x-(U1x-U2x))*0.5;//计算新的速度
					  V2x=(U1x+U2x-(U2x-U1x))*0.5;
					  V1y=U1y;
					  V2y=U2y;

					  for (int j=0;j<NrOfBalls;j++)//更新所有球的位置
					  ArrayPos[j]=OldPos[j]+ArrayVel[j]*BallTime;

					  ArrayVel[BallColNr1]=V1x+V1y;//设置新的速度
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
			//最后的测试，替换下次碰撞的时间，并更新爆炸效果的数组
			if (lamda!=10000)
			{		 
				      RestTime-=lamda;

					  for (int j=0;j<NrOfBalls;j++)
					  ArrayPos[j]=OldPos[j]+ArrayVel[j]*lamda;

					  rt2=ArrayVel[BallNr].mag();//返回速度向量的模
					  ArrayVel[BallNr].unit();//归一化速度向量
					  //计算反射向量
					  ArrayVel[BallNr]=TVector::unit( (normal*(2*normal.dot(-ArrayVel[BallNr]))) + ArrayVel[BallNr] );
					  ArrayVel[BallNr]=ArrayVel[BallNr]*rt2;
							
					  //更新爆炸数组
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

// 初始化变量
void InitVars()
{
	 // 5个墙面
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

	// 3个圆柱
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
	//创建二次对象以渲染圆柱体
	cylinder_obj= gluNewQuadric();
	gluQuadricTexture(cylinder_obj, GL_TRUE);

	//设置球的初始位置和速度
    //还初始化保存爆炸的数组
	NrOfBalls=10;//10个球
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

//判断是否和平面相交，是则返回1，否则返回0
int TestIntersionPlane(const Plane& plane,const TVector& position,const TVector& direction, double& lamda, TVector& pNormal)
{
    double DotProduct=direction.dot(plane._Normal);
	double l2;

	//确定线是否平行于平面
    if ((DotProduct<ZERO)&&(DotProduct>-ZERO)) return 0;
    l2=(plane._Normal.dot(plane._Position-position))/DotProduct;
    if (l2<-ZERO) return 0;
    pNormal=plane._Normal;
	lamda=l2;
    return 1;
}

//判断是否和圆柱相交，是则返回1，否则返回0
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

//加载位图并转换为纹理       
void LoadGLTextures() {	
	LoadTextureFromFile(texture[0],"Data/marble.bmp", true);
	LoadTextureFromFile(texture[1],"Data/spark.bmp", false);
	LoadTextureFromFile(texture[2],"Data/boden.bmp", true);
	LoadTextureFromFile(texture[3],"Data/wand.bmp", false);
};

// 键盘响应
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
	// F5 键   加速运动
	if (keys[VK_F5])
	{
		Time+=0.1;keys[VK_F5]=FALSE;
	}
	// F4 键   减速
	if (keys[VK_F4])
	{
		Time-=0.1;keys[VK_F4]=FALSE;
	}
	// F3 键  声音开关
	if (keys[VK_F3]) 
	{   
		sounds^=1;  //1->0   0->1
        keys[VK_F3]=FALSE;
	}
	// F2 键  视角跟随球运动
	if (keys[VK_F2])
	{
	    hook_toball1^=1;
	    camera_rotation=0;
		keys[VK_F2]=FALSE;
	}
	// F1 键
	if (keys[VK_F1])						
	{
		keys[VK_F1]=FALSE;
		KillGLWindow();	
		fullscreen=!fullscreen;
		// 重建OpenGL窗口
		if (!CreateGLWindow("3D-Collision",640,480,16,fullscreen)){
			return 0;
		}
	}
	return 1;
}
