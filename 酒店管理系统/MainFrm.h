﻿
// MainFrm.h: CMainFrame 类的接口
//

#pragma once

//自定义消息时间
#define NM_A	(WM_USER + 100)//个人信息
#define NM_B	(WM_USER + 101)//房间信息
#define NM_C	(WM_USER + 102)//订购房间
#define NM_D	(WM_USER + 103)//房客登记
#define NM_E	(WM_USER + 104)
#define NM_F	(WM_USER + 105)
#define NM_G	(WM_USER + 106)
#define NM_H	(WM_USER + 107)
#define NM_I	(WM_USER + 108)
#define NM_J	(WM_USER + 109)
class CMainFrame : public CFrameWnd
{
	
protected: // 仅从序列化创建
	CMainFrame() noexcept;
	DECLARE_DYNCREATE(CMainFrame)

// 特性
public:

// 操作
public:

// 重写
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// 实现
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // 控件条嵌入成员
	CStatusBar        m_wndStatusBar;

// 生成的消息映射函数
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	DECLARE_MESSAGE_MAP()
private:
	CSplitterWnd m_spliter; // 切分窗口类对象
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
	afx_msg LRESULT OnMyChange(WPARAM wParam, LPARAM lParam);
};


