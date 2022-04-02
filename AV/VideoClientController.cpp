#include "pch.h"
#include "VideoClientController.h"

CVideoClientController::CVideoClientController()
{
	m_dlg.m_controller = this;
}

int CVideoClientController::Init(CWnd*& pWnd)
{
    pWnd = &m_dlg;
    return 0;
}

int CVideoClientController::Invoke()
{
	INT_PTR nResponse = m_dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: �ڴ˷��ô����ʱ��
		//  ��ȷ�������رնԻ���Ĵ���
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: �ڴ˷��ô����ʱ��
		//  ��ȡ�������رնԻ���Ĵ���
	}
	else if (nResponse == -1)
	{
		TRACE(traceAppMsg, 0, "����: �Ի��򴴽�ʧ�ܣ�Ӧ�ó���������ֹ��\n");
		TRACE(traceAppMsg, 0, "����: ������ڶԻ�����ʹ�� MFC �ؼ������޷� #define _AFX_NO_MFC_CONTROLS_IN_DIALOGS��\n");
	}
    return nResponse;
}

int CVideoClientController::SetMedia(std::string strUrl)
{
    return m_vlc.SetMedia(strUrl);
}

float CVideoClientController::VideoCtol(CVlcCommend cmd)
{
	switch (cmd)
	{
	case CVLC_PLAY:
		return m_vlc.play();
	case CVLC_PAUSE:
		return m_vlc.Pause();
	case CVLC_STOP:
		return m_vlc.Stop();
	case CVLC_GET_VOLUME:
		return m_vlc.GetVolume();
	case CVLC_GET_POSITON:
		return m_vlc.GetPostion();
	case CVLC_GET_LENGTH:
		return m_vlc.GetLength();
	default:
		break;
	}
    return -1.0f;
}

void CVideoClientController::SetPostion(float pos)
{
	m_vlc.SetPostion(pos);
}

void CVideoClientController::SetWnd(HWND hWnd)
{
	m_vlc.SetHwnd(hWnd);
}

void CVideoClientController::SetVolume(int volume)
{
	if (m_vlc.SetVolume(volume) == -1) {
		CString str;
		str.Format(_T("FileName:%s\nLine:%d\nFunctionName:%s\n"), __FILE__, __LINE__, __FUNCTION__);
		AfxMessageBox(str);
	}
}

CSize CVideoClientController::GetMediaInfo()
{
    return m_vlc.GetMediaInfo();
}

int CVideoClientController::SetRate(float rate)
{
	return m_vlc.SetRate(rate);
}
