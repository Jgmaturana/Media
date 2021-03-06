/***********************************************************************************************************************
Copyright:  
FileName: Lock.cpp   
Author:        Version :          Date:   
Description:    
Version:         
Function List:    
History:               
<author>   <time>   <version >   <desc>       
 ------    14/26/8   1.0.0.0     build this file 
************************************************************************************************************************/
#include "Lock.h"

/***********************************************************************************************************************
Function:  CLock
Description:   
Called By:    
Input:          
Output:          
Return:       
Others:        
************************************************************************************************************************/
CLock::CLock()
{
	LOCK_INIT(m_Handle); 
}

/***********************************************************************************************************************
Function:  ~CLock
Description:   
Called By:    
Input:          
Output:          
Return:       
Others:        
************************************************************************************************************************/
CLock::~CLock()
{
	LOCK_DESTROY(m_Handle);
}

/***********************************************************************************************************************
Function:  Inc
Description:   
Called By:    
Input:          
Output:          
Return:       
Others:        
************************************************************************************************************************/
Void CLock::Inc()
{
	Lock();
}

/***********************************************************************************************************************
Function:  Dec
Description:   
Called By:    
Input:          
Output:          
Return:       
Others:        
************************************************************************************************************************/
Void CLock::Dec()
{
	Unlock();
}

/***********************************************************************************************************************
Function:  Lock
Description:   
Called By:    
Input:          
Output:          
Return:       
Others:        
************************************************************************************************************************/
Void CLock::Lock()
{
	LOCK_LOCK(m_Handle);
}

/***********************************************************************************************************************
Function:  Unlock
Description:   
Called By:    
Input:          
Output:          
Return:       
Others:        
************************************************************************************************************************/
Void CLock::Unlock()
{
	LOCK_UNLOCK(m_Handle);
}

/***********************************************************************************************************************
Function:  GetHandle
Description:   
Called By:    
Input:          
Output:          
Return:       
Others:        
************************************************************************************************************************/
lkHandle_t &CLock::GetHandle()
{
	return m_Handle;
}
