#pragma once

#include "MyBmp.h"

class CBmpMgr
{
private:
	CBmpMgr();
	~CBmpMgr();

public:
	void		Insert_Bmp(const TCHAR* pFilePath, const TCHAR* pImgKey);
	HDC			Find_Image(const TCHAR* pImgKey);
	void		Delete_Image(const TCHAR* pImgKey);
	void		Release();

public:
	static CBmpMgr*		Get_Instance()
	{
		if (!m_pInstance)
			m_pInstance = new CBmpMgr;

		return m_pInstance;
	}
	static void		Destroy()
	{
		if (m_pInstance)
		{
			delete m_pInstance;
			m_pInstance = nullptr;
		}
	}

private:
	static CBmpMgr*		m_pInstance;

	// Ű, �׸� �����ϴ� ��.
	map<const TCHAR*, CMyBmp*>		m_mapBit;
};
