
// ChatRoomDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ChatRoom.h"
#include "ChatRoomDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
public:
//	afx_msg void OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
//	ON_WM_ACTIVATE()
END_MESSAGE_MAP()


// CChatRoomDlg 对话框



CChatRoomDlg::CChatRoomDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CChatRoomDlg::IDD, pParent)
	, m_recv(_T(""))
	, m_send(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CChatRoomDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_RECV_EDIT, m_recv);
	DDX_Text(pDX, IDC_SEND_EDIT, m_send);
}

BEGIN_MESSAGE_MAP(CChatRoomDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_STAR_BTN, &CChatRoomDlg::OnBnClickedStarBtn)
	ON_BN_CLICKED(IDC_SEND_BTN, &CChatRoomDlg::OnBnClickedSendBtn)
	ON_BN_CLICKED(IDC_CANCEL_BTN, &CChatRoomDlg::OnBnClickedCancelBtn)
END_MESSAGE_MAP()


// CChatRoomDlg 消息处理程序

BOOL CChatRoomDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
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

	// TODO:  在此添加额外的初始化代码
	m_socketListen.SetParent(this);//把当前对话框类的指针设置给对象
	m_socketServer.SetParent(this);
	m_socketListen.Create(10000);
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CChatRoomDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CChatRoomDlg::OnPaint()
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
HCURSOR CChatRoomDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



//void CAboutDlg::OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized)
//{
//	CDialogEx::OnActivate(nState, pWndOther, bMinimized);
//
//	// TODO:  在此处添加消息处理程序代码
//}


void CChatRoomDlg::OnBnClickedStarBtn()//监听事件响应处理函数
{
	// TODO:  在此添加控件通知处理程序代码
	m_socketListen.Create(10000);
	m_socketListen.Listen();

}

void CChatRoomDlg::OnAccept()//接收事件响应的处理函数
{
	SOCKADDR sockAddr;//保存地址变量
	int nSockAddrLen = sizeof(SOCKADDR);
	CString tmp;//临时字符串变量
	if (m_socketListen.Accept(m_socketServer, &sockAddr, &nSockAddrLen))
	{
		tmp.Format("有客服端连接，来自 %d,%d,%d,%d\r\n",
			(UCHAR)sockAddr.sa_data[2], (UCHAR)sockAddr.sa_data[3],
			(UCHAR)sockAddr.sa_data[4],(UCHAR)sockAddr.sa_data[5]);//接收客户端连接
		m_recv += tmp;//更新字符串数据
		UpdateData(FALSE);//更新显示
	}
}

void CChatRoomDlg::OnReceive()
{
	BYTE byBuf[1024]= { 0 };//数据接收缓冲区
	int nRecvLen = 0;//存储接收到的数据的长度
	nRecvLen = m_socketServer.Receive(byBuf, sizeof(byBuf));//获取接收到的数据的长度
	CString tmp;//临时变量
	if (nRecvLen > 0)//nRecvLen > 0表示服务端接收到了数据
	{
		UpdateData();
		tmp.Format("%s\r\n", byBuf);//格式化数据
		m_recv += tmp;//更新编辑框变量
		UpdateData(FALSE);//显示
	}
	else
	{
		AfxMessageBox("收到的数据有问题！");//错误提示
	}
}

void CChatRoomDlg::OnBnClickedSendBtn()
{
	// TODO:  在此添加控件通知处理程序代码
	UpdateData();//更新数据到变量
	int nSendLen = m_socketServer.Send((void *)m_send.GetBuffer(0), m_send.GetLength());//发送字符串
	if (nSendLen > 0)
	{
		AfxMessageBox("发送数据成功！");
	}
	else
	{
		AfxMessageBox("发送数据失败！");
	}
}

void CChatRoomDlg::OnClose()//关闭事件
{
	m_socketServer.Close();//调用关闭函数
}

void CChatRoomDlg::OnBnClickedCancelBtn()//取消事件响应
{
	// TODO:  在此添加控件通知处理程序代码
	CDialog::OnCancel();
}
