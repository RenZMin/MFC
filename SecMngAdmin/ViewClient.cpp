// ViewClient.cpp : 实现文件
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


// ViewClient 诊断

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


// ViewClient 消息处理程序
extern CDatabase* g_pDB;
int ViewClient::DbInitListSecNode(CString &ClientId, CString &ServerId,
	int KeyId, int state, CTime &time)
{
	// TODO:  在此添加控件通知处理程序代

	LVITEM   lvi;			//结构体变量

	lvi.mask = LVIF_IMAGE | LVIF_TEXT;	//按什么方式显示数据：图片、文本
	lvi.iItem = 0;			//在第0行上插入新数据 头插法
	lvi.iImage = 0;			//使用图片列表中的第4个图片	

							//插入第0列数据
	lvi.iSubItem = 0;		// Set subitem 0
	lvi.pszText = (LPTSTR)(LPCTSTR)ClientId;
	m_listSecNode.InsertItem(&lvi);

	//插入第1列数据
	lvi.iSubItem = 1;		// Set subitem 1
	lvi.pszText = (LPTSTR)(LPCTSTR)ServerId;
	m_listSecNode.SetItem(&lvi);

	//插入第2列数据
	lvi.iSubItem = 2;		// Set subitem 4
							//CString strAuthcode(authcode) ;
	char buf[100];
	sprintf(buf, "%d", KeyId);
	lvi.pszText = buf;
	m_listSecNode.SetItem(&lvi);

	//插入第3列数据
	lvi.iSubItem = 3;		// Set subitem 3
	if (state == 1)
	{
		lvi.pszText = "禁用";
	}
	else {
		lvi.pszText = "正常";
	}
	m_listSecNode.SetItem(&lvi);

	//插入第4列数据
	CString strTime = time.Format("%Y-%m-%d %H:%M:%S");
	lvi.iSubItem = 4;		// Set subitem 1
	lvi.pszText = (LPTSTR)(LPCTSTR)strTime;
	m_listSecNode.SetItem(&lvi);
	return 0;
}














void ViewClient::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: 在此添加专用代码和/或调用基类

	// 按 16 x 16 排列，一共有8个图标，组成一个图片列表。
	HIMAGELIST hList = ImageList_Create(16, 16, ILC_COLOR8 | ILC_MASK, 8, 1);
	m_imageList.Attach(hList);

	CBitmap cBmp;
	cBmp.LoadBitmap(IDB_BITMAP_SECNODE);
	m_imageList.Add(&cBmp, RGB(255, 0, 255));
	cBmp.DeleteObject();

	m_listSecNode.SetImageList(&m_imageList, LVSIL_SMALL);

	//获取控件的显示状态
	DWORD dwExStyle = ListView_GetExtendedListViewStyle(m_listSecNode.m_hWnd);
	dwExStyle |= LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES;	//修改 状态
	ListView_SetExtendedListViewStyle(m_listSecNode.m_hWnd, dwExStyle); //设置

	CRect rect; //msdn
	m_listSecNode.GetClientRect(&rect);
	int nColInterval = rect.Width() / 5;

	m_listSecNode.SetRedraw(FALSE);

	m_listSecNode.InsertColumn(0, "Client编号", LVCFMT_LEFT, nColInterval);
	m_listSecNode.InsertColumn(1, "Server编号", LVCFMT_LEFT, nColInterval);
	m_listSecNode.InsertColumn(2, "当前密钥KeyId", LVCFMT_LEFT, nColInterval);
	m_listSecNode.InsertColumn(3, "密钥状态", LVCFMT_LEFT, nColInterval);
	m_listSecNode.InsertColumn(4, "请求时间", LVCFMT_LEFT, rect.Width() - 4 * nColInterval);

	m_listSecNode.SetRedraw(TRUE);


	//读入数据库的信息 并写入界面展示给用户

	
	//select * from SRVCFG where key = 'secmng_server_ip';  --IP
	CSECMNGSECKYEINFO cliKeyInfo(g_pDB);//到这里 已经有数据库表名了
										//srvCfgAddNode.m_strFilter.Format("key='%s'", "secmng_server_ip");//相当于where子句有												
										//相当于select *
	if (!cliKeyInfo.Open(CRecordset::snapshot, NULL, CRecordset::none))//相当于加上了select from
	{
		AfxMessageBox("记录类打开数据库失败");
		return;
	}
	while (!cliKeyInfo.IsEOF())//have result 结果已经保存到SECMNGSRVCFG.h变量m_VALUE了
	{
		cliKeyInfo.m_CLIENTID.TrimLeft();//左边去空格
		cliKeyInfo.m_CLIENTID.TrimRight();
		CString ClientId = cliKeyInfo.m_CLIENTID;;//将查询结果 给到控件对应的变量

		cliKeyInfo.m_SERVERID.TrimLeft();//左边去空格
		cliKeyInfo.m_SERVERID.TrimRight();
		CString ServerId = cliKeyInfo.m_SERVERID;//将查询结果 给到控件对应的变量

		
		int KeyId = cliKeyInfo.m_KEYID;//将查询结果 给到控件对应的变量

		int State = cliKeyInfo.m_STATE;

		CTime time = CTime::GetCurrentTime();

		DbInitListSecNode(ClientId, ServerId, KeyId, State, time);

		cliKeyInfo.MoveNext();
	}
	cliKeyInfo.Close();
	UpdateData(FALSE);//从变量到空间显示	*/
}
