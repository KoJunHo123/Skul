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
	// ������ ��ġ
	INFO* m_pInfo;

	// ���� ���� ��ġ
	INFO		m_tAttackInfo;

	// ���� ����
	RECT		m_tRect;

	// ���� ����
	ATTACKTYPE	m_eAttackType;

	// ���� ����
	DIRECTION	m_eDir;

	// �÷��̾�/���� ���� ����
	bool		m_bPlayerAttack;

	// ��� false �Ǹ� ����.
	bool*		m_bAttacking;

	// ���� ������
	int			m_iDamage;

	// �������� ������
	FRAME		m_tFrame;

};

