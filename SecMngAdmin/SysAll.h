#pragma once



// CSysAll 窗体视图

class CSysAll : public CFormView
{
	DECLARE_DYNCREATE(CSysAll)

protected:
	CSysAll();           // 动态创建所使用的受保护的构造函数
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
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};


