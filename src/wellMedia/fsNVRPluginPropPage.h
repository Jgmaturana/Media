#pragma once

// fsNVRPluginPropPage.h : CfsNVRPluginPropPage ����ҳ���������


// CfsNVRPluginPropPage : �й�ʵ�ֵ���Ϣ������� fsNVRPluginPropPage.cpp��

class CfsNVRPluginPropPage : public COlePropertyPage
{
	DECLARE_DYNCREATE(CfsNVRPluginPropPage)
	DECLARE_OLECREATE_EX(CfsNVRPluginPropPage)

// ���캯��
public:
	CfsNVRPluginPropPage();

// �Ի�������
	enum { IDD = IDD_PROPPAGE_FSNVRPLUGIN };

// ʵ��
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ��Ϣӳ��
protected:
	DECLARE_MESSAGE_MAP()
public:
};

