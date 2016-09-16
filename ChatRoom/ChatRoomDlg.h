
// ChatRoomDlg.h : 头文件
//

#pragma once

#include "MySocket.h"
// CChatRoomDlg 对话框
class CChatRoomDlg : public CDialogEx
{
// 构造
public:
	CChatRoomDlg(CWnd* pParent = NULL);	// 标准构造函数
	void OnReceive();//接收响应事件函数
	void OnAccept();//连接响应事件
	void OnClose();//关闭响应事件

// 对话框数据
	enum { IDD = IDD_CHATROOM_DIALOG };

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
	CString m_recv;
	CString m_send;
private:
	CMySocket m_socketListen;//监听端口
	CMySocket m_socketServer;//服务端口
public:
	afx_msg void OnBnClickedStarBtn();
	afx_msg void OnBnClickedSendBtn();//退出按钮响应
	afx_msg void OnBnClickedCancelBtn();//发送按钮响应
};
