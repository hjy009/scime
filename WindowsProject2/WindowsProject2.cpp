﻿// WindowsProject2.cpp : 定义应用程序的入口点。
//

#include "framework.h"
#include "WindowsProject2.h"

#define MAX_LOADSTRING 100

/*
 * Cust Window Styles
 */
#define WS_CustWINDOW (WS_OVERLAPPED    )

// 全局变量:
HINSTANCE hInst;                                // 当前实例
WCHAR szTitle[MAX_LOADSTRING];                  // 标题栏文本
WCHAR szWindowClass[MAX_LOADSTRING];            // 主窗口类名

HWND hwnd;
HDC hdc;          // handle to device context (DC)  
//PAINTSTRUCT ps;   // paint data for Begin/EndPaint  
POINT ptClientUL; // client area upper left corner  
POINT ptClientLR; // client area lower right corner  
static HDC hdcCompat; // handle to DC for bitmap  
static POINT pt;      // x- and y-coordinates of cursor  
static RECT rcTarget; // rect to receive filled shape  
static RECT rcClient; // client area rectangle  
static BOOL fSizeEllipse; // TRUE if ellipse is sized  
static BOOL fDrawEllipse;   // TRUE if ellipse is drawn  
static BOOL fDrawRectangle; // TRUE if rectangle is drawn  
static BOOL fSizeRectangle; // TRUE if rectangle is sized  
static BOOL fSizeRoundRect; // TRUE if rounded rect is sized  
static BOOL fDrawRoundRect; // TRUE if rounded rect is drawn  
static int nEllipseWidth;   // width for round corners  
static int nEllipseHeight;  // height for round corners  

static RECT clientRect;
static RECT textRect;
static HRGN bgRgn;
static HBRUSH hBrush;
static HPEN hPen;

//设置窗口透明色
static COLORREF m_clrWndTransparencyColorKey = RGB(147, 147, 148);
//缺省的不透明色
static COLORREF m_clrWndNoTransparencyColorKey = RGB(255, 0, 19);


static int divx =4;
static int divy = 3;

// 此代码模块中包含的函数的前向声明:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: 在此处放置代码。

    // 初始化全局字符串
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_WINDOWSPROJECT2, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 执行应用程序初始化:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WINDOWSPROJECT2));

    MSG msg;

    // 主消息循环:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  函数: MyRegisterClass()
//
//  目标: 注册窗口类。
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WINDOWSPROJECT2));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_WINDOWSPROJECT2);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   函数: InitInstance(HINSTANCE, int)
//
//   目标: 保存实例句柄并创建主窗口
//
//   注释:
//
//        在此函数中，我们在全局变量中保存实例句柄并
//        创建和显示主程序窗口。
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // 将实例句柄存储在全局变量中

   /*
   //ModifyStyleEx(WS_EX_CLIENTEDGE, NULL);

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);
   */
   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_CustWINDOW,
       CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   //nCmdShow = SW_SHOWMAXIMIZED;


   ////////////////////////////////////////////////////////////////////////////
   //设置窗口的扩展样式：WS_EX_LAYERED,以形成透明窗口风格。
   // Set WS_EX_LAYERED on this window 
   /*
   SetWindowLong(hWnd,
       GWL_EXSTYLE,
       GetWindowLong(hWnd, GWL_EXSTYLE) | WS_EX_LAYERED);
   */
   //设置窗口：用透明色来实现透明窗口。（还可以通过透明度来设置透明窗口：LWA_ALPHA）
   // Make this window 70% alpha
   //SetLayeredWindowAttributes(hWnd, 0, (255 * 70) / 100, LWA_ALPHA);
   //SetLayeredWindowAttributes(hWnd, 0, 150, LWA_ALPHA);
   /*
   // Make this window 70% alpha
   SetLayeredWindowAttributes(hWnd,
       m_clrWndTransparencyColorKey,
       255,
       LWA_COLORKEY);
   */

   ////////////////////////////////////////////////////////////////////////////

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

