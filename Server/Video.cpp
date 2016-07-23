#include "StdAfx.h"
#include "Phone.h"
#include "VideoView.h"
#include "Resource.h"
#include "PhoneWindow.h"

FILE *fp_b;

CVideo::CVideo()
	//:buffer(NULL)
{
	//m_pSensorTab = pSensorTab;
	memset(inbuf,0,(INBUF_SIZE));
	// set end of buffer to 0 (this ensures that no overreading happens 
	// for damaged mpeg streams)
	//memset(inbuf + INBUF_SIZE, 0, FF_INPUT_BUFFER_PADDING_SIZE);

	//mPlayCwnd = pSensorTab->GetDlgItem(IDC_STATIC_VIDEO);
	//mdisplayBuffer = NULL;
	//mDrawDib  = DrawDibOpen();
	_wfopen_s(&fp_b, _T("D:/1.h264"), _T("wb+"));
	//initFFMPEG();
}

CVideo::CVideo(CWnd *win)
	:buffer(NULL),
	m_pPlayCwnd(win)
{
	//show video view dialog
	CRect rect;
	m_pPlayCwnd->GetClientRect(&rect);

	CVideoView *pView = new CVideoView(m_pPlayCwnd);

	pView->Create(IDD_DIALOG1, m_pPlayCwnd);
	pView->MoveWindow(rect);
	pView->ShowWindow(SW_SHOW);
	m_pPlayCwnd = pView->GetDlgItem(IDC_STATIC_SHOW);

	//m_pSensorTab = pSensorTab;
	memset(inbuf,0,(INBUF_SIZE));
	// set end of buffer to 0 (this ensures that no overreading happens 
	// for damaged mpeg streams)
	//memset(inbuf + INBUF_SIZE, 0, FF_INPUT_BUFFER_PADDING_SIZE);

	//mPlayCwnd = pSensorTab->GetDlgItem(IDC_STATIC_VIDEO);
	mdisplayBuffer = NULL;
	mDrawDib  = DrawDibOpen();
	_wfopen_s(&fp_b, _T("D:/1.h264"), _T("wb+"));
	initFFMPEG();
}

CVideo::CVideo(PhoneWindow *p)
	:m_pPhoneWindow(p)
{
	canShow = FALSE;
	m_pPlayCwnd = p->m_pWnd;
	memset(inbuf,0,(INBUF_SIZE));
	// set end of buffer to 0 (this ensures that no overreading happens 
	// for damaged mpeg streams)
	//memset(inbuf + INBUF_SIZE, 0, FF_INPUT_BUFFER_PADDING_SIZE);

	//mPlayCwnd = pSensorTab->GetDlgItem(IDC_STATIC_VIDEO);
	mdisplayBuffer = NULL;
	mDrawDib  = DrawDibOpen();
	//_wfopen_s(&fp_b, _T("D:/1.h264"), _T("wb+"));
	initFFMPEG();
}

CVideo::~CVideo(void)
{
	
	fclose(fp_b);
	if (buffer != NULL)
	{
		delete [] buffer;
	}

	if (mdisplayBuffer != NULL)
	{
		free(mdisplayBuffer);
	}
	closeFFMPEG();
	
}

void CVideo::OnConnect(int nErrorCode)
{
	if (nErrorCode == 0)
	{
	}
	else
	{
	}

	CAsyncSocket::OnConnect(nErrorCode);
}


void CVideo::OnClose(int nErrorCode)
{
	m_pPhoneWindow->state = FREE;
	//TODO: Send Message to VideoServer to notify it the window is free now, and you can assign this window to other MVideo


	this->Close();
	CAsyncSocket::OnClose(nErrorCode);
}

void CVideo::OnSend(int nErrorCode)
{
	//InternalSend ();
	CAsyncSocket::OnSend(nErrorCode);
}


void CVideo::OnReceive(int nErrorCode)
{
	// TODO: 在此添加专用代码和/或调用基类
	if (nErrorCode == 0)
	{
		int nReceived = Receive(inbuf, INBUF_SIZE);
		if (nReceived == SOCKET_ERROR)
		{
			if (GetLastError() != WSAEWOULDBLOCK)
			{

				//////  TODO: Terminate The Connection  /////
				closeVideo();	
			}
		}
		//if(m_pSensorTab->isShowVideo)
		//{
			unsigned char *inbuf_ptr = inbuf;
			//fwrite(inbuf_ptr, 1, nReceived, fp_b);
			if (canShow) {
				showVideo(inbuf_ptr, nReceived);
			}else {
				TRACE("no enough window to show this phone\n");
			}
		//}
	}
	CAsyncSocket::OnReceive(nErrorCode);
}

