#pragma once
#include "CVlc.h"
#include "AVDlg.h"
enum CVlcCommend {
	CVLC_PLAY,								//��ʼ����
	CVLC_PAUSE,								//��ͣ����
	CVLC_STOP,								//ֹͣ����
	CVLC_GET_VOLUME,						//��ȡ��������
	CVLC_GET_POSITON,						//��ȡ����λ��
	CVLC_GET_LENGTH							//��ȡ����ʱ����s��
};
class CVideoClientController
{
private:
	CVlc	m_vlc;							//����Ƶ(model)
	CAVDlg	m_dlg;							//�Ի���(view)
public:
	CVideoClientController();
	~CVideoClientController() = default;
	int		Init(CWnd*& pWnd);				//��ʼ��
	int		Invoke();						//���ô���
	int		SetMedia(std::string strUrl);	//����ý�岢���ò��Ŵ���
	float	VideoCtol(CVlcCommend cmd);		//ָ��ַ�
	void	SetPostion(float pos);			//���ò���λ��
	void	SetWnd(HWND hWnd);				//���û�
	void	SetVolume(int volume);			//���ò��ŵ�����
	CSize	GetMediaInfo();					//��ȡ����ý��Ŀ�/��
	int		SetRate(float rate);			//���ò����ٶ�
};
