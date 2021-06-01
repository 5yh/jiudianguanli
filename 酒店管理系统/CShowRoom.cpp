// CShowRoom.cpp: 实现文件
//

#include "pch.h"
#include "酒店管理系统.h"
#include "CShowRoom.h"
#include "ConnectDB.cpp"

// CShowRoom

IMPLEMENT_DYNCREATE(CShowRoom, CFormView)

CShowRoom::CShowRoom()
	: CFormView(DIALOG_SHOW_ROOM)
{

}

CShowRoom::~CShowRoom()
{
}

void CShowRoom::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_list_room);
}

BEGIN_MESSAGE_MAP(CShowRoom, CFormView)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST1, &CShowRoom::OnLvnItemchangedList1)
END_MESSAGE_MAP()


// CShowRoom 诊断

#ifdef _DEBUG
void CShowRoom::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CShowRoom::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CShowRoom 消息处理程序


void CShowRoom::OnLvnItemchangedList1(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
}


void CShowRoom::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: 在此添加专用代码和/或调用基类
	DataBase A;
	CString status;
	A.ConnectDatabase(status);
	int RoomNum=0;
	Room* room = new Room[10];
	A.QueryRoom(RoomNum, room);
	//列表控件添加值
	CString RoomListTable[] = { TEXT("房间号"),TEXT("房间类型") ,TEXT("房间地址") };
	for (int i = 0; i < 3; i++)
	{
		//设置表头
		m_list_room.InsertColumn(i, RoomListTable[i],LVCFMT_LEFT,150);
	}
	//设置正文

	for (int i = 0; i < RoomNum; i++)
	{	//索引从0开始
		m_list_room.InsertItem(i, room[i].RoomID);
		//给这个item插入数据
		m_list_room.SetItemText(i, 1, room[i].RoomType);
		m_list_room.SetItemText(i, 2, room[i].RoomAddress);
	}
}
