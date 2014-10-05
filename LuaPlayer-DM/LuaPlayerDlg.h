
// LuaPlayerDlg.h : ͷ�ļ�
//

#pragma once
#include "loadlua.h"
#include "afxwin.h"


// CLuaPlayerDlg �Ի���
class CLuaPlayerDlg : public CDialogEx
{
// ����
public:
	CLuaPlayerDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_LUAPLAYER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	LoadLua lua;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	CButton button;
	CString output;
	void UpdateLog(CString str);
//	afx_msg void OnClose();
//	afx_msg void OnCancelMode();
	afx_msg void OnCancel();
};
