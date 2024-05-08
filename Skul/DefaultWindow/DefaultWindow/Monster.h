#pragma once
#include "Obj.h"
#include "CameraMgr.h"


class CMonster : public CObj
{
public:
	CMonster();
	virtual ~CMonster();

public:
	// CObj��(��) ���� ��ӵ�
	virtual void Initialize() PURE;
	virtual int Update() PURE;
	virtual void Late_Update() PURE;
	virtual void Render(HDC hDC) PURE;
	virtual void Release() PURE;

	// ���� ���
	virtual void Attack() PURE;

protected:
	void		Find_Target();
	void		Follow_Target();
	void		WariGari();
	void		LineCollision();

	void		Set_HealthBar();

protected:
	MONSTERID	m_eMonsterID;
	AGGROLEVEL	m_eAggro;	// ��׷� ����


	float	m_fTargetDistance;		// Ÿ�ٰ��� �Ÿ�
	float	m_fAggroRange;			// ��׷� ����
	float	m_fFollowRange;			// ���� ����
	float	m_fTargetAngle;			// Ÿ�������� ����

	float	m_fAttackRange;			// ���� ����

	int m_iMoveTime;
	int m_iAttackDelay;
	int	m_iBreakState;

	bool m_bMoveLeft;

	float m_fHpRate;
};

