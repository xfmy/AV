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
	int		SetMedia(std::string strUrl);	//����ý�岢���ò��Ŵ���
	int		play();							//��ʼ����
	void	SetHwnd(HWND hWnd);				//���ò��Ŵ���
	int		Pause();						//��ͣ����
	int		Stop();							//ֹͣ����
	float	GetPostion();					//��ȡ����λ��
	void	SetPostion(float pos);			//���ò���λ��
	int		GetVolume();					//��ȡ��������
	int		SetVolume(int volume);			//���ò��ŵ�����
	CSize	GetMediaInfo();					//��ȡ����ý��Ŀ�/��
	int64_t GetLength();					//��ȡ��Ƶ���ȣ���λ���룩
	int		SetRate(float _rate);			//���ò����ٶ�
private:
	libvlc_instance_t*		m_instance;		//ʵ��
	libvlc_media_t*			m_media;		//ý��
	libvlc_media_player_t*	m_player;		//������
	std::string				m_filePath;		//�ļ�·��
	HWND					m_hWnd;			
};

