#undef UNICODE
#undef _UNICODE
#include<Windows.h>
HBRUSH hBrush;
BOOL DrawCube(HWND, HDC);
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow)
{
	HWND hWnd;
	MSG msg;
	WNDCLASS wc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hInstance = hInstance;
	wc.lpfnWndProc = WndProc;
	wc.lpszClassName = TEXT("ClassCube");
	wc.lpszMenuName = NULL;
	wc.style = CS_HREDRAW | CS_VREDRAW;
	RegisterClass(&wc);
	hWnd = CreateWindow(TEXT("ClassCube"),
		TEXT("Cube"),
		WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL,
		hInstance, NULL);
	ShowWindow(hWnd, nCmdShow);
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	switch (uMsg)
	{
	case WM_CREATE:
		hBrush = CreateSolidBrush(RGB(192, 192, 192));
		SetClassLong(hWnd, GCL_HBRBACKGROUND, (LONG)hBrush);
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		if (!DrawCube(hWnd, hdc))
		{
			MessageBox(hWnd, "returned FALSE", "ERROR", MB_OK | MB_ICONERROR);
			PostMessage(hWnd, WM_CLOSE, 0, 0);
		}
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		DeleteObject(hBrush);
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, uMsg, wParam, lParam);
	}
	return 0;
}
BOOL DrawCube(HWND hwnd, HDC hdc)
{
	RECT rect;
	if (!GetClientRect(hwnd, &rect))
		return FALSE;
	DWORD dwStep;
	if (rect.bottom <= rect.right)
		dwStep = rect.bottom / 13;
	else
		dwStep = rect.right / 13;
	int xOrg = rect.right / 2 - dwStep*4.5;
	int yOrg = rect.bottom / 2 - dwStep*4.5;
	if (!SetViewportOrgEx(hdc, xOrg, yOrg, NULL))
		return FALSE;
	HRGN hRgn[9];
	POINT pt1[]{ {0,dwStep * 5},{dwStep * 2,dwStep * 5},{dwStep * 2,dwStep * 3},
	{dwStep * 4,dwStep * 3},{dwStep * 4,dwStep * 5},{dwStep * 6,dwStep * 5},
	{dwStep * 6,dwStep * 7},{dwStep * 4,dwStep * 7},{dwStep * 4,dwStep * 9},
	{dwStep * 2,dwStep * 9},{dwStep * 2,dwStep * 7},{0,dwStep * 7},{0,dwStep * 5} };

	hRgn[0] = CreatePolygonRgn(pt1, 13, ALTERNATE);

	POINT pt2[]{ {dwStep * 2,dwStep * 3},{dwStep * 3,dwStep * 2},{dwStep,dwStep * 2},
	{dwStep * 2,dwStep},{dwStep * 4,dwStep},{dwStep * 5,0},{dwStep * 7,0},
	{dwStep * 6,dwStep},{dwStep * 8,dwStep},{dwStep * 7,dwStep * 2},{dwStep * 5,dwStep * 2},
	{dwStep * 4,dwStep * 3},{dwStep * 2,dwStep * 3} };

	hRgn[1] = CreatePolygonRgn(pt2, 13, ALTERNATE);

	POINT pt3[]{ {dwStep * 6,dwStep * 5},{dwStep * 7,dwStep * 4},{dwStep * 7,dwStep * 2},
	{dwStep * 8,dwStep},{dwStep * 8,dwStep * 3},{dwStep * 9,dwStep * 2},
	{dwStep * 9,dwStep * 4},{dwStep * 8,dwStep * 5},{dwStep * 8,dwStep * 7},
	{dwStep * 7,dwStep * 8},{dwStep * 7,dwStep * 6},{dwStep * 6,dwStep * 7},{dwStep * 6,dwStep * 5} };

	hRgn[2] = CreatePolygonRgn(pt3, 13, ALTERNATE);

	POINT pt4[]{ {dwStep * 4,dwStep * 5},{dwStep * 4,dwStep * 3},{dwStep * 5,dwStep * 2},
	{dwStep * 7,dwStep * 2},{dwStep * 7,dwStep * 4},{dwStep * 6,dwStep * 5},
	{dwStep * 4,dwStep * 5} };

	hRgn[3] = CreatePolygonRgn(pt4, 7, ALTERNATE);

	POINT pt5[]{ {0,dwStep * 5},{dwStep,dwStep * 4},{dwStep,dwStep * 2},{dwStep * 3,dwStep * 2},
	{dwStep * 2,dwStep * 3},{dwStep * 2,dwStep * 5},{0,dwStep * 5} };

	hRgn[4] = CreatePolygonRgn(pt5, 7, ALTERNATE);

	POINT pt6[]{ {dwStep * 4,dwStep * 7},{dwStep * 6,dwStep * 7},{dwStep * 7,dwStep * 6},
	{dwStep * 7,dwStep * 8},{dwStep * 5,dwStep * 8},{dwStep * 4,dwStep * 9},
	{dwStep * 4,dwStep * 7} };

	hRgn[5] = CreatePolygonRgn(pt6, 7, ALTERNATE);

	POINT pt7[]{ {dwStep,dwStep * 8},{dwStep,dwStep * 7},{dwStep * 2,dwStep * 7},
	{dwStep * 2,dwStep * 8},{dwStep,dwStep * 8} };

	hRgn[6] = CreatePolygonRgn(pt7, 5, ALTERNATE);

	POINT pt8[]{ {dwStep * 6,dwStep},{dwStep * 7,0},{dwStep * 7,dwStep},{dwStep * 6,dwStep} };

	hRgn[7] = CreatePolygonRgn(pt8, 4, ALTERNATE);

	POINT pt9[]{ {dwStep * 8,dwStep * 2},{dwStep * 9,dwStep * 2},{dwStep * 8,dwStep * 3},
	{dwStep * 8,dwStep * 2} };

	hRgn[8] = CreatePolygonRgn(pt9, 4, ALTERNATE);

	HBRUSH hMBr = CreateSolidBrush(RGB(0, 0, 0));
	HBRUSH hSBr = CreateSolidBrush(RGB(89, 89, 89));
	
	for (int i(0); i < 3; i++)
		FillRgn(hdc, hRgn[i], hMBr);
	for (int i(3); i < 9; i++)
		FillRgn(hdc, hRgn[i], hSBr);

	HPEN hOldPen = (HPEN)SelectObject(hdc, CreatePen(PS_SOLID, 3, RGB(0, 0, 0)));

	Polyline(hdc, pt1, 13);
	Polyline(hdc, pt2, 13);
	Polyline(hdc, pt3, 13);
	MoveToEx(hdc, 0, dwStep * 5, NULL);
	LineTo(hdc, dwStep, dwStep * 4);
	LineTo(hdc, dwStep, dwStep * 2);
	MoveToEx(hdc, dwStep, dwStep * 4, NULL);
	LineTo(hdc, dwStep * 2, dwStep * 4);
	MoveToEx(hdc, dwStep, dwStep * 7, NULL);
	LineTo(hdc, dwStep, dwStep * 8);
	LineTo(hdc, dwStep * 2, dwStep * 8);
	MoveToEx(hdc, dwStep * 4, dwStep * 9, NULL);
	LineTo(hdc, dwStep * 5, dwStep * 8);
	LineTo(hdc, dwStep * 7, dwStep * 8);
	MoveToEx(hdc, dwStep * 5, dwStep * 8, NULL);
	LineTo(hdc, dwStep * 5, dwStep * 7);
	MoveToEx(hdc, dwStep * 4, dwStep * 5, NULL);
	LineTo(hdc, dwStep * 5, dwStep * 4);
	LineTo(hdc, dwStep * 5, dwStep * 2);
	MoveToEx(hdc, dwStep * 5, dwStep * 4, NULL);
	LineTo(hdc, dwStep * 7, dwStep * 4);
	MoveToEx(hdc, dwStep * 7, 0, NULL);
	LineTo(hdc, dwStep * 7, dwStep);
	MoveToEx(hdc, dwStep * 8, dwStep * 2, NULL);
	LineTo(hdc, dwStep * 9, dwStep * 2);

	for (int i(0); i < 9; i++)
		DeleteObject(hRgn[i]);
	DeleteObject(hMBr);
	DeleteObject(hSBr);
	DeleteObject(SelectObject(hdc, hOldPen));
	return TRUE;
}