
// MainFrm.cpp : CMainFrame ���ʵ��
//

#include "stdafx.h"
#include "SecMngAdmin.h"

#include "MainFrm.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
END_MESSAGE_MAP()

// CMainFrame ����/����

CMainFrame::CMainFrame()
{
	// TODO: �ڴ����ӳ�Ա��ʼ������
}

CMainFrame::~CMainFrame()
{
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return TRUE;
}

// CMainFrame ���

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}
#endif //_DEBUG


// CMainFrame ��Ϣ��������





static UINT nImages[] =
{
	IDI_ICON_SET,
	IDI_ICON_USER,
	IDI_ICON_OP_LOG,
	IDI_ICON_LOG,
	IDI_ICON_REQ,
	IDI_ICON_RE,
	IDI_ICON_REPORT,
};

BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext)
{
	// TODO: �ڴ�����ר�ô����/����û���
	// TODO: �ڴ�����ר�ô����/����û���
	if (!wndSplitter.CreateStatic(this, 1, 2)) return false;

	if (!wndSplitter.CreateView(0, 1, RUNTIME_CLASS(CFormBackground), CSize(0, 0), pContext))
		return false;

	//pContext->m_pNewViewClass RUNTIME_CLASS(CFormUserManager) CFormUserManager
	DWORD dwf = CGfxOutBarCtrl::fDragItems |
		CGfxOutBarCtrl::fEditGroups |
		CGfxOutBarCtrl::fEditItems |
		CGfxOutBarCtrl::fRemoveGroups |
		CGfxOutBarCtrl::fRemoveItems |
		CGfxOutBarCtrl::fAddGroups |
		CGfxOutBarCtrl::fAnimation;

	wndBar.Create(WS_CHILD | WS_VISIBLE, CRect(0, 0, 0, 0), &wndSplitter,
		wndSplitter.IdFromRowCol(0, 0), dwf);
	wndBar.SetOwner(this);

	imaLarge.Create(32, 32, true, 2, 1);
	HICON hIcon;

	for (int i = 0; i < 7; ++i)
	{
		hIcon = AfxGetApp()->LoadIcon(nImages[i]);
		imaLarge.Add(hIcon);
	}

	wndBar.SetImageList(&imaLarge, CGfxOutBarCtrl::fLargeIcon);
	wndBar.SetImageList(&imaSmall, CGfxOutBarCtrl::fSmallIcon);

	wndTree.Create(WS_CHILD | TVS_HASLINES | TVS_LINESATROOT | TVS_HASBUTTONS | TVS_SHOWSELALWAYS,
		CRect(0, 0, 0, 0), &wndBar, 1010);
	wndTree.SetImageList(&imaSmall, TVSIL_NORMAL);
	wndBar.SetAnimationTickCount(20);
	wndBar.SetAnimSelHighlight(200);

	wndBar.AddFolder("SecMngServer���ù���", 0);
	wndBar.AddFolder("SecMngAdmin�������", 1);
	wndBar.AddFolder("��Ա����", 2);
	wndBar.AddFolder("�豸����", 3);
	//wndBar.AddFolder("CA��Ա������ѯ", 4);	

	wndBar.InsertItem(0, 0, "SecMngServer����", 0, 0);
	wndBar.InsertItem(0, 1, "������Ϣ����", 1, 0);
	wndBar.InsertItem(0, 2, "��̨ҵ�����", 4, 0); //
	wndBar.InsertItem(0, 3, "��̨���ײ�ѯ", 5, 0); //

	wndBar.InsertItem(1, 0, "ǰ̨��ϵ����", 6, 0);
	wndBar.InsertItem(1, 1, "ǰ̨ҵ�����", 4, 0);
	wndBar.InsertItem(1, 2, "ǰ̨���ײ�ѯ", 3, 0);

	wndBar.InsertItem(2, 0, "������Ա", 3, 0);
	wndBar.InsertItem(2, 1, "������Ա", 4, 0);
	wndBar.InsertItem(2, 2, "�ⶳ", 2, 0);
	wndBar.InsertItem(2, 3, "ע����Ա", 1, 0);

	wndBar.InsertItem(3, 0, "�����豸", 5, 0);
	wndBar.InsertItem(3, 1, "ע������", 4, 0);

	wndBar.SetSelFolder(0);

	CRect r;
	GetClientRect(&r);
	int w1 = r.Width() / 5;
	int w2 = r.Width() / 4;

	wndSplitter.SetColumnInfo(0, w1, 0);
	wndSplitter.SetColumnInfo(1, w2, 0);
	wndSplitter.RecalcLayout();
	return true;

	//return CFrameWndEx::OnCreateClient(lpcs, pContext);
	return CFrameWnd::OnCreateClient(lpcs, pContext);
}