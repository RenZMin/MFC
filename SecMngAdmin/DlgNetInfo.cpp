// DlgNetInfo.cpp : ʵ���ļ�
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


// CDlgNetInfo ���

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
//UINT mask;			//��ʾ��ʽ ���ֺ�ͼƬ��ʽ��ʾ
//int iItem;			//����λ�ã�=0 �ڵ�0�в���һ��
//int iSubItem;		//�ڵ�n�� ���ӽڵ�
//UINT state;			//״̬
//UINT stateMask;
//LPWSTR pszText;		//��ʾ������ -- �ַ���
//int cchTextMax;
//int iImage;			//ʹ�õ�ͼƬ����� 
//LPARAM lParam;		//������ÿһ���� ����һЩ����
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
	// TODO:  �ڴ���ӿؼ�֪ͨ��������

	LVITEM   lvi;			//�ṹ�����

	lvi.mask = LVIF_IMAGE | LVIF_TEXT;	//��ʲô��ʽ��ʾ���ݣ�ͼƬ���ı�
	lvi.iItem = 0;			//�ڵ�0���ϲ��������� ͷ�巨
	lvi.iImage = 4;			//ʹ��ͼƬ�б��еĵ�4��ͼƬ	

							//�����0������
	lvi.iSubItem = 0;		// Set subitem 0
	lvi.pszText = (LPTSTR)(LPCTSTR)ID;
	m_listSecNode.InsertItem(&lvi);

	//�����1������
	lvi.iSubItem = 1;		// Set subitem 1
	lvi.pszText = (LPTSTR)(LPCTSTR)Name;
	m_listSecNode.SetItem(&lvi);

	//�����2������
	CString strTime = time.Format("%Y-%m-%d %H:%M:%S");
	lvi.iSubItem = 2;		// Set subitem 1
	lvi.pszText = (LPTSTR)(LPCTSTR)strTime;
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
	lvi.iSubItem = 4;		// Set subitem 4
							//CString strAuthcode(authcode) ;
	char buf[100];
	sprintf(buf, "%d", authcode);
	lvi.pszText = buf;
	m_listSecNode.SetItem(&lvi);

	return 0;
}


// CDlgNetInfo ��Ϣ�������

void CDlgNetInfo::OnInitialUpdate()
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

	m_listSecNode.InsertColumn(0, "������", LVCFMT_LEFT, nColInterval);
	m_listSecNode.InsertColumn(1, "��������", LVCFMT_LEFT, nColInterval);
	m_listSecNode.InsertColumn(2, "���㴴��ʱ��", LVCFMT_LEFT, nColInterval);
	m_listSecNode.InsertColumn(3, "����״̬", LVCFMT_LEFT, nColInterval);
	m_listSecNode.InsertColumn(4, "������Ȩ��", LVCFMT_LEFT, rect.Width() - 4 * nColInterval);

	m_listSecNode.SetRedraw(TRUE);


	//�������ݿ����Ϣ ��д�����չʾ���û�


	//select * from SRVCFG where key = 'secmng_server_ip';  --IP
	CSECMNGSECNODE srvCfgAddNode(g_pDB);//������ �Ѿ������ݿ������
	//srvCfgAddNode.m_strFilter.Format("key='%s'", "secmng_server_ip");//�൱��where�Ӿ���												
	//�൱��select *
	if (!srvCfgAddNode.Open(CRecordset::snapshot, NULL, CRecordset::none))//�൱�ڼ�����select from
	{
		AfxMessageBox("��¼������ݿ�ʧ��");
		return;
	}
	while (!srvCfgAddNode.IsEOF())//have result ����Ѿ����浽SECMNGSRVCFG.h����m_VALUE��
	{
		srvCfgAddNode.m_ID.TrimLeft();//���ȥ�ո�
		srvCfgAddNode.m_ID.TrimRight();
		CString ID = srvCfgAddNode.m_ID;;//����ѯ��� �����ؼ���Ӧ�ı���

		srvCfgAddNode.m_NAME.TrimLeft();//���ȥ�ո�
		srvCfgAddNode.m_NAME.TrimRight();
		CString Name = srvCfgAddNode.m_NAME;//����ѯ��� �����ؼ���Ӧ�ı���

		srvCfgAddNode.m_NODEDESC.TrimLeft();//���ȥ�ո�
		srvCfgAddNode.m_NODEDESC.TrimRight();
		CString netDescription = srvCfgAddNode.m_NODEDESC;//����ѯ��� �����ؼ���Ӧ�ı���

		CTime time = srvCfgAddNode.m_CREATETIME;

		int state = srvCfgAddNode.m_STATE;
		int authcode = srvCfgAddNode.m_AUTHCODE;
		DbInitListSecNode(ID, Name, time, state, authcode);
		
		srvCfgAddNode.MoveNext();
	}
	srvCfgAddNode.Close();
	UpdateData(FALSE);//�ӱ������ռ���ʾ	
}

