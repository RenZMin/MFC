
#pragma once

class CSECMNGSECKYEINFO : public CRecordset
{
public:
	CSECMNGSECKYEINFO(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CSECMNGSECKYEINFO)

	// �ֶ�/��������

	// �����ַ�������(�������)��ӳ���ݿ��ֶ�(ANSI �������͵� CStringA �� Unicode
	// �������͵� CStringW)��ʵ���������͡�
	//  ����Ϊ��ֹ ODBC ��������ִ�п���
	// ����Ҫ��ת�������ϣ�������Խ���Щ��Ա����Ϊ
	// CString ���ͣ�ODBC ��������ִ�����б�Ҫ��ת����
	// (ע��: ����ʹ�� 3.5 �����߰汾�� ODBC ��������
	// ��ͬʱ֧�� Unicode ����Щת��)��
	
	
	CString	m_CLIENTID;
	CString	m_SERVERID;
	int	m_KEYID;
	CTime	m_CREATETIME;
	int	m_STATE;
	CString	m_SECKEY;

	// ��д
	// �����ɵ��麯����д
public:
	virtual CString GetDefaultConnect();	// Ĭ�������ַ���

	virtual CString GetDefaultSQL(); 	// ��¼����Ĭ�� SQL
	virtual void DoFieldExchange(CFieldExchange* pFX);	// RFX ֧��

														// ʵ��
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

};


