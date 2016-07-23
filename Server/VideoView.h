#pragma once

#include "Resource.h"
// CVideoView dialog

class CVideoView : public CDialogEx
{
	DECLARE_DYNAMIC(CVideoView)

public:
	CVideoView(CWnd* pParent = NULL);   // standard constructor
	virtual ~CVideoView();

// Dialog Data
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
};
