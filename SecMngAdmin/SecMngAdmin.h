
// SecMngAdmin.h : SecMngAdmin Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������


// CSecMngAdminApp:
// �йش����ʵ�֣������ SecMngAdmin.cpp
//

class CSecMngAdminApp : public CWinApp
{
public:
	CSecMngAdminApp();


// ��д
public:
	virtual BOOL InitInstance();

// ʵ��
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CSecMngAdminApp theApp;
