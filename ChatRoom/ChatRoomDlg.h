
// ChatRoomDlg.h : ͷ�ļ�
//

#pragma once

#include "MySocket.h"
// CChatRoomDlg �Ի���
class CChatRoomDlg : public CDialogEx
{
// ����
public:
	CChatRoomDlg(CWnd* pParent = NULL);	// ��׼���캯��
	void OnReceive();//������Ӧ�¼�����
	void OnAccept();//������Ӧ�¼�
	void OnClose();//�ر���Ӧ�¼�

// �Ի�������
	enum { IDD = IDD_CHATROOM_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CString m_recv;
	CString m_send;
private:
	CMySocket m_socketListen;//�����˿�
	CMySocket m_socketServer;//����˿�
public:
	afx_msg void OnBnClickedStarBtn();
	afx_msg void OnBnClickedSendBtn();//�˳���ť��Ӧ
	afx_msg void OnBnClickedCancelBtn();//���Ͱ�ť��Ӧ
};
