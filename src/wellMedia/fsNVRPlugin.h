#pragma once

// fsNVRPlugin.h : fsNVRPlugin.DLL ����ͷ�ļ�

#if !defined( __AFXCTL_H__ )
#error "�ڰ������ļ�֮ǰ������afxctl.h��"
#endif

#include "resource.h"       // ������


// CfsNVRPluginApp : �й�ʵ�ֵ���Ϣ������� fsNVRPlugin.cpp��

class CfsNVRPluginApp : public COleControlModule
{
public:
	BOOL InitInstance();
	int ExitInstance();

private:
	BOOL m_bInit;
};

extern const GUID CDECL _tlid;
extern const WORD _wVerMajor;
extern const WORD _wVerMinor;

