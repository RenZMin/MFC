// CfgView.cpp : ʵ���ļ�
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
	, m_Dsn(_T(""))
	, m_Uid(_T(""))
	, m_Pwd(_T(""))
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
	DDX_Text(pDX, IDC_EDIT_DSN, m_Dsn);
	DDX_Text(pDX, IDC_EDIT_UID, m_Uid);
	DDX_Text(pDX, IDC_EDIT_PWD, m_Pwd);
}

BEGIN_MESSAGE_MAP(CCfgView, CFormView)
	
	ON_BN_CLICKED(IDOK_SRVCFG, &CCfgView::OnBnClickedSrvcfg)
	ON_BN_CLICKED(IDOK_DSN_UID_PWD, &CCfgView::OnBnClickedDsnUidPwd)
END_MESSAGE_MAP()


// CCfgView ���

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


// CCfgView ��Ϣ�������

int CCfgView::writeSecMngCfg(char *pItemName, CString pItemValue,char *fileName)
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

	g_strINIPath = g_strINIPath + "\\" + fileName;
	//AfxMessageBox(g_strINIPath);
	//д��DSN
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

	// TODO: �ڴ����ר�ô����/����û���
	//select * from SRVCFG where key = 'secmng_server_ip';  --IP
	CSECMNGSRVCFG srvCfgSet(g_pDB);//������ �Ѿ������ݿ������
	srvCfgSet.m_strFilter.Format("key='%s'", "secmng_server_ip");//�൱��where�Ӿ�����
	//��ѯ���IP��
	if (!srvCfgSet.Open(CRecordset::snapshot, NULL, CRecordset::none))//�൱�ڼ�����select from
	{
		AfxMessageBox("��¼������ݿ�ʧ��");
		return;
	}
	if (!srvCfgSet.IsEOF())//have result ����Ѿ����浽SECMNGSRVCFG.h����m_VALUE��
	{
		srvCfgSet.m_VALUDE.TrimLeft();//���ȥ�ո�
		srvCfgSet.m_VALUDE.TrimRight();
		m_strsrvip = srvCfgSet.m_VALUDE;//����ѯ��� �����ؼ���Ӧ�ı���
	}
	else
	{
		m_strsrvip = "";
	}


	srvCfgSet.m_strFilter.Format("key='%s'", "secmng_server_maxnetnum");//�൱��where�Ӿ�����
	if (!srvCfgSet.Requery())//�൱�ڼ�����select from
	{
		AfxMessageBox("Requery maxnetnum ʧ��");
		return;
	}
	if (!srvCfgSet.IsEOF())//have result ����Ѿ����浽SECMNGSRVCFG.h����m_VALUE��
	{
		srvCfgSet.m_VALUDE.TrimLeft();//���ȥ�ո�
		srvCfgSet.m_VALUDE.TrimRight();
		m_strsrvmaxnode = srvCfgSet.m_VALUDE;//����ѯ��� �����ؼ���Ӧ�ı���
	}
	else
	{
		m_strsrvmaxnode = "";
	}

	srvCfgSet.m_strFilter.Format("key='%s'", "secmng_server_port");//�൱��where�Ӿ�����
	if (!srvCfgSet.Requery())//�൱�ڼ�����select from
	{
		AfxMessageBox("Requery port ʧ��");
		return;
	}
	if (!srvCfgSet.IsEOF())//have result ����Ѿ����浽SECMNGSRVCFG.h����m_VALUE��
	{
		srvCfgSet.m_VALUDE.TrimLeft();//���ȥ�ո�
		srvCfgSet.m_VALUDE.TrimRight();
		m_strsrvport = srvCfgSet.m_VALUDE;//����ѯ��� �����ؼ���Ӧ�ı���
	}
	else
	{
		m_strsrvport = "";
	}
	///
	srvCfgSet.m_strFilter.Format("key='%s'", "secmng_data_source");//�൱��where�Ӿ�����
	if (!srvCfgSet.Requery())//�൱�ڼ�����select from
	{
		AfxMessageBox("Requery secmng_data_source ʧ��");
		return;
	}
	if (!srvCfgSet.IsEOF())//have result ����Ѿ����浽SECMNGSRVCFG.h����m_VALUE��
	{
		srvCfgSet.m_VALUDE.TrimLeft();//���ȥ�ո�
		srvCfgSet.m_VALUDE.TrimRight();
		m_Dsn = srvCfgSet.m_VALUDE;//����ѯ��� �����ؼ���Ӧ�ı���
	}
	else
	{
		m_Dsn = "";
	}

	srvCfgSet.m_strFilter.Format("key='%s'", "secmng_user_id");//�൱��where�Ӿ�����
	if (!srvCfgSet.Requery())//�൱�ڼ�����select from
	{
		AfxMessageBox("Requery secmng_user_id ʧ��");
		return;
	}
	if (!srvCfgSet.IsEOF())//have result ����Ѿ����浽SECMNGSRVCFG.h����m_VALUE��
	{
		srvCfgSet.m_VALUDE.TrimLeft();//���ȥ�ո�
		srvCfgSet.m_VALUDE.TrimRight();
		m_Uid = srvCfgSet.m_VALUDE;//����ѯ��� �����ؼ���Ӧ�ı���
	}
	else
	{
		m_Uid = "";
	}

	srvCfgSet.m_strFilter.Format("key='%s'", "secmng_password");//�൱��where�Ӿ�����
	if (!srvCfgSet.Requery())//�൱�ڼ�����select from
	{
		AfxMessageBox("Requery secmng_password ʧ��");
		return;
	}
	if (!srvCfgSet.IsEOF())//have result ����Ѿ����浽SECMNGSRVCFG.h����m_VALUE��
	{
		srvCfgSet.m_VALUDE.TrimLeft();//���ȥ�ո�
		srvCfgSet.m_VALUDE.TrimRight();
		m_Pwd = srvCfgSet.m_VALUDE;//����ѯ��� �����ؼ���Ӧ�ı���
	}
	else
	{
		m_Pwd = "";
	}

	srvCfgSet.Close();
	UpdateData(FALSE);//�ӱ������ռ���ʾ

}

