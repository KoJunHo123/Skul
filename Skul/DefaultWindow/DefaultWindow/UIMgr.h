#pragma once
#include "Obj.h"

class CUIMgr
{
private:
	static CUIMgr*	m_pInstance;
	CObj*			m_pPlayer;
	float			m_fHpRate;
	int				m_iBoneCount;

	INFO	m_tInfo; // 플레이어 프레임 위치, 크기
	int*	m_iLeftMonster;

private:
	CUIMgr();
	~CUIMgr();

public:
	static CUIMgr* Get_Instance()
	{
		if (!m_pInstance)
			m_pInstance = new CUIMgr;

		return m_pInstance;
	}

	static void Destroy()
	{
		if (m_pInstance)
		{
			delete m_pInstance;
			m_pInstance = nullptr;
		}
	}

public:
	void Initialize();
	void Update();
	void Late_Update();
	void Render(HDC hDC);
	void Release();

	void Set_Player(CObj* _pPlayer) { m_pPlayer = _pPlayer; }
	void Set_LeftMonster(int* _left) { m_iLeftMonster = _left; }

	void Add_Bone(int _bone) { m_iBoneCount += _bone; }
	void Use_Bone(int _bone) { m_iBoneCount -= _bone; }
	int  Get_Bone() { return m_iBoneCount; }
};

