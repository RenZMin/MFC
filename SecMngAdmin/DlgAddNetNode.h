#pragma once


// DlgAddNetNode 对话框

class CDlgAddNetNode : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgAddNetNode)

public:
	CDlgAddNetNode(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgAddNetNode();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_AddNetNode };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	int m_Autor;
	CString m_Description;
	CString m_Name;
	CString m_ID;
	int m_State;
};
