#include <afxwin.h>
#include "Simple.h"
#include"CMainFrame.h"
#include"resource.h"




SimpleApp::SimpleApp()
{
	//设置窗口透明色
	m_clrWndTransparencyColorKey = RGB(147, 147, 148);
	//缺省的不透明色
	m_clrWndNoTransparencyColorKey = RGB(255, 0, 19);
}


SimpleApp::~SimpleApp()
{
}


BOOL SimpleApp::InitInstance()
{
	// TODO: 在此添加专用代码和/或调用基类
	
	//创建窗口并显示、更新窗口
	m_pMainWnd = new CMainFrame();
	////////////////////////////////////////////////////////////////////////////
	//设置窗口启动时最大化，且成为活动窗口。

	m_nCmdShow = SW_SHOWMAXIMIZED;

	////////////////////////////////////////////////////////////////////////////

	m_pMainWnd->ShowWindow(m_nCmdShow);
	m_pMainWnd->UpdateWindow();


	//

	m_pMainWnd->SetIcon(LoadIcon(IDI_SIMPLEICON), TRUE);

	m_pMainWnd->SetIcon(LoadIcon(IDI_SIMPLEICON), FALSE);


	////////////////////////////////////////////////////////////////////////////
	//设置窗口的扩展样式：WS_EX_LAYERED,以形成透明窗口风格。

	CMainFrame *pWnd = (CMainFrame *)m_pMainWnd;
	LONG nExStyle = ::GetWindowLong(pWnd->m_hWnd, GWL_EXSTYLE);
	nExStyle |= WS_EX_LAYERED;
	::SetWindowLong(pWnd->m_hWnd, GWL_EXSTYLE, nExStyle);
	//设置窗口：用透明色来实现透明窗口。（还可以通过透明度来设置透明窗口：LWA_ALPHA）
	::SetLayeredWindowAttributes(pWnd->m_hWnd,
		m_clrWndTransparencyColorKey,
		255,
		LWA_COLORKEY);

	////////////////////////////////////////////////////////////////////////////



	return CWinApp::InitInstance();
}
