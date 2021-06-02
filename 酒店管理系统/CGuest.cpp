// CGuest.cpp: 实现文件
//

#include "pch.h"
#include "酒店管理系统.h"
#include "CGuest.h"


// CGuest

IMPLEMENT_DYNCREATE(CGuest, CFormView)

CGuest::CGuest()
	: CFormView(DIALOG_GUEST)
{

}

CGuest::~CGuest()
{
}

void CGuest::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CGuest, CFormView)
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
