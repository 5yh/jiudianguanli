﻿#pragma once
#include <afxcview.h>
//为了使ctreeview不报错
// CSelectView 视图

class CSelectView : public CTreeView
{
	DECLARE_DYNCREATE(CSelectView)

protected:
	CSelectView();           // 动态创建所使用的受保护的构造函数
	virtual ~CSelectView();

public:
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	DECLARE_MESSAGE_MAP()
private:
	CTreeCtrl* m_treectrl;
	CImageList m_imageList;
public:
	virtual void OnInitialUpdate();
	afx_msg void OnTvnSelchanged(NMHDR* pNMHDR, LRESULT* pResult);
};


