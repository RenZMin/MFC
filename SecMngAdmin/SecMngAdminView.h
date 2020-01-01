
// SecMngAdminView.h : CSecMngAdminView 类的接口
//

#pragma once


class CSecMngAdminView : public CView
{
protected: // 仅从序列化创建
	CSecMngAdminView();
	DECLARE_DYNCREATE(CSecMngAdminView)

// 特性
public:
	CSecMngAdminDoc* GetDocument() const;

// 操作
public:

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// 实现
public:
	virtual ~CSecMngAdminView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // SecMngAdminView.cpp 中的调试版本
inline CSecMngAdminDoc* CSecMngAdminView::GetDocument() const
   { return reinterpret_cast<CSecMngAdminDoc*>(m_pDocument); }
#endif

