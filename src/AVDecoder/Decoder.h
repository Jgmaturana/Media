#pragma once
#include "MediaConvent.h"
#include "g726/g726.h"
#include "../AACCodec/AACDecodeImpl.h"

class CDecoder
{
public:
	CDecoder(void);
	~CDecoder(void);

	bool SetDecoder(int type, FSDECORD_CB cb, void* userdata);
	void UnRegisterDecoder(int type);

	bool ResetDecoder();

	char* GetYUV420Buffer(char* data, int lenght);
	char* GetPCMBuffer(char* data, int lenght, int& newLength);

	bool SetResolution(int nWidth, int nHeight);
protected:
	char* (CDecoder::*GetYUV420Data)(char* data, int lenght);
	char* (CDecoder::*GetPCMData)(char* data, int lenght, int& newLength);

	char* H2642YUV420(char* data, int lenght);
	char* MJPG2YUV420(char* data, int lenght);

	char* ADPCM2PCM(char* data, int lenght, int& newLength);
	char* G7262PCM(char* data, int lenght, int& newLength);
	char* PCM2PCM(char* data, int lenght, int& newLength);

	char* AAC2PCM(char* data, int length, int& newLength);

private:
	FSDECORD_CB m_audioCb;
	FSDECORD_CB m_videoCb;

	/*�������*/
	MediaConvert *_cvt;
	FRAME_PER	_frame;
	int		_height;
	int		_width;

	char*   m_audioBuf;
	int		m_audioBufSize;

	void* m_userdata;

	bool	m_bResetDecord;
	CRITICAL_SECTION m_cri;

	//��Ƶ-aac �������
	CAACDecoder* m_pAac;
	WAVEFORMATEX m_wfx;
	int	 m_nChannels;						//���� 1��������  2��������
	int m_wBitsPerSample;				//16λ
	int m_nSamplesPerSec;			//������, 44100HZ
};
