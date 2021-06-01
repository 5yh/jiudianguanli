// CUserDlg.cpp: 实现文件
//

#include "pch.h"
#include "酒店管理系统.h"
#include "CUserDlg.h"
#include "CLoginDlg.h"
#include "ConnectDB.cpp"
#include "resource.h"
extern Staff tempworker;
// CUserDlg

IMPLEMENT_DYNCREATE(CUserDlg, CFormView)

CUserDlg::CUserDlg()
	: CFormView(DIALOG_USER)
	, m_name(_T(""))
	, m_passwd(_T(""))
	, m_ID(_T(""))
	, m_newpasswd(_T(""))
	, m_surepasswd(_T(""))
{

}

CUserDlg::~CUserDlg()
{
}

void CUserDlg::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT2, m_name);
	DDX_Text(pDX, IDC_EDIT1, m_passwd);
	DDX_Text(pDX, IDC_EDIT3, m_ID);
	DDX_Text(pDX, IDC_EDIT4, m_newpasswd);
	DDX_Text(pDX, IDC_EDIT5, m_surepasswd);
}

BEGIN_MESSAGE_MAP(CUserDlg, CFormView)
	ON_BN_CLICKED(IDC_BUTTON1, &CUserDlg::OnBnClickedButton1)
	ON_EN_CHANGE(IDC_EDIT1, &CUserDlg::OnEnChangeEdit1)
	ON_BN_CLICKED(IDC_BUTTON2, &CUserDlg::OnBnClickedButton2)
END_MESSAGE_MAP()


// CUserDlg 诊断

#ifdef _DEBUG
void CUserDlg::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CUserDlg::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CUserDlg 消息处理程序


void CUserDlg::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: 在此添加专用代码和/或调用基类
	//初始化
	m_name = tempworker.StaffName;
	m_ID = tempworker.StaffID;
	m_passwd = tempworker.StaffPasswd;
	UpdateData(FALSE);
}


void CUserDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	//取到最新值
	if (m_newpasswd.IsEmpty() || m_surepasswd.IsEmpty())
	{
		MessageBox(TEXT("输入内容不能为空！"));
		return;
	}
	if (m_newpasswd != m_surepasswd)
	{
		MessageBox(TEXT("两次密码不一致！"));
		return;
	}
	if (m_newpasswd == m_passwd)
	{
		MessageBox(TEXT("新密码与原密码相同！"));
		return;
	}
	DataBase A;
	CString status;
	A.ConnectDatabase(status);
	CstringChar changePasswd;
	CStringA tmp1,tmp2;
	tmp1 = m_newpasswd;
	tmp2 = tempworker.StaffID;
	A.ChangePasswd(tmp1.GetBuffer(), tmp2.GetBuffer());
	MessageBox(TEXT("修改成功！"));
	m_passwd = m_newpasswd;
	UpdateData(FALSE);

}


void CUserDlg::OnEnChangeEdit1()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CFormView::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}


void CUserDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	//取消按钮
	m_newpasswd.Empty();
	m_surepasswd.Empty();
	UpdateData(FALSE);
}
