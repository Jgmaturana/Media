#pragma once
#include "NPWndProc.h"
#include "gluelib.h"

#define MAXCHANNEL	1

//�Ƿ��ж�w���ڣ� ��Ҫ��MAXCHANNEL�Q��
#define MULIT_WND  (MAXCHANNEL > 1 ? 1 : 0)

#define NPMSG_PARAM	\
	CNPWnd* pWnd, WPARAM wParam, LPARAM lParam

#define DECLARE_ONMSG(func) \
	LRESULT func(NPMSG_PARAM);

class CGlue
{
public:
	CGlue(void);
	~CGlue(void);

public:
	void RegisterPlugin(CreateVarRiant vrcreate, DeleteVarRiant vrdel, Int32ToVarRiant cvint, StringToVarRiant cvstring, InvokeJavaScriptFunc func, void* data);
	void OnCreate(HWND hParent, HINSTANCE hInstance);
	void OnSize(int w, int h);
	void OnDestroy();

	void SetPropertyOfStr(char* name, char* value);
	void SetPropertyOfLong(char* name, long value);

	void GetNextPage();
	void GetPrevPage();
	void EnterOrExitFullScreen();
	void EnterOrExitFullScreenForSigChanl(HWND hWnd);
	void SetSelectedChanl(CNPWndProc* pWnd);
	CNPWndProc GetSelectedChanl();

	bool OpenMedia(const char* mediaPath, short nType);
	bool CloseMedia();
	bool Play();
	bool Pause();
	bool Stop();
	bool Forward(short nSpeed);
	bool Reverse(short nSpeed);
	void PreFrame();
	void NextFrame();
	bool Seek(long pos, long minVal, long maxVal);
	short Snap(const char* savePath);
	short SetSelectWnd(short nWndIndex);
	short SetWndChannels(short nWndId, short nChannels);
	void Exit();
	void GetPlayPos(long* curPos, long* totalFrames);

	short SetWndChannelSelect(short nWndIndex, short nChannel);
	short GetWndChannelSelect(short nWndIndex);
	short GetWndChannelCount(short nWndIndex);


	bool IsParentFullScreen() const { return m_bIsParentFullScreen; }
	bool IsChildFullScreen() const { return m_bIsChildFullScreen; }
	bool IsPolling() const { return m_bIsPolling; }
	void DrawBorderAll(CNPWndProc* pWnd);

	HPEN GetBoderPen() const { return m_hBorderPen; }
	HPEN GetBoderPen2() const { return m_hBorderPen2; }

protected://��Ϣ��Ӧ
	DECLARE_ONMSG(OnLButtonDBClick)
	DECLARE_ONMSG(OnLButtonDown)
	DECLARE_ONMSG(OnLButtonUp)
	DECLARE_ONMSG(OnRButtonDown)
	DECLARE_ONMSG(OnRButtonUp)
	DECLARE_ONMSG(OnMouseMove)
	DECLARE_ONMSG(OnMouseWheel)
	DECLARE_ONMSG(OnKeyDown)
	DECLARE_ONMSG(OnPaint)
	DECLARE_ONMSG(OnSize)

protected:
	static LRESULT CALLBACK NPWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	void DrawBorderSingle(CNPWndProc* pWnd);

	void FullScreen();

private:
	CNPWndProc		  m_VideoWnd[MAXCHANNEL];	//�ؼ����֧��9·�豸
	int				  m_iMaxWnd;		//��ǰ�豸���ͨ��֧������,m_iMaxWnd <= 9;ȡֵ 1,4,9
	short			  m_iCurMaxWnd;		//��ǰͨ��״̬;ȡֵ 1,4,6,8,9
	short			  m_iCurSelChannel;	//��ǰѡ��ͨ��
	short			  m_iWndStyle;		//��ǰWnd������ʽ
	short			  m_iFstChannel;    //ÿ����·���ڵĵ�һ���������
	HWND			  m_hParentWnd;
	HWND			  m_hSuperWnd;

	HINSTANCE		  m_hInstance;
	HPEN			  m_hBorderPen;
	HPEN			  m_hBorderPen2;
	BOOL			  m_bActScrProtection;
	bool			  m_bIsParentFullScreen;
	bool			  m_bIsChildFullScreen;
	bool			  m_bIsPolling;
	RECT			  m_rcWnd;
	RECT			  m_rcParentWnd;
	RECT			  m_rcChildWnd;
	RECT			  m_rcParentWndPos;
	RECT			  m_rcChildWndPos;

	CreateVarRiant			m_pVrCreate;
	DeleteVarRiant			m_pVrDelete;
	Int32ToVarRiant			m_pCvInt;
	StringToVarRiant		m_pCvString;
	InvokeJavaScriptFunc	m_jsCall;
	void*					m_pUserData;

	short			 m_nSelectWnd;
};
