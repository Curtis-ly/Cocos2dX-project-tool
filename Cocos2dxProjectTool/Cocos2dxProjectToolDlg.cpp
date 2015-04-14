
// Cocos2dxProjectToolDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Cocos2dxProjectTool.h"
#include "Cocos2dxProjectToolDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CCocos2dxProjectToolDlg 对话框



CCocos2dxProjectToolDlg::CCocos2dxProjectToolDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CCocos2dxProjectToolDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCocos2dxProjectToolDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_PROJECT_NAME, edt_project_name);
	DDX_Control(pDX, IDC_EDIT_PACKAGE_NAME, edt_package_name);
	DDX_Control(pDX, IDC_EDIT_PROJECT_PATH, edt_project_path);
}

BEGIN_MESSAGE_MAP(CCocos2dxProjectToolDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_CHOOSE_DIR, &CCocos2dxProjectToolDlg::OnBnClickedButtonChooseDir)
	ON_BN_CLICKED(IDC_BUTTON_CREATE, &CCocos2dxProjectToolDlg::OnBnClickedButtonCreate)
END_MESSAGE_MAP()


// CCocos2dxProjectToolDlg 消息处理程序

BOOL CCocos2dxProjectToolDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	ShowWindow(SW_MINIMIZE);

	// TODO:  在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CCocos2dxProjectToolDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CCocos2dxProjectToolDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CCocos2dxProjectToolDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CCocos2dxProjectToolDlg::OnBnClickedButtonChooseDir()
{
	char szPath[MAX_PATH];     //存放选择的目录路径  
	ZeroMemory(szPath, sizeof(szPath));

	BROWSEINFO bi;
	bi.hwndOwner = m_hWnd;
	bi.pidlRoot = NULL;
	bi.pszDisplayName = szPath;
	bi.lpszTitle = "请选择工程目录：";
	bi.ulFlags = 0;
	bi.lpfn = NULL;
	bi.lParam = 0;
	bi.iImage = 0;
	//弹出选择目录对话框 
	LPITEMIDLIST lp = SHBrowseForFolder(&bi);

	if (lp && SHGetPathFromIDList(lp, szPath))
	{
		SetDlgItemTextA(IDC_EDIT_PROJECT_PATH, szPath);
	}
}


void CCocos2dxProjectToolDlg::OnBnClickedButtonCreate()
{
	// TODO:  在此添加控件通知处理程序代码
	CString project_name, package_name, project_path;
	char cmd[1024];
	ZeroMemory(cmd, sizeof(cmd));
	GetDlgItemTextA(IDC_EDIT_PROJECT_NAME, project_name);
	if (project_name.IsEmpty()) {
		AfxMessageBox("请输入工程名称");
		return;
	}
	GetDlgItemTextA(IDC_EDIT_PACKAGE_NAME, package_name);
	if (package_name.IsEmpty()) {
		AfxMessageBox("请输入工程包名");
		return;
	}
	GetDlgItemTextA(IDC_EDIT_PROJECT_PATH, project_path);
	if (project_path.IsEmpty()) {
		AfxMessageBox("请选择工程路径");
		return;
	}
	sprintf_s(cmd, "cocos new %s -p %s -l cpp -d %s", project_name, package_name, project_path);
	system(cmd);
}
