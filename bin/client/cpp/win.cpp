/*
#include <windows.h>


LRESULT CALLBACK WndProc( HWND, UINT, WPARAM, LPARAM ) ;        //声明用来处理消息的函数

int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow )
{
    static TCHAR szAppName[] = TEXT("MyWindow") ;
    HWND hwnd ;
    MSG msg ;
    WNDCLASS wndclass ;        //声明一个窗口类对象

    //以下为窗口类对象wndclass的属性
    wndclass.style = CS_HREDRAW | CS_VREDRAW ;                         //窗口样式
    wndclass.lpszClassName = szAppName ;                               //窗口类名
    wndclass.lpszMenuName = NULL ;                                     //窗口菜单:无
    wndclass.hbrBackground = (HBRUSH) GetStockObject(WHITE_BRUSH) ;    //窗口背景颜色
    wndclass.lpfnWndProc = WndProc ;                                   //窗口处理函数
    wndclass.cbWndExtra = 0 ;                                          //窗口实例扩展:无
    wndclass.cbClsExtra = 0 ;                                          //窗口类扩展:无
    wndclass.hInstance = hInstance ;                                   //窗口实例句柄
    wndclass.hIcon = LoadIcon( NULL, IDI_APPLICATION ) ;               //窗口最小化图标:使用缺省图标
    wndclass.hCursor = LoadCursor( NULL, IDC_ARROW ) ;                 //窗口采用箭头光标

    if( !RegisterClass( &wndclass ) )
    {    //注册窗口类, 如果注册失败弹出错误提示
        MessageBox( NULL, TEXT("窗口注册失败"), TEXT("错误"), MB_OK | MB_ICONERROR ) ;
        return 0 ;
    }

    hwnd = CreateWindow(               //创建窗口
        szAppName,                     //窗口类名
        TEXT("我的第一个Windows窗口"),   //窗口标题
        WS_OVERLAPPEDWINDOW,           //窗口的风格
        CW_USEDEFAULT,                 //窗口初始显示位置x:使用缺省值
        CW_USEDEFAULT,                 //窗口初始显示位置y:使用缺省值
        CW_USEDEFAULT,                 //窗口的宽度:使用缺省值
        CW_USEDEFAULT,                 //窗口的高度:使用缺省值
        NULL,                          //父窗口:无
        NULL,                          //子菜单:无
        hInstance,                     //该窗口应用程序的实例句柄 
        NULL                       
    ) ;

    ShowWindow( hwnd, iCmdShow ) ;        //显示窗口
    UpdateWindow( hwnd ) ;                //更新窗口

    while( GetMessage( &msg, NULL, 0, 0 ) )        //从消息队列中获取消息
    {
        TranslateMessage( &msg ) ;                 //将虚拟键消息转换为字符消息
        DispatchMessage( &msg ) ;                  //分发到回调函数(过程函数)
    }
    return msg.wParam ;
}

LRESULT CALLBACK WndProc( HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam )
{
    HDC hdc ;                //设备环境句柄
    PAINTSTRUCT ps ;         //绘制结构
    RECT rect;               //矩形结构

    switch( message )        //处理得到的消息
    {
        case WM_PAINT:           //处理窗口区域无效时发来的消息
            hdc = BeginPaint( hwnd, &ps ) ;
            GetClientRect( hwnd, &rect ) ;
            DrawText( hdc, TEXT("Hello World"), -1, &rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER ) ;  //文字
            EndPaint( hwnd, &ps ) ;
            return 0 ;
        case WM_DESTROY:         //处理窗口关闭时的消息
            MessageBox( hwnd, TEXT("关闭程序!"), TEXT("结束"), MB_OK | MB_ICONINFORMATION ) ;
            PostQuitMessage( 0 ) ;
            return 0;
    }
    return DefWindowProc( hwnd, message, wParam, lParam ) ;        //DefWindowProc处理我们自定义的消息处理函数没有处理到的消息
}
*/

#include<windows.h>
#include<time.h>
#include<iostream>
using namespace std;

int g_arrTetrics[2][4] = { 0 };

//窗口处理函数
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg,WPARAM wParam,LPARAM lParam);
//绘图
void OnPaint(HDC hDC);
//绘制方块
void DrawBlock(HDC hDC);
//生成一个随机方块
void CreateTetris();

//入口函数：所有代码都从这里开始执行
//WinMain:C语言Windows窗口程序入口函数

//做游戏窗口的步骤
//1.设计窗口类
//2.注册窗口类
//3.创建窗口
//4.显示窗口
//5.更新窗口
//6.消息循环

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPreInstance, LPSTR lpCmdLine, int nCmdShow)
{
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