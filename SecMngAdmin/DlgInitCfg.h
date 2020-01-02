#pragma once


// CDlgInitCfg 对话框

class CDlgInitCfg : public CDialog
{
	DECLARE_DYNAMIC(CDlgInitCfg)

public:
	CDlgInitCfg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgInitCfg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_INITDB };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	int CDlgInitCfg::writeSecMngCfg(char *pItemName, CString pItemValue);
	CString m_dbDSN;
	CString m_dbPWD;
	CString m_dbUID;
	afx_msg void OnBnClickedButtonLinktest();
};
