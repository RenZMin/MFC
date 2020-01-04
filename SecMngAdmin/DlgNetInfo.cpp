// DlgNetInfo.cpp : 实现文件
//

#include "stdafx.h"
#include "SecMngAdmin.h"
#include "DlgNetInfo.h"


// CDlgNetInfo

IMPLEMENT_DYNCREATE(CDlgNetInfo, CFormView)

CDlgNetInfo::CDlgNetInfo()
	: CFormView(IDD_DIALOG_NETMNG)
	, m_dateBegin(0)
	, m_dateEnd(0)
	, m_Id(_T(""))
	, m_Name(_T(""))
{

}

CDlgNetInfo::~CDlgNetInfo()
{
}

void CDlgNetInfo::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER1, m_dateBegin);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER2, m_dateEnd);
	DDX_Control(pDX, IDC_LIST_SECNODE, m_listSecNode);
	DDX_Text(pDX, IDC_EDIT_ID, m_Id);
	DDX_Text(pDX, IDC_EDIT_NAME, m_Name);
}

BEGIN_MESSAGE_MAP(CDlgNetInfo, CFormView)
	ON_BN_CLICKED(IDC_BUTTON1, &CDlgNetInfo::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON_SEARCHINFO, &CDlgNetInfo::OnBnClickedButtonSearchinfo)
	ON_BN_CLICKED(IDC_BUTTON_EXACTSEARCH, &CDlgNetInfo::OnBnClickedButtonExactsearch)
	ON_BN_CLICKED(IDC_BUTTON_IDSEARCH, &CDlgNetInfo::OnBnClickedButtonIdsearch)
	ON_BN_CLICKED(IDC_BUTTON3, &CDlgNetInfo::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON_EDITNODE, &CDlgNetInfo::OnBnClickedButtonEditnode)
END_MESSAGE_MAP()


// CDlgNetInfo 诊断

#ifdef _DEBUG
void CDlgNetInfo::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CDlgNetInfo::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


//typedef struct tagLVITEMA
//{
//UINT mask;			//显示方式 文字和图片方式显示
//int iItem;			//插入位置，=0 在第0行插入一行
//int iSubItem;		//在第n列 的子节点
//UINT state;			//状态
//UINT stateMask;
//LPWSTR pszText;		//显示的内容 -- 字符型
//int cchTextMax;
//int iImage;			//使用的图片的序号 
//LPARAM lParam;		//可以在每一行上 隐藏一些数据
//int iIndent;
//#if (NTDDI_VERSION >= NTDDI_WINXP)
//	int iGroupId;
//	UINT cColumns; // tile view columns
//	PUINT puColumns;
//#endif
//#if (NTDDI_VERSION >= NTDDI_VISTA) // Will be unused downlevel, but sizeof(LVITEMA) must be equal to sizeof(LVITEMW)
//	int* piColFmt;
//	int iGroup; // readonly. only valid for owner data.
//#endif
//} LVITEMA, *LPLVITEMA;

extern CDatabase *g_pDB;
int CDlgNetInfo::DbInitListSecNode(CString &ID, CString &Name,
	CTime &time, int state, int authcode)
{
	// TODO:  在此添加控件通知处理程序代

	LVITEM   lvi;			//结构体变量

	lvi.mask = LVIF_IMAGE | LVIF_TEXT;	//按什么方式显示数据：图片、文本
	lvi.iItem = 0;			//在第0行上插入新数据 头插法
	lvi.iImage = 4;			//使用图片列表中的第4个图片	

							//插入第0列数据
	lvi.iSubItem = 0;		// Set subitem 0
	lvi.pszText = (LPTSTR)(LPCTSTR)ID;
	m_listSecNode.InsertItem(&lvi);

	//插入第1列数据
	lvi.iSubItem = 1;		// Set subitem 1
	lvi.pszText = (LPTSTR)(LPCTSTR)Name;
	m_listSecNode.SetItem(&lvi);

	//插入第2列数据
	CString strTime = time.Format("%Y-%m-%d %H:%M:%S");
	lvi.iSubItem = 2;		// Set subitem 1
	lvi.pszText = (LPTSTR)(LPCTSTR)strTime;
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
	lvi.iSubItem = 4;		// Set subitem 4
							//CString strAuthcode(authcode) ;
	char buf[100];
	sprintf(buf, "%d", authcode);
	lvi.pszText = buf;
	m_listSecNode.SetItem(&lvi);

	return 0;
}


// CDlgNetInfo 消息处理程序

