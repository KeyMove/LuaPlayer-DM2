
// LuaPlayer.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CLuaPlayerApp:
// �йش����ʵ�֣������ LuaPlayer.cpp
//

class CLuaPlayerApp : public CWinApp
{
public:
	CLuaPlayerApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CLuaPlayerApp theApp;