void CCfgView::OnBnClickedSrvcfg()
{
	int dbflag = 0;
	char sql[1024];
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	if (m_strsrvip.IsEmpty() || m_strsrvmaxnode.IsEmpty() || m_strsrvport.IsEmpty())
	{
		AfxMessageBox("�������ݲ�����Ϊ��ֵ");
		return;
	}
	g_pDB->BeginTrans();//��������
	CSECMNGSRVCFG srvCfgSet(g_pDB);//������ �Ѿ������ݿ������
	
	
	TRY 
	{
		memset(sql, 0, sizeof(sql));
		srvCfgSet.m_strFilter.Format("key='%s'", "secmng_server_ip");//�൱��where�Ӿ�����
		//��ѯ���IP��
		if (!srvCfgSet.Open(CRecordset::snapshot, NULL, CRecordset::none))//�൱�ڼ�����select from
		{
			AfxMessageBox("��¼������ݿ�ʧ��");
			return;
		}
		if (!srvCfgSet.IsEOF())//have result 
		{
			sprintf(sql, "update SECMNG.SRVCFG set valude ='%s' WHERE key='secmng_server_ip'", (LPTSTR)(LPCTSTR)m_strsrvip);
			g_pDB->ExecuteSQL(sql);
			if (writeSecMngCfg("ServerIp", m_strsrvip,"config.ini") != 0)
			{
				AfxMessageBox("¼��ServerIp��Ϣʧ��");
				return;
			}
			//��֪��Ϊʲô �ҵ������ִ��Edit��update���Ǳ��� ORA-01410 invalid RoWID ���Ծͷ����˼�¼��Ĳ�����ʽ����ֱ��ִ��sql���
			//����ִ��AddNew��updateȴ�������ģ������
			//srvCfgSet.Edit();//���к����������ݿ� ��Ҫ�����˹�
			//srvCfgSet.m_VALUDE = m_strsrvip;
			//srvCfgSet.Update();//����������������˸��²������ύ����
		}
		else
		{
			//ִ��AddNew��updateȴ�������ģ������
			srvCfgSet.AddNew();//���к����������ݿ� ��Ҫ�������˹�
			srvCfgSet.m_KEY = "secmng_server_ip";
			srvCfgSet.m_VALUDE = m_strsrvip;
			srvCfgSet.Update();//����������������˸��²������ύ����
			if (writeSecMngCfg("ServerIp", m_strsrvip, "config.ini") != 0)
			{
				AfxMessageBox("¼��ServerIp��Ϣʧ��");
				return;
			}
		}

		memset(sql, 0, sizeof(sql));
		srvCfgSet.m_strFilter.Format("key='%s'", "secmng_server_port");//�൱��where�Ӿ�����												
		//��ѯ���port��
		if (!srvCfgSet.Requery())//�൱�ڼ�����select from
		{
			AfxMessageBox("��¼������ݿ�ʧ��");
			return;
		}
		if (!srvCfgSet.IsEOF())//have result 
		{
			sprintf(sql, "update SECMNG.SRVCFG set valude ='%s' WHERE key='secmng_server_port'", (LPTSTR)(LPCTSTR)m_strsrvport);
			g_pDB->ExecuteSQL(sql);
			if (writeSecMngCfg("ServerPort", m_strsrvport, "config.ini") != 0)
			{
				AfxMessageBox("¼��ServerPort��Ϣʧ��");
				return;
			}
			//��֪��Ϊʲô �ҵ������ִ��Edit��update���Ǳ��� ORA-01410 invalid RoWID ���Ծͷ����˼�¼��Ĳ�����ʽ����ֱ��ִ��sql���
			//����ִ��AddNew��updateȴ�������ģ������
			//srvCfgSet.Edit();//���к����������ݿ� ��Ҫ�����˹�
			//srvCfgSet.m_VALUDE = m_strsrvip;
			//srvCfgSet.Update();//����������������˸��²������ύ����
		}
		else
		{
			//ִ��AddNew��updateȴ�������ģ������
			srvCfgSet.AddNew();//���к����������ݿ� ��Ҫ�������˹�
			srvCfgSet.m_KEY = "secmng_server_port";
			srvCfgSet.m_VALUDE = m_strsrvport;
			srvCfgSet.Update();//����������������˸��²������ύ����
			if (writeSecMngCfg("ServerPort", m_strsrvport, "config.ini") != 0)
			{
				AfxMessageBox("¼��ServerPort��Ϣʧ��");
				return;
			}
		}

		memset(sql, 0, sizeof(sql));
		srvCfgSet.m_strFilter.Format("key='%s'", "secmng_server_port");//�൱��where�Ӿ�����												
		//��ѯ���maxnetnum��
		if (!srvCfgSet.Requery())//�൱�ڼ�����select from
		{
			AfxMessageBox("��¼������ݿ�ʧ��");
			return;
		}
		if (!srvCfgSet.IsEOF())//have result 
		{
			sprintf(sql, "update SECMNG.SRVCFG set valude ='%s' WHERE key='secmng_server_maxnetnum'", (LPTSTR)(LPCTSTR)m_strsrvmaxnode);
			g_pDB->ExecuteSQL(sql);
			//��֪��Ϊʲô �ҵ������ִ��Edit��update���Ǳ��� ORA-01410 invalid RoWID ���Ծͷ����˼�¼��Ĳ�����ʽ����ֱ��ִ��sql���
			//����ִ��AddNew��updateȴ�������ģ������
			//srvCfgSet.Edit();//���к����������ݿ� ��Ҫ�����˹�
			//srvCfgSet.m_VALUDE = m_strsrvip;
			//srvCfgSet.Update();//����������������˸��²������ύ����
			if (writeSecMngCfg("ServerMaxnode", m_strsrvmaxnode, "config.ini") != 0)
			{
				AfxMessageBox("¼��ServerMaxnode��Ϣʧ��");
				return;
			}
		}
		else
		{
			//ִ��AddNew��updateȴ�������ģ������
			srvCfgSet.AddNew();//���к����������ݿ� ��Ҫ�������˹�
			srvCfgSet.m_KEY = "secmng_server_maxnetnum";
			srvCfgSet.m_VALUDE = m_strsrvmaxnode;
			srvCfgSet.Update();//����������������˸��²������ύ����
			if (writeSecMngCfg("ServerMaxnode", m_strsrvmaxnode, "config.ini") != 0)
			{
				AfxMessageBox("¼��ServerMaxnode��Ϣʧ��");
				return;
			}
		}
		//д���Ǹ�ini�ļ�
		



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
		AfxMessageBox("���ݿ���Ϣд��ɹ�");
	}
	else
	{
		g_pDB->Rollback();
		return;
	}

	if (srvCfgSet.IsOpen())
		srvCfgSet.Close();//�Ͽ����ݿ�����
	return;
}



