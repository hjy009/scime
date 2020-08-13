//#include <afxwin.h>
#include"StdAfx.h"
#include "CMainFrame.h"
#include"Simple.h"
#include"resource.h"


SimpleApp theApp;

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_CONTEXTMENU()
	ON_WM_CREATE()
	ON_WM_PAINT()
	
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_COMMAND(ID_OPERATION_CLOSE, &CMainFrame::OnOperationClose)
	ON_COMMAND(ID_OPERATION_CLEAR, &CMainFrame::OnOperationClear)
	ON_COMMAND(ID_COLOR_RED, &CMainFrame::OnColorRed)
	ON_COMMAND(ID_COLOR_YELLOW, &CMainFrame::OnColorYellow)
	ON_COMMAND(ID_COLOR_GREEN, &CMainFrame::OnColorGreen)
	ON_COMMAND(ID_COLOR_BLACK, &CMainFrame::OnColorBlack)
	ON_COMMAND(ID_COLOR_WHITE, &CMainFrame::OnColorWhite)
	ON_COMMAND(ID_LINEWIDTH_1, &CMainFrame::OnLinewidth1)
	ON_COMMAND(ID_LINEWIDTH_2, &CMainFrame::OnLinewidth2)
	ON_COMMAND(ID_LINEWIDTH_5, &CMainFrame::OnLinewidth5)
	ON_COMMAND(ID_LINEWIDTH_10, &CMainFrame::OnLinewidth10)
	ON_UPDATE_COMMAND_UI(ID_COLOR_RED, &CMainFrame::OnUpdateColorRed)
	ON_UPDATE_COMMAND_UI(ID_COLOR_GREEN, &CMainFrame::OnUpdateColorGreen)
	ON_UPDATE_COMMAND_UI(ID_COLOR_YELLOW, &CMainFrame::OnUpdateColorYellow)
	ON_UPDATE_COMMAND_UI(ID_COLOR_BLACK, &CMainFrame::OnUpdateColorBlack)
	ON_UPDATE_COMMAND_UI(ID_COLOR_WHITE, &CMainFrame::OnUpdateColorWhite)
	ON_UPDATE_COMMAND_UI(ID_LINEWIDTH_1, &CMainFrame::OnUpdateLinewidth1)
	ON_UPDATE_COMMAND_UI(ID_LINEWIDTH_10, &CMainFrame::OnUpdateLinewidth10)
	ON_UPDATE_COMMAND_UI(ID_LINEWIDTH_2, &CMainFrame::OnUpdateLinewidth2)
	ON_UPDATE_COMMAND_UI(ID_LINEWIDTH_5, &CMainFrame::OnUpdateLinewidth5)
	ON_COMMAND(ID_MOUSETRACK, &CMainFrame::OnMouseTrack)
	ON_UPDATE_COMMAND_UI(ID_MOUSETRACK, &CMainFrame::OnUpdateMouseTrack)
	ON_COMMAND(ID_TEXTOUT, &CMainFrame::OnTextout)
	ON_UPDATE_COMMAND_UI(ID_TEXTOUT, &CMainFrame::OnUpdateTextout)
	ON_COMMAND(ID_TEXTCOLOR_BLACK, &CMainFrame::OnTextcolorBlack)
	ON_UPDATE_COMMAND_UI(ID_TEXTCOLOR_BLACK, &CMainFrame::OnUpdateTextcolorBlack)
	ON_COMMAND(ID_TEXTCOLOR_BLUE, &CMainFrame::OnTextcolorBlue)
	ON_UPDATE_COMMAND_UI(ID_TEXTCOLOR_BLUE, &CMainFrame::OnUpdateTextcolorBlue)
	ON_COMMAND(ID_TEXTCOLOR_GREEN, &CMainFrame::OnTextcolorGreen)
	ON_UPDATE_COMMAND_UI(ID_TEXTCOLOR_GREEN, &CMainFrame::OnUpdateTextcolorGreen)
	ON_COMMAND(ID_TEXTCOLOR_RED, &CMainFrame::OnTextcolorRed)
	ON_UPDATE_COMMAND_UI(ID_TEXTCOLOR_RED, &CMainFrame::OnUpdateTextcolorRed)
	ON_COMMAND(ID_TEXTCOLOR_WHITE, &CMainFrame::OnTextcolorWhite)
	ON_UPDATE_COMMAND_UI(ID_TEXTCOLOR_WHITE, &CMainFrame::OnUpdateTextcolorWhite)
	ON_WM_CHAR()
	ON_COMMAND(ID_TEXTPOINT_125, &CMainFrame::OnTextpoint125)
	ON_UPDATE_COMMAND_UI(ID_TEXTPOINT_125, &CMainFrame::OnUpdateTextpoint125)
	ON_COMMAND(ID_TEXTPOINT_150, &CMainFrame::OnTextpoint150)
	ON_UPDATE_COMMAND_UI(ID_TEXTPOINT_150, &CMainFrame::OnUpdateTextpoint150)
	ON_COMMAND(ID_TEXTPOINT_250, &CMainFrame::OnTextpoint250)
	ON_UPDATE_COMMAND_UI(ID_TEXTPOINT_250, &CMainFrame::OnUpdateTextpoint250)
	ON_COMMAND(ID_TEXTPOINT_350, &CMainFrame::OnTextpoint350)
	ON_UPDATE_COMMAND_UI(ID_TEXTPOINT_350, &CMainFrame::OnUpdateTextpoint350)
	ON_COMMAND(ID_SCREENSHOTS, &CMainFrame::OnScreenshots)
	ON_UPDATE_COMMAND_UI(ID_SCREENSHOTS, &CMainFrame::OnUpdateScreenshots)
	ON_COMMAND(ID_OPERATION_MINIMIZED, &CMainFrame::OnOperationMinimized)
	ON_WM_GETMINMAXINFO()
	ON_COMMAND(ID_OPERATION_MAXMIZED, &CMainFrame::OnOperationMaxmized)
	ON_COMMAND(ID_OPERATION_NORMAL, &CMainFrame::OnOperationNormal)
	ON_WM_SIZE()
	ON_COMMAND(ID_TEXTPOINT_750, &CMainFrame::OnTextpoint750)
	ON_UPDATE_COMMAND_UI(ID_TEXTPOINT_750, &CMainFrame::OnUpdateTextpoint750)

	//custom message
	ON_MESSAGE(WM_CUSTOM_SETFOCUS, &OnCustomSetFocus)
	ON_MESSAGE(WM_CUSTOM_KILLFOCUS, &OnCustomKillFocus)
	ON_MESSAGE(WM_CUSTOM_TEXTOUT, &OnCustomTextOut)
	ON_MESSAGE(WM_CUSTOM_EXITTEXTOUT, &OnCustomExitTextOut)
	ON_MESSAGE(WM_CUSTOM_INPUTTING, &OnCustomInputting)
	ON_MESSAGE(WM_CUSTOM_ENDINPUT, &OnCustomEndInput)
	//custom message end

