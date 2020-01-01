// FormBackground.cpp : 实现文件
//

#include "stdafx.h"
#include "SecMngAdmin.h"
#include "FormBackground.h"


// CFormBackground

IMPLEMENT_DYNCREATE(CFormBackground, CFormView)

CFormBackground::CFormBackground()
	: CFormView(IDD_FORMBACKGROUND_FORM)
{

}

CFormBackground::~CFormBackground()
{
}

void CFormBackground::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CFormBackground, CFormView)
END_MESSAGE_MAP()


// CFormBackground 诊断

#ifdef _DEBUG
void CFormBackground::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CFormBackground::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CFormBackground 消息处理程序