void CDlgNetInfo::OnInitialUpdate()
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

	m_listSecNode.InsertColumn(0, "网点编号", LVCFMT_LEFT, nColInterval);
	m_listSecNode.InsertColumn(1, "网点名称", LVCFMT_LEFT, nColInterval);
	m_listSecNode.InsertColumn(2, "网点创建时间", LVCFMT_LEFT, nColInterval);
	m_listSecNode.InsertColumn(3, "网点状态", LVCFMT_LEFT, nColInterval);
	m_listSecNode.InsertColumn(4, "网点授权码", LVCFMT_LEFT, rect.Width() - 4 * nColInterval);

	m_listSecNode.SetRedraw(TRUE);


	//读入数据库的信息 并写入界面展示给用户


	//select * from SRVCFG where key = 'secmng_server_ip';  --IP
	CSECMNGSECNODE srvCfgAddNode(g_pDB);//到这里 已经有数据库表名了
	//srvCfgAddNode.m_strFilter.Format("key='%s'", "secmng_server_ip");//相当于where子句有												
	//相当于select *
	if (!srvCfgAddNode.Open(CRecordset::snapshot, NULL, CRecordset::none))//相当于加上了select from
	{
		AfxMessageBox("记录类打开数据库失败");
		return;
	}
	while (!srvCfgAddNode.IsEOF())//have result 结果已经保存到SECMNGSRVCFG.h变量m_VALUE了
	{
		srvCfgAddNode.m_ID.TrimLeft();//左边去空格
		srvCfgAddNode.m_ID.TrimRight();
		CString ID = srvCfgAddNode.m_ID;;//将查询结果 给到控件对应的变量

		srvCfgAddNode.m_NAME.TrimLeft();//左边去空格
		srvCfgAddNode.m_NAME.TrimRight();
		CString Name = srvCfgAddNode.m_NAME;//将查询结果 给到控件对应的变量

		srvCfgAddNode.m_NODEDESC.TrimLeft();//左边去空格
		srvCfgAddNode.m_NODEDESC.TrimRight();
		CString netDescription = srvCfgAddNode.m_NODEDESC;//将查询结果 给到控件对应的变量

		CTime time = srvCfgAddNode.m_CREATETIME;

		int state = srvCfgAddNode.m_STATE;
		int authcode = srvCfgAddNode.m_AUTHCODE;
		DbInitListSecNode(ID, Name, time, state, authcode);
		
		srvCfgAddNode.MoveNext();
	}
	srvCfgAddNode.Close();
	UpdateData(FALSE);//从变量到空间显示	
}

//CString	m_ID;
//CString	m_NAME;
//CString	m_NODEDESC;
//CTime	m_CREATETIME;
//int	m_AUTHCODE;  //编译器给我自动生成的 我们可以修改 微调
//int	m_STATE;

