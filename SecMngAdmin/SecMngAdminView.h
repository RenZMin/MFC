
// SecMngAdminView.h : CSecMngAdminView ��Ľӿ�
//

#pragma once


class CSecMngAdminView : public CView
{
protected: // �������л�����
	CSecMngAdminView();
	DECLARE_DYNCREATE(CSecMngAdminView)

// ����
public:
	CSecMngAdminDoc* GetDocument() const;

// ����
public:

// ��д
public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// ʵ��
public:
	virtual ~CSecMngAdminView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // SecMngAdminView.cpp �еĵ��԰汾
inline CSecMngAdminDoc* CSecMngAdminView::GetDocument() const
   { return reinterpret_cast<CSecMngAdminDoc*>(m_pDocument); }
#endif

