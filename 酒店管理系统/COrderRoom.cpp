﻿// COrderRoom.cpp: 实现文件
//

#include "pch.h"
#include "酒店管理系统.h"
#include "COrderRoom.h"
#include "ConnectDB.cpp"
int OrderID=0;
// COrderRoom

IMPLEMENT_DYNCREATE(COrderRoom, CFormView)

COrderRoom::COrderRoom()
	: CFormView(DIALOG_ORDER_ROOM)
	, m_order_roomID(_T(""))
	, m_guestID(_T(""))
{

}

COrderRoom::~COrderRoom()
{
}

void COrderRoom::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_DATETIMEPICKER1, m_begintime);
	DDX_Control(pDX, IDC_DATETIMEPICKER2, m_endtime);
	DDX_Text(pDX, IDC_EDIT1, m_order_roomID);
	DDX_Text(pDX, IDC_EDIT2, m_guestID);
}

BEGIN_MESSAGE_MAP(COrderRoom, CFormView)
	ON_NOTIFY(DTN_DATETIMECHANGE, IDC_DATETIMEPICKER1, &COrderRoom::OnDtnDatetimechangeDatetimepicker1)
	ON_BN_CLICKED(IDC_BUTTON1, &COrderRoom::OnBnClickedButton1)
END_MESSAGE_MAP()


// COrderRoom 诊断

#ifdef _DEBUG
void COrderRoom::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void COrderRoom::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// COrderRoom 消息处理程序


void COrderRoom::OnDtnDatetimechangeDatetimepicker1(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMDATETIMECHANGE pDTChange = reinterpret_cast<LPNMDATETIMECHANGE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
}


void COrderRoom::OnBnClickedButton1()
{
	CTime BeginTime,EndTime;
	// TODO: 在此添加控件通知处理程序代码
	m_begintime.GetTime(BeginTime);
	m_endtime.GetTime(EndTime);
	if (BeginTime > EndTime)
	{
		MessageBox(TEXT("订房起始时间不可以晚于结束时间，订房失败！"));
		return;
	}
	int BeginYear,BeginMonth,BeginDay,EndYear,EndMonth,EndDay;
	BeginYear =BeginTime.GetYear();
	BeginMonth = BeginTime.GetMonth();
	BeginDay = BeginTime.GetDay();
	EndYear = EndTime.GetYear();
	EndMonth = EndTime.GetMonth();
	EndDay = EndTime.GetDay();
	CString CBeginYear, CBeginMonth, CBeginDay, CEndYear, CEndMonth, CEndDay;
	CBeginYear.Format(_T("%d"), BeginYear);
	CBeginMonth.Format(_T("%d"), BeginMonth);
	CBeginDay.Format(_T("%d"), BeginDay);
	CEndYear.Format(_T("%d"), EndYear);
	CEndMonth.Format(_T("%d"), EndMonth);
	CEndDay.Format(_T("%d"), EndDay);

	DataBase A;
	CString status;
	A.ConnectDatabase(status);




	MessageBox(TEXT("订房成功！"));
}
