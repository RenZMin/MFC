// SysAll.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "SecMngAdmin.h"
#include "SysAll.h"


// CSysAll

IMPLEMENT_DYNCREATE(CSysAll, CFormView)

CSysAll::CSysAll()
	: CFormView(IDD_DIALOG_SYSALL)
{

}

CSysAll::~CSysAll()
{
}

void CSysAll::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CSysAll, CFormView)
END_MESSAGE_MAP()


// CSysAll ���

#ifdef _DEBUG
void CSysAll::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CSysAll::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CSysAll ��Ϣ�������
