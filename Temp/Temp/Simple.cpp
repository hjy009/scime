#include <afxwin.h>
#include "Simple.h"
#include"CMainFrame.h"
#include"resource.h"




SimpleApp::SimpleApp()
{
	//���ô���͸��ɫ
	m_clrWndTransparencyColorKey = RGB(147, 147, 148);
	//ȱʡ�Ĳ�͸��ɫ
	m_clrWndNoTransparencyColorKey = RGB(255, 0, 19);
}


SimpleApp::~SimpleApp()
{
}


BOOL SimpleApp::InitInstance()
{
	// TODO: �ڴ����ר�ô����/����û���
	
	//�������ڲ���ʾ�����´���
	m_pMainWnd = new CMainFrame();
	////////////////////////////////////////////////////////////////////////////
	//���ô�������ʱ��󻯣��ҳ�Ϊ����ڡ�

	m_nCmdShow = SW_SHOWMAXIMIZED;

	////////////////////////////////////////////////////////////////////////////

	m_pMainWnd->ShowWindow(m_nCmdShow);
	m_pMainWnd->UpdateWindow();


	//

	m_pMainWnd->SetIcon(LoadIcon(IDI_SIMPLEICON), TRUE);

	m_pMainWnd->SetIcon(LoadIcon(IDI_SIMPLEICON), FALSE);


	////////////////////////////////////////////////////////////////////////////
	//���ô��ڵ���չ��ʽ��WS_EX_LAYERED,���γ�͸�����ڷ��

	CMainFrame *pWnd = (CMainFrame *)m_pMainWnd;
	LONG nExStyle = ::GetWindowLong(pWnd->m_hWnd, GWL_EXSTYLE);
	nExStyle |= WS_EX_LAYERED;
	::SetWindowLong(pWnd->m_hWnd, GWL_EXSTYLE, nExStyle);
	//���ô��ڣ���͸��ɫ��ʵ��͸�����ڡ���������ͨ��͸����������͸�����ڣ�LWA_ALPHA��
	::SetLayeredWindowAttributes(pWnd->m_hWnd,
		m_clrWndTransparencyColorKey,
		255,
		LWA_COLORKEY);

	////////////////////////////////////////////////////////////////////////////



	return CWinApp::InitInstance();
}
