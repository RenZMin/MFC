#pragma once


// CCfgView �Ի���

class CCfgView1 : public CDialogEx
{/*
	DECLARE_DYNAMIC(CCfgView1)

public:
	CCfgView1(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CCfgView1();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_CFG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()*/
};
#pragma once



// CCfgView ������ͼ

class CCfgView : public CFormView
{
	DECLARE_DYNCREATE(CCfgView)

protected:
	CCfgView();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CCfgView();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_CFG };
#endif
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLbnSelchangeList1();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedCheck1();
};