void CVideo::showVideo(unsigned char *buf, int size)
{
	
	while (size > 0)
	{
		// 处理接收的指令
		int len = avcodec_decode_video(pCodecCtx, picture, &got_picture, buf, size);
		if (len < 0) {
			fprintf(stderr, "Error while decoding frame %d\n", frame);
			//exit(1);
		}
		if (got_picture)
		{
			picture->data[0] += picture->linesize[0] * (pCodecCtx->height - 1);
			picture->linesize[0] = -picture->linesize[0];
			picture->data[1]+= picture->linesize[1] * (pCodecCtx->height / 2 - 1);
			picture->linesize[1] = -picture->linesize[1];
			picture->data[2] += picture->linesize[2]* (pCodecCtx->height / 2 - 1);
			picture->linesize[2] = -picture->linesize[2];
			printf("saving frame %3d\n", frame);                           
			frame++;

			// Determine required buffer size and allocate buffer
			if(numBytes==0)
			{
				numBytes=avpicture_get_size(PIX_FMT_RGB24, pCodecCtx->width,
					pCodecCtx->height);

				if (buffer != NULL)
				{
					delete [] buffer;
				}

				buffer=new uint8_t[numBytes];
				// Assign appropriate parts of buffer to image planes in pFrameRGB
				avpicture_fill((AVPicture *)pFrameRGB, buffer, PIX_FMT_RGB24,
					pCodecCtx->width, pCodecCtx->height);
			}
			int ret = img_convert((AVPicture *)pFrameRGB, PIX_FMT_BGR24, (AVPicture*)picture, 
				pCodecCtx->pix_fmt, pCodecCtx->width, pCodecCtx->height);
			DisplayPicture(pFrameRGB->data[0],pCodecCtx->width, pCodecCtx->height);// --> surfaceflinger
			
		}
		size -= len;
		buf += len;
	}
}

void CVideo::closeVideo()
{
	Close();
}

void CVideo::initFFMPEG()
{
	frame=0;
	got_picture=0;
	len=0;
	numBytes = 0;

	av_register_all();//#####
	pFrameRGB=avcodec_alloc_frame();//#####
	if(pFrameRGB==NULL)
		TRACE("pFrame error ...");

	codec = avcodec_find_decoder(CODEC_ID_H264);//#####CODEC_ID_H264
	if (!codec) {
		fprintf(stderr, "codec not found\n");
	}

	pCodecCtx= avcodec_alloc_context();//#####
    picture= avcodec_alloc_frame();//#####

	// we dont send complete frames 
    if(codec->capabilities&CODEC_CAP_TRUNCATED)//#####
        pCodecCtx->flags|= CODEC_FLAG_TRUNCATED; //#####

    /* for some codecs, such as msmpeg4 and mpeg4, width and height
       MUST be initialized there because these info are not available
       in the bitstream */

	// open it 
    if (avcodec_open(pCodecCtx, codec) < 0) {//#####
        fprintf(stderr, "could not open codec\n");
    }
}

void CVideo::closeFFMPEG()
{
	avcodec_close(pCodecCtx);//#####
	av_free(pCodecCtx);//#####
	av_free(picture);//#####
}


void CVideo::DisplayPicture(unsigned char *dis_buf,int dis_width,int dis_height)
{
	CRect  rc;
	//CWnd *mPlayCWnd = p_SensorTab->GetDlgItem(IDC_STATIC_VIDEO);
	CDC *pdc = m_pPlayCwnd->GetDC();
	HDC hdc = pdc->GetSafeHdc();

	m_pPlayCwnd->GetClientRect(&rc);

	BITMAPINFO BmpInfo;
	BitMapInfoInit(&BmpInfo,dis_width,dis_height);

	if(mdisplayBuffer == NULL)
	{
		//mdisplayBuffer = (unsigned char *)malloc(3*dis_width*dis_height);
	}

	//PicChange(dis_buf,mdisplayBuffer,dis_width,dis_height);

	DrawDibDraw(mDrawDib,hdc,rc.left,
		rc.top,
		rc.Width(),
		rc.Height(),
		&BmpInfo.bmiHeader, dis_buf,0,0,dis_width,dis_height,0);

	m_pPlayCwnd->ReleaseDC(pdc);
	printf("display frame  %d\n\n",GetTickCount());

}

void CVideo::BitMapInfoInit(PBITMAPINFO pBitmapInfo,LONG BitmapWidth, LONG BitmapHeight)
{
	pBitmapInfo->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	pBitmapInfo->bmiHeader.biWidth =BitmapWidth;
	pBitmapInfo->bmiHeader.biHeight = BitmapHeight;
	pBitmapInfo->bmiHeader.biPlanes =1;
	pBitmapInfo->bmiHeader.biBitCount = 24;
	pBitmapInfo->bmiHeader.biCompression = BI_RGB;
	pBitmapInfo->bmiHeader.biSizeImage = 0;
	pBitmapInfo->bmiHeader.biClrUsed = 0;
	pBitmapInfo->bmiHeader.biClrImportant = 0;
}

void CVideo::PicChange(unsigned char *picbuffer,unsigned char *outbuff,int width,int height)
{
	int i;
	int d = 0;
	int s;

	int newheight = height;
	int newwidth = width;

	for(i=0;i<newheight;i++)
	{
		for(int j=0;j<newwidth;j++)
		{
			s = ((height-i) *width + j)*3;
			outbuff[d++] = picbuffer[s++];
			outbuff[d++] = picbuffer[s++];
			outbuff[d++] = picbuffer[s++];
		}
	}
	
}

void CVideo::show()
{
	canShow = TRUE;
}