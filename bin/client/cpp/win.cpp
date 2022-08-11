
#include"win.h"

int g_arrTetrics[2][4] = { 0 };




int main()
{
	HINSTANCE hInstance;
	//1.设计窗口类
	TCHAR szAppClassName[] = TEXT("ZWX");
	WNDCLASS wc = { 0 };
	wc.hbrBackground = CreateSolidBrush(RGB(255, 255, 0));					//背景颜色画刷
	wc.hCursor = LoadCursor(NULL, IDC_HAND);								//鼠标光标类型,手：DC_HAND
	wc.hIcon = LoadIcon(NULL, IDI_ERROR);									//图标
	wc.hInstance = hInstance;												//应用程序实例句柄，表示exe
	wc.lpfnWndProc = WindowProc;											//窗口处理函数
	wc.lpszClassName = szAppClassName;										//窗口类型名
	wc.style = CS_HREDRAW | CS_VREDRAW;										//窗口类的风格

	//2.注册窗口类
	RegisterClass(&wc);

	//3.创建窗口
	HWND hWnd=CreateWindow(
		szAppClassName,														    //窗口类型名
		TEXT("俄罗斯方块"),					                                    //窗口标题
		WS_BORDER | WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU,                   //窗口的风格
		200, 100,                                                               //窗口左上角坐标（像素）
		492, 634,                                                               //窗口的宽和高
		NULL,                                                                   //父窗口句柄
		NULL,                                                                   //菜单句柄
		hInstance,						                                        //应用程序实例句柄
		NULL                                                                    //附加参数
		);

	//4.显示窗口
	ShowWindow(hWnd, SW_SHOW);

	//5.更新窗口
	UpdateWindow(hWnd);

	//6.消息循环
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))//GetMessage从调用线程的消息队列中取得一个消息并放于msg
	{
		//将虚拟键消息转换为字符消息
		TranslateMessage(&msg);
		//将消息分发给窗口处理函数
		DispatchMessage(&msg);
	}
	return 0;
}

bool create_console()
{
	if(AllocConsole()!=0)
	{
		freopen("CONOUT$", "w", stdout);
		return true;
	}
	return false;
}

//窗口处理函数
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	HDC hDC;
	PAINTSTRUCT ps;

	switch (uMsg)
	{
	case WM_PAINT://窗口绘图消息
		//开始绘图
		hDC = BeginPaint(hWnd, &ps);
		OnPaint(hDC);
		//结束绘图
		EndPaint(hWnd, &ps);
		break;
	case WM_CLOSE://窗口关闭消息
		DestroyWindow(hWnd);
		break;
	case WM_DESTROY://窗口销毁消息
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);	//默认的窗口处理函数
}

void OnPaint(HDC hDC)
{
	//创建内存DC（先放到内存中）
	HDC hMemDC = CreateCompatibleDC(hDC);
	//创建一张兼容位图
	HBITMAP hBackBmp=CreateCompatibleBitmap(hMemDC, 300, 600);
	SelectObject(hMemDC, hBackBmp);
	//绘制
	DrawBlock(hMemDC);
	//一次性绘制到界面上
	BitBlt(hDC, 0, 0, 300, 600, hMemDC, 0, 0, SRCCOPY);
	//释放DC
	DeleteObject(hMemDC);

}

//绘制方块
void DrawBlock(HDC hDC)
{
	Rectangle(hDC, 0, 0, 300, 600);
	CreateTetris();
	for (int i = 0; i < 20; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			if (g_arrTetrics[i][j] == 1)
			{
				//绘制矩形
				Rectangle(hDC, j * 30+1, i * 30+1, j * 30 + 30-1, i * 30 + 30-1);
			}
		}
	}
}

//生成一个随机方块
void CreateTetris()
{
	srand((UINT)time(NULL));
	int index = rand() % 7;
	switch (index)
	{
	case 0:
		g_arrTetrics[0][0] = 1, g_arrTetrics[0][1] = 0, g_arrTetrics[0][2] = 0, g_arrTetrics[0][3] = 0;
		g_arrTetrics[1][0] = 1, g_arrTetrics[1][1] = 1, g_arrTetrics[1][2] = 1, g_arrTetrics[1][3] = 0;
		break;
	case 1:
		g_arrTetrics[0][0] = 0, g_arrTetrics[0][1] = 0, g_arrTetrics[0][2] = 1, g_arrTetrics[0][3] = 0;
		g_arrTetrics[1][0] = 1, g_arrTetrics[1][1] = 1, g_arrTetrics[1][2] = 1, g_arrTetrics[1][3] = 0;
		break;
	case 2:
		g_arrTetrics[0][0] = 1, g_arrTetrics[0][1] = 1, g_arrTetrics[0][2] = 1, g_arrTetrics[0][3] = 1;
		g_arrTetrics[1][0] = 0, g_arrTetrics[1][1] = 0, g_arrTetrics[1][2] = 0, g_arrTetrics[1][3] = 0;
		break;
	case 3:
		g_arrTetrics[0][0] = 1, g_arrTetrics[0][1] = 1, g_arrTetrics[0][2] = 0, g_arrTetrics[0][3] = 0;
		g_arrTetrics[1][0] = 1, g_arrTetrics[1][1] = 1, g_arrTetrics[1][2] = 0, g_arrTetrics[1][3] = 0;
		break;
	case 4:
		g_arrTetrics[0][0] = 0, g_arrTetrics[0][1] = 1, g_arrTetrics[0][2] = 1, g_arrTetrics[0][3] = 0;
		g_arrTetrics[1][0] = 1, g_arrTetrics[1][1] = 1, g_arrTetrics[1][2] = 0, g_arrTetrics[1][3] = 0;
		break;
	case 5:
		g_arrTetrics[0][0] = 1, g_arrTetrics[0][1] = 1, g_arrTetrics[0][2] = 0, g_arrTetrics[0][3] = 0;
		g_arrTetrics[1][0] = 0, g_arrTetrics[1][1] = 1, g_arrTetrics[1][2] = 1, g_arrTetrics[1][3] = 0;
		break;
	case 6:
		g_arrTetrics[0][0] = 0, g_arrTetrics[0][1] = 1, g_arrTetrics[0][2] = 0, g_arrTetrics[0][3] = 0;
		g_arrTetrics[1][0] = 1, g_arrTetrics[1][1] = 1, g_arrTetrics[1][2] = 1, g_arrTetrics[1][3] = 0;
		break;
	}
}