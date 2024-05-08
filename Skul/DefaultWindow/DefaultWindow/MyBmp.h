#pragma once

#include "Define.h"

// 그려줄 DC랑 그릴 그림(비트맵), 전에 그린 그림 가지고 있는 클래스
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
	// dc의 핸들: 구조체 -> 커널 오브젝트
	HDC			m_hMemDC;

	// 현재 비트맵(의 핸들: 구조체)
	HBITMAP		m_hBitmap;

	// 이전 비트맵(의 핸들: 구조체)
	HBITMAP		m_hOldBmp;
};

