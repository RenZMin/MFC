// DlgInitCfg.cpp : 实现文件
//

#include "stdafx.h"
#include "SecMngAdmin.h"
#include "DlgInitCfg.h"
#include "afxdialogex.h"
#include "cfg_op.h"

// CDlgInitCfg 对话框

IMPLEMENT_DYNAMIC(CDlgInitCfg, CDialog)

CDlgInitCfg::CDlgInitCfg(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_DIALOG_INITDB, pParent)
	, m_dbDSN(_T(""))
	, m_dbPWD(_T(""))
	, m_dbUID(_T(""))
{

}

CDlgInitCfg::~CDlgInitCfg()
{
}

void CDlgInitCfg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_DSN, m_dbDSN);
	DDX_Text(pDX, IDC_EDIT_PWD, m_dbPWD);
	DDX_Text(pDX, IDC_EDIT_UID, m_dbUID);
}


BEGIN_MESSAGE_MAP(CDlgInitCfg, CDialog)
	ON_BN_CLICKED(IDOK, &CDlgInitCfg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON_LINKTEST, &CDlgInitCfg::OnBnClickedButtonLinktest)
END_MESSAGE_MAP()


// CDlgInitCfg 消息处理程序

int CDlgInitCfg::writeSecMngCfg(char *pItemName,CString pItemValue)
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

	g_strINIPath = g_strINIPath + "\\" + "secmngadmin.ini";
	//AfxMessageBox(g_strINIPath);
	//写入DSN
	ret = WriteCfgItem((LPTSTR)(LPCTSTR)g_strINIPath, pItemName, (LPTSTR)(LPCTSTR)pItemValue, pItemValue.GetLength());
	if (ret != 0)
	{
		return ret;
	}
	return 0;
}





void CDlgInitCfg::OnBnClickedOk()
{
	int ret = -1;
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);//从空间到变量存储
	if (m_dbDSN.IsEmpty() || m_dbPWD.IsEmpty() || m_dbUID.IsEmpty())
	{
		AfxMessageBox("录入信息不允许为空");
		return;
	}
	if (writeSecMngCfg("DSN", m_dbDSN)!=0)
	{
		AfxMessageBox("录入DSN信息失败");
		return;
	}
	else if (writeSecMngCfg("UID", m_dbUID) != 0)
	{
		AfxMessageBox("录入UID信息失败");
		return;
	}
	else if (writeSecMngCfg("PWD", m_dbPWD) != 0)
	{
		AfxMessageBox("录入PWD信息失败");
		return;
	}
	else
		AfxMessageBox("录入DSN、PWD、UID信息成功");
	CDialog::OnOK();
}

//extern CString	g_dbSource, g_dbUser, g_dbpwd;
void CDlgInitCfg::OnBnClickedButtonLinktest()
{
	// TODO: 在此添加控件通知处理程序代码
	CDatabase myDB;
	CString		strCon;
	UpdateData(TRUE);//从空间到变量存储
	TRY 
	{
		strCon.Format("DSN=%s;UID=%s;PWD=%s", m_dbDSN, m_dbUID, m_dbPWD);
	   //AfxMessageBox("DSN111:" + m_dbDSN + "|UID:" + m_dbUID + "|PWD:" + m_dbPWD);
		if (myDB.OpenEx(strCon, CDatabase::noOdbcDialog) == FALSE)
		{
			AfxMessageBox("连接数据库失败");
			return;
		}
		else
		{
			AfxMessageBox("连接数据库成功");
		}
		myDB.Close();//关闭当前的测试连接

	}
	CATCH_ALL (e)
	{
		e->ReportError();//打印异常
	}
	END_CATCH_ALL
	

}
