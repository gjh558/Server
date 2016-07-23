// VideoView.cpp : implementation file
//

#include "stdafx.h"
#include "Server.h"
#include "VideoView.h"
#include "afxdialogex.h"


// CVideoView dialog

IMPLEMENT_DYNAMIC(CVideoView, CDialogEx)

CVideoView::CVideoView(CWnd* pParent /*=NULL*/)
	: CDialogEx(CVideoView::IDD, pParent)
{

}

CVideoView::~CVideoView()
{
}

void CVideoView::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CVideoView, CDialogEx)
END_MESSAGE_MAP()


// CVideoView message handlers
