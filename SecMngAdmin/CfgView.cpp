// CfgView.cpp : 实现文件
//

#include "stdafx.h"
#include "SecMngAdmin.h"
#include "CfgView.h"

// CCfgView

IMPLEMENT_DYNCREATE(CCfgView, CFormView)

CCfgView::CCfgView()
	: CFormView(IDD_DIALOG_CFG)
	, m_strsrvip(_T(""))
	, m_strsrvmaxnode(_T(""))
	, m_strsrvport(_T(""))
{

}

CCfgView::~CCfgView()
{
}

void CCfgView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_IP, m_strsrvip);
	DDX_Text(pDX, IDC_EDIT_MAXNODE, m_strsrvmaxnode);
	DDX_Text(pDX, IDC_EDIT_PORT, m_strsrvport);
}

BEGIN_MESSAGE_MAP(CCfgView, CFormView)
	
	ON_BN_CLICKED(IDOK_SRVCFG, &CCfgView::OnBnClickedSrvcfg)
END_MESSAGE_MAP()


// CCfgView 诊断

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


// CCfgView 消息处理程序

int CCfgView::writeSecMngCfg(char *pItemName, CString pItemValue,char *fileName)
{
	int ret = 0;
	//找到exe所在目录F:\C++学习\C++项目学习笔记\SecMngAdmin\Debug\SecMngAdmin.exe
	//F:\C++学习\C++项目学习笔记\SecMngAdmin\Debug\secmngadmin.ini
	char strFileName[1024] = { 0 };
	//获取当前工作模块文件路径
	GetModuleFileName(AfxGetInstanceHandle(), strFileName, sizeof(strFileName));
	//拼接文件路径
	CString  g_strINIPath = strFileName;		//定义Ctring类变量，使用CString API
	int i = g_strINIPath.ReverseFind('\\');		//自右向左查找'\'
	g_strINIPath = g_strINIPath.Left(i);		//根据找到的位置提取

	g_strINIPath = g_strINIPath + "\\" + fileName;
	//AfxMessageBox(g_strINIPath);
	//写入DSN
	ret = WriteCfgItem((LPTSTR)(LPCTSTR)g_strINIPath, pItemName, (LPTSTR)(LPCTSTR)pItemValue, pItemValue.GetLength());
	if (ret != 0)
	{
		return ret;
	}
	return 0;
}



extern CDatabase	*g_pDB;
void CCfgView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: 在此添加专用代码和/或调用基类
	//select * from SRVCFG where key = 'secmng_server_ip';  --IP
	CSECMNGSRVCFG srvCfgSet(g_pDB);//到这里 已经有数据库表名了
	srvCfgSet.m_strFilter.Format("key='%s'", "secmng_server_ip");//相当于where子句有了
	//查询表的IP列
	if (!srvCfgSet.Open(CRecordset::snapshot, NULL, CRecordset::none))//相当于加上了select from
	{
		AfxMessageBox("记录类打开数据库失败");
		return;
	}
	if (!srvCfgSet.IsEOF())//have result 结果已经保存到SECMNGSRVCFG.h变量m_VALUE了
	{
		srvCfgSet.m_VALUDE.TrimLeft();//左边去空格
		srvCfgSet.m_VALUDE.TrimRight();
		m_strsrvip = srvCfgSet.m_VALUDE;//将查询结果 给到控件对应的变量
	}
	else
	{
		m_strsrvip = "";
	}


	srvCfgSet.m_strFilter.Format("key='%s'", "secmng_server_maxnetnum");//相当于where子句有了
	if (!srvCfgSet.Requery())//相当于加上了select from
	{
		AfxMessageBox("Requery maxnetnum 失败");
		return;
	}
	if (!srvCfgSet.IsEOF())//have result 结果已经保存到SECMNGSRVCFG.h变量m_VALUE了
	{
		srvCfgSet.m_VALUDE.TrimLeft();//左边去空格
		srvCfgSet.m_VALUDE.TrimRight();
		m_strsrvmaxnode = srvCfgSet.m_VALUDE;//将查询结果 给到控件对应的变量
	}
	else
	{
		m_strsrvmaxnode = "";
	}

	srvCfgSet.m_strFilter.Format("key='%s'", "secmng_server_port");//相当于where子句有了
	if (!srvCfgSet.Requery())//相当于加上了select from
	{
		AfxMessageBox("Requery port 失败");
		return;
	}
	if (!srvCfgSet.IsEOF())//have result 结果已经保存到SECMNGSRVCFG.h变量m_VALUE了
	{
		srvCfgSet.m_VALUDE.TrimLeft();//左边去空格
		srvCfgSet.m_VALUDE.TrimRight();
		m_strsrvport = srvCfgSet.m_VALUDE;//将查询结果 给到控件对应的变量
	}
	else
	{
		m_strsrvport = "";
	}
	srvCfgSet.Close();
	UpdateData(FALSE);//从变量到空间显示

}

//CString m_strsrvip;
//CString m_strsrvmaxnode;
//CString m_strsrvport;
void CCfgView::OnBnClickedSrvcfg()
{
	int dbflag = 0;
	char sql[1024];
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	if (m_strsrvip.IsEmpty() || m_strsrvmaxnode.IsEmpty() || m_strsrvport.IsEmpty())
	{
		AfxMessageBox("输入数据不允许为空值");
		return;
	}
	g_pDB->BeginTrans();//开启事务
	CSECMNGSRVCFG srvCfgSet(g_pDB);//到这里 已经有数据库表名了
	
	
	TRY 
	{
		memset(sql, 0, sizeof(sql));
		srvCfgSet.m_strFilter.Format("key='%s'", "secmng_server_ip");//相当于where子句有了
		//查询表的IP列
		if (!srvCfgSet.Open(CRecordset::snapshot, NULL, CRecordset::none))//相当于加上了select from
		{
			AfxMessageBox("记录类打开数据库失败");
			return;
		}
		if (!srvCfgSet.IsEOF())//have result 
		{
			sprintf(sql, "update SECMNG.SRVCFG set valude ='%s' WHERE key='secmng_server_ip'", (LPTSTR)(LPCTSTR)m_strsrvip);
			g_pDB->ExecuteSQL(sql);
			if (writeSecMngCfg("ServerIp", m_strsrvip,"config.ini") != 0)
			{
				AfxMessageBox("录入ServerIp信息失败");
				return;
			}
			//不知道为什么 我的这个当执行Edit再update总是报错 ORA-01410 invalid RoWID 所以就放弃了记录类的操作方式，改直接执行sql语句
			//但是执行AddNew再update却是正常的，好奇怪
			//srvCfgSet.Edit();//打招呼，告诉数据库 我要更新了哈
			//srvCfgSet.m_VALUDE = m_strsrvip;
			//srvCfgSet.Update();//这里才是真正进行了更新操作，提交更新
		}
		else
		{
			//执行AddNew再update却是正常的，好奇怪
			srvCfgSet.AddNew();//打招呼，告诉数据库 我要加数据了哈
			srvCfgSet.m_KEY = "secmng_server_ip";
			srvCfgSet.m_VALUDE = m_strsrvip;
			srvCfgSet.Update();//这里才是真正进行了更新操作，提交更新
			if (writeSecMngCfg("ServerIp", m_strsrvip, "config.ini") != 0)
			{
				AfxMessageBox("录入ServerIp信息失败");
				return;
			}
		}

		memset(sql, 0, sizeof(sql));
		srvCfgSet.m_strFilter.Format("key='%s'", "secmng_server_port");//相当于where子句有了												
		//查询表的port列
		if (!srvCfgSet.Requery())//相当于加上了select from
		{
			AfxMessageBox("记录类打开数据库失败");
			return;
		}
		if (!srvCfgSet.IsEOF())//have result 
		{
			sprintf(sql, "update SECMNG.SRVCFG set valude ='%s' WHERE key='secmng_server_port'", (LPTSTR)(LPCTSTR)m_strsrvport);
			g_pDB->ExecuteSQL(sql);
			if (writeSecMngCfg("ServerPort", m_strsrvport, "config.ini") != 0)
			{
				AfxMessageBox("录入ServerPort信息失败");
				return;
			}
			//不知道为什么 我的这个当执行Edit再update总是报错 ORA-01410 invalid RoWID 所以就放弃了记录类的操作方式，改直接执行sql语句
			//但是执行AddNew再update却是正常的，好奇怪
			//srvCfgSet.Edit();//打招呼，告诉数据库 我要更新了哈
			//srvCfgSet.m_VALUDE = m_strsrvip;
			//srvCfgSet.Update();//这里才是真正进行了更新操作，提交更新
		}
		else
		{
			//执行AddNew再update却是正常的，好奇怪
			srvCfgSet.AddNew();//打招呼，告诉数据库 我要加数据了哈
			srvCfgSet.m_KEY = "secmng_server_port";
			srvCfgSet.m_VALUDE = m_strsrvport;
			srvCfgSet.Update();//这里才是真正进行了更新操作，提交更新
			if (writeSecMngCfg("ServerPort", m_strsrvport, "config.ini") != 0)
			{
				AfxMessageBox("录入ServerPort信息失败");
				return;
			}
		}

		memset(sql, 0, sizeof(sql));
		srvCfgSet.m_strFilter.Format("key='%s'", "secmng_server_port");//相当于where子句有了												
		//查询表的maxnetnum列
		if (!srvCfgSet.Requery())//相当于加上了select from
		{
			AfxMessageBox("记录类打开数据库失败");
			return;
		}
		if (!srvCfgSet.IsEOF())//have result 
		{
			sprintf(sql, "update SECMNG.SRVCFG set valude ='%s' WHERE key='secmng_server_maxnetnum'", (LPTSTR)(LPCTSTR)m_strsrvmaxnode);
			g_pDB->ExecuteSQL(sql);
			//不知道为什么 我的这个当执行Edit再update总是报错 ORA-01410 invalid RoWID 所以就放弃了记录类的操作方式，改直接执行sql语句
			//但是执行AddNew再update却是正常的，好奇怪
			//srvCfgSet.Edit();//打招呼，告诉数据库 我要更新了哈
			//srvCfgSet.m_VALUDE = m_strsrvip;
			//srvCfgSet.Update();//这里才是真正进行了更新操作，提交更新
			if (writeSecMngCfg("ServerMaxnode", m_strsrvmaxnode, "config.ini") != 0)
			{
				AfxMessageBox("录入ServerMaxnode信息失败");
				return;
			}
		}
		else
		{
			//执行AddNew再update却是正常的，好奇怪
			srvCfgSet.AddNew();//打招呼，告诉数据库 我要加数据了哈
			srvCfgSet.m_KEY = "secmng_server_maxnetnum";
			srvCfgSet.m_VALUDE = m_strsrvmaxnode;
			srvCfgSet.Update();//这里才是真正进行了更新操作，提交更新
			if (writeSecMngCfg("ServerMaxnode", m_strsrvmaxnode, "config.ini") != 0)
			{
				AfxMessageBox("录入ServerMaxnode信息失败");
				return;
			}
		}
		//写到那个ini文件
		



	}
	CATCH_ALL(e)
	{
		e->ReportError();
		dbflag = 1;
	}
	END_CATCH_ALL

	if (dbflag==0)
	{
		g_pDB->CommitTrans();
		AfxMessageBox("数据库信息写入成功");
	}
	else
	{
		g_pDB->Rollback();
		return;
	}

	if (srvCfgSet.IsOpen())
		srvCfgSet.Close();//断开数据库连接
	return;
}



























