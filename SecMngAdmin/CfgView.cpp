// CfgView.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "SecMngAdmin.h"
#include "CfgView.h"


// CCfgView

IMPLEMENT_DYNCREATE(CCfgView, CFormView)

CCfgView::CCfgView()
	: CFormView(IDD_DIALOG_CFG)
{

}

CCfgView::~CCfgView()
{
}

void CCfgView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CCfgView, CFormView)
	
END_MESSAGE_MAP()


// CCfgView ���

#ifdef _DEBUG
void CCfgView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CCfgView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CCfgView ��Ϣ�������






