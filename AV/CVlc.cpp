#include "pch.h"
#include "Vlc.h"
#include "CVlc.h"

CVlc::CVlc():m_instance(nullptr), m_media(nullptr), m_player(nullptr)
{
	int argc = 1;
	char* argv[2];
	argv[0] = (char*)"--ignore-config";//多字节转 Unicode，再转 utf-8
	argv[1] = nullptr;
	m_instance = libvlc_new(argc, argv);
	m_hWnd = nullptr;
	if (!m_instance)
		AfxMessageBox(L"libvlc_new失败");
}

CVlc::~CVlc()
{
	if (m_instance) {
		libvlc_release(m_instance);
		m_instance = nullptr;
	}
	if (m_media) {
		libvlc_media_release(m_media);
		m_media = nullptr;
	}
	if (m_player) {
		libvlc_media_player_release(m_player);
		m_player = nullptr;
	}
}

int CVlc::SetMedia(std::string strUrl)
{
	if (!m_instance) return -1;
	if (m_filePath == strUrl) return 0;
	m_filePath = strUrl;
	if (m_media) {
		libvlc_media_release(m_media);
		m_media = nullptr;
	}
	m_media = libvlc_media_new_location(m_instance, strUrl.c_str());
	if(!m_media) return -2;
	if (m_player) {
		libvlc_media_player_release(m_player);
		m_player = nullptr;
	}
	m_player = libvlc_media_player_new_from_media(m_media);
	if (!m_player) return -3;
	libvlc_media_player_set_hwnd(m_player, m_hWnd);
	return 0;
}

int CVlc::play()
{
	if (!m_instance || !m_player || !m_media) return -1;
	
	return libvlc_media_player_play(m_player);
}

void CVlc::SetHwnd(HWND hWnd)
{
	m_hWnd = hWnd;
}

int CVlc::Pause()
{
	if (!m_instance || !m_player || !m_media) return -1;
	libvlc_media_player_pause(m_player);
	return 0;
}

int CVlc::Stop()
{
	if (!m_instance || !m_player || !m_media) return -1;
	libvlc_media_player_stop(m_player);
	return 0;
}

float CVlc::GetPostion()
{
	if (!m_instance || !m_player || !m_media) return -1;
	return libvlc_media_player_get_position(m_player);
}

void CVlc::SetPostion(float pos)
{
	if (!m_instance || !m_player || !m_media) return;
	libvlc_media_player_set_position(m_player, pos);
}

int CVlc::GetVolume()
{
	if (!m_instance || !m_player || !m_media) return -1;
	return libvlc_audio_get_volume(m_player);
}

int CVlc::SetVolume(int volume)
{
	if (!m_instance || !m_player || !m_media) return -1;
	return libvlc_audio_set_volume(m_player, volume);
}

CSize CVlc::GetMediaInfo()
{
	CSize sz(-1, -1);
	if (!m_instance || !m_player || !m_media) return sz;
	sz.cx = libvlc_video_get_width(m_player);
	sz.cy = libvlc_video_get_height(m_player);
	return sz;
}

int64_t CVlc::GetLength()
{
	if (!m_instance || !m_player || !m_media) return -1;
	return libvlc_media_player_get_length(m_player) / 1000;
}

int CVlc::SetRate(float _rate)
{
	static float rate = 1.0f;
	if (!m_instance || !m_player || !m_media) return -1;
	if (rate == _rate) return 0;
	//float a = libvlc_media_player_get_rate(m_player);
	libvlc_media_player_set_rate(m_player, _rate);
	rate = _rate;
	return 0;
}
