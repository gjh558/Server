#pragma once
#include "afxsock.h"
#include "ffmpeg/include/avformat.h"


#define INBUF_SIZE 4096

class CVideo : public CAsyncSocket
{
public:

	CVideo();
	CVideo(CWnd *win);
	~CVideo(void);
public:
	virtual void OnConnect(int nErrorCode);
	virtual void OnClose(int nErrorCode);
	virtual void OnSend(int nErrorCode);
	virtual void OnReceive(int nErrorCode);
public:
	//CSensorTab *m_pSensorTab;
	unsigned char inbuf[INBUF_SIZE];
	
	void showVideo(unsigned char *buf, int size);
	void closeVideo();
	void initFFMPEG();
	void closeFFMPEG();
	void BitMapInfoInit(PBITMAPINFO pBitmapInfo,LONG BitmapWidth, LONG BitmapHeight);
	void PicChange(unsigned char *picbuffer,unsigned char *outbuff,int width,int height);
	void DisplayPicture(unsigned char *dis_buf,int dis_width,int dis_height);
	
public:
	
	AVCodec *codec;//#####
	AVCodecContext *pCodecCtx;//#####
	int frame, got_picture, len;
	AVFrame *picture;//#####
	AVFrame *pFrameRGB;//#####
	int     numBytes ;
	uint8_t *buffer;
	unsigned char* mdisplayBuffer;

	HDRAWDIB mDrawDib;
	CWnd *m_pPlayCwnd;
	
};

