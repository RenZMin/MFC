#pragma once



// CFormBackground ������ͼ

class CFormBackground : public CFormView
{
	DECLARE_DYNCREATE(CFormBackground)

protected:
	CFormBackground();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CFormBackground();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_FORMBACKGROUND_FORM };
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


