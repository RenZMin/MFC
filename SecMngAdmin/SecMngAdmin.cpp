
// SecMngAdmin.cpp : 定义应用程序的类行为。
//

#include "stdafx.h"
#include "afxwinappex.h"
#include "afxdialogex.h"
#include "SecMngAdmin.h"
#include "MainFrm.h"

#include "SecMngAdminDoc.h"
#include "SecMngAdminView.h"
#include "cfg_op.h"
#include "secmng_globvar.h"//该头文件只能被包含一次，因为里面有全局变量的定义

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CSecMngAdminApp

BEGIN_MESSAGE_MAP(CSecMngAdminApp, CWinApp)
	ON_COMMAND(ID_APP_ABOUT, &CSecMngAdminApp::OnAppAbout)
	// 基于文件的标准文档命令
	ON_COMMAND(ID_FILE_NEW, &CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, &CWinApp::OnFileOpen)
END_MESSAGE_MAP()


// CSecMngAdminApp 构造

CSecMngAdminApp::CSecMngAdminApp()
{
	// TODO: 将以下应用程序 ID 字符串替换为唯一的 ID 字符串；建议的字符串格式
	//为 CompanyName.ProductName.SubProduct.VersionInformation
	SetAppID(_T("SecMngAdmin.AppID.NoVersion"));

	// TODO: 在此处添加构造代码，
	// 将所有重要的初始化放置在 InitInstance 中
}



int CSecMngAdminApp::readSecMngCfg()
{
	int ret = 0;
	char pValue[64] = { 0 };
	int pValueLen = sizeof(pValue);
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
	//读取DSN
	ret = GetCfgItem((LPTSTR)(LPCTSTR)g_strINIPath, "DSN", pValue, &pValueLen);
	if (ret!=0)
	{
		//AfxMessageBox("DSN读取失败\n");
		return -1;
	}
	//给全局DSN赋值
	g_dbSource = pValue;
	//读取UID
	memset(pValue, 0, pValueLen);
	ret = GetCfgItem((LPTSTR)(LPCTSTR)g_strINIPath, "UID", pValue, &pValueLen);
	if (ret != 0)
	{
		//AfxMessageBox("UID读取失败\n");
		return -1;
	}
	//给全局UID赋值
	g_dbUser = pValue;
	//读取PWD
	memset(pValue, 0, pValueLen);
	ret = GetCfgItem((LPTSTR)(LPCTSTR)g_strINIPath, "PWD", pValue, &pValueLen);
	if (ret != 0)
	{
		//AfxMessageBox("PWD读取失败\n");
		return -1;
	}
	//给全局PWD赋值
	g_dbpwd = pValue;
	return 0;
}


int CSecMngAdminApp::NewOdbc_Connet()
{
	g_pDB = &myDB;//g_pDB代表一条数据库连接，用于数据库操作
	CString	strCon;
	TRY
	{
		strCon.Format("DSN=%s;UID=%s;PWD=%s", g_dbSource, g_dbUser, g_dbpwd);
		//AfxMessageBox("DSN111:" + m_dbDSN + "|UID:" + m_dbUID + "|PWD:" + m_dbPWD);
		if (g_pDB->OpenEx(strCon, CDatabase::noOdbcDialog) == FALSE)
		{
			return -1;
		}
	}
	CATCH_ALL(e)
	{
		e->ReportError();//打印异常
	}
	END_CATCH_ALL
	return 0;
}




// 唯一的一个 CSecMngAdminApp 对象
CSecMngAdminApp theApp;


// CSecMngAdminApp 初始化

BOOL CSecMngAdminApp::InitInstance()
{
	int ret = 0;
	CWinApp::InitInstance();


	EnableTaskbarInteraction(FALSE);

	// 使用 RichEdit 控件需要 AfxInitRichEdit2()	
	// AfxInitRichEdit2();

	//弹出对话框，用户输入信息
	CDlgInitCfg dlgInitCfg;

	// 标准初始化
	ret = readSecMngCfg();
	if (ret != 0)
	{
		AfxMessageBox("配置文件不存在，请手动输入");

		if (dlgInitCfg.DoModal() == IDCANCEL)
		{
			return FALSE;
		}
		g_dbSource = dlgInitCfg.m_dbDSN;
		g_dbUser = dlgInitCfg.m_dbUID;
		g_dbpwd = dlgInitCfg.m_dbPWD;
	}
	else
	{
		AfxMessageBox("DSN:" + g_dbSource + "|UID:" + g_dbUser + "|PWD:" + g_dbpwd);
	}

	//借助全局变量 连接数据库
	ret = NewOdbc_Connet();
	if (ret != 0)
	{
		AfxMessageBox("数据库连接失败");
		return FALSE;
	}
	else
		AfxMessageBox("数据库连接成功");



	// 如果未使用这些功能并希望减小
	// 最终可执行文件的大小，则应移除下列
	// 不需要的特定初始化例程
	// 更改用于存储设置的注册表项
	// TODO: 应适当修改该字符串，
	// 例如修改为公司或组织名
	SetRegistryKey(_T("应用程序向导生成的本地应用程序"));
	LoadStdProfileSettings(4);  // 加载标准 INI 文件选项(包括 MRU)


	// 注册应用程序的文档模板。  文档模板
	// 将用作文档、框架窗口和视图之间的连接
	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CSecMngAdminDoc),
		RUNTIME_CLASS(CMainFrame),       // 主 SDI 框架窗口
		RUNTIME_CLASS(CSecMngAdminView));
	if (!pDocTemplate)
		return FALSE;
	AddDocTemplate(pDocTemplate);


	// 分析标准 shell 命令、DDE、打开文件操作的命令行
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);



	// 调度在命令行中指定的命令。  如果
	// 用 /RegServer、/Register、/Unregserver 或 /Unregister 启动应用程序，则返回 FALSE。
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	// 唯一的一个窗口已初始化，因此显示它并对其进行更新
	m_pMainWnd->ShowWindow(SW_SHOW);
	m_pMainWnd->UpdateWindow();
	return TRUE;
}

// CSecMngAdminApp 消息处理程序


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()

// 用于运行对话框的应用程序命令
void CSecMngAdminApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

// CSecMngAdminApp 消息处理程序



