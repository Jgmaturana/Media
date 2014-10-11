#ifndef __INIFILE_H__
#define __INIFILE_H__

#include <Windows.h>

class CIniFile    
{    
public:    
	CIniFile();
	CIniFile(LPCTSTR szFileName);
	virtual ~CIniFile();    

public:    
	// Attributes  
	void SetFileName(LPCTSTR szFileName);
public:    
	// Operations  
	BOOL SetProfileInt(LPCTSTR lpszSectionName, LPCTSTR lpszKeyName, int nKeyValue);    

	BOOL SetProfileString(LPCTSTR lpszSectionName, LPCTSTR lpszKeyName, LPCTSTR lpszKeyValue);  

	int GetProfileInt(LPCTSTR lpszSectionName, LPCTSTR lpszKeyName);    
	DWORD GetProfileString(LPCTSTR lpszSectionName, LPCTSTR lpszKeyName, TCHAR* szKeyValue);    

	BOOL DeleteSection(LPCTSTR lpszSectionName); 
	BOOL DeleteKey(LPCTSTR lpszSectionName, LPCTSTR lpszKeyName);

private:    
	TCHAR m_szFileName[MAX_PATH]; // .//Config.ini, ������ļ������ڣ���exe��һ����ͼWriteʱ���������ļ�     
	
	UINT m_unMaxSection; // ���֧�ֵ�section��(256)     
	
	UINT m_unSectionNameMaxSize; // section���Ƴ��ȣ�������Ϊ32(Null-terminated)     
	void Init();
};    


#endif //#define __INIFILE_H__
