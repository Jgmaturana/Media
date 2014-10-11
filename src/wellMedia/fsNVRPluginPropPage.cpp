// fsNVRPluginPropPage.cpp : CfsNVRPluginPropPage ����ҳ���ʵ�֡�

#include "stdafx.h"
#include "fsNVRPlugin.h"
#include "fsNVRPluginPropPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


IMPLEMENT_DYNCREATE(CfsNVRPluginPropPage, COlePropertyPage)



// ��Ϣӳ��

BEGIN_MESSAGE_MAP(CfsNVRPluginPropPage, COlePropertyPage)
END_MESSAGE_MAP()



// ��ʼ���๤���� guid

IMPLEMENT_OLECREATE_EX(CfsNVRPluginPropPage, "FSNVRPLUGIN.fsNVRPluginPropPage.1",
	0x65757c0, 0x4c46, 0x47d8, 0xa9, 0x40, 0x76, 0x47, 0xb4, 0x23, 0x67, 0x8)



// CfsNVRPluginPropPage::CfsNVRPluginPropPageFactory::UpdateRegistry -
// ��ӻ��Ƴ� CfsNVRPluginPropPage ��ϵͳע�����

BOOL CfsNVRPluginPropPage::CfsNVRPluginPropPageFactory::UpdateRegistry(BOOL bRegister)
{
	if (bRegister)
		return AfxOleRegisterPropertyPageClass(AfxGetInstanceHandle(),
			m_clsid, IDS_FSNVRPLUGIN_PPG);
	else
		return AfxOleUnregisterClass(m_clsid, NULL);
}



// CfsNVRPluginPropPage::CfsNVRPluginPropPage - ���캯��

CfsNVRPluginPropPage::CfsNVRPluginPropPage() :
	COlePropertyPage(IDD, IDS_FSNVRPLUGIN_PPG_CAPTION)
{
}



// CfsNVRPluginPropPage::DoDataExchange - ��ҳ�����Լ��ƶ�����

void CfsNVRPluginPropPage::DoDataExchange(CDataExchange* pDX)
{
	DDP_PostProcessing(pDX);
}



// CfsNVRPluginPropPage ��Ϣ�������
