
// SecMngAdminView.cpp : CSecMngAdminView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "SecMngAdmin.h"
#endif

#include "SecMngAdminDoc.h"
#include "SecMngAdminView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CSecMngAdminView

IMPLEMENT_DYNCREATE(CSecMngAdminView, CView)

BEGIN_MESSAGE_MAP(CSecMngAdminView, CView)
END_MESSAGE_MAP()

// CSecMngAdminView ����/����

CSecMngAdminView::CSecMngAdminView()
{
	// TODO: �ڴ˴���ӹ������

}

CSecMngAdminView::~CSecMngAdminView()
{
}

BOOL CSecMngAdminView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CSecMngAdminView ����

void CSecMngAdminView::OnDraw(CDC* /*pDC*/)
{
	CSecMngAdminDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
}


// CSecMngAdminView ���

#ifdef _DEBUG
void CSecMngAdminView::AssertValid() const
{
	CView::AssertValid();
}

void CSecMngAdminView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CSecMngAdminDoc* CSecMngAdminView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSecMngAdminDoc)));
	return (CSecMngAdminDoc*)m_pDocument;
}
#endif //_DEBUG


// CSecMngAdminView ��Ϣ�������
