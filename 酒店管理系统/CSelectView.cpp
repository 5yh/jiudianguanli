// CSelectView.cpp: 实现文件
//

#include "pch.h"
#include "酒店管理系统.h"
#include "CSelectView.h"
#include "MainFrm.h"

// CSelectView

IMPLEMENT_DYNCREATE(CSelectView, CTreeView)

CSelectView::CSelectView()
{

}

CSelectView::~CSelectView()
{
}

BEGIN_MESSAGE_MAP(CSelectView, CTreeView)
	ON_NOTIFY_REFLECT(TVN_SELCHANGED, &CSelectView::OnTvnSelchanged)
END_MESSAGE_MAP()


// CSelectView 诊断

#ifdef _DEBUG
void CSelectView::AssertValid() const
{
	CTreeView::AssertValid();
}

#ifndef _WIN32_WCE
void CSelectView::Dump(CDumpContext& dc) const
{
	CTreeView::Dump(dc);
}
#endif
#endif //_DEBUG


// CSelectView 消息处理程序


void CSelectView::OnInitialUpdate()
{
	CTreeView::OnInitialUpdate();
	//对树视图代码进行初始化
	//获取树控件
	m_treectrl = &GetTreeCtrl();
	//		准备图片
	HICON icon = AfxGetApp()->LoadIconW(IDI_ICON_RE);
	m_imageList.Create(30, 30, ILC_COLOR32, 1, 1);
	m_imageList.Add(icon);
	m_treectrl->SetImageList(&m_imageList,TVSIL_NORMAL);

	// 	   添加节点
	m_treectrl->InsertItem(TEXT("个人信息"), 0, 0, NULL);
	m_treectrl->InsertItem(TEXT("房间信息"), 0, 0, NULL);
	m_treectrl->InsertItem(TEXT("房客信息"), 0, 0, NULL);







	// 
	// TODO: 在此添加专用代码和/或调用基类
}


void CSelectView::OnTvnSelchanged(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
	//获取当前的选中项
	HTREEITEM item = m_treectrl->GetSelectedItem();
	//获取这个项中内容
	CString listinf = m_treectrl->GetItemText(item);
	//MessageBox(listinf);
	//一点就出来相关界面



	if (listinf == TEXT("个人信息"))
	{
		//需要包含框架类头文件#include "MainFrm.h" 
		//CWnd::PostMessage 将一个消息放入窗口的消息队列
		//AfxGetMainWnd()：框架窗口对象的指针
		//AfxGetMainWnd()->GetSafeHwnd()：获取返回窗口的句柄，CWnd::GetSafeHwnd
		//NM_A：发送自定义消息
		//(WPARAM)NM_A：指定了附加的消息信息
		//(LPARAM)0：指定了附加的消息信息，此参数这里没有意义
		//::作用域，使用原生api
		
		::PostMessage(AfxGetMainWnd()->GetSafeHwnd(), NM_A, (WPARAM)NM_A, (LPARAM)0);
	}
	else if (listinf == TEXT("房间信息"))
	{
		::PostMessage(AfxGetMainWnd()->GetSafeHwnd(), NM_B, (WPARAM)NM_B, (LPARAM)0);
	}

}
