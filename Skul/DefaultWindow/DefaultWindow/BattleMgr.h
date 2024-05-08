#pragma once
#include "MeleeAttack.h"
#include "RangedAttack.h"

class CBattleMgr
{
private:
	static CBattleMgr* m_pInstance;
	list<CAttack*>		m_AttackList;
	int		m_iCheckTime;

private:
	CBattleMgr();
	~CBattleMgr();

public:
	static CBattleMgr* Get_Instance()
	{
		if (!m_pInstance)
		{
			m_pInstance = new CBattleMgr;
		}
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

	CAttack* Get_LastAttack() { return m_AttackList.back(); }

public:
	// 위치(Info포인터), 방향, 데미지, 플레이어or몬스터
	void Add_MeleeAttack(INFO* _info, ATTACKTYPE _type, DIRECTION _dir, int _damage, bool _playerAttack, bool* _attacking);
	void Add_RangedAttack(INFO* _info, ATTACKTYPE _type, DIRECTION _dir, int _damage, bool _playerAttack, bool* _attacking, CObj* _target);

	void Collision_Attack(list<CObj*> _obj);
	INFO Find_SkullHead();
};
