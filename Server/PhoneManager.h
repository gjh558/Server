#pragma once
// CServerSocket ÃüÁîÄ¿±ê

class CVideo;
class CServerDlg;

class CVideoServer : public CAsyncSocket
{
public:
	CVideoServer();
	CVideoServer(CServerDlg *parentWind);
	virtual ~CVideoServer();

public:
	virtual void OnAccept(int nErrorCode);
	virtual void OnConnect(int nErrorCode);
	virtual void OnClose(int nErrorCode);
	virtual void OnSend(int nErrorCode);
	virtual void OnReceive(int nErrorCode);

private:
	CServerDlg *m_pPrarentWin;

	CWnd *m_pVideoWin;

	CVideo * m_pVideo;


};