void CCfgView::OnBnClickedDsnUidPwd()

{
	int dbflag = 0;
	char sql[1024];
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	if (m_Dsn.IsEmpty() || m_Uid.IsEmpty() || m_Pwd.IsEmpty())
	{
		AfxMessageBox("�������ݲ�����Ϊ��ֵ");
		return;
	}
	g_pDB->BeginTrans();//��������
	CSECMNGSRVCFG srvCfgSet(g_pDB);//������ �Ѿ������ݿ������

	TRY
	{
		memset(sql, 0, sizeof(sql));
		srvCfgSet.m_strFilter.Format("key='%s'", "secmng_data_source");//�൱��where�Ӿ�����
																	 //��ѯ���IP��
		if (!srvCfgSet.Open(CRecordset::snapshot, NULL, CRecordset::none))//�൱�ڼ�����select from
		{
			AfxMessageBox("��¼������ݿ�ʧ��");
			return;
		}
		if (!srvCfgSet.IsEOF())//have result 
		{
			sprintf(sql, "update SECMNG.SRVCFG set valude ='%s' WHERE key='secmng_data_source'", (LPTSTR)(LPCTSTR)m_Dsn);
			g_pDB->ExecuteSQL(sql);
			if (writeSecMngCfg("DSN", m_Dsn,"config.ini") != 0)
			{
				AfxMessageBox("¼��DSN��Ϣʧ��");
				return;
			}
		}
		else
		{
			//ִ��AddNew��updateȴ�������ģ������
			srvCfgSet.AddNew();//���к����������ݿ� ��Ҫ�������˹�
			srvCfgSet.m_KEY = "secmng_data_source";
			srvCfgSet.m_VALUDE = m_Dsn;
			srvCfgSet.Update();//����������������˸��²������ύ����
			if (writeSecMngCfg("DSN", m_Dsn, "config.ini") != 0)
			{
				AfxMessageBox("¼��DSN��Ϣʧ��");
				return;
			}
		}

		memset(sql, 0, sizeof(sql));
		srvCfgSet.m_strFilter.Format("key='%s'", "secmng_user_id");//�൱��where�Ӿ�����												
																   //��ѯ���port��
		if (!srvCfgSet.Requery())//�൱�ڼ�����select from
		{
			AfxMessageBox("��¼������ݿ�ʧ��");
			return;
		}
		if (!srvCfgSet.IsEOF())//have result 
		{
			sprintf(sql, "update SECMNG.SRVCFG set valude ='%s' WHERE key='secmng_user_id'", (LPTSTR)(LPCTSTR)m_Uid);
			g_pDB->ExecuteSQL(sql);
			if (writeSecMngCfg("secmng_user_id", m_Uid, "config.ini") != 0)
			{
				AfxMessageBox("¼��secmng_user_id��Ϣʧ��");
				return;
			}
		}
		else
		{
			//ִ��AddNew��updateȴ�������ģ������
			srvCfgSet.AddNew();//���к����������ݿ� ��Ҫ�������˹�
			srvCfgSet.m_KEY = "secmng_user_id";
			srvCfgSet.m_VALUDE = m_Uid;
			srvCfgSet.Update();//����������������˸��²������ύ����
			if (writeSecMngCfg("UID", m_Uid, "config.ini") != 0)
			{
				AfxMessageBox("¼��secmng_user_id��Ϣʧ��");
				return;
			}
		}

		memset(sql, 0, sizeof(sql));
		srvCfgSet.m_strFilter.Format("key='%s'", "secmng_password");//�൱��where�Ӿ�����												
																	   //��ѯ���maxnetnum��
		if (!srvCfgSet.Requery())//�൱�ڼ�����select from
		{
			AfxMessageBox("��¼������ݿ�ʧ��");
			return;
		}
		if (!srvCfgSet.IsEOF())//have result 
		{
			sprintf(sql, "update SECMNG.SRVCFG set valude ='%s' WHERE key='secmng_password'", (LPTSTR)(LPCTSTR)m_Pwd);
			g_pDB->ExecuteSQL(sql);
			if (writeSecMngCfg("PWD", m_Pwd, "config.ini") != 0)
			{
				AfxMessageBox("¼��secmng_password��Ϣʧ��");
				return;
			}
		}
		else
		{
			//ִ��AddNew��updateȴ�������ģ������
			srvCfgSet.AddNew();//���к����������ݿ� ��Ҫ�������˹�
			srvCfgSet.m_KEY = "secmng_password";
			srvCfgSet.m_VALUDE = m_Pwd;
			srvCfgSet.Update();//����������������˸��²������ύ����
			if (writeSecMngCfg("PWD", m_Pwd, "config.ini") != 0)
			{
				AfxMessageBox("¼��secmng_password��Ϣʧ��");
				return;
			}
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
			AfxMessageBox("���ݿ���Ϣд��ɹ�");
		}
		else
		{
			g_pDB->Rollback();
			return;
		}

	if (srvCfgSet.IsOpen())
		srvCfgSet.Close();//�Ͽ����ݿ�����
	return;
}