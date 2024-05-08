#include "stdafx.h"
#include "MyBmp.h"


CMyBmp::CMyBmp()
{
}


CMyBmp::~CMyBmp()
{
}

// HDC : 그림
void CMyBmp::Load_Bmp(const TCHAR * pFilePath)
{
	HDC		hDC = GetDC(g_hWnd);

	// 화면 DC와 호환되는(바꿔 쓸 수 있는) DC를 할당
	m_hMemDC = CreateCompatibleDC(hDC);

	ReleaseDC(g_hWnd, hDC);

	// LaadImage가 void* 타입의 핸들을 반환하는데 이걸 비트맵 핸들의 형식으로 강제 캐스팅.
	m_hBitmap = (HBITMAP)LoadImage(NULL,	// 프로그램 인스턴스 핸들
							pFilePath,		// 이미지 파일의 경로
							IMAGE_BITMAP,	// 어떤 타입을 읽어올지 결정
							0, 0,			// 이미지의 가로, 세로 크기
							LR_LOADFROMFILE | LR_CREATEDIBSECTION);
							//LR_LOADFROMFILE : 파일로부터 이미지를 읽어들인다는 옵션
							// LR_CREATEDIBSECTION : 읽어온 파일을 DIB 형태로 변환
							// DIB(장치 독립 비트맵) : 표준 비트맵 파일(BMP/image/bmp/)과 구조가 유사한 래스터(=비트맵) 이미지 파일입니다.
							// 래스터 이미지 파일 : 그냥 픽셀로 된 거.


	// SelectObject : 준비한 DC의 GDI 오브젝트를 불러 비트맵을 선택하게 만드는 함수
	// 현재 이 코드는 GDI 오브젝트를 선택하기 전 기존에 가지고 있던 오브젝트를 반환하게 만든다.
	// DC의 GDI에다가 새로운거 받고 원래 있던거 뱉어냄.
	m_hOldBmp = (HBITMAP)SelectObject(m_hMemDC, m_hBitmap);
}	

void CMyBmp::Release()
{
	// 옛날거 다시 받고
	SelectObject(m_hMemDC, m_hOldBmp);
	// 지금거 지우고
	DeleteObject(m_hBitmap);
	// 옛날것도 지우고
	DeleteDC(m_hMemDC);
}
