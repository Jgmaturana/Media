// stdafx.h : ��׼ϵͳ�����ļ��İ����ļ���
// ���Ǿ���ʹ�õ��������ĵ�
// �ض�����Ŀ�İ����ļ�
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // �� Windows ͷ���ų�����ʹ�õ�����

#ifndef ASSERT
#include <assert.h>
#define ASSERT assert
#endif

// TODO: �ڴ˴����ó�����Ҫ������ͷ�ļ�
#include <Windows.h>
#include <windowsx.h>
#include <tchar.h>

#include <iostream>
using namespace std;

#define INT32_TO_VARIANT(_val, _v)  \
	(_v).vt = VT_I4;                                         \
	(_v).lVal = _val

#define STRINGZ_TO_VARIANT(_val, _v)                    \
	(_v).vt =VT_BSTR;                                         \
	(_v).bstrVal = _com_util::ConvertStringToBSTR(_val)

#include "NPWnd.h"
#include "NPWndProc.h"
#include "Glue.h"
#include "../wellLog/Log.h"
#pragma comment(lib, "../../lib/wellLog.lib")

#include "../../include/stdint.h"
#include "../../include/typeinfo.h"