//CString	m_ID;
//CString	m_NAME;
//CString	m_NODEDESC;
//CTime	m_CREATETIME;
//int	m_AUTHCODE;  //�����������Զ����ɵ� ���ǿ����޸� ΢��
//int	m_STATE;

//��������  ������һ����¼
void CDlgNetInfo::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//�����Ի����û�������Ϣ
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
		AfxMessageBox("�������ݲ�����Ϊ��ֵ");
		return;
	}
	CString ID = dlgAddNetNode.m_ID;
	CString Name =dlgAddNetNode.m_Name;
	CString netDescription = dlgAddNetNode.m_Description;
	CTime time = CTime::GetCurrentTime();
	CString tempTime = time.Format("%Y-%m-%d %H:%M:%S");
	int state = dlgAddNetNode.m_State;
	int authcode = dlgAddNetNode.m_Autor;
	
	g_pDB->BeginTrans();//��������
	CSECMNGSECNODE srvCfgAddNode(g_pDB);//������ �Ѿ������ݿ������

	TRY
	{
		memset(sql, 0, sizeof(sql));
		memset(toDate, 0, sizeof(toDate));
		sprintf(toDate, "to_date('%s', 'yyyy-mm-dd hh24:mi:ss')", tempTime);
		srvCfgAddNode.m_strFilter.Format("ID='%s'", ID);//�൱��where�Ӿ�����,��������ȥ�����
																	 //��ѯ���IP��
		if (!srvCfgAddNode.Open(CRecordset::snapshot, NULL, CRecordset::none))//�൱�ڼ�����select from
		{
			AfxMessageBox("��¼������ݿ�ʧ��");
			return;
		}
		if (!srvCfgAddNode.IsEOF())//have result 
		{
			sprintf(sql, "update SECMNG.SECNODE set ID ='%s',NAME='%s',NODEDESC='%s',CREATETIME=%s,AUTHCODE=%d,STATE=%d WHERE ID='%s'", (LPTSTR)(LPCTSTR)ID, (LPTSTR)(LPCTSTR)Name, (LPTSTR)(LPCTSTR)netDescription,toDate,authcode,state, (LPTSTR)(LPCTSTR)ID);
			g_pDB->ExecuteSQL(sql);
			//��֪��Ϊʲô �ҵ������ִ��Edit��update���Ǳ��� ORA-01410 invalid RoWID ���Ծͷ����˼�¼��Ĳ�����ʽ����ֱ��ִ��sql���
			//����ִ��AddNew��updateȴ�������ģ������
			//srvCfgSet.Edit();//���к����������ݿ� ��Ҫ�����˹�
			//srvCfgSet.m_VALUDE = m_strsrvip;
			//srvCfgSet.Update();//����������������˸��²������ύ����
		}
		else
		{
			//ִ��AddNew��updateȴ�������ģ������
			srvCfgAddNode.AddNew();//���к����������ݿ� ��Ҫ�������˹�
			srvCfgAddNode.m_ID = ID;
			srvCfgAddNode.m_NAME = Name;
			srvCfgAddNode.m_NODEDESC = netDescription;
			srvCfgAddNode.m_CREATETIME = time;
			srvCfgAddNode.m_AUTHCODE = authcode;
			srvCfgAddNode.m_STATE = state;

			srvCfgAddNode.Update();//����������������˸��²������ύ����
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
		AfxMessageBox("���ݿ�������Ϣд��ɹ�");
	}
	else
	{
		g_pDB->Rollback();
		return;
	}

	if (srvCfgAddNode.IsOpen())
		srvCfgAddNode.Close();//�Ͽ����ݿ�����
	return;
}


