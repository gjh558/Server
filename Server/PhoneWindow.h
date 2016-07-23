#pragma once

enum STATE {
	OCCUPIED = 0,
	FREE = 1
};

class PhoneWindow
{
public:
	PhoneWindow(CWnd *pWnd);
	~PhoneWindow(void);

	CWnd *m_pWnd;
	STATE state;
};

