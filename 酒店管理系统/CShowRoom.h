#pragma once



// CShowRoom 窗体视图

class CShowRoom : public CFormView
{
	DECLARE_DYNCREATE(CShowRoom)

protected:
	CShowRoom();           // 动态创建所使用的受保护的构造函数
	virtual ~CShowRoom();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = DIALOG_SHOW_ROOM };
#endif
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLvnItemchangedList1(NMHDR* pNMHDR, LRESULT* pResult);
	virtual void OnInitialUpdate();
private:
	CListCtrl m_list_room;
};


