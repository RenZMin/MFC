#pragma once


// DlgAddNetNode �Ի���

class CDlgAddNetNode : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgAddNetNode)

public:
	CDlgAddNetNode(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgAddNetNode();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_AddNetNode };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	int m_Autor;
	CString m_Description;
	CString m_Name;
	CString m_ID;
	int m_State;
};