//创建网点  即创建一条记录
void CDlgNetInfo::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	//弹出对话框，用户输入信息
	CDlgAddNetNode dlgAddNetNode;
	UpdateData(TRUE);
	if (dlgAddNetNode.DoModal() == IDCANCEL)
	{
		return;
	}
	int dbflag = 0;
	char sql[1024];
	char toDate[128];
	UpdateData(TRUE);
	if (dlgAddNetNode.m_ID.IsEmpty() || dlgAddNetNode.m_Name.IsEmpty() || dlgAddNetNode.m_Description.IsEmpty())
	{
		AfxMessageBox("输入数据不允许为空值");
		return;
	}
	CString ID = dlgAddNetNode.m_ID;
	CString Name =dlgAddNetNode.m_Name;
	CString netDescription = dlgAddNetNode.m_Description;
	CTime time = CTime::GetCurrentTime();
	CString tempTime = time.Format("%Y-%m-%d %H:%M:%S");
	int state = dlgAddNetNode.m_State;
	int authcode = dlgAddNetNode.m_Autor;
	
	g_pDB->BeginTrans();//开启事务
	CSECMNGSECNODE srvCfgAddNode(g_pDB);//到这里 已经有数据库表名了

	TRY
	{
		memset(sql, 0, sizeof(sql));
		memset(toDate, 0, sizeof(toDate));
		sprintf(toDate, "to_date('%s', 'yyyy-mm-dd hh24:mi:ss')", tempTime);
		srvCfgAddNode.m_strFilter.Format("ID='%s'", ID);//相当于where子句有了,根据名字去表里查
																	 //查询表的IP列
		if (!srvCfgAddNode.Open(CRecordset::snapshot, NULL, CRecordset::none))//相当于加上了select from
		{
			AfxMessageBox("记录类打开数据库失败");
			return;
		}
		if (!srvCfgAddNode.IsEOF())//have result 
		{
			sprintf(sql, "update SECMNG.SECNODE set ID ='%s',NAME='%s',NODEDESC='%s',CREATETIME=%s,AUTHCODE=%d,STATE=%d WHERE ID='%s'", (LPTSTR)(LPCTSTR)ID, (LPTSTR)(LPCTSTR)Name, (LPTSTR)(LPCTSTR)netDescription,toDate,authcode,state, (LPTSTR)(LPCTSTR)ID);
			g_pDB->ExecuteSQL(sql);
			//不知道为什么 我的这个当执行Edit再update总是报错 ORA-01410 invalid RoWID 所以就放弃了记录类的操作方式，改直接执行sql语句
			//但是执行AddNew再update却是正常的，好奇怪
			//srvCfgSet.Edit();//打招呼，告诉数据库 我要更新了哈
			//srvCfgSet.m_VALUDE = m_strsrvip;
			//srvCfgSet.Update();//这里才是真正进行了更新操作，提交更新
		}
		else
		{
			//执行AddNew再update却是正常的，好奇怪
			srvCfgAddNode.AddNew();//打招呼，告诉数据库 我要加数据了哈
			srvCfgAddNode.m_ID = ID;
			srvCfgAddNode.m_NAME = Name;
			srvCfgAddNode.m_NODEDESC = netDescription;
			srvCfgAddNode.m_CREATETIME = time;
			srvCfgAddNode.m_AUTHCODE = authcode;
			srvCfgAddNode.m_STATE = state;

			srvCfgAddNode.Update();//这里才是真正进行了更新操作，提交更新
		}
		DbInitListSecNode(ID, Name, time, state, authcode);
	}
	CATCH_ALL(e)
	{
		e->ReportError();
		dbflag = 1;
	}
	END_CATCH_ALL

	if (dbflag == 0)
	{
		g_pDB->CommitTrans();
		AfxMessageBox("数据库网点信息写入成功");
	}
	else
	{
		g_pDB->Rollback();
		return;
	}

	if (srvCfgAddNode.IsOpen())
		srvCfgAddNode.Close();//断开数据库连接
	return;
}


