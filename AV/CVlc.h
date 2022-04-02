#pragma once
#include <string>
#include <pch.h>
#include "vlc.h"
#include <conio.h>
#pragma comment(lib , "libvlc.lib")
#pragma comment(lib , "libvlccore.lib")

class CVlc
{
public:
	CVlc();
	~CVlc();
	int		SetMedia(std::string strUrl);	//加载媒体并设置播放窗口
	int		play();							//开始播放
	void	SetHwnd(HWND hWnd);				//设置播放窗口
	int		Pause();						//暂停播放
	int		Stop();							//停止播放
	float	GetPostion();					//获取播放位置
	void	SetPostion(float pos);			//设置播放位置
	int		GetVolume();					//获取播放音量
	int		SetVolume(int volume);			//设置播放的音量
	CSize	GetMediaInfo();					//获取播放媒体的宽/高
	int64_t GetLength();					//获取视频长度（单位：秒）
	int		SetRate(float _rate);			//设置播放速度
private:
	libvlc_instance_t*		m_instance;		//实例
	libvlc_media_t*			m_media;		//媒体
	libvlc_media_player_t*	m_player;		//播放器
	std::string				m_filePath;		//文件路径
	HWND					m_hWnd;			
};

