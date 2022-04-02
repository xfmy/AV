
// AVDlg.h: 头文件
//

#pragma once
extern class CVideoClientController;
#define FILETYPE L"file:///"
// CAVDlg 对话框
class CAVDlg : public CDialogEx
{
// 构造
public:
	CAVDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_AV_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	// 视频播放控件
	CEdit m_play;
	// 视频滚动条
	CSliderCtrl m_pos;
	// 音响调节
	CSliderCtrl m_volume;
	CEdit m_url;
	afx_msg void OnBnClickedBtnPlay();
	afx_msg void OnBnClickedBtnStop();
	afx_msg void OnBnClickedBtnSelectFile();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	// 播放按钮
	CButton m_playBtn;
	//是否正在播放
	bool m_isPlay = false;
	CString m_filePath;
	CVideoClientController* m_controller;
	afx_msg void OnDestroy();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnCbnSelchangeCombo1();
	// 下拉框
	CComboBox m_dropDownBox;
	CComboBox m_fileType;
	afx_msg void OnCbnSelchangeComboFileType();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton1();
};
