#pragma once

#include "SECMNGSRVCFG.h"
#include "cfg_op.h"
// CCfgView 对话框

class CCfgView1 : public CDialogEx
{/*
	DECLARE_DYNAMIC(CCfgView1)

public:
	CCfgView1(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CCfgView1();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_CFG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()*/
};
#pragma once



// CCfgView 窗体视图

class CCfgView : public CFormView
{
	DECLARE_DYNCREATE(CCfgView)

protected:
	CCfgView();           // 动态创建所使用的受保护的构造函数
	virtual ~CCfgView();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_CFG };
#endif
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	int CCfgView::writeSecMngCfg(char *pItemName, CString pItemValue, char *fileName);

	DECLARE_MESSAGE_MAP()
public:

	CString m_strsrvip;
	CString m_strsrvmaxnode;
	CString m_strsrvport;
	virtual void OnInitialUpdate();
	afx_msg void OnBnClickedSrvcfg();
	CString m_Dsn;
	CString m_Uid;
	CString m_Pwd;
	afx_msg void OnBnClickedDsnUidPwd();
};


