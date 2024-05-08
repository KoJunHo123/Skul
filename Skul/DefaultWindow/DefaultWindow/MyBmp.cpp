#include "stdafx.h"
#include "MyBmp.h"


CMyBmp::CMyBmp()
{
}


CMyBmp::~CMyBmp()
{
}

// HDC : �׸�
void CMyBmp::Load_Bmp(const TCHAR * pFilePath)
{
	HDC		hDC = GetDC(g_hWnd);

	// ȭ�� DC�� ȣȯ�Ǵ�(�ٲ� �� �� �ִ�) DC�� �Ҵ�
	m_hMemDC = CreateCompatibleDC(hDC);

	ReleaseDC(g_hWnd, hDC);

	// LaadImage�� void* Ÿ���� �ڵ��� ��ȯ�ϴµ� �̰� ��Ʈ�� �ڵ��� �������� ���� ĳ����.
	m_hBitmap = (HBITMAP)LoadImage(NULL,	// ���α׷� �ν��Ͻ� �ڵ�
							pFilePath,		// �̹��� ������ ���
							IMAGE_BITMAP,	// � Ÿ���� �о���� ����
							0, 0,			// �̹����� ����, ���� ũ��
							LR_LOADFROMFILE | LR_CREATEDIBSECTION);
							//LR_LOADFROMFILE : ���Ϸκ��� �̹����� �о���δٴ� �ɼ�
							// LR_CREATEDIBSECTION : �о�� ������ DIB ���·� ��ȯ
							// DIB(��ġ ���� ��Ʈ��) : ǥ�� ��Ʈ�� ����(BMP/image/bmp/)�� ������ ������ ������(=��Ʈ��) �̹��� �����Դϴ�.
							// ������ �̹��� ���� : �׳� �ȼ��� �� ��.


	// SelectObject : �غ��� DC�� GDI ������Ʈ�� �ҷ� ��Ʈ���� �����ϰ� ����� �Լ�
	// ���� �� �ڵ�� GDI ������Ʈ�� �����ϱ� �� ������ ������ �ִ� ������Ʈ�� ��ȯ�ϰ� �����.
	// DC�� GDI���ٰ� ���ο�� �ް� ���� �ִ��� ��.
	m_hOldBmp = (HBITMAP)SelectObject(m_hMemDC, m_hBitmap);
}	

void CMyBmp::Release()
{
	// ������ �ٽ� �ް�
	SelectObject(m_hMemDC, m_hOldBmp);
	// ���ݰ� �����
	DeleteObject(m_hBitmap);
	// �����͵� �����
	DeleteDC(m_hMemDC);
}
