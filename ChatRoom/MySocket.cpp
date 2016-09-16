// MySocket.cpp : 实现文件
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


// CMySocket 成员函数
void CMySocket::SetParent(CDialog *pDlg)//设置CChatRoomDlg类的指针
{
	m_pDlg = (CChatRoomDlg*)pDlg;
}
void CMySocket::OnAccept(int nErrorCode)//接收事件处理函数
{
	if (nErrorCode == 0)
	{
		((CChatRoomDlg*)m_pDlg)->OnAccept();//调用CChatRoomDlg类的的OnAccept函数
	}
}

void CMySocket::OnConnect(int nErrorCode)//连接事件的处理函数
{

}

void CMySocket::OnReceive(int nErrorCode)
{
	((CChatRoomDlg*)m_pDlg)->OnReceive();//调用CChatRoomDlg类的的OnReceive函数
}

void CMySocket::OnClose(int nErrorCode)
{
	((CChatRoomDlg*)m_pDlg)->OnClose();//调用CChatRoomDlg类的的OnClose函数
}