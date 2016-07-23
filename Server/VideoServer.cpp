// VideoServer.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "PhoneManager.h"
#include "Phone.h"
#include "ServerDlg.h"
#include "VideoView.h"

// CVideoServer

CVideoServer::CVideoServer()
{
	
}

CVideoServer::CVideoServer(CServerDlg *parentWind)
{
	m_pPrarentWin = parentWind;
	m_pVideoWin = parentWind->GetDlgItem(IDC_STATIC2);
}
CVideoServer::~CVideoServer()
{
	//delete m_pVideo;
}


// CVideoServer ��Ա����


void CVideoServer::OnAccept(int nErrorCode)
{
	// TODO: �ڴ����ר�ô����/����û���
	if(nErrorCode == 0)
	{
		m_pVideo = new CVideo(m_pVideoWin);
			
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
	// TODO: �ڴ����ר�ô����/����û���
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
	// TODO: �ڴ����ר�ô����/����û���
	CAsyncSocket::OnReceive(nErrorCode);
}
