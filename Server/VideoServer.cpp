// VideoServer.cpp : 实现文件
//

#include "stdafx.h"
#include "PhoneManager.h"
#include "Phone.h"
#include "ServerDlg.h"
#include "VideoView.h"
#include "PhoneWindowmanager.h"
#include "PhoneWindow.h"

// CVideoServer

CVideoServer::CVideoServer()
{
	
}

CVideoServer::CVideoServer(CServerDlg *parentWind)
{
	m_pPrarentWin = parentWind;
	//m_pVideoWin = parentWind->GetDlgItem(IDC_STATIC2);
	pPhoneWindowManager = new CPhoneWindowManager(parentWind);
}
CVideoServer::~CVideoServer()
{
	delete pPhoneWindowManager;
}


// CVideoServer 成员函数


void CVideoServer::OnAccept(int nErrorCode)
{
	// TODO: 在此添加专用代码和/或调用基类
	if(nErrorCode == 0)
	{
		//m_pVideo = new CVideo(m_pVideoWin);
		PhoneWindow *win = pPhoneWindowManager->getOnePhoneWindow();
		BOOL show = (win->state == FREE)?TRUE:FALSE;
		win->state = OCCUPIED;
		m_pVideo = new CVideo(win);

		if (show == TRUE) {
			m_pVideo->show();
		}else {
			mVideos.push(m_pVideo);
		}
			
		if (!Accept (*m_pVideo))
		{
			//delete pVideo;
			TRACE("ACcept error ...");
		}
		else
		{
			TRACE("ACcept success ...");
		}
	}
	
	CAsyncSocket::OnAccept(nErrorCode);
}

void CVideoServer::OnConnect(int nErrorCode)
{
	if (nErrorCode == 0)
	{
	}
	else
	{
	}

	CAsyncSocket::OnConnect(nErrorCode);
}


void CVideoServer::OnClose(int nErrorCode)
{
	// TODO: 在此添加专用代码和/或调用基类
	Close();
	CAsyncSocket::OnClose(nErrorCode);
}


void CVideoServer::OnSend(int nErrorCode)
{
	//InternalSend ();
	CAsyncSocket::OnSend(nErrorCode);
}


void CVideoServer::OnReceive(int nErrorCode)
{
	// TODO: 在此添加专用代码和/或调用基类
	CAsyncSocket::OnReceive(nErrorCode);
}

