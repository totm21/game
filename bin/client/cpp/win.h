#ifndef WIN_ME
#define WIN_ME

/*
    �����ڻ���
    @auther:    ����
    @date:      2022.8.10
    @alter:     2022.8.12
*/

//����Ϸ���ڵĲ���
//1.��ƴ�����
//2.ע�ᴰ����
//3.��������
//4.��ʾ����
//5.���´���
//6.��Ϣѭ��

#include<windows.h>
#include<time.h>
#include<iostream>

//����һ������̨���� ��������󶨵��ô���
bool create_console();

//���ڴ�����
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg,WPARAM wParam,LPARAM lParam);
//��ͼ
void OnPaint(HDC hDC);
//���Ʒ���
void DrawBlock(HDC hDC);
//����һ���������
void CreateTetris();



#endif