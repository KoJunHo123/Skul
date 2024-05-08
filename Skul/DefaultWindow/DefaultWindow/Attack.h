#pragma once
#include "Obj.h"

class CAttack
{
public:
	CAttack();
	CAttack(INFO* _pInfo, ATTACKTYPE _attType, DIRECTION _dir, int _damage, bool _PlayerAttack, bool* _attacking);
	virtual ~CAttack();

public:
	virtual void Initialize()		PURE;
	virtual int Update()			PURE;
	virtual void Late_Update()		PURE;
	virtual void Render(HDC hDC)	PURE;
	virtual void Release()			PURE;

public:
	RECT Get_Rect() { return m_tRect; }
	int Get_Damage() { return m_iDamage; }
	DIRECTION Get_Dir() { return m_eDir; }
	bool Get_PlayerAttack() { return m_bPlayerAttack; }
	bool* Get_Attacking() { return m_bAttacking; }
	ATTACKTYPE Get_AttackType() { return m_eAttackType; }
	INFO& Get_Info() { return m_tAttackInfo; }
	

protected:
	void Update_Rect();
	void Move_frame();

protected:
	// 공격자 위치
	INFO* m_pInfo;

	// 실제 공격 위치
	INFO		m_tAttackInfo;

	// 공격 범위
	RECT		m_tRect;

	// 공격 종류
	ATTACKTYPE	m_eAttackType;

	// 공격 방향
	DIRECTION	m_eDir;

	// 플레이어/몬스터 공격 구별
	bool		m_bPlayerAttack;

	// 요게 false 되면 해제.
	bool*		m_bAttacking;

	// 적용 데미지
	int			m_iDamage;

	// 랜더링용 프레임
	FRAME		m_tFrame;

};

