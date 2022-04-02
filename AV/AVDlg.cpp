
// AVDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "AV.h"
#include "AVDlg.h"
#include "afxdialogex.h"
#include "VideoClientController.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

std::string Unicode2Utf8(const std::wstring& strIn)
{
	std::string str;
	int length = ::WideCharToMultiByte(CP_UTF8, 0, strIn.c_str(), strIn.size(), NULL, 0, NULL, NULL);
	str.resize(length + 1);
	::WideCharToMultiByte(CP_UTF8, 0, strIn.c_str(), strIn.size(), (LPSTR)str.c_str(), length, NULL, NULL);
	return str;
}

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CAVDlg 对话框



CAVDlg::CAVDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_AV_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	//m_vlc = nullptr;
}

void CAVDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_PLAY, m_play);
	DDX_Control(pDX, IDC_SLIDER_POS, m_pos);
	DDX_Control(pDX, IDC_SLIDER_VOLUME, m_volume);
	DDX_Control(pDX, IDC_EDIT_FILE_PATH, m_url);
	DDX_Control(pDX, IDC_BTN_PLAY, m_playBtn);
	DDX_Control(pDX, IDC_COMBO1, m_dropDownBox);
	DDX_Control(pDX, IDC_COMBO_FILE_TYPE, m_fileType);
}

BEGIN_MESSAGE_MAP(CAVDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_PLAY, &CAVDlg::OnBnClickedBtnPlay)
	ON_BN_CLICKED(IDC_BTN_STOP, &CAVDlg::OnBnClickedBtnStop)
	ON_BN_CLICKED(IDC_BTN_SELECT_FILE, &CAVDlg::OnBnClickedBtnSelectFile)
	ON_WM_HSCROLL()
	ON_WM_VSCROLL()
	ON_WM_DESTROY()
	ON_WM_TIMER()
	ON_CBN_SELCHANGE(IDC_COMBO1, &CAVDlg::OnCbnSelchangeCombo1)
	ON_CBN_SELCHANGE(IDC_COMBO_FILE_TYPE, &CAVDlg::OnCbnSelchangeComboFileType)
	ON_BN_CLICKED(IDC_BUTTON2, &CAVDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON1, &CAVDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CAVDlg 消息处理程序

BOOL CAVDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	SetTimer(0, 500, nullptr);
	m_pos.SetRange(0, 100);
	m_volume.SetRange(0, 100);
	m_volume.SetTic(10);
	m_volume.SetTicFreq(20);
	SetDlgItemText(IDC_STATIC_VOL_SHOW, L"100%");
	m_controller->SetWnd(m_play.GetSafeHwnd());
	m_dropDownBox.AddString(L"0.5");
	m_dropDownBox.AddString(L"0.8");
	m_dropDownBox.AddString(L"1.0");
	m_dropDownBox.AddString(L"1.5");
	m_dropDownBox.AddString(L"2.0");
	m_dropDownBox.AddString(L"2.5");
	m_dropDownBox.AddString(L"3.0");
	m_dropDownBox.SetCurSel(2);
	m_fileType.AddString(L"FILE");
	m_fileType.AddString(L"HTTP");
	m_fileType.SetCurSel(0);
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CAVDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CAVDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CAVDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


//播放视频
void CAVDlg::OnBnClickedBtnPlay()
{
	CString str;
	m_url.GetWindowTextW(str);
	if (str.GetLength() == 0) return;
	if (m_filePath != str) {
		if (m_fileType.GetCurSel() == 0) str = FILETYPE + str;
		m_filePath = str;
		m_controller->SetMedia(Unicode2Utf8((LPCTSTR)str));
		m_pos.SetPos(0);
	}
	if (m_isPlay) {
		m_playBtn.SetWindowTextW(L"播放");
		m_isPlay = !m_isPlay;
		m_controller->VideoCtol(CVLC_PAUSE);
	}
	else {
		m_playBtn.SetWindowTextW(L"暂停");
		m_isPlay = !m_isPlay;
		m_controller->VideoCtol(CVLC_PLAY);
		int num = 0;
		while ((int)m_controller->VideoCtol(CVLC_GET_LENGTH) == 0 && num++ < 10)Sleep(50);
		str.Format(L"总时长：%d 分钟", (int)m_controller->VideoCtol(CVLC_GET_LENGTH) / 60);
		SetDlgItemText(IDC_STATIC_TIME_LENGTH, str);
	}
}

//停止
void CAVDlg::OnBnClickedBtnStop()
{
	m_playBtn.SetWindowTextW(L"播放");
	m_isPlay = false;
	m_controller->VideoCtol(CVLC_STOP);
}

//选择文件
void CAVDlg::OnBnClickedBtnSelectFile()
{
	TCHAR szpath[] = _T(" mp4 (*.mp4)|*.mp4|AllFiles (*.*)|*.*||");
	CFileDialog fileDlg(TRUE, NULL, NULL, 6, szpath);
	if (fileDlg.DoModal() == IDOK)
	{
		m_url.SetWindowTextW(fileDlg.GetPathName());
		UpdateData(FALSE);
	}
}

//水平滚动条
void CAVDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	CString str;
	m_playBtn.GetWindowTextW(str);
	if (str == L"播放") return;
	if (nSBCode == 4) {
		CString str;
		str.Format(L"%d%%", nPos);
		SetDlgItemText(IDC_STATIC_TIME, str);
		m_controller->SetPostion(nPos*0.01);
	}
	CDialogEx::OnHScroll(nSBCode, nPos, pScrollBar);
}

