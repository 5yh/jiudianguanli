#pragma once



// COrderRoom 窗体视图

class COrderRoom : public CFormView
{
	DECLARE_DYNCREATE(COrderRoom)

protected:
	COrderRoom();           // 动态创建所使用的受保护的构造函数
	virtual ~COrderRoom();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = DIALOG_ORDER_ROOM };
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
	afx_msg void OnDtnDatetimechangeDatetimepicker1(NMHDR* pNMHDR, LRESULT* pResult);
private:
	CDateTimeCtrl m_begintime;
public:
	afx_msg void OnBnClickedButton1();
private:
	CDateTimeCtrl m_endtime;
public:
	CString m_order_roomID;
private:
	CString m_guestID;
};


