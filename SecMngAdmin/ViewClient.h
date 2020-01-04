#pragma once
#include "afxcmn.h"



// ViewClient 窗体视图

class ViewClient : public CFormView
{
	DECLARE_DYNCREATE(ViewClient)

protected:
	ViewClient();           // 动态创建所使用的受保护的构造函数
	virtual ~ViewClient();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	int DbInitListSecNode(CString &ClientId, CString &ServerId,
		int KeyId, int state, CTime &time);
	DECLARE_MESSAGE_MAP()
public:
	CImageList m_imageList;
	CListCtrl m_listSecNode;
	virtual void OnInitialUpdate();
};


