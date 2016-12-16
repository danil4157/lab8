#include <windows.h> 
#include "stdafx.h"
LRESULT CALLBACK WinFun(HWND, UINT, WPARAM, LPARAM);
char WinName[] = "Window";
int WINAPI WinMain(HINSTANCE hIns, HINSTANCE hPrevIns, LPSTR arg, int WinMode)
{
	HWND hwnd;
	MSG msg;
	WNDCLASSEX wcl;
	wcl.hInstance = hIns;
	wcl.lpszClassName = WinName;
	wcl.lpfnWndProc = WinFun;
	wcl.style = 0;
	wcl.cbSize = sizeof(WNDCLASSEX);
	wcl.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wcl.hIconSm = LoadIcon(NULL, IDI_WINLOGO);
	wcl.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcl.lpszMenuName = NULL;
	wcl.cbClsExtra = 0;
	wcl.cbWndExtra = 0;
	wcl.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	if (!RegisterClassEx(&wcl)) return 0;
	hwnd = CreateWindow(
		WinName,
		"Lab8",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		HWND_DESKTOP,
		NULL,
		hIns,
		NULL);
	ShowWindow(hwnd, WinMode);
	UpdateWindow(hwnd);
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}
struct line
{
	int x1, x2, y1, y2;
};
struct lineList
{
	line L;
	lineList *pNext;
};
lineList *pFirst = 0, *p;
void add(lineList *&pF, lineList *p)
{
	p->pNext = pF;
	pF = p;
}
int x1, x2, y1, y2;
HPEN pB;
HBRUSH pW;
LRESULT CALLBACK WinFun(HWND hwnd, UINT message,
	WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	switch (message)
	{
	case WM_MOUSEMOVE:
		if (wParam & MK_LBUTTON)
		{
			int x, y;
			x = LOWORD(lParam);
			y = HIWORD(lParam);
			hdc = GetDC(hwnd);
			HPEN pen = CreatePen(PS_DOT, 1, RGB(152, 0, 2));;
			HBRUSH br = CreateHatchBrush(HS_HORIZONTAL, RGB(255, 179, 0));
			SelectObject(hdc, pen);
			SelectObject(hdc, br);
			Ellipse(hdc, x - 50, y - 50, x + 50, y + 50);
			DeleteObject(pen);
			DeleteObject(br);
			ReleaseDC(hwnd, hdc);
		}
		EndPaint(hwnd, &ps);
		break;
	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		p = pFirst;
		while (p)
		{
			SelectObject(hdc, pW);
			SelectObject(hdc, pB);
			MoveToEx(hdc, p->L.x1, p->L.y1, (LPPOINT)NULL);
			Rectangle(hdc, p->L.x1, p -> L.y1, p->L.x2, p->L.y2);
			p = p-> pNext;
		}
		EndPaint(hwnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hwnd, message, wParam, lParam);
	}
	return 0;
}