void CDlgNetInfo::OnBnClickedButtonSearchinfo()
{
	// TODO: 在此添加控件通知处理程序代码
	CWnd *myWnd = NULL;
	CButton *But = NULL;
	int flag = 0;
	int dbflag = 0;
	int all = 0;
	UpdateData(TRUE);//把界面信息传到变量

	myWnd = (CWnd*)GetDlgItem(IDC_CHECK_TIME);
	But = (CButton *)myWnd;
	CSECMNGSECNODE srvCfgAddNode(g_pDB);//到这里 已经有数据库表名了
	if (But->GetCheck() == BST_CHECKED)
	{
		CTime sqlStartTime(m_dateBegin.GetYear(),m_dateBegin.GetMonth(),m_dateBegin.GetDay(),0,0,0);
		CTime sqlEndTime(m_dateEnd.GetYear(), m_dateEnd.GetMonth(), m_dateEnd.GetDay(), 23, 59, 59);
		if (sqlStartTime>=sqlEndTime)
		{
			AfxMessageBox("开始时间不能大于结束时间");
			return;
		} 
		
		TRY 
		{																				
			//相当于select *
			if (!srvCfgAddNode.Open(CRecordset::snapshot, NULL, CRecordset::none))//相当于加上了select from
			{
				AfxMessageBox("记录类打开数据库失败");
				return;
			}
			m_listSecNode.DeleteAllItems(); //删除视图 所有行
			m_listSecNode.SetRedraw(FALSE); //禁止刷新视图,避免重复插入条目时,闪屏

			while (!srvCfgAddNode.IsEOF())//have result 结果已经保存到SECMNGSRVCFG.h变量m_VALUE了
			{
				if (srvCfgAddNode.m_CREATETIME >= sqlEndTime ||
					srvCfgAddNode.m_CREATETIME <= sqlStartTime)
				{
					srvCfgAddNode.MoveNext();
					continue;
				}
				srvCfgAddNode.m_ID.TrimLeft();//左边去空格
				srvCfgAddNode.m_ID.TrimRight();
				CString ID = srvCfgAddNode.m_ID;;//将查询结果 给到控件对应的变量

				srvCfgAddNode.m_NAME.TrimLeft();//左边去空格
				srvCfgAddNode.m_NAME.TrimRight();
				CString Name = srvCfgAddNode.m_NAME;//将查询结果 给到控件对应的变量

				srvCfgAddNode.m_NODEDESC.TrimLeft();//左边去空格
				srvCfgAddNode.m_NODEDESC.TrimRight();
				CString netDescription = srvCfgAddNode.m_NODEDESC;//将查询结果 给到控件对应的变量

				CTime time = srvCfgAddNode.m_CREATETIME;

				int state = srvCfgAddNode.m_STATE;
				int authcode = srvCfgAddNode.m_AUTHCODE;
				DbInitListSecNode(ID, Name, time, state, authcode);

				srvCfgAddNode.MoveNext();

				flag = 1;
			}
			m_listSecNode.SetRedraw(TRUE);
			srvCfgAddNode.Close();
		}
		CATCH_ALL (e)
		{
			e->ReportError();
			dbflag = -1;

		}
		END_CATCH_ALL	
	}
	else//没选择复选框 就显示全部
	{
		TRY
		{
			//相当于select *
			if (!srvCfgAddNode.Open(CRecordset::snapshot, NULL, CRecordset::none))//相当于加上了select from
			{
				AfxMessageBox("记录类打开数据库失败");
				return;
			}
			m_listSecNode.DeleteAllItems(); //删除视图 所有行
			m_listSecNode.SetRedraw(FALSE); //禁止刷新视图,避免重复插入条目时,闪屏

			while (!srvCfgAddNode.IsEOF())//have result 结果已经保存到SECMNGSRVCFG.h变量m_VALUE了
			{
				srvCfgAddNode.m_ID.TrimLeft();//左边去空格
				srvCfgAddNode.m_ID.TrimRight();
				CString ID = srvCfgAddNode.m_ID;;//将查询结果 给到控件对应的变量

				srvCfgAddNode.m_NAME.TrimLeft();//左边去空格
				srvCfgAddNode.m_NAME.TrimRight();
				CString Name = srvCfgAddNode.m_NAME;//将查询结果 给到控件对应的变量

				srvCfgAddNode.m_NODEDESC.TrimLeft();//左边去空格
				srvCfgAddNode.m_NODEDESC.TrimRight();
				CString netDescription = srvCfgAddNode.m_NODEDESC;//将查询结果 给到控件对应的变量

				CTime time = srvCfgAddNode.m_CREATETIME;

				int state = srvCfgAddNode.m_STATE;
				int authcode = srvCfgAddNode.m_AUTHCODE;
				DbInitListSecNode(ID, Name, time, state, authcode);

				srvCfgAddNode.MoveNext();
				all = 1;
			}
			m_listSecNode.SetRedraw(TRUE);
			srvCfgAddNode.Close();
			}
				CATCH_ALL(e)
			{
				e->ReportError();
				flag = -1;

			}
			END_CATCH_ALL
	}
	if (srvCfgAddNode.IsOpen())
	{
		srvCfgAddNode.Close();
	}
	if (dbflag == -1)
	{
		AfxMessageBox("检索数据库失败!");
		return;
	}
	if (flag == 0&&all==0)
	{
		AfxMessageBox("没有检索到符合条件的记录");
		return;
	}
}


void CDlgNetInfo::OnBnClickedButtonExactsearch()

