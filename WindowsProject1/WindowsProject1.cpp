// WindowsProject1.cpp : 定义应用程序的入口点。
//

#include "framework.h"
#include "WindowsProject1.h"

#define MAX_LOADSTRING 100

// 全局变量:
HINSTANCE hInst;                                // 当前实例
WCHAR szTitle[MAX_LOADSTRING];                  // 标题栏文本
WCHAR szWindowClass[MAX_LOADSTRING];            // 主窗口类名

// 此代码模块中包含的函数的前向声明:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

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
    LoadStringW(hInstance, IDC_WINDOWSPROJECT1, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 执行应用程序初始化:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WINDOWSPROJECT1));

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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WINDOWSPROJECT1));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_WINDOWSPROJECT1);
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

   hwnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hwnd)
   {
      return FALSE;
   }

   ShowWindow(hwnd, nCmdShow);
   UpdateWindow(hwnd);

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
            
            // Set the appropriate flag to indicate which  
            // filled shape the user is drawing.  

            case IDM_ELLIPSE:
                fSizeEllipse = TRUE;
                break;

            case IDM_RECTANGLE:
                fSizeRectangle = TRUE;
                break;

            case IDM_ROUNDRECT:
                fSizeRoundRect = TRUE;
                break;

            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;

    case WM_CREATE:
        nEllipseWidth = 20;
        nEllipseHeight = 20;

        return 0;

    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: 在此处添加使用 hdc 的任何绘图代码...

            // Because the default brush is white, select  
            // a different brush into the device context  
            // to demonstrate the painting of filled shapes.  

            SelectObject(ps.hdc, GetStockObject(GRAY_BRUSH));

            // If one of the filled shape "draw" flags is TRUE,  
            // draw the corresponding shape.  

            if (fDrawEllipse)
            {
                Ellipse(ps.hdc, rcTarget.left, rcTarget.top,
                    rcTarget.right, rcTarget.bottom);
                fDrawEllipse = FALSE;
                rcTarget.left = rcTarget.right = 0;
                rcTarget.top = rcTarget.bottom = 0;
            }

            if (fDrawRectangle)
            {
                Rectangle(ps.hdc, rcTarget.left, rcTarget.top,
                    rcTarget.right, rcTarget.bottom);
                fDrawRectangle = FALSE;
                rcTarget.left = rcTarget.right = 0;
                rcTarget.top = rcTarget.bottom = 0;
            }

            if (fDrawRoundRect)
            {
                RoundRect(ps.hdc, rcTarget.left, rcTarget.top,
                    rcTarget.right, rcTarget.bottom,
                    nEllipseWidth, nEllipseHeight);
                fDrawRectangle = FALSE;
                rcTarget.left = rcTarget.right = 0;
                rcTarget.top = rcTarget.bottom = 0;
            }
            
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

    case WM_LBUTTONDOWN:

        // Restrict the cursor to the client area.  
        // This ensures that the window receives a matching  
        // WM_LBUTTONUP message.  

        ClipCursor(&rcClient);

        // Save the coordinates of the cursor.  

        pt.x = (LONG)LOWORD(lParam);
        pt.y = (LONG)HIWORD(lParam);

        // If the user chooses one of the filled shapes,  
        // set the appropriate flag to indicate that the  
        // shape is being sized.  

        if (fDrawEllipse)
            fSizeEllipse = TRUE;

        return 0;

    case WM_MOUSEMOVE:

        // If one of the "size" flags is set, draw  
        // the target rectangle as the user drags  
        // the mouse.  

        if ((wParam && MK_LBUTTON)
            && (fSizeEllipse || fSizeRectangle
                || fSizeRoundRect))
        {

            // Set the mixing mode so that the pen color is the  
            // inverse of the background color. The previous  
            // rectangle can then be erased by drawing  
            // another rectangle on top of it.  

            hdc = GetDC(hWnd);
            SetROP2(hdc, R2_NOTXORPEN);

            // If a previous target rectangle exists, erase  
            // it by drawing another rectangle on top.  

            if (!IsRectEmpty(&rcTarget))
            {
                Rectangle(hdc, rcTarget.left, rcTarget.top,
                    rcTarget.right, rcTarget.bottom);
            }

            // Save the coordinates of the target rectangle.  
            // Avoid invalid rectangles by ensuring that the  
            // value of the left coordinate is greater than  
            // that of the right, and that the value of the  
            // bottom coordinate is greater than that of  
            // the top.  

            if ((pt.x < (LONG)LOWORD(lParam)) &&
                (pt.y > (LONG) HIWORD(lParam)))
            {
                SetRect(&rcTarget, pt.x, HIWORD(lParam),
                    LOWORD(lParam), pt.y);
            }

            else if ((pt.x > (LONG)LOWORD(lParam)) &&
                (pt.y > (LONG)HIWORD(lParam)))
            {
                SetRect(&rcTarget, LOWORD(lParam),
                    HIWORD(lParam), pt.x, pt.y);
            }

            else if ((pt.x > (LONG)LOWORD(lParam)) &&
                (pt.y < (LONG)HIWORD(lParam)))
            {
                SetRect(&rcTarget, LOWORD(lParam), pt.y,
                    pt.x, HIWORD(lParam));
            }
            else
            {
                SetRect(&rcTarget, pt.x, pt.y, LOWORD(lParam),
                    HIWORD(lParam));
            }

            // Draw the new target rectangle.  

            Rectangle(hdc, rcTarget.left, rcTarget.top,
                rcTarget.right, rcTarget.bottom);
            ReleaseDC(hWnd, hdc);
        }
        return 0;

    case WM_LBUTTONUP:

        // If one of the "size" flags is TRUE, reset it to FALSE,  
        // and then set the corresponding "draw" flag. Invalidate  
        // the appropriate rectangle and issue a WM_PAINT message.  

        if (fSizeEllipse)
        {
            fSizeEllipse = FALSE;
            fDrawEllipse = TRUE;
        }

        if (fSizeRectangle)
        {
            fSizeRectangle = FALSE;
            fDrawRectangle = TRUE;
        }

        if (fSizeRoundRect)
        {
            fSizeRoundRect = FALSE;
            fDrawRoundRect = TRUE;
        }

        if (fDrawEllipse || fDrawRectangle || fDrawRoundRect)
        {
            InvalidateRect(hWnd, &rcTarget, TRUE);
            UpdateWindow(hwnd);
        }

        // Release the cursor.  

        ClipCursor((LPRECT)NULL);
        return 0;

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
