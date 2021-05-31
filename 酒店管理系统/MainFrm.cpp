
// MainFrm.cpp: CMainFrame 类的实现
//

#include "pch.h"
#include "framework.h"
#include "酒店管理系统.h"

#include "MainFrm.h"
#include "ConnectDB.cpp"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_CREATE()
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // 状态行指示器
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

// CMainFrame 构造/析构

CMainFrame::CMainFrame() noexcept
{
	// TODO: 在此添加成员初始化代码
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	if (!m_wndStatusBar.Create(this))
	{
		TRACE0("未能创建状态栏\n");
		return -1;      // 未能创建
	}
	m_wndStatusBar.SetIndicators(indicators, sizeof(indicators)/sizeof(UINT));
	//设置图标
	SetClassLongPtr(m_hWnd, GCLP_HICON, (LONG_PTR)AfxGetApp()->LoadIconW(IDI_ICON_WIN));
	//设置右侧标题
	SetTitle(TEXT("2021/5/29"));
	DataBase A;
	CString str;
	A.ConnectDatabase(str);
	MessageBox(str);
	//使用extern来传递当前登录的是谁
	/*
	str = LoginStaff.StaffID;
	MessageBox(str);*/



	Staff* worker = new Staff[10];
	int StaffNum=0;
	A.QueryStaff(StaffNum, worker);
	//MessageBox(worker[1].StaffID);
	//MessageBox(worker[1].StaffName);
	//设置窗口大小
	//设置窗口的位置和大小：CWnd::MoveWindow
	//0, 0, 起点坐标x和y
	//800, 500, 窗口宽度和高度
	MoveWindow(0, 0, 1000,700);

	//将窗口移动到屏幕中央，CWnd::CenterWindow
	CenterWindow();

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return TRUE;
}

// CMainFrame 诊断

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}
#endif //_DEBUG


// CMainFrame 消息处理程序
  
