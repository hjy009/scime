// Project2.cpp : 定义应用程序的入口点。
//

#include "framework.h"
#include "Project2.h"

#define MAX_LOADSTRING 100

// 全局变量:
HINSTANCE hInst;                                // 当前实例
WCHAR szTitle[MAX_LOADSTRING];                  // 标题栏文本
WCHAR szWindowClass[MAX_LOADSTRING];            // 主窗口类名
HWND hWnd;


BOOL fDraw = FALSE;
POINT ptPrevious;

HDC hdc;                 // device context (DC) for window  
RECT rcTmp;              // temporary rectangle  
PAINTSTRUCT ps;          // paint data for BeginPaint and EndPaint  
POINT ptClientUL;        // client area upper left corner  
POINT ptClientLR;        // client area lower right corner  
static HDC hdcCompat;    // DC for copying bitmap  
static POINT pt;         // x and y coordinates of cursor  
static RECT rcBmp;       // rectangle that encloses bitmap  
static RECT rcTarget;    // rectangle to receive bitmap  
static RECT rcClient;    // client-area rectangle  
static BOOL fDragRect;   // TRUE if bitmap rect. is dragged  
static HBITMAP hbmp;     // handle of bitmap to display  
static HBRUSH hbrBkgnd;  // handle of background-color brush  
static COLORREF crBkgnd; // color of client-area background  
static HPEN hpenDot;     // handle of dotted pen  


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
    LoadStringW(hInstance, IDC_PROJECT2, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 执行应用程序初始化:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_PROJECT2));

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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_PROJECT2));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_PROJECT2);
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
   //HWND hWnd;
   hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   // Set WS_EX_LAYERED on this window 
   SetWindowLong(hWnd,
       GWL_EXSTYLE,
       GetWindowLong(hWnd, GWL_EXSTYLE) | WS_EX_LAYERED);

   // Make this window 70% alpha
   SetLayeredWindowAttributes(hWnd, 0, (255 * 70) / 100, LWA_ALPHA);

