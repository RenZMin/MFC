#pragma once

#include "resource.h"
#include "atltime.h"
#include "afxcmn.h"
#include "DlgAddNetNode.h"
#include "SECMNGSECNODE.h"
// CDlgNetInfo 窗体视图

class CDlgNetInfo : public CFormView
{
	DECLARE_DYNCREATE(CDlgNetInfo)

protected:
	CDlgNetInfo();           // 动态创建所使用的受保护的构造函数
	virtual ~CDlgNetInfo();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_NETMNG };
#endif
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	int CDlgNetInfo::DbInitListSecNode(CString &ID, CString &Name,
		CTime &time, int state, int authcode);
	DECLARE_MESSAGE_MAP()
public:
	virtual void OnInitialUpdate();
	CTime m_dateBegin;
	CTime m_dateEnd;
	CListCtrl m_listSecNode;
	CImageList		m_imageList;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButtonSearchinfo();
	CString m_Id;
	CString m_Name;
	afx_msg void OnBnClickedButtonExactsearch();
	afx_msg void OnBnClickedButtonIdsearch();
	afx_msg void OnBnClickedButton3();
};


