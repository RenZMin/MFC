#pragma once



// CSysAll ������ͼ

class CSysAll : public CFormView
{
	DECLARE_DYNCREATE(CSysAll)

protected:
	CSysAll();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CSysAll();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_SYSALL };
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
};


