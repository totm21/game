#ifndef WIN_ME
#define WIN_ME

/*
    主窗口绘制
    @auther:    程智
    @date:      2022.8.10
    @alter:     2022.8.12
*/

//做游戏窗口的步骤
//1.设计窗口类
//2.注册窗口类
//3.创建窗口
//4.显示窗口
//5.更新窗口
//6.消息循环

#include<windows.h>
#include<time.h>
#include<iostream>

//创建一个控制台窗口 并将输出绑定到该窗口
bool create_console();

//窗口处理函数
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg,WPARAM wParam,LPARAM lParam);
//绘图
void OnPaint(HDC hDC);
//绘制方块
void DrawBlock(HDC hDC);
//生成一个随机方块
void CreateTetris();



#endif