// CGuest.cpp: 实现文件
//

#include "pch.h"
#include "酒店管理系统.h"
#include "CGuest.h"
#include "ConnectDB.h"

// CGuest

IMPLEMENT_DYNCREATE(CGuest, CFormView)

CGuest::CGuest()
	: CFormView(DIALOG_GUEST)
	, m_NewGuestID(_T(""))
	, m_NewGuestName(_T(""))
	, m_NewGuestPhone(_T(""))
{

}

CGuest::~CGuest()
{
}

void CGuest::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_list_guest);
	DDX_Control(pDX, IDC_LIST1, m_list_guest);
	DDX_Text(pDX, IDC_EDIT1, m_NewGuestID);
	DDX_Text(pDX, IDC_EDIT2, m_NewGuestName);
	DDX_Text(pDX, IDC_EDIT6, m_NewGuestPhone);
}

BEGIN_MESSAGE_MAP(CGuest, CFormView)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST1, &CGuest::OnLvnItemchangedList1)
	ON_BN_CLICKED(IDC_BUTTON2, &CGuest::OnBnClickedButton2)
END_MESSAGE_MAP()


// CGuest 诊断

#ifdef _DEBUG
void CGuest::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CGuest::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CGuest 消息处理程序


void CGuest::OnLvnItemchangedList1(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
}


void CGuest::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: 在此添加专用代码和/或调用基类
	DataBase A;
	CString status;
	A.ConnectDatabase(status);
	int GuestNum = 0;
	Guest* guest = new Guest[30];
	A.QueryGuest(GuestNum, guest);
	CString GuestListTable[] = { TEXT("身份证号"),TEXT("姓名") ,TEXT("电话号码") };
	for (int i = 0; i < 3; i++)
	{
		m_list_guest.InsertColumn(i, GuestListTable[i], LVCFMT_LEFT, 130);
	}
	for (int i = 0; i < GuestNum; i++)
	{
		m_list_guest.InsertItem(i, guest[i].GuestID);
		m_list_guest.SetItemText(i, 1, guest[i].GuestName);
		m_list_guest.SetItemText(i, 2, guest[i].PhoneNumber);
	}
	A.CloseConnection(A);
}


void CGuest::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	DataBase A;
	CString status;
	A.ConnectDatabase(status);
	int GuestNum = 0;
	Guest* guest = new Guest[30];
	A.QueryGuest(GuestNum, guest);
	for (int i = 0; i < GuestNum; i++)
	{
		if (guest[i].GuestID == m_NewGuestID)
		{
			MessageBox(TEXT("房客已存在！"));
			return;
		}
	}
	A.AddGuest(m_NewGuestID, m_NewGuestName, m_NewGuestPhone);
	A.QueryGuest(GuestNum, guest);
	m_list_guest.DeleteAllItems();
	for (int i = 0; i < GuestNum; i++)
	{
		m_list_guest.InsertItem(i, guest[i].GuestID);
		m_list_guest.SetItemText(i, 1, guest[i].GuestName);
		m_list_guest.SetItemText(i, 2, guest[i].PhoneNumber);
	}
	A.CloseConnection(A);
}
