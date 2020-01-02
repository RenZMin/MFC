
// SecMngAdmin.cpp : ����Ӧ�ó��������Ϊ��
//

#include "stdafx.h"
#include "afxwinappex.h"
#include "afxdialogex.h"
#include "SecMngAdmin.h"
#include "MainFrm.h"

#include "SecMngAdminDoc.h"
#include "SecMngAdminView.h"
#include "cfg_op.h"
#include "secmng_globvar.h"//��ͷ�ļ�ֻ�ܱ�����һ�Σ���Ϊ������ȫ�ֱ����Ķ���

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CSecMngAdminApp

BEGIN_MESSAGE_MAP(CSecMngAdminApp, CWinApp)
	ON_COMMAND(ID_APP_ABOUT, &CSecMngAdminApp::OnAppAbout)
	// �����ļ��ı�׼�ĵ�����
	ON_COMMAND(ID_FILE_NEW, &CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, &CWinApp::OnFileOpen)
END_MESSAGE_MAP()


// CSecMngAdminApp ����

CSecMngAdminApp::CSecMngAdminApp()
{
	// TODO: ������Ӧ�ó��� ID �ַ����滻ΪΨһ�� ID �ַ�����������ַ�����ʽ
	//Ϊ CompanyName.ProductName.SubProduct.VersionInformation
	SetAppID(_T("SecMngAdmin.AppID.NoVersion"));

	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}



int CSecMngAdminApp::readSecMngCfg()
{
	int ret = 0;
	char pValue[64] = { 0 };
	int pValueLen = sizeof(pValue);
	//�ҵ�exe����Ŀ¼F:\C++ѧϰ\C++��Ŀѧϰ�ʼ�\SecMngAdmin\Debug\SecMngAdmin.exe
	//F:\C++ѧϰ\C++��Ŀѧϰ�ʼ�\SecMngAdmin\Debug\secmngadmin.ini
	char strFileName[1024] = { 0 };
	//��ȡ��ǰ����ģ���ļ�·��
	GetModuleFileName(AfxGetInstanceHandle(), strFileName, sizeof(strFileName));
	//ƴ���ļ�·��
	CString  g_strINIPath = strFileName;		//����Ctring�������ʹ��CString API
	int i = g_strINIPath.ReverseFind('\\');		//�����������'\'
	g_strINIPath = g_strINIPath.Left(i);		//�����ҵ���λ����ȡ

	g_strINIPath = g_strINIPath + "\\" + "secmngadmin.ini";
	//AfxMessageBox(g_strINIPath);
	//��ȡDSN
	ret = GetCfgItem((LPTSTR)(LPCTSTR)g_strINIPath, "DSN", pValue, &pValueLen);
	if (ret!=0)
	{
		//AfxMessageBox("DSN��ȡʧ��\n");
		return -1;
	}
	//��ȫ��DSN��ֵ
	g_dbSource = pValue;
	//��ȡUID
	memset(pValue, 0, pValueLen);
	ret = GetCfgItem((LPTSTR)(LPCTSTR)g_strINIPath, "UID", pValue, &pValueLen);
	if (ret != 0)
	{
		//AfxMessageBox("UID��ȡʧ��\n");
		return -1;
	}
	//��ȫ��UID��ֵ
	g_dbUser = pValue;
	//��ȡPWD
	memset(pValue, 0, pValueLen);
	ret = GetCfgItem((LPTSTR)(LPCTSTR)g_strINIPath, "PWD", pValue, &pValueLen);
	if (ret != 0)
	{
		//AfxMessageBox("PWD��ȡʧ��\n");
		return -1;
	}
	//��ȫ��PWD��ֵ
	g_dbpwd = pValue;
	return 0;
}


int CSecMngAdminApp::NewOdbc_Connet()
{
	g_pDB = &myDB;//g_pDB����һ�����ݿ����ӣ��������ݿ����
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
		e->ReportError();//��ӡ�쳣
	}
	END_CATCH_ALL
	return 0;
}




// Ψһ��һ�� CSecMngAdminApp ����
CSecMngAdminApp theApp;


// CSecMngAdminApp ��ʼ��

BOOL CSecMngAdminApp::InitInstance()
{
	int ret = 0;
	CWinApp::InitInstance();


	EnableTaskbarInteraction(FALSE);

	// ʹ�� RichEdit �ؼ���Ҫ AfxInitRichEdit2()	
	// AfxInitRichEdit2();

	//�����Ի����û�������Ϣ
	CDlgInitCfg dlgInitCfg;

	// ��׼��ʼ��
	ret = readSecMngCfg();
	if (ret != 0)
	{
		AfxMessageBox("�����ļ������ڣ����ֶ�����");

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

	//����ȫ�ֱ��� �������ݿ�
	ret = NewOdbc_Connet();
	if (ret != 0)
	{
		AfxMessageBox("���ݿ�����ʧ��");
		return FALSE;
	}
	else
		AfxMessageBox("���ݿ����ӳɹ�");



	// ���δʹ����Щ���ܲ�ϣ����С
	// ���տ�ִ���ļ��Ĵ�С����Ӧ�Ƴ�����
	// ����Ҫ���ض���ʼ������
	// �������ڴ洢���õ�ע�����
	// TODO: Ӧ�ʵ��޸ĸ��ַ�����
	// �����޸�Ϊ��˾����֯��
	SetRegistryKey(_T("Ӧ�ó��������ɵı���Ӧ�ó���"));
	LoadStdProfileSettings(4);  // ���ر�׼ INI �ļ�ѡ��(���� MRU)


	// ע��Ӧ�ó�����ĵ�ģ�塣  �ĵ�ģ��
	// �������ĵ�����ܴ��ں���ͼ֮�������
	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CSecMngAdminDoc),
		RUNTIME_CLASS(CMainFrame),       // �� SDI ��ܴ���
		RUNTIME_CLASS(CSecMngAdminView));
	if (!pDocTemplate)
		return FALSE;
	AddDocTemplate(pDocTemplate);


	// ������׼ shell ���DDE�����ļ�������������
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);



	// ��������������ָ�������  ���
	// �� /RegServer��/Register��/Unregserver �� /Unregister ����Ӧ�ó����򷵻� FALSE��
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	// Ψһ��һ�������ѳ�ʼ���������ʾ����������и���
	m_pMainWnd->ShowWindow(SW_SHOW);
	m_pMainWnd->UpdateWindow();
	return TRUE;
}

// CSecMngAdminApp ��Ϣ�������


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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

// �������жԻ����Ӧ�ó�������
void CSecMngAdminApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

// CSecMngAdminApp ��Ϣ�������



