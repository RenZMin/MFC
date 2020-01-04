#pragma once
#include "afxcmn.h"



// ViewClient ������ͼ

class ViewClient : public CFormView
{
	DECLARE_DYNCREATE(ViewClient)

protected:
	ViewClient();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
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
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	int DbInitListSecNode(CString &ClientId, CString &ServerId,
		int KeyId, int state, CTime &time);
	DECLARE_MESSAGE_MAP()
public:
	CImageList m_imageList;
	CListCtrl m_listSecNode;
	virtual void OnInitialUpdate();
};


