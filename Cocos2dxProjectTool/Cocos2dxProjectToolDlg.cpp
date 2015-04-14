
// Cocos2dxProjectToolDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Cocos2dxProjectTool.h"
#include "Cocos2dxProjectToolDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CCocos2dxProjectToolDlg �Ի���



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


// CCocos2dxProjectToolDlg ��Ϣ�������

BOOL CCocos2dxProjectToolDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	ShowWindow(SW_MINIMIZE);

	// TODO:  �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CCocos2dxProjectToolDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CCocos2dxProjectToolDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CCocos2dxProjectToolDlg::OnBnClickedButtonChooseDir()
{
	char szPath[MAX_PATH];     //���ѡ���Ŀ¼·��  
	ZeroMemory(szPath, sizeof(szPath));

	BROWSEINFO bi;
	bi.hwndOwner = m_hWnd;
	bi.pidlRoot = NULL;
	bi.pszDisplayName = szPath;
	bi.lpszTitle = "��ѡ�񹤳�Ŀ¼��";
	bi.ulFlags = 0;
	bi.lpfn = NULL;
	bi.lParam = 0;
	bi.iImage = 0;
	//����ѡ��Ŀ¼�Ի��� 
	LPITEMIDLIST lp = SHBrowseForFolder(&bi);

	if (lp && SHGetPathFromIDList(lp, szPath))
	{
		SetDlgItemTextA(IDC_EDIT_PROJECT_PATH, szPath);
	}
}


void CCocos2dxProjectToolDlg::OnBnClickedButtonCreate()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CString project_name, package_name, project_path;
	char cmd[1024];
	ZeroMemory(cmd, sizeof(cmd));
	GetDlgItemTextA(IDC_EDIT_PROJECT_NAME, project_name);
	if (project_name.IsEmpty()) {
		AfxMessageBox("�����빤������");
		return;
	}
	GetDlgItemTextA(IDC_EDIT_PACKAGE_NAME, package_name);
	if (package_name.IsEmpty()) {
		AfxMessageBox("�����빤�̰���");
		return;
	}
	GetDlgItemTextA(IDC_EDIT_PROJECT_PATH, project_path);
	if (project_path.IsEmpty()) {
		AfxMessageBox("��ѡ�񹤳�·��");
		return;
	}
	sprintf_s(cmd, "cocos new %s -p %s -l cpp -d %s", project_name, package_name, project_path);
	system(cmd);
}
