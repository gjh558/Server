#include "stdafx.h"
#include "PhoneWindow.h"


PhoneWindow::PhoneWindow(CWnd *pWnd, STATE status)
	:m_pWnd(pWnd),
	state(status)
{
}


PhoneWindow::~PhoneWindow(void)
{
}

void PhoneWindow::setState(STATE st)
{
		state = st;
}
