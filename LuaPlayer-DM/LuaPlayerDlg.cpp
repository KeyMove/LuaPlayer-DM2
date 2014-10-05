
// LuaPlayerDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "LuaPlayer.h"
#include "LuaPlayerDlg.h"
#include "afxdialogex.h"
#include "LoadLua.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

extern "C"

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


// CLuaPlayerDlg �Ի���



CLuaPlayerDlg::CLuaPlayerDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CLuaPlayerDlg::IDD, pParent)
	, output(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CLuaPlayerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON1, button);
	DDX_Text(pDX, IDC_EDIT1, output);
}

BEGIN_MESSAGE_MAP(CLuaPlayerDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CLuaPlayerDlg::OnBnClickedButton1)
	ON_WM_TIMER()
//	ON_WM_CLOSE()
//	ON_WM_CANCELMODE()
ON_WM_CANCELMODE()
END_MESSAGE_MAP()


// CLuaPlayerDlg ��Ϣ�������

BOOL CLuaPlayerDlg::OnInitDialog()
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
	lua.InitLua();
	lua.SetHWND(this->GetSafeHwnd());
	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CLuaPlayerDlg::OnSysCommand(UINT nID, LPARAM lParam)
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
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CLuaPlayerDlg::OnPaint()
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
HCURSOR CLuaPlayerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CLuaPlayerDlg::OnBnClickedButton1()
{
	static int sw;
	if(sw)
	{
		button.SetWindowTextW(_T("�򿪽ű�"));
		lua.CloseAllTimer();
		sw=0;
		return;
	}
	CFileDialog dlg(TRUE, NULL, NULL, OFN_HIDEREADONLY, _T("lua�ű��ļ� (*.lua)|*.lua|�����ļ� (*.*)|*.*||"), NULL);
	if(dlg.DoModal()==IDOK)
	{
		if(lua.doFile(dlg.GetPathName()))
		{
			output=lua.GetErrorLog();
			UpdateData(false);
			AfxMessageBox(_T("���д���"));
		}
		else
		{
			button.SetWindowTextW(_T("�رսű�"));
			output=_T("");
			UpdateData(false);
			sw=1;
		}
	}
}


void CLuaPlayerDlg::OnTimer(UINT_PTR nIDEvent)
{
	lua.TimerCall(nIDEvent);
	output+=lua.GetErrorLog();
	UpdateData(false);
	CDialogEx::OnTimer(nIDEvent);
}


void CLuaPlayerDlg::UpdateLog(CString str)
{
	output+=str;
	UpdateData(false);
}



void CLuaPlayerDlg::OnCancel()
{
	lua.CloseAllTimer();
	CDialogEx::OnCancel();
	// TODO: �ڴ˴������Ϣ����������
}