void CDlgNetInfo::OnBnClickedButtonSearchinfo()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CWnd *myWnd = NULL;
	CButton *But = NULL;
	int flag = 0;
	int dbflag = 0;
	int all = 0;
	UpdateData(TRUE);//�ѽ�����Ϣ��������

	myWnd = (CWnd*)GetDlgItem(IDC_CHECK_TIME);
	But = (CButton *)myWnd;
	CSECMNGSECNODE srvCfgAddNode(g_pDB);//������ �Ѿ������ݿ������
	if (But->GetCheck() == BST_CHECKED)
	{
		CTime sqlStartTime(m_dateBegin.GetYear(),m_dateBegin.GetMonth(),m_dateBegin.GetDay(),0,0,0);
		CTime sqlEndTime(m_dateEnd.GetYear(), m_dateEnd.GetMonth(), m_dateEnd.GetDay(), 23, 59, 59);
		if (sqlStartTime>=sqlEndTime)
		{
			AfxMessageBox("��ʼʱ�䲻�ܴ��ڽ���ʱ��");
			return;
		} 
		
		TRY 
		{																				
			//�൱��select *
			if (!srvCfgAddNode.Open(CRecordset::snapshot, NULL, CRecordset::none))//�൱�ڼ�����select from
			{
				AfxMessageBox("��¼������ݿ�ʧ��");
				return;
			}
			m_listSecNode.DeleteAllItems(); //ɾ����ͼ ������
			m_listSecNode.SetRedraw(FALSE); //��ֹˢ����ͼ,�����ظ�������Ŀʱ,����

			while (!srvCfgAddNode.IsEOF())//have result ����Ѿ����浽SECMNGSRVCFG.h����m_VALUE��
			{
				if (srvCfgAddNode.m_CREATETIME >= sqlEndTime ||
					srvCfgAddNode.m_CREATETIME <= sqlStartTime)
				{
					srvCfgAddNode.MoveNext();
					continue;
				}
				srvCfgAddNode.m_ID.TrimLeft();//���ȥ�ո�
				srvCfgAddNode.m_ID.TrimRight();
				CString ID = srvCfgAddNode.m_ID;;//����ѯ��� �����ؼ���Ӧ�ı���

				srvCfgAddNode.m_NAME.TrimLeft();//���ȥ�ո�
				srvCfgAddNode.m_NAME.TrimRight();
				CString Name = srvCfgAddNode.m_NAME;//����ѯ��� �����ؼ���Ӧ�ı���

				srvCfgAddNode.m_NODEDESC.TrimLeft();//���ȥ�ո�
				srvCfgAddNode.m_NODEDESC.TrimRight();
				CString netDescription = srvCfgAddNode.m_NODEDESC;//����ѯ��� �����ؼ���Ӧ�ı���

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
	else//ûѡ��ѡ�� ����ʾȫ��
	{
		TRY
		{
			//�൱��select *
			if (!srvCfgAddNode.Open(CRecordset::snapshot, NULL, CRecordset::none))//�൱�ڼ�����select from
			{
				AfxMessageBox("��¼������ݿ�ʧ��");
				return;
			}
			m_listSecNode.DeleteAllItems(); //ɾ����ͼ ������
			m_listSecNode.SetRedraw(FALSE); //��ֹˢ����ͼ,�����ظ�������Ŀʱ,����

			while (!srvCfgAddNode.IsEOF())//have result ����Ѿ����浽SECMNGSRVCFG.h����m_VALUE��
			{
				srvCfgAddNode.m_ID.TrimLeft();//���ȥ�ո�
				srvCfgAddNode.m_ID.TrimRight();
				CString ID = srvCfgAddNode.m_ID;;//����ѯ��� �����ؼ���Ӧ�ı���

				srvCfgAddNode.m_NAME.TrimLeft();//���ȥ�ո�
				srvCfgAddNode.m_NAME.TrimRight();
				CString Name = srvCfgAddNode.m_NAME;//����ѯ��� �����ؼ���Ӧ�ı���

				srvCfgAddNode.m_NODEDESC.TrimLeft();//���ȥ�ո�
				srvCfgAddNode.m_NODEDESC.TrimRight();
				CString netDescription = srvCfgAddNode.m_NODEDESC;//����ѯ��� �����ؼ���Ӧ�ı���

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
		AfxMessageBox("�������ݿ�ʧ��!");
		return;
	}
	if (flag == 0&&all==0)
	{
		AfxMessageBox("û�м��������������ļ�¼");
		return;
	}
}


void CDlgNetInfo::OnBnClickedButtonExactsearch()

{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CWnd *myWnd = NULL;
	CButton *But = NULL;
	int flag = 0;
	int dbflag = 0;
	int all = 0;
	UpdateData(TRUE);//�ѽ�����Ϣ��������
	myWnd = (CWnd*)GetDlgItem(IDC_CHECK_NAME);
	But = (CButton *)myWnd;
	CSECMNGSECNODE srvCfgAddNode(g_pDB);//������ �Ѿ������ݿ������

	if (But->GetCheck() == BST_CHECKED)
	{
		m_Name.TrimLeft();
		m_Name.TrimRight();
		if (m_Name=="")
		{
			AfxMessageBox("�������Ʋ���Ϊ��");
			return;
		}
		TRY
		{
			//�൱��select *
			srvCfgAddNode.m_strFilter.Format("NAME='%s'",m_Name);
			if (!srvCfgAddNode.Open(CRecordset::snapshot, NULL, CRecordset::none))//�൱�ڼ�����select from
			{
				AfxMessageBox("��¼������ݿ�ʧ��");
				return;
			}
			m_listSecNode.DeleteAllItems(); //ɾ����ͼ ������
			m_listSecNode.SetRedraw(FALSE); //��ֹˢ����ͼ,�����ظ�������Ŀʱ,����

			while (!srvCfgAddNode.IsEOF())//have result ����Ѿ����浽SECMNGSRVCFG.h����m_VALUE��
			{
	
				srvCfgAddNode.m_ID.TrimLeft();//���ȥ�ո�
				srvCfgAddNode.m_ID.TrimRight();
				CString ID = srvCfgAddNode.m_ID;;//����ѯ��� �����ؼ���Ӧ�ı���

				srvCfgAddNode.m_NAME.TrimLeft();//���ȥ�ո�
				srvCfgAddNode.m_NAME.TrimRight();
				CString Name = srvCfgAddNode.m_NAME;//����ѯ��� �����ؼ���Ӧ�ı���

				srvCfgAddNode.m_NODEDESC.TrimLeft();//���ȥ�ո�
				srvCfgAddNode.m_NODEDESC.TrimRight();
				CString netDescription = srvCfgAddNode.m_NODEDESC;//����ѯ��� �����ؼ���Ӧ�ı���

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
		else//ûѡ��ѡ�� ����ʾȫ��
		{
			TRY
			{
				//�൱��select *
				if (!srvCfgAddNode.Open(CRecordset::snapshot, NULL, CRecordset::none))//�൱�ڼ�����select from
				{
					AfxMessageBox("��¼������ݿ�ʧ��");
					return;
				}
				m_listSecNode.DeleteAllItems(); //ɾ����ͼ ������
				m_listSecNode.SetRedraw(FALSE); //��ֹˢ����ͼ,�����ظ�������Ŀʱ,����

				while (!srvCfgAddNode.IsEOF())//have result ����Ѿ����浽SECMNGSRVCFG.h����m_VALUE��
				{
					srvCfgAddNode.m_ID.TrimLeft();//���ȥ�ո�
					srvCfgAddNode.m_ID.TrimRight();
					CString ID = srvCfgAddNode.m_ID;;//����ѯ��� �����ؼ���Ӧ�ı���

					srvCfgAddNode.m_NAME.TrimLeft();//���ȥ�ո�
					srvCfgAddNode.m_NAME.TrimRight();
					CString Name = srvCfgAddNode.m_NAME;//����ѯ��� �����ؼ���Ӧ�ı���

					srvCfgAddNode.m_NODEDESC.TrimLeft();//���ȥ�ո�
					srvCfgAddNode.m_NODEDESC.TrimRight();
					CString netDescription = srvCfgAddNode.m_NODEDESC;//����ѯ��� �����ؼ���Ӧ�ı���

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
		AfxMessageBox("�������ݿ�ʧ��!");
		return;
	}
	if (flag == 0 && all == 0)
	{
		AfxMessageBox("û�м��������������ļ�¼");
		return;
	}
}

void CDlgNetInfo::OnBnClickedButtonIdsearch()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CWnd *myWnd = NULL;
	CButton *But = NULL;
	int flag = 0;
	int dbflag = 0;
	int all = 0;
	UpdateData(TRUE);//�ѽ�����Ϣ��������
		myWnd = (CWnd*)GetDlgItem(IDC_CHECK_ID);
	But = (CButton *)myWnd;
	CSECMNGSECNODE srvCfgAddNode(g_pDB);//������ �Ѿ������ݿ������

	if (But->GetCheck() == BST_CHECKED)
	{
		m_Id.TrimLeft();
		m_Id.TrimRight();
		if (m_Id == "")
		{
			AfxMessageBox("����ID����Ϊ��");
			return;
		}
		TRY
		{
			//�൱��select *
			srvCfgAddNode.m_strFilter.Format("ID='%s'",m_Id);
		if (!srvCfgAddNode.Open(CRecordset::snapshot, NULL, CRecordset::none))//�൱�ڼ�����select from
		{
			AfxMessageBox("��¼������ݿ�ʧ��");
			return;
		}
		m_listSecNode.DeleteAllItems(); //ɾ����ͼ ������
		m_listSecNode.SetRedraw(FALSE); //��ֹˢ����ͼ,�����ظ�������Ŀʱ,����

		while (!srvCfgAddNode.IsEOF())//have result ����Ѿ����浽SECMNGSRVCFG.h����m_VALUE��
		{

			srvCfgAddNode.m_ID.TrimLeft();//���ȥ�ո�
			srvCfgAddNode.m_ID.TrimRight();
			CString ID = srvCfgAddNode.m_ID;;//����ѯ��� �����ؼ���Ӧ�ı���

			srvCfgAddNode.m_NAME.TrimLeft();//���ȥ�ո�
			srvCfgAddNode.m_NAME.TrimRight();
			CString Name = srvCfgAddNode.m_NAME;//����ѯ��� �����ؼ���Ӧ�ı���

			srvCfgAddNode.m_NODEDESC.TrimLeft();//���ȥ�ո�
			srvCfgAddNode.m_NODEDESC.TrimRight();
			CString netDescription = srvCfgAddNode.m_NODEDESC;//����ѯ��� �����ؼ���Ӧ�ı���

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
	else//ûѡ��ѡ�� ����ʾȫ��
	{
		TRY
		{
			//�൱��select *
			if (!srvCfgAddNode.Open(CRecordset::snapshot, NULL, CRecordset::none))//�൱�ڼ�����select from
			{
				AfxMessageBox("��¼������ݿ�ʧ��");
				return;
			}
		m_listSecNode.DeleteAllItems(); //ɾ����ͼ ������
		m_listSecNode.SetRedraw(FALSE); //��ֹˢ����ͼ,�����ظ�������Ŀʱ,����

		while (!srvCfgAddNode.IsEOF())//have result ����Ѿ����浽SECMNGSRVCFG.h����m_VALUE��
		{
			srvCfgAddNode.m_ID.TrimLeft();//���ȥ�ո�
			srvCfgAddNode.m_ID.TrimRight();
			CString ID = srvCfgAddNode.m_ID;;//����ѯ��� �����ؼ���Ӧ�ı���

			srvCfgAddNode.m_NAME.TrimLeft();//���ȥ�ո�
			srvCfgAddNode.m_NAME.TrimRight();
			CString Name = srvCfgAddNode.m_NAME;//����ѯ��� �����ؼ���Ӧ�ı���

			srvCfgAddNode.m_NODEDESC.TrimLeft();//���ȥ�ո�
			srvCfgAddNode.m_NODEDESC.TrimRight();
			CString netDescription = srvCfgAddNode.m_NODEDESC;//����ѯ��� �����ؼ���Ӧ�ı���

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
		AfxMessageBox("�������ݿ�ʧ��!");
		return;
	}
	if (flag == 0 && all == 0)
	{
		AfxMessageBox("û�м��������������ļ�¼");
		return;
	}
}

//ɾ������
void CDlgNetInfo::OnBnClickedButton3()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//˼·���ӽ�����ɾ����¼�������ݿ���ɾ����¼�����
	//�ж�1�� ������¼��
	//	�ӽ������ҵ������ţ����������ţ������ݿ���ɾ�������¼
	//	�ӽ�����ɾ����ʾ��
	
	//�û����� �쳣�ж�
	POSITION pos = m_listSecNode.GetFirstSelectedItemPosition();
	if (pos == NULL)
	{
		AfxMessageBox("��ѡ���ɾ������Ŀ");
		return;
	}
	int selectNum = m_listSecNode.GetSelectedCount();
	if (selectNum>1)
	{
		AfxMessageBox("��ѡ���˶��м�¼, ����ѡ�����е�һ����¼��");
		return;
	}
	
	int nItem = m_listSecNode.GetNextSelectedItem(pos);//�õ�ѡ����
	CString strTmp = m_listSecNode.GetItemText(nItem, 3);
	if (strTmp == "����")
	{
		AfxMessageBox("����������ʹ�ã����Ƚ�����ɾ��");
		return;
	}
	CString strId = m_listSecNode.GetItemText(nItem, 0);
	if (strId == "")
	{
		AfxMessageBox("�����Ų�����Ϊ��");
		return;
	}
	
	strTmp.Format("ȷ��Ҫɾ�����Ϊ��%s����������", strId);

	if (AfxMessageBox(strTmp, MB_ICONQUESTION | MB_YESNO | MB_DEFBUTTON2) == IDNO)
		return;


	int dbflag = 0;
	char sql[1024];
	
	g_pDB->BeginTrans();//��������
	CSECMNGSECNODE srvCfgDeleteNode(g_pDB);//������ �Ѿ������ݿ������
	TRY
	{
		memset(sql, 0, sizeof(sql));
		if (!srvCfgDeleteNode.Open(CRecordset::snapshot, NULL, CRecordset::none))//�൱�ڼ�����select from
		{
			AfxMessageBox("��¼������ݿ�ʧ��");
			return;
		}
		if (!srvCfgDeleteNode.IsEOF())//have result 
		{
			sprintf(sql, "delete  from SECMNG.SECNODE WHERE ID='%s'", (LPTSTR)(LPCTSTR)strId);
			g_pDB->ExecuteSQL(sql);
		}
		else
		{
			AfxMessageBox("���ݿ����޶�Ӧ��������Ϣ");
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
		m_listSecNode.DeleteItem(nItem);//����ʾ����ɾ��
		AfxMessageBox("���ݿ�������Ϣɾ���ɹ�");
	}
	else
	{
		g_pDB->Rollback();
		return;
	}
	if (srvCfgDeleteNode.IsOpen())
		srvCfgDeleteNode.Close();//�Ͽ����ݿ�����
	return;
}


void CDlgNetInfo::OnBnClickedButtonEditnode()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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

	

	//�û����� �쳣�ж�
	POSITION pos = m_listSecNode.GetFirstSelectedItemPosition();
	if (pos == NULL)
	{
		AfxMessageBox("��ѡ����޸ĵ���Ŀ");
		return;
	}
	int selectNum = m_listSecNode.GetSelectedCount();
	if (selectNum > 1)
	{
		AfxMessageBox("��ѡ���˶��м�¼, ����ѡ�����е�һ����¼��");
		return;
	}
	int nItem = m_listSecNode.GetNextSelectedItem(pos);//�õ�ѡ����
	CString strTmp = m_listSecNode.GetItemText(nItem, 3);
	CString strId = m_listSecNode.GetItemText(nItem, 0);

	if (strTmp == "����")
	{
		AfxMessageBox("����������ʹ�ã����Ƚ����ٽ����޸�");
		return;
	}
	
	if (strId == "")
	{
		AfxMessageBox("�����Ų�����Ϊ��,��ѡ����Ч����Ŀ");
		return;
	}
	
	g_pDB->BeginTrans();//��������
	CSECMNGSECNODE srvCfgAddNode(g_pDB);//������ �Ѿ������ݿ������
	TRY 
	{
		memset(sql, 0, sizeof(sql));
		srvCfgAddNode.m_strFilter.Format("ID='%s'", strId);//�൱��where�Ӿ�����,��������ȥ�����
														//��ѯ���IP��
		if (!srvCfgAddNode.Open(CRecordset::snapshot, NULL, CRecordset::none))//�൱�ڼ�����select from
		{
			AfxMessageBox("��¼������ݿ�ʧ��");
			return;
		}
		//�Ƚ���Ϣ��ʾ����������
		if (!srvCfgAddNode.IsEOF())
		{
			srvCfgAddNode.m_ID.TrimLeft();//���ȥ�ո�
			srvCfgAddNode.m_ID.TrimRight();
			dlgAddNetNode.m_ID = srvCfgAddNode.m_ID;;//����ѯ��� �����ؼ���Ӧ�ı���

			srvCfgAddNode.m_NAME.TrimLeft();//���ȥ�ո�
			srvCfgAddNode.m_NAME.TrimRight();
			dlgAddNetNode.m_Name = srvCfgAddNode.m_NAME;//����ѯ��� �����ؼ���Ӧ�ı���

			srvCfgAddNode.m_NODEDESC.TrimLeft();//���ȥ�ո�
			srvCfgAddNode.m_NODEDESC.TrimRight();
			dlgAddNetNode.m_Description = srvCfgAddNode.m_NODEDESC;//����ѯ��� �����ؼ���Ӧ�ı���
		
			dlgAddNetNode.m_State = srvCfgAddNode.m_STATE;
			dlgAddNetNode.m_Autor = srvCfgAddNode.m_AUTHCODE;
		}
		else
		{
			AfxMessageBox("���ݿ����޸���Ŀ��Ӧ����Ϣ������������������");
			return;
		}
		
		if (dlgAddNetNode.DoModal() == IDCANCEL)
		{
			return;
		}
		UpdateData(FALSE);
		//�ӽ���������������
		UpdateData(TRUE);
		if (dlgAddNetNode.m_ID.IsEmpty() || dlgAddNetNode.m_Name.IsEmpty() || dlgAddNetNode.m_Description.IsEmpty())
		{
			AfxMessageBox("�������ݲ�����Ϊ��ֵ");
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
			AfxMessageBox("ID����,��ɾ�������㲢�½�������Ϣ");
			//ɾ��
			sprintf(sql, "delete  from SECMNG.SECNODE WHERE ID='%s'", (LPTSTR)(LPCTSTR)strId);
			g_pDB->ExecuteSQL(sql);
			//�½�
			srvCfgAddNode.AddNew();//���к����������ݿ� ��Ҫ�������˹�
			srvCfgAddNode.m_ID = ID;
			srvCfgAddNode.m_NAME = Name;
			srvCfgAddNode.m_NODEDESC = netDescription;
			srvCfgAddNode.m_CREATETIME = time;
			srvCfgAddNode.m_AUTHCODE = authcode;
			srvCfgAddNode.m_STATE = state;

			srvCfgAddNode.Update();//����������������˸��²������ύ����
		}
		else//ID���� ֻ������
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
		m_listSecNode.DeleteItem(nItem);//����ʾ����ɾ��ԭ������Ϣ
		DbInitListSecNode(ID, Name, time, state, authcode);//�����������ʾ
		AfxMessageBox("���ݿ�������Ϣд��ɹ�");
	}
	else
	{
		g_pDB->Rollback();
	}

	if (srvCfgAddNode.IsOpen())
		srvCfgAddNode.Close();//�Ͽ����ݿ�����
	return;
}