END_MESSAGE_MAP()

//////////////////////////////////////////////////////////
//��Ĺ���������


CMainFrame::CMainFrame()
{
	InputTextState.blInputting = FALSE;
	InputTextState.blTextOut = FALSE;
	InputTextState.blWndFocus = FALSE;

	m_blMenuEnabled = TRUE;
	m_cxChar = 30;
	m_cyChar = 70;
	m_rtScreenShot.left = m_rtScreenShot.top = 0;
	m_rtScreenShot.right = m_rtScreenShot.bottom = 0;
	m_strFontName = _T("����");
	m_ptCaretLineBeginning.x = 0;
	m_ptCaretLineBeginning.y = 0;
	m_nFontSize = 350;
	m_blScreenShots = FALSE;
	m_blMouseTrack = TRUE;
	m_blMouseDown = FALSE;
	m_nLineWidth = 5;
	m_clrLineColor = RGB(255, 0, 0);
	m_clrFontColor = RGB(255, 0, 0);
	m_bAutoMenuEnable = FALSE;


	CString strWndClass = AfxRegisterWndClass(CS_HREDRAW | CS_VREDRAW,
		theApp.LoadStandardCursor(IDC_ARROW),
		(HBRUSH)(COLOR_3DFACE+1),
		theApp.LoadIcon(IDI_SIMPLEICON));
	Create(strWndClass, _T("Simple"), WS_OVERLAPPEDWINDOW,rectDefault,NULL,NULL);
	
}

