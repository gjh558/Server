#pragma once
#include <vector>

using namespace std;

class PhoneWindow;
class CServerDlg;

class CPhoneWindowManager
{
public:
	CPhoneWindowManager(CServerDlg *pServerDlg);

	~CPhoneWindowManager(void);

	PhoneWindow *getOnePhoneWindow();

private:
	void init(CServerDlg *pServerDlg);
private:
	vector<PhoneWindow *> mPhoneWindows;
	int mNumberOfWindows;
	int mNextWindow;
};

