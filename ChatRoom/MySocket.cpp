// MySocket.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ChatRoom.h"
#include "MySocket.h"
#include "ChatRoomDlg.h"

// CMySocket

CMySocket::CMySocket()
{
}

CMySocket::~CMySocket()
{
}


// CMySocket ��Ա����
void CMySocket::SetParent(CDialog *pDlg)//����CChatRoomDlg���ָ��
{
	m_pDlg = (CChatRoomDlg*)pDlg;
}
void CMySocket::OnAccept(int nErrorCode)//�����¼�������
{
	if (nErrorCode == 0)
	{
		((CChatRoomDlg*)m_pDlg)->OnAccept();//����CChatRoomDlg��ĵ�OnAccept����
	}
}

void CMySocket::OnConnect(int nErrorCode)//�����¼��Ĵ�����
{

}

void CMySocket::OnReceive(int nErrorCode)
{
	((CChatRoomDlg*)m_pDlg)->OnReceive();//����CChatRoomDlg��ĵ�OnReceive����
}

void CMySocket::OnClose(int nErrorCode)
{
	((CChatRoomDlg*)m_pDlg)->OnClose();//����CChatRoomDlg��ĵ�OnClose����
}