#pragma once

#include "Define.h"

// �׷��� DC�� �׸� �׸�(��Ʈ��), ���� �׸� �׸� ������ �ִ� Ŭ����
class CMyBmp
{
public:
	CMyBmp();
	~CMyBmp();

public:
	HDC			Get_MemDC() { return m_hMemDC; }

	void		Load_Bmp(const TCHAR* pFilePath);
	void		Release();

private:
	// dc�� �ڵ�: ����ü -> Ŀ�� ������Ʈ
	HDC			m_hMemDC;

	// ���� ��Ʈ��(�� �ڵ�: ����ü)
	HBITMAP		m_hBitmap;

	// ���� ��Ʈ��(�� �ڵ�: ����ü)
	HBITMAP		m_hOldBmp;
};

