
#include"win.h"

int g_arrTetrics[2][4] = { 0 };




int main()
{
	HINSTANCE hInstance;
	//1.��ƴ�����
	TCHAR szAppClassName[] = TEXT("ZWX");
	WNDCLASS wc = { 0 };
	wc.hbrBackground = CreateSolidBrush(RGB(255, 255, 0));					//������ɫ��ˢ
	wc.hCursor = LoadCursor(NULL, IDC_HAND);								//���������,�֣�DC_HAND
	wc.hIcon = LoadIcon(NULL, IDI_ERROR);									//ͼ��
	wc.hInstance = hInstance;												//Ӧ�ó���ʵ���������ʾexe
	wc.lpfnWndProc = WindowProc;											//���ڴ�����
	wc.lpszClassName = szAppClassName;										//����������
	wc.style = CS_HREDRAW | CS_VREDRAW;										//������ķ��

	//2.ע�ᴰ����
	RegisterClass(&wc);

	//3.��������
	HWND hWnd=CreateWindow(
		szAppClassName,														    //����������
		TEXT("����˹����"),					                                    //���ڱ���
		WS_BORDER | WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU,                   //���ڵķ��
		200, 100,                                                               //�������Ͻ����꣨���أ�
		492, 634,                                                               //���ڵĿ�͸�
		NULL,                                                                   //�����ھ��
		NULL,                                                                   //�˵����
		hInstance,						                                        //Ӧ�ó���ʵ�����
		NULL                                                                    //���Ӳ���
		);

	//4.��ʾ����
	ShowWindow(hWnd, SW_SHOW);

	//5.���´���
	UpdateWindow(hWnd);

	//6.��Ϣѭ��
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))//GetMessage�ӵ����̵߳���Ϣ������ȡ��һ����Ϣ������msg
	{
		//���������Ϣת��Ϊ�ַ���Ϣ
		TranslateMessage(&msg);
		//����Ϣ�ַ������ڴ�����
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

//���ڴ�����
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	HDC hDC;
	PAINTSTRUCT ps;

	switch (uMsg)
	{
	case WM_PAINT://���ڻ�ͼ��Ϣ
		//��ʼ��ͼ
		hDC = BeginPaint(hWnd, &ps);
		OnPaint(hDC);
		//������ͼ
		EndPaint(hWnd, &ps);
		break;
	case WM_CLOSE://���ڹر���Ϣ
		DestroyWindow(hWnd);
		break;
	case WM_DESTROY://����������Ϣ
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);	//Ĭ�ϵĴ��ڴ�����
}

void OnPaint(HDC hDC)
{
	//�����ڴ�DC���ȷŵ��ڴ��У�
	HDC hMemDC = CreateCompatibleDC(hDC);
	//����һ�ż���λͼ
	HBITMAP hBackBmp=CreateCompatibleBitmap(hMemDC, 300, 600);
	SelectObject(hMemDC, hBackBmp);
	//����
	DrawBlock(hMemDC);
	//һ���Ի��Ƶ�������
	BitBlt(hDC, 0, 0, 300, 600, hMemDC, 0, 0, SRCCOPY);
	//�ͷ�DC
	DeleteObject(hMemDC);

}

//���Ʒ���
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
				//���ƾ���
				Rectangle(hDC, j * 30+1, i * 30+1, j * 30 + 30-1, i * 30 + 30-1);
			}
		}
	}
}

//����һ���������
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