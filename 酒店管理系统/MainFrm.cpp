
// MainFrm.cpp: CMainFrame 类的实现
//

#include "pch.h"
#include "framework.h"
#include "酒店管理系统.h"
#include "CSelectView.h"
#include "CDisplayView.h"
#include "CUserDlg.h"

#include "MainFrm.h"
#include "ConnectDB.cpp"
#include "CLoginDlg.h"
#include "CShowRoom.h"
extern CLoginDlg* p_CLoginDLg;
extern Staff tempworker;
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_CREATE()

	//ON_MESSAGE响应的是自定义消息
//产生NM_X消息，自动调用OnMyChange函数
	ON_MESSAGE(NM_A, OnMyChange)
	ON_MESSAGE(NM_B, OnMyChange)
	ON_MESSAGE(NM_C, OnMyChange)
	ON_MESSAGE(NM_D, OnMyChange)
	ON_MESSAGE(NM_E, OnMyChange)
	ON_MESSAGE(NM_F, OnMyChange)
	ON_MESSAGE(NM_G, OnMyChange)
	ON_MESSAGE(NM_H, OnMyChange)
	ON_MESSAGE(NM_I, OnMyChange)
	ON_MESSAGE(NM_J, OnMyChange)





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
	//p_CLoginDLg->OnBnClickedButton1();
	CString str1=tempworker.StaffID;
	MessageBox(str1);
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
  


BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext)
{
	// TODO: 在此添加专用代码和/或调用基类

	//return CFrameWnd::OnCreateClient(lpcs, pContext);
	//拆成一行两列
	m_spliter.CreateStatic(this, 1, 2);
	//左侧
	m_spliter.CreateView(0, 0, RUNTIME_CLASS(CSelectView), CSize(200, 500),pContext);
	m_spliter.CreateView(0, 1, RUNTIME_CLASS(CDisplayView), CSize(200, 500), pContext);
	return TRUE;//手动拆分
}

LRESULT CMainFrame::OnMyChange(WPARAM wParam, LPARAM lParam) 
{
	CCreateContext   Context;
	if (wParam == NM_A)//个人信息
	{
		Context.m_pNewViewClass = RUNTIME_CLASS(CUserDlg);
		Context.m_pCurrentFrame = this;
		Context.m_pLastView = (CFormView*)m_spliter.GetPane(0, 1);
		m_spliter.DeleteView(0, 1);
		m_spliter.CreateView(0, 1, RUNTIME_CLASS(CUserDlg), CSize(600, 500), &Context);
		CUserDlg* pNewView = (CUserDlg*)m_spliter.GetPane(0, 1);
		m_spliter.RecalcLayout();
		pNewView->OnInitialUpdate();
		m_spliter.SetActivePane(0, 1);

	}
	else if (wParam == NM_B)//个人信息
	{
		Context.m_pNewViewClass = RUNTIME_CLASS(CShowRoom);
		Context.m_pCurrentFrame = this;
		Context.m_pLastView = (CFormView*)m_spliter.GetPane(0, 1);
		m_spliter.DeleteView(0, 1);
		m_spliter.CreateView(0, 1, RUNTIME_CLASS(CShowRoom), CSize(600, 500), &Context);
		CUserDlg* pNewView = (CUserDlg*)m_spliter.GetPane(0, 1);
		m_spliter.RecalcLayout();
		pNewView->OnInitialUpdate();
		m_spliter.SetActivePane(0, 1);

	}
	return 0;
}
