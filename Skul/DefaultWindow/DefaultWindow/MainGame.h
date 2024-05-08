#pragma once

#include "Define.h"

class CMainGame
{
public:
	CMainGame();
	~CMainGame();

public:
	void		Initialize();
	void		Update();		// �ǽð�����(�� �����Ӹ���) ����Ǵ� ���� ����� �Լ�
	void		LateUpdate();
	void		Render();		// �ǽð�����(�� �����Ӹ���) ����ϴ� �Լ�
	void		Release();

private:
	HDC			m_hDC;

	DWORD		m_dwTime;
	int			m_iFPS;
	TCHAR		m_szFPS[32];

};
