
// Cocos2dxProjectTool.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CCocos2dxProjectToolApp: 
// �йش����ʵ�֣������ Cocos2dxProjectTool.cpp
//

class CCocos2dxProjectToolApp : public CWinApp
{
public:
	CCocos2dxProjectToolApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CCocos2dxProjectToolApp theApp;