CMainFrame::~CMainFrame()
{
}

//��Ĺ���������
//////////////////////////////////////////////////////////




//////////////////////////////////////////////////////////
//�����¼�

	//���ڴ���
int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  �ڴ������ר�õĴ�������
	ModifyStyle(WS_CAPTION|WS_THICKFRAME, 0);
	ModifyStyleEx( WS_EX_CLIENTEDGE, NULL);

		
	SetWindowPos(&wndTopMost, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);


	//��ʼ���ַ��Ŀ�Ⱥ͸߶�ֵ
	SetCharCXCY(m_nFontSize, m_strFontName);



	return 0;
}
	//����ˢ�»���
void CMainFrame::OnPaint()
{
	////////////////////////////////////////////////////////////////////////////
	//���ָ����͸��ɫ��ʵ�ִ���͸������
	//��OnPaint()���������ʹ��CPaintDC����Ҫʹ��CClientDC����Ϊ������˸�����������������
	CPaintDC dc(this);
	
	if(InputTextState.blWndFocus)
		KeepTransparent(&dc);
	else 
		KeepNoTransparent(&dc);
	

	
	
	
	////////////////////////////////////////////////////////////////////////////

	
}
	//���ڴ�С�ı��¼�
void CMainFrame::OnSize(UINT nType, int cx, int cy)
{
	CFrameWnd::OnSize(nType, cx, cy);

	// TODO: �ڴ˴������Ϣ����������

	switch (nType)
	{
	case SIZE_MAXIMIZED:
		m_blMenuEnabled = TRUE;
		SendMessage(WM_CUSTOM_SETFOCUS);

		if (InputTextState.blTextOut) {
			ReSetInputText();
		}
		break;


	case SIZE_RESTORED:
	case SIZE_MINIMIZED:
		m_blMenuEnabled = FALSE;
		SendMessage(WM_CUSTOM_KILLFOCUS);
		//fdd
		if (InputTextState.blInputting) {
			ReSetInputText();
			DestroyMyCaret();
			SendMessage(WM_CUSTOM_ENDINPUT);
		}


		break;

	default:

		break;
	}
	Invalidate();
}
void CMainFrame::OnGetMinMaxInfo(MINMAXINFO* lpMMI)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ


	CClientDC dc(this);
	WINDOWPLACEMENT wp;
	GetWindowPlacement(&wp);
	wp.rcNormalPosition.left = 5;
	wp.rcNormalPosition.top = dc.GetDeviceCaps(VERTRES) / 4 * 3;
	wp.rcNormalPosition.right = 105;
	wp.rcNormalPosition.bottom = dc.GetDeviceCaps(VERTRES) / 4 * 3 + 80;

	SetWindowPlacement(&wp);



	CFrameWnd::OnGetMinMaxInfo(lpMMI);
}
	//�Ҽ��˵�
void CMainFrame::OnContextMenu(CWnd* pWnd, CPoint point)
{
	// TODO: �ڴ˴������Ϣ����������
	CRect rect;
	GetClientRect(&rect);
	//��Ϊpoint����Ļ���꣬������Ҫ�ѿͻ�������ת��Ϊ��Ļ����
	ClientToScreen(&rect);

	if (rect.PtInRect(point)) {
		CMenu popMenu;
		popMenu.LoadMenu(MAKEINTRESOURCE(IDR_MENU_CONTEXT));


		int nID = (popMenu.GetSubMenu(0)->TrackPopupMenu(
			TPM_LEFTALIGN | TPM_LEFTBUTTON | TPM_RIGHTBUTTON | TPM_RETURNCMD,
			point.x,
			point.y,
			this));

		SendMessage(WM_COMMAND, nID);

	}


}
	//����¼�
