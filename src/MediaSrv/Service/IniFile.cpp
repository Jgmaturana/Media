#include "IniFile.h"
#include <tchar.h>


void CIniFile::Init()
{    
	m_unMaxSection = 512;
	m_unSectionNameMaxSize = 33; // 32λUID��
}    

CIniFile::CIniFile() 
{    
	Init();
}    

CIniFile::CIniFile(LPCTSTR szFileName)  
{    
	// (1) ����·���������·���Ƿ����
	// (2) ��"./"��ͷ������������·���Ƿ����
	// (3) ��"../"��ͷ�����漰���·���Ľ���
	
	Init();    
	
	// ���·��
	wcscpy(m_szFileName, szFileName);
}    


CIniFile::~CIniFile()
{ 

}  

DWORD CIniFile::GetProfileString(LPCTSTR lpszSectionName, LPCTSTR lpszKeyName, TCHAR* szKeyValue)    
{    
	DWORD dwCopied = 0; 
	dwCopied = ::GetPrivateProfileString(lpszSectionName, lpszKeyName, _T(""), szKeyValue, MAX_PATH, (LPCWSTR)m_szFileName);
	return dwCopied;
}

int CIniFile::GetProfileInt(LPCTSTR lpszSectionName, LPCTSTR lpszKeyName)
{    
	int nKeyValue = ::GetPrivateProfileInt(lpszSectionName, lpszKeyName, 0, (LPCWSTR)m_szFileName);    
	return nKeyValue; 
}

BOOL CIniFile::SetProfileString(LPCTSTR lpszSectionName, LPCTSTR lpszKeyName, LPCTSTR lpszKeyValue) 
{    
	return ::WritePrivateProfileString(lpszSectionName, lpszKeyName, lpszKeyValue, (LPCWSTR)m_szFileName);
}    

BOOL CIniFile::SetProfileInt(LPCTSTR lpszSectionName, LPCTSTR lpszKeyName, int nKeyValue)    
{    
	TCHAR szKeyValue[20] = {0};
	_itot(nKeyValue, szKeyValue, 10);
	return ::WritePrivateProfileString(lpszSectionName, lpszKeyName, szKeyValue, (LPCWSTR)m_szFileName);    
}   

BOOL CIniFile::DeleteSection(LPCTSTR lpszSectionName)
{    
	return ::WritePrivateProfileSection(lpszSectionName, NULL, (LPCWSTR)m_szFileName);    
}    

BOOL CIniFile::DeleteKey(LPCTSTR lpszSectionName, LPCTSTR lpszKeyName)
{   
	return ::WritePrivateProfileString(lpszSectionName, lpszKeyName, NULL, (LPCWSTR)m_szFileName);    
}    