//垂直滚动条
void CAVDlg::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	CString str;
	m_playBtn.GetWindowTextW(str);
	if (str == L"播放") return;
	if (nSBCode == 5) {
		CString str;
		str.Format(L"%d%%", 100-nPos);
		SetDlgItemText(IDC_STATIC_VOL_SHOW, str);
		m_controller->SetVolume(100 - nPos);
	}
	CDialogEx::OnVScroll(nSBCode, nPos, pScrollBar);
}


void CAVDlg::OnDestroy()//即将销毁
{
	CDialogEx::OnDestroy();
	KillTimer(0);
}


void CAVDlg::OnTimer(UINT_PTR nIDEvent)//定时器
{
	static bool is = false;
	if (is) return;
	if (nIDEvent == 0) {
		float pos = m_controller->VideoCtol(CVLC_GET_POSITON);
		if(pos >= 0.99f){
			AfxMessageBox(L"播放完毕感谢观看");
			is = true;
		}
		if (pos != -1.0f) {
			CString strPos;
			strPos.Format(_T("%f%%"), pos*100);
			SetDlgItemText(IDC_STATIC_TIME, strPos);
			m_pos.SetPos(pos*100);
		}
	}
	CDialogEx::OnTimer(nIDEvent);
}


void CAVDlg::OnCbnSelchangeCombo1()
{
	int temp = m_dropDownBox.GetCurSel();
	CString str;
	((CComboBox*)GetDlgItem(IDC_COMBO1))->GetLBText(temp, str);
	char szStr[10]{};
	size_t i;
	wcstombs_s(&i, szStr, str.GetBuffer(), sizeof szStr);
	float rate = atof(szStr);
	m_controller->SetRate(rate);
}


void CAVDlg::OnCbnSelchangeComboFileType()
{
	static int sel = 0;
	int temp = m_fileType.GetCurSel();
	if (sel == temp) return;
	sel = temp;
	m_url.SetReadOnly(temp == 0);
}


void CAVDlg::OnBnClickedButton2()
{
	float temp = m_controller->VideoCtol(CVLC_GET_POSITON);
	if (temp < 0.01) return;
	m_controller->SetPostion(temp - 0.01);
}


void CAVDlg::OnBnClickedButton1()
{
	float temp = m_controller->VideoCtol(CVLC_GET_POSITON);
	if (temp > 0.98) return;
	m_controller->SetPostion(temp + 0.01);
}
