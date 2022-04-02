#pragma once
#include "CVlc.h"
#include "AVDlg.h"
enum CVlcCommend {
	CVLC_PLAY,								//开始播放
	CVLC_PAUSE,								//暂停播放
	CVLC_STOP,								//停止播放
	CVLC_GET_VOLUME,						//获取播放音量
	CVLC_GET_POSITON,						//获取播放位置
	CVLC_GET_LENGTH							//获取播放时长（s）
};
class CVideoClientController
{
private:
	CVlc	m_vlc;							//音视频(model)
	CAVDlg	m_dlg;							//对话框(view)
public:
	CVideoClientController();
	~CVideoClientController() = default;
	int		Init(CWnd*& pWnd);				//初始化
	int		Invoke();						//调用窗口
	int		SetMedia(std::string strUrl);	//加载媒体并设置播放窗口
	float	VideoCtol(CVlcCommend cmd);		//指令分发
	void	SetPostion(float pos);			//设置播放位置
	void	SetWnd(HWND hWnd);				//设置基
	void	SetVolume(int volume);			//设置播放的音量
	CSize	GetMediaInfo();					//获取播放媒体的宽/高
	int		SetRate(float rate);			//设置播放速度
};
