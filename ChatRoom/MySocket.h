#pragma once

// CMySocket ����Ŀ��

class CMySocket : public CAsyncSocket
{
public:
	CMySocket();//���캯��
	virtual ~CMySocket();//��������

protected:
	virtual void OnClose(int nErrorCode);//�رն˿��¼���Ӧ
	virtual void OnReceive(int nErrorCode);//���������¼���Ӧ
	virtual void OnConnect(int nErrorCode);//�����¼���Ӧ
	virtual void OnAccept(int nErrorCode);//�����¼���Ӧ
private:
	CDialog *m_pDlg;
public:
	void SetParent(CDialog *pDlg);
};


