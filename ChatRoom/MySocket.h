#pragma once

// CMySocket 命令目标

class CMySocket : public CAsyncSocket
{
public:
	CMySocket();//构造函数
	virtual ~CMySocket();//析构函数

protected:
	virtual void OnClose(int nErrorCode);//关闭端口事件响应
	virtual void OnReceive(int nErrorCode);//接收数据事件响应
	virtual void OnConnect(int nErrorCode);//连接事件响应
	virtual void OnAccept(int nErrorCode);//接收事件响应
private:
	CDialog *m_pDlg;
public:
	void SetParent(CDialog *pDlg);
};


