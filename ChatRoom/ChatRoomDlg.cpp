
// ChatRoomDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ChatRoom.h"
#include "ChatRoomDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CChatRoomDlg �Ի���



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


// CChatRoomDlg ��Ϣ�������

BOOL CChatRoomDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO:  �ڴ���Ӷ���ĳ�ʼ������
	m_socketListen.SetParent(this);//�ѵ�ǰ�Ի������ָ�����ø�����
	m_socketServer.SetParent(this);
	m_socketListen.Create(10000);
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CChatRoomDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CChatRoomDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



//void CAboutDlg::OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized)
//{
//	CDialogEx::OnActivate(nState, pWndOther, bMinimized);
//
//	// TODO:  �ڴ˴������Ϣ����������
//}


void CChatRoomDlg::OnBnClickedStarBtn()//�����¼���Ӧ������
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	m_socketListen.Create(10000);
	m_socketListen.Listen();

}

void CChatRoomDlg::OnAccept()//�����¼���Ӧ�Ĵ�����
{
	SOCKADDR sockAddr;//�����ַ����
	int nSockAddrLen = sizeof(SOCKADDR);
	CString tmp;//��ʱ�ַ�������
	if (m_socketListen.Accept(m_socketServer, &sockAddr, &nSockAddrLen))
	{
		tmp.Format("�пͷ������ӣ����� %d,%d,%d,%d\r\n",
			(UCHAR)sockAddr.sa_data[2], (UCHAR)sockAddr.sa_data[3],
			(UCHAR)sockAddr.sa_data[4],(UCHAR)sockAddr.sa_data[5]);//���տͻ�������
		m_recv += tmp;//�����ַ�������
		UpdateData(FALSE);//������ʾ
	}
}

void CChatRoomDlg::OnReceive()
{
	BYTE byBuf[1024]= { 0 };//���ݽ��ջ�����
	int nRecvLen = 0;//�洢���յ������ݵĳ���
	nRecvLen = m_socketServer.Receive(byBuf, sizeof(byBuf));//��ȡ���յ������ݵĳ���
	CString tmp;//��ʱ����
	if (nRecvLen > 0)//nRecvLen > 0��ʾ����˽��յ�������
	{
		UpdateData();
		tmp.Format("%s\r\n", byBuf);//��ʽ������
		m_recv += tmp;//���±༭�����
		UpdateData(FALSE);//��ʾ
	}
	else
	{
		AfxMessageBox("�յ������������⣡");//������ʾ
	}
}

void CChatRoomDlg::OnBnClickedSendBtn()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData();//�������ݵ�����
	int nSendLen = m_socketServer.Send((void *)m_send.GetBuffer(0), m_send.GetLength());//�����ַ���
	if (nSendLen > 0)
	{
		AfxMessageBox("�������ݳɹ���");
	}
	else
	{
		AfxMessageBox("��������ʧ�ܣ�");
	}
}

void CChatRoomDlg::OnClose()//�ر��¼�
{
	m_socketServer.Close();//���ùرպ���
}

void CChatRoomDlg::OnBnClickedCancelBtn()//ȡ���¼���Ӧ
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CDialog::OnCancel();
}