void CMainFrame::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	//���������±�־
	m_blMouseDown = TRUE;
	if (!m_blMenuEnabled)
		return;
	//�������
	SetCapture();
	//������MouseTrack or ScreenShots״̬ʱ
	if (m_blMouseTrack|| m_blScreenShots) {
		m_ptCurrent = m_ptPrev = point;
		if (m_blScreenShots) {
			//Ҫ��ȡ���ε����Ͻ�����Ϊ����������ʱ����������
			m_rtScreenShot.left = point.x;
			m_rtScreenShot.top = point.y;
			
		}
	}

	//TextOut--fdd
	if (InputTextState.blWndFocus&&InputTextState.blTextOut) {
		SendMessage(WM_CUSTOM_INPUTTING);
		ReSetInputText();
		CreateMyCaret(point);
		

	}

	
	CFrameWnd::OnLButtonDown(nFlags, point);
}
void CMainFrame::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if (!m_blMenuEnabled)
		return;
	//MouseDown
	if (m_blMouseDown) {

		CClientDC dc(this);
		CPen pen(PS_SOLID, m_nLineWidth, m_clrLineColor);
		CPen *pPen = dc.SelectObject(&pen);
		//MouseTrack
		if (m_blMouseTrack) {
			dc.MoveTo(m_ptPrev);
			m_ptCurrent = point;
			dc.LineTo(m_ptCurrent);
			m_ptPrev = m_ptCurrent;

		}
		//ScreenShots
		else if (m_blScreenShots) {
			//ʼ�հ�ROP2��R2_NOTģʽ����
				//�Ȳ���֮ǰ������
			int OldRop2 = dc.SetROP2(R2_NOT);
			dc.MoveTo(m_ptPrev);
			dc.LineTo(m_ptPrev.x, m_ptCurrent.y);
			dc.LineTo(m_ptCurrent);
			dc.LineTo(m_ptCurrent.x, m_ptPrev.y);
			dc.LineTo(m_ptPrev);

				//�ٻ�����㵽��ǰ�������
			dc.MoveTo(m_ptPrev);
			dc.LineTo(m_ptPrev.x, point.y);
			dc.LineTo(point);
			dc.LineTo(point.x, m_ptPrev.y);
			dc.LineTo(m_ptPrev);
			dc.SetROP2(OldRop2);

				//���µ�ǰ�������Ϊ��ǰ��������
			m_ptCurrent = point;

		}
		dc.SelectObject(pPen);


	}
	



	CFrameWnd::OnMouseMove(nFlags, point);
}
void CMainFrame::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	//�������ͷű�־
	m_blMouseDown = FALSE;
	if (!m_blMenuEnabled)
		return;
	//ScreenShots
	if (m_blScreenShots) {
		//������ĻDC������ΪNULLʱ������ĻDC��
		CClientDC dc(NULL);
		CRect rect;
		GetClientRect(&rect);

		//Ҫ��ȡ�ľ������½�����Ϊ��ǰ��������
		m_rtScreenShot.right = point.x;
		m_rtScreenShot.bottom = point.y;
		
		//������ƶ�ָ���ľ�������Ŵ�������Ļ
		dc.SetStretchBltMode(STRETCH_HALFTONE);
		dc.StretchBlt(
			rect.left, rect.top,
			rect.Width(), rect.Height(),
			&dc,
			m_rtScreenShot.left, m_rtScreenShot.top,
			m_rtScreenShot.Width(), m_rtScreenShot.Height(),
			SRCCOPY);
		//���³�ʼ��Ҫ��ȡ�ľ���ֵΪ0
		m_rtScreenShot.left = m_rtScreenShot.top = 0;
		m_rtScreenShot.right = m_rtScreenShot.bottom = 0;
		
	}

	//�ͷŲ�����
	ReleaseCapture();
	CFrameWnd::OnLButtonUp(nFlags, point);
}
	//�����¼�
void CMainFrame::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	//�ַ����������
	if ((!InputTextState.blWndFocus) ||
		(!InputTextState.blTextOut) ||
		(!InputTextState.blInputting))
		return;

	CClientDC dc(this);
	CRect rect;
	GetClientRect(&rect);
	switch (nChar)
	{
	case VK_RETURN:
		m_strInputText.Empty();
		m_ptCaretLineBeginning.y += (WCHAR)m_cyChar;
		break;
	case VK_BACK:

		break;

	default:

		m_strInputText += (WCHAR)nChar;
		break;
	}

	HideCaret();
	DrawInputText(&dc);
	SetCaretPosition(&dc);
	ShowCaret();


	CFrameWnd::OnChar(nChar, nRepCnt, nFlags);
}


//�����¼�
//////////////////////////////////////////////////////////





////////////////////////////////////////////////////////////////////////////////////
//�˵��¼�

///////////////////////////�����л�////////////////////////
void CMainFrame::OnMouseTrack()
{
	// TODO: �ڴ���������������
	m_blMouseTrack = TRUE;
	//fdd
	if (InputTextState.blTextOut) {
		SendMessage(WM_CUSTOM_EXITTEXTOUT);
		if (InputTextState.blInputting) {
			SendMessage(WM_CUSTOM_ENDINPUT);

			DestroyMyCaret();
		}
		ReSetInputText();

	}
	m_blScreenShots = FALSE;
}
void CMainFrame::OnUpdateMouseTrack(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	pCmdUI->Enable(m_blMenuEnabled);
	pCmdUI->SetCheck(m_blMouseTrack);
}

void CMainFrame::OnTextout()
{
	// TODO: �ڴ���������������
	SendMessage(WM_CUSTOM_TEXTOUT);
	m_blScreenShots = FALSE;
	m_blMouseTrack = FALSE;





}
void CMainFrame::OnUpdateTextout(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	pCmdUI->Enable(m_blMenuEnabled);

	pCmdUI->SetCheck(InputTextState.blTextOut);
}

void CMainFrame::OnScreenshots()
{
	// TODO: �ڴ���������������
	m_blScreenShots = TRUE;
	m_blMouseTrack = FALSE;
	//fdd
	if (InputTextState.blTextOut) {
		SendMessage(WM_CUSTOM_EXITTEXTOUT);
		if (InputTextState.blInputting) {
			SendMessage(WM_CUSTOM_ENDINPUT);
			DestroyMyCaret();
		}
		ReSetInputText();
	}

}
void CMainFrame::OnUpdateScreenshots(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	pCmdUI->Enable(m_blMenuEnabled);

	pCmdUI->SetCheck(m_blScreenShots);
}

///////////////////////////�����л�////////////////////////


///////////////////////////�Զ��崰�ڴ�С�����²���////////////////////////

//ʹ�������
void CMainFrame::OnOperationMaxmized()
{
	// TODO: �ڴ���������������
	SendMessage(WM_SYSCOMMAND, SC_MAXIMIZE);
}
//ʹ����������С״̬
void CMainFrame::OnOperationNormal()
{
	// TODO: �ڴ���������������

	SendMessage(WM_SYSCOMMAND, SC_RESTORE);

}
//ʹ������С��
void CMainFrame::OnOperationMinimized()
{
	// TODO: �ڴ���������������
	
	SendMessage(WM_SYSCOMMAND, SC_MINIMIZE);
}
//�˳�����
void CMainFrame::OnOperationClose()
{
	// TODO: �ڴ���������������
	SendMessage(WM_SYSCOMMAND, SC_CLOSE);
}
//ˢ�´���
void CMainFrame::OnOperationClear()
{
	// TODO: �ڴ���������������
	Invalidate();
	

}

///////////////////////////�Զ��崰�ڴ�С�����µĲ���////////////////////////



///////////////////////////������ɫ�����////////////////////////


void CMainFrame::OnColorRed()
{
	// TODO: �ڴ���������������
	m_clrLineColor = RGB(255, 0, 0);

	
}


void CMainFrame::OnColorYellow()
{
	// TODO: �ڴ���������������
	m_clrLineColor = RGB(255, 255, 0);
}


void CMainFrame::OnColorGreen()
{
	// TODO: �ڴ���������������
	m_clrLineColor = RGB(0, 255, 0);
}


void CMainFrame::OnColorBlack()
{
	// TODO: �ڴ���������������
	m_clrLineColor = RGB(0, 0, 0);
}


void CMainFrame::OnColorWhite()
{
	// TODO: �ڴ���������������
	m_clrLineColor = RGB(255, 255, 255);
}


void CMainFrame::OnLinewidth1()
{
	// TODO: �ڴ���������������
	m_nLineWidth = 1;
}


void CMainFrame::OnLinewidth2()
{
	// TODO: �ڴ���������������
	m_nLineWidth = 2;

}


void CMainFrame::OnLinewidth5()
{
	// TODO: �ڴ���������������
	m_nLineWidth = 5;

}


void CMainFrame::OnLinewidth10()
{
	// TODO: �ڴ���������������
	m_nLineWidth = 10;

}