{
	// TODO: 在此添加控件通知处理程序代码
	CWnd *myWnd = NULL;
	CButton *But = NULL;
	int flag = 0;
	int dbflag = 0;
	int all = 0;
	UpdateData(TRUE);//把界面信息传到变量
	myWnd = (CWnd*)GetDlgItem(IDC_CHECK_NAME);
	But = (CButton *)myWnd;
	CSECMNGSECNODE srvCfgAddNode(g_pDB);//到这里 已经有数据库表名了

	if (But->GetCheck() == BST_CHECKED)
	{
		m_Name.TrimLeft();
		m_Name.TrimRight();
		if (m_Name=="")
		{
			AfxMessageBox("网点名称不能为空");
			return;
		}
		TRY
		{
			//相当于select *
			srvCfgAddNode.m_strFilter.Format("NAME='%s'",m_Name);
			if (!srvCfgAddNode.Open(CRecordset::snapshot, NULL, CRecordset::none))//相当于加上了select from
			{
				AfxMessageBox("记录类打开数据库失败");
				return;
			}
			m_listSecNode.DeleteAllItems(); //删除视图 所有行
			m_listSecNode.SetRedraw(FALSE); //禁止刷新视图,避免重复插入条目时,闪屏

			while (!srvCfgAddNode.IsEOF())//have result 结果已经保存到SECMNGSRVCFG.h变量m_VALUE了
			{
	
				srvCfgAddNode.m_ID.TrimLeft();//左边去空格
				srvCfgAddNode.m_ID.TrimRight();
				CString ID = srvCfgAddNode.m_ID;;//将查询结果 给到控件对应的变量

				srvCfgAddNode.m_NAME.TrimLeft();//左边去空格
				srvCfgAddNode.m_NAME.TrimRight();
				CString Name = srvCfgAddNode.m_NAME;//将查询结果 给到控件对应的变量

				srvCfgAddNode.m_NODEDESC.TrimLeft();//左边去空格
				srvCfgAddNode.m_NODEDESC.TrimRight();
				CString netDescription = srvCfgAddNode.m_NODEDESC;//将查询结果 给到控件对应的变量

				CTime time = srvCfgAddNode.m_CREATETIME;

				int state = srvCfgAddNode.m_STATE;
				int authcode = srvCfgAddNode.m_AUTHCODE;
				DbInitListSecNode(ID, Name, time, state, authcode);

				srvCfgAddNode.MoveNext();

				flag = 1;
			}
			m_listSecNode.SetRedraw(TRUE);
			srvCfgAddNode.Close();
			}
				CATCH_ALL(e)
			{
				e->ReportError();
				dbflag = -1;

			}
			END_CATCH_ALL
		}
		else//没选择复选框 就显示全部
		{
			TRY
			{
				//相当于select *
				if (!srvCfgAddNode.Open(CRecordset::snapshot, NULL, CRecordset::none))//相当于加上了select from
				{
					AfxMessageBox("记录类打开数据库失败");
					return;
				}
				m_listSecNode.DeleteAllItems(); //删除视图 所有行
				m_listSecNode.SetRedraw(FALSE); //禁止刷新视图,避免重复插入条目时,闪屏

				while (!srvCfgAddNode.IsEOF())//have result 结果已经保存到SECMNGSRVCFG.h变量m_VALUE了
				{
					srvCfgAddNode.m_ID.TrimLeft();//左边去空格
					srvCfgAddNode.m_ID.TrimRight();
					CString ID = srvCfgAddNode.m_ID;;//将查询结果 给到控件对应的变量

					srvCfgAddNode.m_NAME.TrimLeft();//左边去空格
					srvCfgAddNode.m_NAME.TrimRight();
					CString Name = srvCfgAddNode.m_NAME;//将查询结果 给到控件对应的变量

					srvCfgAddNode.m_NODEDESC.TrimLeft();//左边去空格
					srvCfgAddNode.m_NODEDESC.TrimRight();
					CString netDescription = srvCfgAddNode.m_NODEDESC;//将查询结果 给到控件对应的变量

					CTime time = srvCfgAddNode.m_CREATETIME;

					int state = srvCfgAddNode.m_STATE;
					int authcode = srvCfgAddNode.m_AUTHCODE;
					DbInitListSecNode(ID, Name, time, state, authcode);

					srvCfgAddNode.MoveNext();
					all = 1;
				}
				m_listSecNode.SetRedraw(TRUE);
				srvCfgAddNode.Close();
			}
			CATCH_ALL(e)
			{
				e->ReportError();
				flag = -1;

			}
			END_CATCH_ALL
		}
	if (srvCfgAddNode.IsOpen())
	{
		srvCfgAddNode.Close();
	}
	if (dbflag == -1)
	{
		AfxMessageBox("检索数据库失败!");
		return;
	}
	if (flag == 0 && all == 0)
	{
		AfxMessageBox("没有检索到符合条件的记录");
		return;
	}
}

