#pragma once

enum STATE{
	OCCUPY = 0,
	FREE = 1
};

struct PhoneWindow
{
public:
	PhoneWindow(CWnd *pWnd, STATE status);
	~PhoneWindow(void);

	CWnd *m_pWnd;
	STATE state;

	void setState(STATE st);
};

