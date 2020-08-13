#pragma once

#define WM_CUSTOM_INPUTTING WM_USER+10
#define WM_CUSTOM_ENDINPUT WM_USER+11
#define WM_CUSTOM_TEXTOUT WM_USER+12
#define WM_CUSTOM_EXITTEXTOUT WM_USER+13
#define WM_CUSTOM_SETFOCUS WM_USER+14
#define WM_CUSTOM_KILLFOCUS WM_USER+15

struct TEXTOUTSTATE
{
	BOOL blWndFocus;
	BOOL blTextOut;
	BOOL blInputting;
};

class CMainFrame :
	public CFrameWnd
{
public:
	CMainFrame();
	~CMainFrame();

public:
	DECLARE_MESSAGE_MAP()

	afx_msg void OnContextMenu(CWnd* /*pWnd*/, CPoint /*point*/);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnPaint();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnOperationClose();
	afx_msg void OnOperationClear();
	afx_msg void OnColorRed();
	afx_msg void OnColorYellow();
	afx_msg void OnColorGreen();
	afx_msg void OnColorBlack();
	afx_msg void OnColorWhite();
	afx_msg void OnLinewidth1();
	afx_msg void OnLinewidth2();
	afx_msg void OnLinewidth5();
	afx_msg void OnLinewidth10();
	afx_msg void OnUpdateColorRed(CCmdUI *pCmdUI);
	afx_msg void OnUpdateColorGreen(CCmdUI *pCmdUI);
	afx_msg void OnUpdateColorYellow(CCmdUI *pCmdUI);
	afx_msg void OnUpdateColorBlack(CCmdUI *pCmdUI);
	afx_msg void OnUpdateColorWhite(CCmdUI *pCmdUI);
	afx_msg void OnUpdateLinewidth1(CCmdUI *pCmdUI);
	afx_msg void OnUpdateLinewidth10(CCmdUI *pCmdUI);
	afx_msg void OnUpdateLinewidth2(CCmdUI *pCmdUI);
	afx_msg void OnUpdateLinewidth5(CCmdUI *pCmdUI);
	afx_msg void OnMouseTrack();
	afx_msg void OnUpdateMouseTrack(CCmdUI *pCmdUI);
	afx_msg void OnTextout();
	afx_msg void OnUpdateTextout(CCmdUI *pCmdUI);
	afx_msg void OnTextcolorBlack();
	afx_msg void OnUpdateTextcolorBlack(CCmdUI *pCmdUI);
	afx_msg void OnTextcolorBlue();
	afx_msg void OnUpdateTextcolorBlue(CCmdUI *pCmdUI);
	afx_msg void OnTextcolorGreen();
	afx_msg void OnUpdateTextcolorGreen(CCmdUI *pCmdUI);
	afx_msg void OnTextcolorRed();
	afx_msg void OnUpdateTextcolorRed(CCmdUI *pCmdUI);
	afx_msg void OnTextcolorWhite();
	afx_msg void OnUpdateTextcolorWhite(CCmdUI *pCmdUI);
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnTextpoint125();
	afx_msg void OnUpdateTextpoint125(CCmdUI *pCmdUI);
	afx_msg void OnTextpoint350();
	afx_msg void OnUpdateTextpoint350(CCmdUI *pCmdUI);
	afx_msg void OnTextpoint150();
	afx_msg void OnUpdateTextpoint150(CCmdUI *pCmdUI);
	afx_msg void OnTextpoint250();
	afx_msg void OnUpdateTextpoint250(CCmdUI *pCmdUI);
	afx_msg void OnOperationMinimized();
	afx_msg void OnScreenshots();
	afx_msg void OnUpdateScreenshots(CCmdUI *pCmdUI);
	afx_msg void OnGetMinMaxInfo(MINMAXINFO* lpMMI);
	afx_msg void OnOperationMaxmized();
	afx_msg void OnOperationNormal();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnTextpoint750();
	afx_msg void OnUpdateTextpoint750(CCmdUI *pCmdUI);
	//custom message
	afx_msg LRESULT OnCustomSetFocus(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnCustomKillFocus(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnCustomTextOut(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnCustomExitTextOut(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnCustomInputting(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnCustomEndInput(WPARAM wParam, LPARAM lParam);




public:
	void DrawInputText(CDC *pDC);
	void SetCaretPosition(CDC *pDC);
	void SetCharCXCY(int nFontSize, LPCTSTR strFont = _T("����"));
	void ReSetInputText();
	void KeepTransparent(CDC *pDC);
	void KeepNoTransparent(CDC *pDC);
	void CreateMyCaret(CPoint point);
	void DestroyMyCaret();

public:
	TEXTOUTSTATE InputTextState;
	CPoint m_ptPrev;//����ƶ�ʱ�㣨֮ǰ�ĵ㣩
	CPoint m_ptCurrent;//����ƶ�ʱ�㣨��ǰ�ĵ㣩

	BOOL m_blMouseDown;//���������ڰ��µ�״̬��־

	COLORREF m_clrLineColor;//����ɫ
	COLORREF m_clrFontColor;//������ɫ

	int m_nLineWidth;//�߿�

	BOOL m_blMouseTrack;//�Ƿ������켣״̬
	BOOL m_blScreenShots;//�Ƿ��ڽ�ͼ�Ŵ�����״̬

	CFont m_fontMain;//����
	int m_nFontSize;//�����С���ֺţ�
	int m_cxChar;//��ǰ�����ֺ��µ�������
	int m_cyChar;//��ǰ�����ֺ��µ�����߶�

	CPoint m_ptCaretLineBeginning;//�������λ�õ�
	CString m_strInputText;//������ı�
	CString m_strFontName;//��������

	CRect m_rtScreenShot;
	BOOL m_blMenuEnabled;
	


	
	
};

