// CLoginDlg.cpp: 实现文件
//

#include "pch.h"
#include "酒店管理系统.h"
#include "CLoginDlg.h"
#include "afxdialogex.h"
#include "ConnectDB.cpp"
#include "string.h"
//不添加总是爆红
#include "resource.h"
// CLoginDlg 对话框
Staff tempworker;
CLoginDlg* p_CLoginDLg;
IMPLEMENT_DYNAMIC(CLoginDlg, CDialogEx)
CLoginDlg::CLoginDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(DIALOG_LOGIN, pParent)
	, m_user(_T(""))
	, m_pwd(_T(""))
{

}

CLoginDlg::~CLoginDlg()
{
}

void CLoginDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_user);
	DDX_Text(pDX, IDC_EDIT2, m_pwd);
}


BEGIN_MESSAGE_MAP(CLoginDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CLoginDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CLoginDlg::OnBnClickedButton2)
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// CLoginDlg 消息处理程序


void CLoginDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	//登录按钮点击事件
	UpdateData(TRUE);//控件内容同步
	if (m_user.IsEmpty() || m_pwd.IsEmpty())
	{
		MessageBox(TEXT("用户名及密码禁止为空！"));
		return;
	}
	//获取正确的值
	DataBase GetStaff;
	CString status;
	GetStaff.ConnectDatabase(status);
	Staff* worker = new Staff[10];
	int StaffNum = 0;
	int i = 0;
	GetStaff.QueryStaff(StaffNum, worker);
	while (i != StaffNum)
	{
		if (worker[i].StaffID == m_user)//找到了
		{
			break;
		}
		i++;
	}
	if (i == StaffNum)//没找到
	{
		MessageBox(TEXT("用户名错误！"));
	}
	if (worker[i].StaffID == m_user)
	{
		if (worker[i].StaffPasswd == m_pwd)
		{ 
			//tempworker = worker[i];
			tempworker.StaffID=worker[i].StaffID;
			tempworker.StaffName = worker[i].StaffName;
			tempworker.StaffPasswd = worker[i].StaffPasswd;
			tempworker.Staffrwx = worker[i].Staffrwx;
			strcpy(tempworker.CharStaffID, worker[i].CharStaffID);
			strcpy(tempworker.CharStaffPasswd, worker[i].CharStaffPasswd);
			//用户名和密码都正确，关闭对话框
			CDialog::OnCancel();
		}
		else
		{
			MessageBox(TEXT("密码错误！"));
		}
	}
	mysql_close(GetStaff.mysql);
}


BOOL CLoginDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	//添加默认登录信息
	m_user = "114514";
	m_pwd = "1919810";
	p_CLoginDLg = this;
	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CLoginDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	exit(0);
}


void CLoginDlg::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类

	//CDialogEx::OnOK();
}


void CLoginDlg::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	//CDialogEx::OnClose();
	exit(0);
}


void CLoginDlg::OnCancel()
{
	// TODO: 在此添加专用代码和/或调用基类

	//CDialogEx::OnCancel();
	exit(0);
}

