#pragma once


// CDlgInitCfg �Ի���

class CDlgInitCfg : public CDialog
{
	DECLARE_DYNAMIC(CDlgInitCfg)

public:
	CDlgInitCfg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgInitCfg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_INITDB };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	int CDlgInitCfg::writeSecMngCfg(char *pItemName, CString pItemValue);
	CString m_dbDSN;
	CString m_dbPWD;
	CString m_dbUID;
	afx_msg void OnBnClickedButtonLinktest();
};