void CDlgNetInfo::OnBnClickedButtonIdsearch()
{
	// TODO: 在此添加控件通知处理程序代码
	CWnd *myWnd = NULL;
	CButton *But = NULL;
	int flag = 0;
	int dbflag = 0;
	int all = 0;
	UpdateData(TRUE);//把界面信息传到变量
		myWnd = (CWnd*)GetDlgItem(IDC_CHECK_ID);
	But = (CButton *)myWnd;
	CSECMNGSECNODE srvCfgAddNode(g_pDB);//到这里 已经有数据库表名了

	if (But->GetCheck() == BST_CHECKED)
	{
		m_Id.TrimLeft();
		m_Id.TrimRight();
		if (m_Id == "")
		{
			AfxMessageBox("网点ID不能为空");
			return;
		}
		TRY
		{
			//相当于select *
			srvCfgAddNode.m_strFilter.Format("ID='%s'",m_Id);
		if (!srvCfgAddNode.Open(CRecordset::snapshot, NULL, CRecordset::none))//相当于加上了select from
		{
			AfxMessageBox("记录类打开数据库失败");
			return;
		}
		m_listSecNode.DeleteAllItems(); //删除视图 所有行
		m_listSecNode.SetRedraw(FALSE); //禁止刷新视图,避免重复插入条目时,闪屏

		while (!srvCfgAddNode.IsEOF())//have result 结果已经保存到SECMNGSRVCFG.h变量m_VALUE了
		{

			srvCfgAddNode.m_ID.TrimLeft();//左边去空格
			srvCfgAddNode.m_ID.TrimRight();
			CString ID = srvCfgAddNode.m_ID;;//将查询结果 给到控件对应的变量

			srvCfgAddNode.m_NAME.TrimLeft();//左边去空格
			srvCfgAddNode.m_NAME.TrimRight();
			CString Name = srvCfgAddNode.m_NAME;//将查询结果 给到控件对应的变量

			srvCfgAddNode.m_NODEDESC.TrimLeft();//左边去空格
			srvCfgAddNode.m_NODEDESC.TrimRight();
			CString netDescription = srvCfgAddNode.m_NODEDESC;//将查询结果 给到控件对应的变量

			CTime time = srvCfgAddNode.m_CREATETIME;

			int state = srvCfgAddNode.m_STATE;
			int authcode = srvCfgAddNode.m_AUTHCODE;
			DbInitListSecNode(ID, Name, time, state, authcode);

			srvCfgAddNode.MoveNext();

			flag = 1;
		}
		m_listSecNode.SetRedraw(TRUE);
		srvCfgAddNode.Close();
		}
			CATCH_ALL(e)
		{
			e->ReportError();
			dbflag = -1;

		}
		END_CATCH_ALL
	}
	else//没选择复选框 就显示全部
	{
		TRY
		{
			//相当于select *
			if (!srvCfgAddNode.Open(CRecordset::snapshot, NULL, CRecordset::none))//相当于加上了select from
			{
				AfxMessageBox("记录类打开数据库失败");
				return;
			}
		m_listSecNode.DeleteAllItems(); //删除视图 所有行
		m_listSecNode.SetRedraw(FALSE); //禁止刷新视图,避免重复插入条目时,闪屏

		while (!srvCfgAddNode.IsEOF())//have result 结果已经保存到SECMNGSRVCFG.h变量m_VALUE了
		{
			srvCfgAddNode.m_ID.TrimLeft();//左边去空格
			srvCfgAddNode.m_ID.TrimRight();
			CString ID = srvCfgAddNode.m_ID;;//将查询结果 给到控件对应的变量

			srvCfgAddNode.m_NAME.TrimLeft();//左边去空格
			srvCfgAddNode.m_NAME.TrimRight();
			CString Name = srvCfgAddNode.m_NAME;//将查询结果 给到控件对应的变量

			srvCfgAddNode.m_NODEDESC.TrimLeft();//左边去空格
			srvCfgAddNode.m_NODEDESC.TrimRight();
			CString netDescription = srvCfgAddNode.m_NODEDESC;//将查询结果 给到控件对应的变量

			CTime time = srvCfgAddNode.m_CREATETIME;

			int state = srvCfgAddNode.m_STATE;
			int authcode = srvCfgAddNode.m_AUTHCODE;
			DbInitListSecNode(ID, Name, time, state, authcode);

			srvCfgAddNode.MoveNext();
			all = 1;
		}
		m_listSecNode.SetRedraw(TRUE);
		srvCfgAddNode.Close();
		}
			CATCH_ALL(e)
		{
			e->ReportError();
			flag = -1;

		}
		END_CATCH_ALL
	}
	if (srvCfgAddNode.IsOpen())
	{
		srvCfgAddNode.Close();
	}
	if (dbflag == -1)
	{
		AfxMessageBox("检索数据库失败!");
		return;
	}
	if (flag == 0 && all == 0)
	{
		AfxMessageBox("没有检索到符合条件的记录");
		return;
	}
}

