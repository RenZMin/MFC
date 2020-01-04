// SECMNGSRVCFG.h : CSECMNGSRVCFG ���ʵ��


// CSECMNGSRVCFG ʵ��

#include "stdafx.h"
#include "SECMNGSECKYEINFO.h"

IMPLEMENT_DYNAMIC(CSECMNGSECKYEINFO, CRecordset)

CSECMNGSECKYEINFO::CSECMNGSECKYEINFO(CDatabase* pdb)
	: CRecordset(pdb)
{
	m_CLIENTID ="";
	m_SERVERID = "";
	m_KEYID = 0;
	m_CREATETIME;
	//�����������Զ����ɵ� ���ǿ����޸� ΢��
	m_STATE = 0;
	m_SECKEY = "";
	m_nFields = 6;
	m_nDefaultType = dynaset;

}
//#error ��ȫ���⣺�����ַ������ܰ������롣
// �������ַ����п��ܰ������������/��������Ҫ
// ��Ϣ�����ڲ鿴��������ַ������ҵ������밲ȫ
// �йص�������Ƴ� #error��������Ҫ���������
// ��Ϊ������ʽ��ʹ���������û������֤��
CString CSECMNGSECKYEINFO::GetDefaultConnect()
{
	return _T("DSN=WINREDHAT;UID=SECMNGADMIN;PWD=123456;DBQ=SECMNGADMIN;DBA=W;APA=T;EXC=F;FEN=T;QTO=T;FRC=10;FDL=10;LOB=T;RST=T;GDE=F;FRL=F;BAM=IfAllSuccessful;NUM=NLS;DPM=F;MTS=T;MDI=F;CSR=F;FWC=F;FBS=64000;TLO=0;");
}
//WINREDHAT UID=SECMNGADMIN;PWD=123456;DBQ=SECMNGADMIN
CString CSECMNGSECKYEINFO::GetDefaultSQL()
{
	return _T("[SECMNG].[SECKYEINFO]");
}

void CSECMNGSECKYEINFO::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
	// RFX_Text() �� RFX_Int() �������������
	// ��Ա���������ͣ����������ݿ��ֶε����͡�
	// ODBC �����Զ�����ֵת��Ϊ�����������
	
	RFX_Text(pFX, _T("[CLIENTID]"), m_CLIENTID);
	RFX_Text(pFX, _T("[SERVERID]"), m_SERVERID);
	RFX_Int(pFX, _T("[KEYID]"), m_KEYID);
	RFX_Date(pFX, _T("[CREATETIME]"), m_CREATETIME);
	RFX_Int(pFX, _T("[STATE]"), m_STATE);
	RFX_Text(pFX, _T("[SECKEY]"), m_SECKEY);

}
/////////////////////////////////////////////////////////////////////////////
// CSECMNGSRVCFG ���

#ifdef _DEBUG
void CSECMNGSECKYEINFO::AssertValid() const
{
	CRecordset::AssertValid();
}

void CSECMNGSECKYEINFO::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG


