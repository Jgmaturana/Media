#include "WavePlay.h"

#include <mmsystem.h>
#include <stdio.h>
#include <string.h>

#define BLOCK_SIZE  8192
#define BLOCK_COUNT 20

#define BLOCK_MAX 8192


//�ص�����
//���ѡ�񴰿ڽ��ܻص���Ϣ, ���ܻᷢ�͵����ڵ���Ϣ��:
//MM_WOM_OPEN  = $3BB;
// MM_WOM_CLOSE = $3BC;
// MM_WOM_DONE  = $3BD;

// ���ѡ�������ܻص���Ϣ, ���ܻᷢ�͸���������Ϣ��:
// WOM_OPEN  = MM_WOM_OPEN;
// WOM_CLOSE = MM_WOM_CLOSE;
// WOM_DONE  = MM_WOM_DONE;
void CALLBACK callback_waveOutProc( HWAVEOUT hwo, UINT uMsg, DWORD dwInstance, DWORD dwParam1, DWORD dwParam2 ) 
{ 
    /*
     * ���Դ򿪹ر��豸����
     */
    if(uMsg != WOM_DONE)
        return;
	CWavePlay* pThis=(CWavePlay*)dwInstance;
	if (NULL==pThis)
	{
		return;
	}
	pThis->WaveMsg(hwo,uMsg,dwParam1,dwParam2);
	return;
} 

CWavePlay::CWavePlay(void)
{
	m_bPalyState = false; 
	ZeroMemory(&m_wavformex,sizeof(WAVEFORMATEX)); 
	_waveBlocks          = NULL;
	_nWaveFreeBlockCount = 0;
	_nWaveCurrentBlock   = 0;

	InitializeCriticalSection(&_waveCriticalSection);
}

//�ر��̣߳��ͷ���Դ
CWavePlay::~CWavePlay(void)
{
	CloseDevice();
	DeleteCriticalSection(&_waveCriticalSection);
}

bool CWavePlay::CloseDevice()
{
	ZeroMemory(&m_wavformex,sizeof(WAVEFORMATEX)); 

	 while(_nWaveFreeBlockCount != 0 && _nWaveFreeBlockCount < BLOCK_COUNT)
        Sleep(10);

    /*
     * unprepare any blocks that are still prepared
     */
    for(int i = 0; i < _nWaveFreeBlockCount; i++)
	{
        if(_waveBlocks && _waveBlocks[i].dwFlags & WHDR_PREPARED)
		{
            waveOutUnprepareHeader(m_hWaveOut, &_waveBlocks[i], sizeof(WAVEHDR));
		}
	}
	if(_waveBlocks)
	{
		freeBlocks(_waveBlocks);
		_waveBlocks = NULL;
	}
	waveOutClose(m_hWaveOut);
	m_bPalyState = false; 
	return true;
}

bool CWavePlay::Start(PWAVEFORMATEX pWavHead) 
{ 
	if (m_bPalyState) 
	{
		return false;
	}
	if (NULL==pWavHead)
	{
		return false;
	}
	//CloseDevice();
	_waveBlocks = allocateBlocks(BLOCK_SIZE, BLOCK_COUNT);
	_nWaveFreeBlockCount = BLOCK_COUNT;
	_nWaveCurrentBlock   = 0;
	memcpy(&m_wavformex,pWavHead,sizeof(WAVEFORMATEX));
	m_wavformex.nBlockAlign     = (m_wavformex.wBitsPerSample * m_wavformex.nChannels) >> 3;
	m_wavformex.nAvgBytesPerSec = m_wavformex.nBlockAlign * m_wavformex.nSamplesPerSec;

	if(::waveOutOpen (0,0,&m_wavformex,0,0,WAVE_FORMAT_QUERY)) //WAVE_FORMAT_QUERY = $0001;{ֻ���ж��豸�Ƿ�֧�ָ����ĸ�ʽ, ������}
	{ 
		//TRACE_ERR2("wave�豸��ʼ��ʧ�ܡ�"); 
		return false; 
	} 

	//lphWaveOut: PHWaveOut;   {���ڷ����豸�����ָ��; ��� dwFlags=WAVE_FORMAT_QUERY, ����Ӧ�� nil}
	//uDeviceID: UINT;         {�豸ID; ����ָ��Ϊ: WAVE_MAPPER, ������������ݸ����Ĳ��θ�ʽѡ����ʵ��豸}
	//lpFormat: PWaveFormatEx; {TWaveFormat �ṹ��ָ��; TWaveFormat ����Ҫ����Ĳ��θ�ʽ}
	//dwCallback: DWORD        {�ص�������ַ�򴰿ھ��; ����ʹ�ûص�����, ��Ϊ nil}
	//dwInstance: DWORD        {���ص�������ʵ������; �����ڴ���}
	//dwFlags: DWORD           {��ѡ��}
	if(waveOutOpen(&m_hWaveOut, WAVE_MAPPER, &m_wavformex, (DWORD_PTR)callback_waveOutProc, (DWORD)this, CALLBACK_FUNCTION) != MMSYSERR_NOERROR) 
	{
		 //TRACE_ERR2("wave�豸��ʧ�ܡ�"); 
		 return false;
	}
	m_bPalyState    = true;
	_nWaveCurrentBlock   = 0;
	return true;
} 


void CWavePlay::WaveMsg(HWAVEOUT hwo, UINT uMsg, DWORD dwParam1, DWORD dwParam2) 
{
	EnterCriticalSection(&_waveCriticalSection);
	_nWaveFreeBlockCount++;
	LeaveCriticalSection(&_waveCriticalSection);
	return;
}

void CWavePlay::PlayAudio(LPSTR data, int size)
{
	if (!m_bPalyState) 
		return ; 

    WAVEHDR* current;
    int remain;

    current = &_waveBlocks[_nWaveCurrentBlock];
	if(current == NULL)
		return;
    
    while(size > 0) {
        /* 
         * ����ȷ��ʹ�õ�header �� unprepared
         */
        if(current->dwFlags & WHDR_PREPARED) 
            waveOutUnprepareHeader(m_hWaveOut, current, sizeof(WAVEHDR));

        if(size < (int)(BLOCK_SIZE - current->dwUser)) {
            memcpy(current->lpData + current->dwUser, data, size);
            current->dwUser += size;
            break;
        }

        remain = BLOCK_SIZE - current->dwUser;
        memcpy(current->lpData + current->dwUser, data, remain);
        size -= remain;
        data += remain;
        current->dwBufferLength = BLOCK_SIZE;
       
        waveOutPrepareHeader(m_hWaveOut, current, sizeof(WAVEHDR));
        waveOutWrite(m_hWaveOut, current, sizeof(WAVEHDR));
        
        EnterCriticalSection(&_waveCriticalSection);
        _nWaveFreeBlockCount--;
        LeaveCriticalSection(&_waveCriticalSection);
        
        /*
         * �ȴ�freeһ��block
         */
        while(!_nWaveFreeBlockCount)
            Sleep(10);

        /*
         * ָ����һ��block
         */
        _nWaveCurrentBlock++;
        _nWaveCurrentBlock %= BLOCK_COUNT;

        current = &_waveBlocks[_nWaveCurrentBlock];
        current->dwUser = 0;
    }
}


WAVEHDR* CWavePlay::allocateBlocks(int size, int count)
{
	unsigned char* buffer;
	WAVEHDR* blocks;
	DWORD totalBufferSize = (size + sizeof(WAVEHDR)) * count;

	if((buffer = (unsigned char*)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, totalBufferSize)) == NULL) 
	{
		fprintf(stderr, "Memory allocation error\n");
		ExitProcess(1);
	}
	blocks = (WAVEHDR*)buffer;
	buffer += sizeof(WAVEHDR) * count;
	for(int i = 0; i < count; i++) {
		blocks[i].dwBufferLength = size;
		blocks[i].lpData = (LPSTR)buffer;
		buffer += size;
	}

	return blocks;
}

void CWavePlay::freeBlocks(WAVEHDR* blockArray)
{
	HeapFree(GetProcessHeap(), 0, blockArray);
}

BOOL CWavePlay::OpenDev(int nSamplesPerSec, int nChannels, int nBitPerSample)
{
	WAVEFORMATEX wfmt;
	wfmt.nSamplesPerSec = nSamplesPerSec; //44100;
	wfmt.wBitsPerSample = nBitPerSample; //16
	wfmt.nChannels = nChannels; //2
	wfmt.cbSize = 0;
	wfmt.wFormatTag = WAVE_FORMAT_PCM;
	wfmt.nBlockAlign = (wfmt.wBitsPerSample * wfmt.nChannels) >> 3;
	wfmt.nAvgBytesPerSec = wfmt.nBlockAlign * wfmt.nSamplesPerSec;

	return Start(&wfmt);
}

BOOL CWavePlay::PlayData(unsigned char* buf, int size)
{
	PlayAudio((LPSTR)buf, size);
	return TRUE;
}

BOOL CWavePlay::CloseDev()
{
	return CloseDevice();
}