/*

   // Load the bitmap resource.  

   hbmp = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_FLOATINGIMAGE));

   // Create a device context (DC) to hold the bitmap.  
   // The bitmap is copied from this DC to the window's DC  
   // whenever it must be drawn.  

   hdc = GetDC(hWnd);
   hdcCompat = CreateCompatibleDC(hdc);
   SelectObject(hdcCompat, hbmp);

   // Create a brush of the same color as the background  
   // of the client area. The brush is used later to erase  
   // the old bitmap before copying the bitmap into the  
   // target rectangle.  

   crBkgnd = GetBkColor(hdc);
   hbrBkgnd = CreateSolidBrush(crBkgnd);
   ReleaseDC(hWnd, hdc);

   // Create a dotted pen. The pen is used to draw the  
   // bitmap rectangle as the user drags it.  

   hpenDot = CreatePen(PS_DOT, 1, RGB(0, 0, 0));

   // Set the initial rectangle for the bitmap. Note that  
   // this application supports only a 32- by 32-pixel  
   // bitmap. The rectangle is slightly larger than the  
   // bitmap.  

   SetRect(&rcBmp, 1, 1, 177, 137);
*/

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
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
    PAINTSTRUCT ps;
    HDC hdc;
    RECT rc;
    POINT aptStar[6] = { 50,2, 2,98, 98,33, 2,33, 98,98, 50,2 };

    POINT aptTriangle[4] = { 50,2, 98,86,  2,86, 50,2 },
        aptRectangle[5] = { 2,2, 98,2,  98,98,  2,98, 2,2 },
        aptPentagon[6] = { 50,2, 98,35, 79,90, 21,90, 2,35, 50,2 },
        aptHexagon[7] = { 50,2, 93,25, 93,75, 50,98, 7,75, 7,25, 50,2 };


    switch (message)
    {
    case WM_CREATE:

        // Load the bitmap resource.  

        hbmp = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_FLOATINGIMAGE));

        // Create a device context (DC) to hold the bitmap.  
        // The bitmap is copied from this DC to the window's DC  
        // whenever it must be drawn.  

        hdc = GetDC(hWnd);
        hdcCompat = CreateCompatibleDC(hdc);
        SelectObject(hdcCompat, hbmp);

        // Create a brush of the same color as the background  
        // of the client area. The brush is used later to erase  
        // the old bitmap before copying the bitmap into the  
        // target rectangle.  

        crBkgnd = GetBkColor(hdc);
        hbrBkgnd = CreateSolidBrush(crBkgnd);
        ReleaseDC(hWnd, hdc);

        // Create a dotted pen. The pen is used to draw the  
        // bitmap rectangle as the user drags it.  

        hpenDot = CreatePen(PS_DOT, 1, RGB(0, 0, 0));

        // Set the initial rectangle for the bitmap. Note that  
        // this application supports only a 32- by 32-pixel  
        // bitmap. The rectangle is slightly larger than the  
        // bitmap.  

        SetRect(&rcBmp, 1, 1, 177, 137);
        return 0;
    case WM_INITDIALOG:
        {
            // Set WS_EX_LAYERED on this window 
            SetWindowLong(hWnd,
                GWL_EXSTYLE,
                GetWindowLong(hWnd, GWL_EXSTYLE) | WS_EX_LAYERED);

            // Make this window 70% alpha
            SetLayeredWindowAttributes(hWnd, 0, (255 * 70) / 100, LWA_ALPHA);         
        }
        break;
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
    case WM_LBUTTONDOWN:
        fDraw = TRUE;
        ptPrevious.x = LOWORD(lParam);
        ptPrevious.y = HIWORD(lParam);
        return 0L;
    case WM_LBUTTONUP:
        if (fDraw)
        {
            hdc = GetDC(hWnd);
            MoveToEx(hdc, ptPrevious.x, ptPrevious.y, NULL);
            LineTo(hdc, LOWORD(lParam), HIWORD(lParam));
            ReleaseDC(hWnd, hdc);
        }
        fDraw = FALSE;
        return 0L;

    case WM_MOUSEMOVE:
        if (fDraw)
        {
            hdc = GetDC(hWnd);
            MoveToEx(hdc, ptPrevious.x, ptPrevious.y, NULL);
            LineTo(hdc, ptPrevious.x = LOWORD(lParam),
                ptPrevious.y = HIWORD(lParam));
            ReleaseDC(hWnd, hdc);
        }
    return 0L; 

    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: 在此处添加使用 hdc 的任何绘图代码...

            Rectangle(ps.hdc, rcBmp.left, rcBmp.top,
                rcBmp.right, rcBmp.bottom);
            StretchBlt(ps.hdc, rcBmp.left + 1, rcBmp.top + 1,
                (rcBmp.right - rcBmp.left) - 2,
                (rcBmp.bottom - rcBmp.top) - 2, hdcCompat,
                0, 0, 177, 137, SRCCOPY);

            // All painting occurs here, between BeginPaint and EndPaint.
//            FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));
 /*
            GetClientRect(hWnd, &rc);
            SetMapMode(hdc, MM_ANISOTROPIC);
            SetWindowExtEx(hdc, 100, 100, NULL);
            SetViewportExtEx(hdc, rc.right, rc.bottom, NULL);
            Polyline(hdc, aptStar, 6);
            
//            TextOutA(hdc, 0, 0, "Hello, Windows!", 15);
//            TextOut(hdc, 0, 0, L"Hello, Windows!", 15);
*/
/* 
            SetRect(&rc, 0, 0, 100, 100);

            if (RectVisible(hdc, &rc))
                Polyline(hdc, aptTriangle, 4);

            SetViewportOrgEx(hdc, 100, 0, NULL);
            if (RectVisible(hdc, &rc))
                Polyline(hdc, aptRectangle, 5);

            SetViewportOrgEx(hdc, 0, 100, NULL);
            if (RectVisible(hdc, &rc))
                Polyline(hdc, aptPentagon, 6);

            SetViewportOrgEx(hdc, 100, 100, NULL);
            if (RectVisible(hdc, &rc))
                Polyline(hdc, aptHexagon, 7);
*/
            EndPaint(hWnd, &ps);
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
