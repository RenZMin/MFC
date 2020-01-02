// DlgInitCfg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "SecMngAdmin.h"
#include "DlgInitCfg.h"
#include "afxdialogex.h"
#include "cfg_op.h"

// CDlgInitCfg �Ի���

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


// CDlgInitCfg ��Ϣ�������

int CDlgInitCfg::writeSecMngCfg(char *pItemName,CString pItemValue)
{
	int ret = 0;
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
	//д��DSN
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);//�ӿռ䵽�����洢
	if (m_dbDSN.IsEmpty() || m_dbPWD.IsEmpty() || m_dbUID.IsEmpty())
	{
		AfxMessageBox("¼����Ϣ������Ϊ��");
		return;
	}
	if (writeSecMngCfg("DSN", m_dbDSN)!=0)
	{
		AfxMessageBox("¼��DSN��Ϣʧ��");
		return;
	}
	else if (writeSecMngCfg("UID", m_dbUID) != 0)
	{
		AfxMessageBox("¼��UID��Ϣʧ��");
		return;
	}
	else if (writeSecMngCfg("PWD", m_dbPWD) != 0)
	{
		AfxMessageBox("¼��PWD��Ϣʧ��");
		return;
	}
	else
		AfxMessageBox("¼��DSN��PWD��UID��Ϣ�ɹ�");
	CDialog::OnOK();
}

//extern CString	g_dbSource, g_dbUser, g_dbpwd;
void CDlgInitCfg::OnBnClickedButtonLinktest()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDatabase myDB;
	CString		strCon;
	UpdateData(TRUE);//�ӿռ䵽�����洢
	TRY 
	{
		strCon.Format("DSN=%s;UID=%s;PWD=%s", m_dbDSN, m_dbUID, m_dbPWD);
	   //AfxMessageBox("DSN111:" + m_dbDSN + "|UID:" + m_dbUID + "|PWD:" + m_dbPWD);
		if (myDB.OpenEx(strCon, CDatabase::noOdbcDialog) == FALSE)
		{
			AfxMessageBox("�������ݿ�ʧ��");
			return;
		}
		else
		{
			AfxMessageBox("�������ݿ�ɹ�");
		}
		myDB.Close();//�رյ�ǰ�Ĳ�������

	}
	CATCH_ALL (e)
	{
		e->ReportError();//��ӡ�쳣
	}
	END_CATCH_ALL
	

}
