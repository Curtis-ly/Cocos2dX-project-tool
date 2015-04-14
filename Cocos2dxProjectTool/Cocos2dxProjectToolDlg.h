
// Cocos2dxProjectToolDlg.h : 头文件
//

#pragma once
#include "afxwin.h"


// CCocos2dxProjectToolDlg 对话框
class CCocos2dxProjectToolDlg : public CDialogEx
{
// 构造
public:
	CCocos2dxProjectToolDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_COCOS2DXPROJECTTOOL_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CEdit edt_project_name;
	CEdit edt_package_name;
	CEdit edt_project_path;
	afx_msg void OnBnClickedButtonChooseDir();
	afx_msg void OnBnClickedButtonCreate();
};