void CMainFrame::OnUpdateColorRed(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	pCmdUI->SetCheck(m_clrLineColor == RGB(255, 0, 0));
}


void CMainFrame::OnUpdateColorGreen(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	pCmdUI->SetCheck(m_clrLineColor == RGB(0, 255, 0));
}


void CMainFrame::OnUpdateColorYellow(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	pCmdUI->SetCheck(m_clrLineColor == RGB(255, 255, 0));
}


void CMainFrame::OnUpdateColorBlack(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	pCmdUI->SetCheck(m_clrLineColor == RGB(0, 0, 0));
}


void CMainFrame::OnUpdateColorWhite(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	pCmdUI->SetCheck(m_clrLineColor == RGB(255, 255, 255));
}


void CMainFrame::OnUpdateLinewidth1(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	pCmdUI->SetCheck(m_nLineWidth == 1);
}


void CMainFrame::OnUpdateLinewidth10(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	pCmdUI->SetCheck(m_nLineWidth == 10);
}


void CMainFrame::OnUpdateLinewidth2(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	pCmdUI->SetCheck(m_nLineWidth == 2);
}


void CMainFrame::OnUpdateLinewidth5(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	pCmdUI->SetCheck(m_nLineWidth == 5);
}


///////////////////////////������ɫ�����////////////////////////



///////////////////////////������ɫ����С////////////////////////




void CMainFrame::OnTextcolorBlack()
{
	// TODO: �ڴ���������������

	//fdd
	m_clrFontColor = RGB(0, 0, 0);

	if (InputTextState.blWndFocus&&
		InputTextState.blTextOut&&
		InputTextState.blInputting) 
	{
		CreateMyCaret(GetCaretPos());
	}
	ReSetInputText();
}
void CMainFrame::OnUpdateTextcolorBlack(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	pCmdUI->SetCheck(m_clrFontColor == RGB(0, 0, 0));

}


void CMainFrame::OnTextcolorBlue()
{
	// TODO: �ڴ���������������
	m_clrFontColor = RGB(0, 0, 255);

	if (InputTextState.blWndFocus&&
		InputTextState.blTextOut&&
		InputTextState.blInputting)
	{
		CreateMyCaret(GetCaretPos());
	}

	ReSetInputText();
}
void CMainFrame::OnUpdateTextcolorBlue(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	pCmdUI->SetCheck(m_clrFontColor == RGB(0, 0, 255));

}


void CMainFrame::OnTextcolorGreen()
{
	// TODO: �ڴ���������������
	m_clrFontColor = RGB(0, 255, 0);

	if (InputTextState.blWndFocus&&
		InputTextState.blTextOut&&
		InputTextState.blInputting)
	{
		CreateMyCaret(GetCaretPos());
	}

	ReSetInputText();
}
void CMainFrame::OnUpdateTextcolorGreen(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	pCmdUI->SetCheck(m_clrFontColor == RGB(0, 255, 0));

}


void CMainFrame::OnTextcolorRed()
{
	// TODO: �ڴ���������������
	m_clrFontColor = RGB(255, 0, 0);

	if (InputTextState.blWndFocus&&
		InputTextState.blTextOut&&
		InputTextState.blInputting)
	{
		CreateMyCaret(GetCaretPos());
	}

	ReSetInputText();
}
void CMainFrame::OnUpdateTextcolorRed(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	pCmdUI->SetCheck(m_clrFontColor == RGB(255, 0, 0));

}

void CMainFrame::OnTextcolorWhite()
{
	// TODO: �ڴ���������������
	m_clrFontColor = RGB(255, 255, 255);

	if (InputTextState.blWndFocus&&
		InputTextState.blTextOut&&
		InputTextState.blInputting)
	{
		CreateMyCaret(GetCaretPos());
	}

	ReSetInputText();
}
void CMainFrame::OnUpdateTextcolorWhite(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	pCmdUI->SetCheck(m_clrFontColor == RGB(255, 255, 255));
}

void CMainFrame::OnTextpoint125()
{
	// TODO: �ڴ���������������
	m_nFontSize = 125;
	SetCharCXCY(125, m_strFontName);
	if (InputTextState.blWndFocus&&
		InputTextState.blTextOut&&
		InputTextState.blInputting)
	{
		CreateMyCaret(GetCaretPos());
	}
	ReSetInputText();

}
void CMainFrame::OnUpdateTextpoint125(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	pCmdUI->SetCheck(m_nFontSize == 125);
}