void drawgrid(RECT rect)
{
    int width, hight;
    width = rect.right - rect.left;
    hight = rect.bottom - rect.top;
    for (int i = 1; i < divx; i++) {
        pt.x = rect.left + width / divx * i;
        pt.y = rect.top;
        MoveToEx(hdc, pt.x, pt.y , NULL);
        pt.x = rect.left + width / divx * i;
        pt.y = rect.bottom;
        LineTo(hdc, pt.x, pt.y);
    }
    for (int i = 1; i < divy; i++) {
        pt.x = rect.left;
        pt.y = rect.top + hight / divy * i;
        MoveToEx(hdc, pt.x , pt.y, NULL);
        pt.x = rect.right;
        pt.y = rect.top + hight / divy * i;
        LineTo(hdc, pt.x, pt.y);
    }

}

void drawx(RECT rect)
{
    drawgrid(rect);
}

//
//  函数: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  目标: 处理主窗口的消息。
//
//  WM_COMMAND  - 处理应用程序菜单
//  WM_PAINT    - 绘制主窗口
//  WM_DESTROY  - 发送退出消息并返回
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // 分析菜单选择:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            //HDC hdc = BeginPaint(hWnd, &ps);
            hdc = BeginPaint(hWnd, &ps);
            // TODO: 在此处添加使用 hdc 的任何绘图代码...

        // Fill the client area with a brush
            GetClientRect(hWnd, &clientRect);
            bgRgn = CreateRectRgnIndirect(&clientRect);
            hBrush = CreateSolidBrush(RGB(255, 255, 255));
            FillRgn(hdc, bgRgn, hBrush);

            hPen = CreatePen(PS_DOT, 1, RGB(0, 0, 0));
            SelectObject(hdc, hPen);
            SetBkColor(hdc, RGB(0, 0, 0));
//            Rectangle(hdc, 10, 10, 200, 200);

            drawgrid(clientRect);

            DeleteObject(hPen);
            hPen = CreatePen(PS_DOT, 1, RGB(0, 255, 0));
            SelectObject(hdc, hPen);
            SetBkColor(hdc, RGB(0, 0, 0));

            for (int i = 0; i < divx; i++) {
                for (int j = 0; j < divy; j++) {
                    rcTarget.left = clientRect.right / divx * i;
                    rcTarget.right = clientRect.right / divx * (i+1);
                    rcTarget.top = clientRect.bottom / divy * j;
                    rcTarget.bottom = clientRect.bottom / divy * (j+1);
                    drawx(rcTarget);
                }
            }




            // Clean up
            DeleteObject(bgRgn);
            DeleteObject(hBrush);
            DeleteObject(hPen);

            GetStockObject(WHITE_BRUSH);
            GetStockObject(DC_PEN);


            EndPaint(hWnd, &ps);
        }
        break;
    case WM_SIZE:

        // Convert the client coordinates of the client area  
        // rectangle to screen coordinates and save them in a  
        // rectangle. The rectangle is passed to the ClipCursor  
        // function during WM_LBUTTONDOWN processing.  

        GetClientRect(hWnd, &rcClient);
        ptClientUL.x = rcClient.left;
        ptClientUL.y = rcClient.top;
        ptClientLR.x = rcClient.right;
        ptClientLR.y = rcClient.bottom;
        ClientToScreen(hWnd, &ptClientUL);
        ClientToScreen(hWnd, &ptClientLR);
        SetRect(&rcClient, ptClientUL.x, ptClientUL.y,
            ptClientLR.x, ptClientLR.y);
        return 0;
    case WM_KEYDOWN:
        if (wParam == VK_ESCAPE)
        {
            DestroyWindow(hWnd);
        }

        
        if (wParam == L'J')
        {
            SetCursorPos(100, 100);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// “关于”框的消息处理程序。
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
