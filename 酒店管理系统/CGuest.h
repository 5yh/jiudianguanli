#pragma once



// CGuest 窗体视图

class CGuest : public CFormView
{
	DECLARE_DYNCREATE(CGuest)

protected:
	CGuest();           // 动态创建所使用的受保护的构造函数
	virtual ~CGuest();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = DIALOG_GUEST };
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
private:
	CListCtrl m_list_guest;
public:
	virtual void OnInitialUpdate();
private:
	CString m_NewGuestID;
	CString m_NewGuestName;
	CString m_NewGuestPhone;
public:
	afx_msg void OnBnClickedButton2();
};