void CMainFrame::OnTextpoint150()
{
	// TODO: �ڴ���������������
	m_nFontSize = 150;
	SetCharCXCY(150, m_strFontName);
	if (InputTextState.blWndFocus&&
		InputTextState.blTextOut&&
		InputTextState.blInputting)
	{
		CreateMyCaret(GetCaretPos());
	}
	ReSetInputText();
}
void CMainFrame::OnUpdateTextpoint150(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	pCmdUI->SetCheck(m_nFontSize == 150);
}

void CMainFrame::OnTextpoint250()
{
	// TODO: �ڴ���������������
	m_nFontSize = 250;
	SetCharCXCY(250, m_strFontName);
	if (InputTextState.blWndFocus&&
		InputTextState.blTextOut&&
		InputTextState.blInputting)
	{
		CreateMyCaret(GetCaretPos());
	}
	ReSetInputText();
}
void CMainFrame::OnUpdateTextpoint250(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	pCmdUI->SetCheck(m_nFontSize == 250);
}

void CMainFrame::OnTextpoint350()
{
	// TODO: �ڴ���������������
	m_nFontSize = 350;
	SetCharCXCY(350, m_strFontName);
	if (InputTextState.blWndFocus&&
		InputTextState.blTextOut&&
		InputTextState.blInputting)
	{
		CreateMyCaret(GetCaretPos());
	}
	ReSetInputText();
}
void CMainFrame::OnUpdateTextpoint350(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	pCmdUI->SetCheck(m_nFontSize == 350);
}

void CMainFrame::OnTextpoint750()
{
	// TODO: �ڴ���������������
	m_nFontSize = 750;
	SetCharCXCY(750, m_strFontName);
	if (InputTextState.blWndFocus&&
		InputTextState.blTextOut&&
		InputTextState.blInputting)
	{
		CreateMyCaret(GetCaretPos());
	}
	ReSetInputText();
}
void CMainFrame::OnUpdateTextpoint750(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	pCmdUI->SetCheck(m_nFontSize == 750);
}

///////////////////////////������ɫ����С////////////////////////





//�˵��¼�����
////////////////////////////////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////////
//�Զ����¼�


LRESULT CMainFrame::OnCustomSetFocus(WPARAM wParam, LPARAM lParam) {

	InputTextState.blWndFocus = TRUE;
	return TRUE;

}
LRESULT CMainFrame::OnCustomKillFocus(WPARAM wParam, LPARAM lParam) {

	InputTextState.blWndFocus = FALSE;
	return TRUE;

}
LRESULT CMainFrame::OnCustomTextOut(WPARAM wParam, LPARAM lParam) {

	InputTextState.blTextOut = TRUE;
	return TRUE;
}
LRESULT CMainFrame::OnCustomExitTextOut(WPARAM wParam, LPARAM lParam) {

	InputTextState.blTextOut = FALSE;


	return TRUE;

}
LRESULT CMainFrame::OnCustomInputting(WPARAM wParam, LPARAM lParam) {

	InputTextState.blInputting = TRUE;

	return TRUE;

}
LRESULT CMainFrame::OnCustomEndInput(WPARAM wParam, LPARAM lParam) {

	InputTextState.blInputting = FALSE;

	return TRUE;

}




//�Զ����¼�
//////////////////////////////////////////////////////////////