//删除网点
void CDlgNetInfo::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	//思路：从界面上删除记录，从数据库中删除记录（事物）
	//判断1条 多条记录；
	//	从界面中找到网点编号，根据网点编号，从数据库中删除网点记录
	//	从界面中删除显示。
	
	//用户输入 异常判断
	POSITION pos = m_listSecNode.GetFirstSelectedItemPosition();
	if (pos == NULL)
	{
		AfxMessageBox("请选择待删除的条目");
		return;
	}
	int selectNum = m_listSecNode.GetSelectedCount();
	if (selectNum>1)
	{
		AfxMessageBox("你选中了多行记录, 请你选中其中的一条记录！");
		return;
	}
	
	int nItem = m_listSecNode.GetNextSelectedItem(pos);//得到选中行
	CString strTmp = m_listSecNode.GetItemText(nItem, 3);
	if (strTmp == "正常")
	{
		AfxMessageBox("该网点正在使用，请先禁用再删除");
		return;
	}
	CString strId = m_listSecNode.GetItemText(nItem, 0);
	if (strId == "")
	{
		AfxMessageBox("网点编号不允许为空");
		return;
	}
	
	strTmp.Format("确定要删除编号为【%s】的网点吗？", strId);

	if (AfxMessageBox(strTmp, MB_ICONQUESTION | MB_YESNO | MB_DEFBUTTON2) == IDNO)
		return;


	int dbflag = 0;
	char sql[1024];
	
	g_pDB->BeginTrans();//开启事务
	CSECMNGSECNODE srvCfgDeleteNode(g_pDB);//到这里 已经有数据库表名了
	TRY
	{
		memset(sql, 0, sizeof(sql));
		if (!srvCfgDeleteNode.Open(CRecordset::snapshot, NULL, CRecordset::none))//相当于加上了select from
		{
			AfxMessageBox("记录类打开数据库失败");
			return;
		}
		if (!srvCfgDeleteNode.IsEOF())//have result 
		{
			sprintf(sql, "delete  from SECMNG.SECNODE WHERE ID='%s'", (LPTSTR)(LPCTSTR)strId);
			g_pDB->ExecuteSQL(sql);
		}
		else
		{
			AfxMessageBox("数据库中无对应的网点信息");
			return;
		}
	}
	CATCH_ALL(e)
	{
		e->ReportError();
		dbflag = 1;
	}
	END_CATCH_ALL

	if (dbflag == 0)
	{
		g_pDB->CommitTrans();
		m_listSecNode.DeleteItem(nItem);//从显示界面删除
		AfxMessageBox("数据库网点信息删除成功");
	}
	else
	{
		g_pDB->Rollback();
		return;
	}
	if (srvCfgDeleteNode.IsOpen())
		srvCfgDeleteNode.Close();//断开数据库连接
	return;
}


