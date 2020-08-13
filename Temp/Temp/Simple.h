#pragma once
class SimpleApp :
	public CWinApp
{
public:
	SimpleApp();
	~SimpleApp();
	virtual BOOL InitInstance();
	COLORREF m_clrWndTransparencyColorKey;
	COLORREF m_clrWndNoTransparencyColorKey;
};