//////////////////////////////////////////////////////////////
//�Զ��庯��
void CMainFrame::ReSetInputText()
{
	// TODO: �ڴ˴����ʵ�ִ���.
	m_strInputText.Empty();
	
}
void CMainFrame::SetCharCXCY(int nFontSize, LPCTSTR strFont)
{
	// TODO: �ڴ˴����ʵ�ִ���.
	CClientDC dc(this);
	m_fontMain.DeleteObject();
	m_fontMain.CreatePointFont(nFontSize, strFont);
	CFont *pOldFont = dc.SelectObject(&m_fontMain);
	TEXTMETRIC tm;
	dc.GetTextMetrics(&tm);
	m_cxChar = tm.tmAveCharWidth;
	m_cyChar = tm.tmHeight + tm.tmExternalLeading;
	dc.SelectObject(pOldFont);

}
void CMainFrame::DrawInputText(CDC *pDC) {
	CFont *pOldFont = pDC->SelectObject(&m_fontMain);
	COLORREF clrOldTextColor = pDC->SetTextColor(m_clrFontColor);
	pDC->SetBkMode(TRANSPARENT);
	pDC->TextOutW(m_ptCaretLineBeginning.x, m_ptCaretLineBeginning.y, m_strInputText);
	pDC->SetTextColor(clrOldTextColor);
	pDC->SelectObject(pOldFont);
}
void CMainFrame::SetCaretPosition(CDC *pDC) {
	CFont *pOldFont = pDC->SelectObject(&m_fontMain);
	CPoint point = m_ptCaretLineBeginning;
	point.x += pDC->GetTextExtent(m_strInputText).cx;
	SetCaretPos(point);
	pDC->SelectObject(pOldFont);

}
void CMainFrame::KeepTransparent(CDC *pDC)
{
	// TODO: �ڴ˴����ʵ�ִ���.

	CRect rect;
	GetClientRect(&rect);
	pDC->FillSolidRect(&rect, theApp.m_clrWndTransparencyColorKey);
}
void CMainFrame::KeepNoTransparent(CDC *pDC) {
	CRect rect;
	GetClientRect(&rect);
	pDC->FillSolidRect(&rect, theApp.m_clrWndTransparencyColorKey);

	//ԴͼƬ���ز���ȡ����Ϣ
	CBitmap bmpSource;
	bmpSource.LoadBitmapW(IDB_FLOATINGIMAGE);
	BITMAP bm;
	bmpSource.GetBitmap(&bm);
	CDC dcMemSource;
	dcMemSource.CreateCompatibleDC(pDC);
	CBitmap *pOldBmpSource = dcMemSource.SelectObject(&bmpSource);

	//������ɫͼƬ���ڴ�dc
	CBitmap bmpMask;
	bmpMask.CreateBitmap(bm.bmWidth, bm.bmHeight, 1, 1, NULL);
	CDC dcMemMask;
	dcMemMask.CreateCompatibleDC(pDC);
	CBitmap *pOldBmpMask = dcMemMask.SelectObject(&bmpMask);

	//����Դͼ�����ڰ׵ĵ�ɫͼƬ��Ҫ��ʾ�Ĳ���Ϊ��ɫ������ʾ�Ĳ���Ϊ��ɫ
	dcMemSource.SetBkColor(RGB(255, 255, 255));
	dcMemMask.BitBlt(0, 0, bm.bmWidth, bm.bmHeight, &dcMemSource, 0, 0, NOTSRCCOPY);
	//pDC->StretchBlt(0, 0, rect.Width(), rect.Height(), &dcMemMask, 0, 0, bm.bmWidth, bm.bmHeight, SRCCOPY);
	//ʹ��PlgBlt���������ݵ�ɫͼƬ��Դͼ����Ҫ��ʾ�Ĳ��ָ��Ƶ��ͻ�����
	POINT point[3];//�趨��ƽ���ı���Ϊ���Ρ�
	point[0].x = 0;
	point[0].y = 0;
	point[1].x = rect.Width();
	point[1].y = 0;
	point[2].x = 0;
	point[2].y = rect.Height();


	pDC->PlgBlt(point, &dcMemSource, 0, 0, bm.bmWidth, bm.bmHeight, bmpMask, 0, 0);
	//�ָ��ڴ�dc
	dcMemMask.SelectObject(pOldBmpMask);
	dcMemSource.SelectObject(pOldBmpSource);


	
}
void CMainFrame::CreateMyCaret(CPoint point)
{
	// TODO: �ڴ˴����ʵ�ִ���.

	CreateSolidCaret(m_cxChar / 7, m_cyChar);
	m_ptCaretLineBeginning = point;
	SetCaretPos(m_ptCaretLineBeginning);
	ShowCaret();
}
void CMainFrame::DestroyMyCaret()
{
	// TODO: �ڴ˴����ʵ�ִ���.
	HideCaret();
	m_ptCaretLineBeginning = GetCaretPos();
	::DestroyCaret();
	
}



//�Զ��庯������
//////////////////////////////////////////////////////////////