void CDlgNetInfo::OnBnClickedButtonEditnode()
{
	// TODO: 在此添加控件通知处理程序代码
	CDlgAddNetNode dlgAddNetNode;
	int dbflag = 0;
	char sql[1024];
	char toDate[128];
	CString ID = NULL;
	CString Name = NULL;
	CString netDescription = NULL;
	CTime time = CTime::GetCurrentTime();
	CString tempTime = NULL;
	int state = -1;
	int authcode =-1;

	

	//用户输入 异常判断
	POSITION pos = m_listSecNode.GetFirstSelectedItemPosition();
	if (pos == NULL)
	{
		AfxMessageBox("请选择待修改的条目");
		return;
	}
	int selectNum = m_listSecNode.GetSelectedCount();
	if (selectNum > 1)
	{
		AfxMessageBox("你选中了多行记录, 请你选中其中的一条记录！");
		return;
	}
	int nItem = m_listSecNode.GetNextSelectedItem(pos);//得到选中行
	CString strTmp = m_listSecNode.GetItemText(nItem, 3);
	CString strId = m_listSecNode.GetItemText(nItem, 0);

	if (strTmp == "正常")
	{
		AfxMessageBox("该网点正在使用，请先禁用再进行修改");
		return;
	}
	
	if (strId == "")
	{
		AfxMessageBox("网点编号不允许为空,请选择有效的条目");
		return;
	}
	
	g_pDB->BeginTrans();//开启事务
	CSECMNGSECNODE srvCfgAddNode(g_pDB);//到这里 已经有数据库表名了
	TRY 
	{
		memset(sql, 0, sizeof(sql));
		srvCfgAddNode.m_strFilter.Format("ID='%s'", strId);//相当于where子句有了,根据名字去表里查
														//查询表的IP列
		if (!srvCfgAddNode.Open(CRecordset::snapshot, NULL, CRecordset::none))//相当于加上了select from
		{
			AfxMessageBox("记录类打开数据库失败");
			return;
		}
		//先将信息显示到弹出框中
		if (!srvCfgAddNode.IsEOF())
		{
			srvCfgAddNode.m_ID.TrimLeft();//左边去空格
			srvCfgAddNode.m_ID.TrimRight();
			dlgAddNetNode.m_ID = srvCfgAddNode.m_ID;;//将查询结果 给到控件对应的变量

			srvCfgAddNode.m_NAME.TrimLeft();//左边去空格
			srvCfgAddNode.m_NAME.TrimRight();
			dlgAddNetNode.m_Name = srvCfgAddNode.m_NAME;//将查询结果 给到控件对应的变量

			srvCfgAddNode.m_NODEDESC.TrimLeft();//左边去空格
			srvCfgAddNode.m_NODEDESC.TrimRight();
			dlgAddNetNode.m_Description = srvCfgAddNode.m_NODEDESC;//将查询结果 给到控件对应的变量
		
			dlgAddNetNode.m_State = srvCfgAddNode.m_STATE;
			dlgAddNetNode.m_Autor = srvCfgAddNode.m_AUTHCODE;
		}
		else
		{
			AfxMessageBox("数据库中无该条目对应的信息，请深入检查其他错误");
			return;
		}
		
		if (dlgAddNetNode.DoModal() == IDCANCEL)
		{
			return;
		}
		UpdateData(FALSE);
		//从界面往变量传数据
		UpdateData(TRUE);
		if (dlgAddNetNode.m_ID.IsEmpty() || dlgAddNetNode.m_Name.IsEmpty() || dlgAddNetNode.m_Description.IsEmpty())
		{
			AfxMessageBox("输入数据不允许为空值");
			return;
		}
	    ID = dlgAddNetNode.m_ID;
		Name = dlgAddNetNode.m_Name;
		netDescription = dlgAddNetNode.m_Description;
		time = CTime::GetCurrentTime();
		tempTime = time.Format("%Y-%m-%d %H:%M:%S");
		state = dlgAddNetNode.m_State;
		authcode = dlgAddNetNode.m_Autor;
		memset(sql, 0, sizeof(sql));
		memset(toDate, 0, sizeof(toDate));
		if (ID != strId)
		{
			AfxMessageBox("ID更改,将删除本网点并新建网点信息");
			//删除
			sprintf(sql, "delete  from SECMNG.SECNODE WHERE ID='%s'", (LPTSTR)(LPCTSTR)strId);
			g_pDB->ExecuteSQL(sql);
			//新建
			srvCfgAddNode.AddNew();//打招呼，告诉数据库 我要加数据了哈
			srvCfgAddNode.m_ID = ID;
			srvCfgAddNode.m_NAME = Name;
			srvCfgAddNode.m_NODEDESC = netDescription;
			srvCfgAddNode.m_CREATETIME = time;
			srvCfgAddNode.m_AUTHCODE = authcode;
			srvCfgAddNode.m_STATE = state;

			srvCfgAddNode.Update();//这里才是真正进行了更新操作，提交更新
		}
		else//ID不变 只做更新
		{
			memset(sql, 0, sizeof(sql));
			sprintf(toDate, "to_date('%s', 'yyyy-mm-dd hh24:mi:ss')", tempTime);
			sprintf(sql, "update SECMNG.SECNODE set NAME='%s',NODEDESC='%s',CREATETIME=%s,AUTHCODE=%d,STATE=%d WHERE ID='%s'", (LPTSTR)(LPCTSTR)Name, (LPTSTR)(LPCTSTR)netDescription, toDate, authcode, state, (LPTSTR)(LPCTSTR)ID);
			g_pDB->ExecuteSQL(sql);
		}
	}
	CATCH_ALL (e)
	{
		e->ReportError();
		dbflag = 1;
	}
	END_CATCH_ALL
	if (dbflag == 0)
	{
		g_pDB->CommitTrans();
		m_listSecNode.DeleteItem(nItem);//从显示界面删除原网点信息
		DbInitListSecNode(ID, Name, time, state, authcode);//添加新网点显示
		AfxMessageBox("数据库网点信息写入成功");
	}
	else
	{
		g_pDB->Rollback();
	}

	if (srvCfgAddNode.IsOpen())
		srvCfgAddNode.Close();//断开数据库连接
	return;
}
