
// SecMngAdmin.h : SecMngAdmin 应用程序的主头文件
//
#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"       // 主符号
#include "DlgInitCfg.h"
#include<string>
// CSecMngAdminApp:
// 有关此类的实现，请参阅 SecMngAdmin.cpp
//

class CSecMngAdminApp : public CWinApp
{
public:
	CSecMngAdminApp();


// 重写
public:
	virtual BOOL InitInstance();

	//声明
	int readSecMngCfg();
	int NewOdbc_Connet();

// 实现
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CSecMngAdminApp theApp;
