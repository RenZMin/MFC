// DlgAddNetNode.cpp : 实现文件
//

#include "stdafx.h"
#include "SecMngAdmin.h"
#include "DlgAddNetNode.h"
#include "afxdialogex.h"


// DlgAddNetNode 对话框

IMPLEMENT_DYNAMIC(CDlgAddNetNode, CDialogEx)

CDlgAddNetNode::CDlgAddNetNode(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_AddNetNode, pParent)
	, m_Autor(0)
	, m_Description(_T(""))
	, m_Name(_T(""))
	, m_ID(_T(""))
	, m_State(0)
{

}

CDlgAddNetNode::~CDlgAddNetNode()
{
}

void CDlgAddNetNode::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_AUTOR, m_Autor);
	DDX_Text(pDX, IDC_EDIT_DESR, m_Description);
	DDX_Text(pDX, IDC_EDIT_NAME, m_Name);
	DDX_Text(pDX, IDC_EDIT_NUM, m_ID);
	DDX_Text(pDX, IDC_EDIT_STATE, m_State);
}


BEGIN_MESSAGE_MAP(CDlgAddNetNode, CDialogEx)
END_MESSAGE_MAP()


// DlgAddNetNode 消息处理程序
