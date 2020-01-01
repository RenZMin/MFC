
// MainFrm.h : CMainFrame ��Ľӿ�
//

#pragma once
#include "GfxSplitterWnd.h"
#include "GfxOutBarCtrl.h"
#include "FormBackground.h"
class CMainFrame : public CFrameWnd
{
	
protected: // �������л�����
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame);

// ����
public:
	CGfxSplitterWnd		wndSplitter;
	CGfxOutBarCtrl		wndBar;
	CImageList			imaLarge, imaSmall;
	CTreeCtrl			wndTree;


// ����
public:

// ��д
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// ʵ��
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif


// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()

	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
};


