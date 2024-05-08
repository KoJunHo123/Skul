#pragma once
#include "Obj.h"
#include "CameraMgr.h"


class CMonster : public CObj
{
public:
	CMonster();
	virtual ~CMonster();

public:
	// CObj을(를) 통해 상속됨
	virtual void Initialize() PURE;
	virtual int Update() PURE;
	virtual void Late_Update() PURE;
	virtual void Render(HDC hDC) PURE;
	virtual void Release() PURE;

	// 공격 방식
	virtual void Attack() PURE;

protected:
	void		Find_Target();
	void		Follow_Target();
	void		WariGari();
	void		LineCollision();

	void		Set_HealthBar();

protected:
	MONSTERID	m_eMonsterID;
	AGGROLEVEL	m_eAggro;	// 어그로 유무


	float	m_fTargetDistance;		// 타겟과의 거리
	float	m_fAggroRange;			// 어그로 범위
	float	m_fFollowRange;			// 추적 범위
	float	m_fTargetAngle;			// 타겟으로의 각도

	float	m_fAttackRange;			// 공격 범위

	int m_iMoveTime;
	int m_iAttackDelay;
	int	m_iBreakState;

	bool m_bMoveLeft;

	float m_fHpRate;
};

