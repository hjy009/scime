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
	void SetCharCXCY(int nFontSize, LPCTSTR strFont = _T("宋体"));
	void ReSetInputText();
	void KeepTransparent(CDC *pDC);
	void KeepNoTransparent(CDC *pDC);
	void CreateMyCaret(CPoint point);
	void DestroyMyCaret();

public:
	TEXTOUTSTATE InputTextState;
	CPoint m_ptPrev;//鼠标移动时点（之前的点）
	CPoint m_ptCurrent;//鼠标移动时点（当前的点）

	BOOL m_blMouseDown;//鼠标左键处于按下的状态标志

	COLORREF m_clrLineColor;//线颜色
	COLORREF m_clrFontColor;//字体颜色

	int m_nLineWidth;//线宽

	BOOL m_blMouseTrack;//是否处于鼠标轨迹状态
	BOOL m_blScreenShots;//是否处于截图放大局面的状态

	CFont m_fontMain;//字体
	int m_nFontSize;//字体大小（字号）
	int m_cxChar;//当前字体字号下的字体宽度
	int m_cyChar;//当前字体字号下的字体高度

	CPoint m_ptCaretLineBeginning;//输入光标的位置点
	CString m_strInputText;//输入的文本
	CString m_strFontName;//字体名称

	CRect m_rtScreenShot;
	BOOL m_blMenuEnabled;
	


	
	
};

