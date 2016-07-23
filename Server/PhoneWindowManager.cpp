#include "stdafx.h"
#include "ServerDlg.h"
#include "PhoneWindow.h"
#include "PhoneWindowManager.h"
#include "VideoView.h"


CPhoneWindowManager::CPhoneWindowManager(CServerDlg *pServerDlg)
{
	init(pServerDlg);
}


CPhoneWindowManager::~CPhoneWindowManager(void)
{
	int i = 0;
	for (; i < mNumberOfWindows; i++)
	{
		delete(mPhoneWindows[i]);
	}

	mPhoneWindows.clear();
}

void CPhoneWindowManager::init(CServerDlg *pServerDlg)
{
	int i = IDC_STATIC1;
	for (; i < IDC_STATIC1 + 6; i++) {
		CWnd *wnd = pServerDlg->GetDlgItem(i);

		CRect rect;
		wnd->GetClientRect(&rect);
		CVideoView *pView = new CVideoView(wnd);
		pView->Create(IDD_DIALOG1, wnd);
		pView->MoveWindow(rect);
		pView->ShowWindow(SW_SHOW);
		wnd = pView->GetDlgItem(IDC_STATIC_SHOW);

		PhoneWindow *pPhoneWindow = new PhoneWindow(wnd);
		mPhoneWindows.push_back(pPhoneWindow);
	}

	mNumberOfWindows = 6;
	mNextWindow = 0;
}

PhoneWindow *CPhoneWindowManager::getOnePhoneWindow()
{
	int index = mNextWindow % mNumberOfWindows;
	PhoneWindow *pDst = mPhoneWindows[index];

	mNextWindow++;

	return pDst;
}