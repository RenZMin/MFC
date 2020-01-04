// ViewClient.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "SecMngAdmin.h"
#include "ViewClient.h"
#include "SECMNGSECKYEINFO.h"

// ViewClient

IMPLEMENT_DYNCREATE(ViewClient, CFormView)

ViewClient::ViewClient()
	: CFormView(IDD_DIALOG1)
{

}

ViewClient::~ViewClient()
{
}

void ViewClient::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_SECNODE, m_listSecNode);
}

BEGIN_MESSAGE_MAP(ViewClient, CFormView)
END_MESSAGE_MAP()


// ViewClient ���

#ifdef _DEBUG
void ViewClient::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void ViewClient::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// ViewClient ��Ϣ�������
extern CDatabase* g_pDB;
int ViewClient::DbInitListSecNode(CString &ClientId, CString &ServerId,
	int KeyId, int state, CTime &time)
{
	// TODO:  �ڴ���ӿؼ�֪ͨ��������

	LVITEM   lvi;			//�ṹ�����

	lvi.mask = LVIF_IMAGE | LVIF_TEXT;	//��ʲô��ʽ��ʾ���ݣ�ͼƬ���ı�
	lvi.iItem = 0;			//�ڵ�0���ϲ��������� ͷ�巨
	lvi.iImage = 0;			//ʹ��ͼƬ�б��еĵ�4��ͼƬ	

							//�����0������
	lvi.iSubItem = 0;		// Set subitem 0
	lvi.pszText = (LPTSTR)(LPCTSTR)ClientId;
	m_listSecNode.InsertItem(&lvi);

	//�����1������
	lvi.iSubItem = 1;		// Set subitem 1
	lvi.pszText = (LPTSTR)(LPCTSTR)ServerId;
	m_listSecNode.SetItem(&lvi);

	//�����2������
	lvi.iSubItem = 2;		// Set subitem 4
							//CString strAuthcode(authcode) ;
	char buf[100];
	sprintf(buf, "%d", KeyId);
	lvi.pszText = buf;
	m_listSecNode.SetItem(&lvi);

	//�����3������
	lvi.iSubItem = 3;		// Set subitem 3
	if (state == 1)
	{
		lvi.pszText = "����";
	}
	else {
		lvi.pszText = "����";
	}
	m_listSecNode.SetItem(&lvi);

	//�����4������
	CString strTime = time.Format("%Y-%m-%d %H:%M:%S");
	lvi.iSubItem = 4;		// Set subitem 1
	lvi.pszText = (LPTSTR)(LPCTSTR)strTime;
	m_listSecNode.SetItem(&lvi);
	return 0;
}














void ViewClient::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: �ڴ����ר�ô����/����û���

	// �� 16 x 16 ���У�һ����8��ͼ�꣬���һ��ͼƬ�б�
	HIMAGELIST hList = ImageList_Create(16, 16, ILC_COLOR8 | ILC_MASK, 8, 1);
	m_imageList.Attach(hList);

	CBitmap cBmp;
	cBmp.LoadBitmap(IDB_BITMAP_SECNODE);
	m_imageList.Add(&cBmp, RGB(255, 0, 255));
	cBmp.DeleteObject();

	m_listSecNode.SetImageList(&m_imageList, LVSIL_SMALL);

	//��ȡ�ؼ�����ʾ״̬
	DWORD dwExStyle = ListView_GetExtendedListViewStyle(m_listSecNode.m_hWnd);
	dwExStyle |= LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES;	//�޸� ״̬
	ListView_SetExtendedListViewStyle(m_listSecNode.m_hWnd, dwExStyle); //����

	CRect rect; //msdn
	m_listSecNode.GetClientRect(&rect);
	int nColInterval = rect.Width() / 5;

	m_listSecNode.SetRedraw(FALSE);

	m_listSecNode.InsertColumn(0, "Client���", LVCFMT_LEFT, nColInterval);
	m_listSecNode.InsertColumn(1, "Server���", LVCFMT_LEFT, nColInterval);
	m_listSecNode.InsertColumn(2, "��ǰ��ԿKeyId", LVCFMT_LEFT, nColInterval);
	m_listSecNode.InsertColumn(3, "��Կ״̬", LVCFMT_LEFT, nColInterval);
	m_listSecNode.InsertColumn(4, "����ʱ��", LVCFMT_LEFT, rect.Width() - 4 * nColInterval);

	m_listSecNode.SetRedraw(TRUE);


	//�������ݿ����Ϣ ��д�����չʾ���û�

	
	//select * from SRVCFG where key = 'secmng_server_ip';  --IP
	CSECMNGSECKYEINFO cliKeyInfo(g_pDB);//������ �Ѿ������ݿ������
										//srvCfgAddNode.m_strFilter.Format("key='%s'", "secmng_server_ip");//�൱��where�Ӿ���												
										//�൱��select *
	if (!cliKeyInfo.Open(CRecordset::snapshot, NULL, CRecordset::none))//�൱�ڼ�����select from
	{
		AfxMessageBox("��¼������ݿ�ʧ��");
		return;
	}
	while (!cliKeyInfo.IsEOF())//have result ����Ѿ����浽SECMNGSRVCFG.h����m_VALUE��
	{
		cliKeyInfo.m_CLIENTID.TrimLeft();//���ȥ�ո�
		cliKeyInfo.m_CLIENTID.TrimRight();
		CString ClientId = cliKeyInfo.m_CLIENTID;;//����ѯ��� �����ؼ���Ӧ�ı���

		cliKeyInfo.m_SERVERID.TrimLeft();//���ȥ�ո�
		cliKeyInfo.m_SERVERID.TrimRight();
		CString ServerId = cliKeyInfo.m_SERVERID;//����ѯ��� �����ؼ���Ӧ�ı���

		
		int KeyId = cliKeyInfo.m_KEYID;//����ѯ��� �����ؼ���Ӧ�ı���

		int State = cliKeyInfo.m_STATE;

		CTime time = CTime::GetCurrentTime();

		DbInitListSecNode(ClientId, ServerId, KeyId, State, time);

		cliKeyInfo.MoveNext();
	}
	cliKeyInfo.Close();
	UpdateData(FALSE);//�ӱ������ռ���ʾ	*/
}
