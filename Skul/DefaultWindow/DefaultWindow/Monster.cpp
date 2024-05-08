#include "stdafx.h"
#include "Monster.h"
#include "LineMgr.h"

CMonster::CMonster()
	: m_eMonsterID(MONSTERID_END)
	, m_eAggro(UNRECOGNIZE)
	, m_fTargetDistance(0.f)
	, m_fAggroRange(0.f)
	, m_fFollowRange(0.f)
	, m_fTargetAngle(0.f)
	, m_fAttackRange(0.f)
	, m_iMoveTime(GetTickCount())
	, m_iAttackDelay(GetTickCount())
	, m_iBreakState(GetTickCount())
	, m_bMoveLeft(true)
	, m_fHpRate()
{
    m_eRender = RENDER_MONSTER;
}

CMonster::~CMonster()
{
}

void CMonster::Find_Target()
{

	float xRange = m_pTarget->Get_Info().fX - m_tInfo.fX;
	float yRange = m_pTarget->Get_Info().fY - m_tInfo.fY;

	m_fTargetDistance = sqrt(pow(xRange, 2) + pow(yRange, 2));

	m_fTargetAngle = acosf(xRange / m_fTargetDistance);

	if (yRange > 0)
	{
		m_fTargetAngle *= -1;
	}

	if(m_eCurState != ATTACK)
		m_iAttackDelay = GetTickCount();

	if(m_eDir == LEFT)
	{
		if (m_fTargetDistance < m_fAggroRange && (ANGLE(m_fTargetAngle) >= 135 || ANGLE(m_fTargetAngle) <= -135))
		{
			m_eAggro = RECOGNIZE;
		}
		 if (m_fTargetDistance < m_fAttackRange && m_eAggro == RECOGNIZE)
		{
			m_eAggro = AGGRO_ATTACK;
		}
		if (m_fTargetDistance > m_fFollowRange)
		{
			m_eAggro = UNRECOGNIZE;
		}
	}
	else
	{
		if (m_fTargetDistance < m_fAggroRange && (ANGLE(m_fTargetAngle) <= 45 && ANGLE(m_fTargetAngle) >= -45))
		{
			m_eAggro = RECOGNIZE;
		}
		if (m_fTargetDistance < m_fAttackRange && m_eAggro == RECOGNIZE)
		{
			m_eAggro = AGGRO_ATTACK;
		}
		if (m_fTargetDistance > m_fFollowRange)
		{
			m_eAggro = UNRECOGNIZE;
		}
	}
}

//

// ÃßÀû
void CMonster::Follow_Target()
{
	if(m_eCurState != ATTACK)
	{
		m_eCurState = WALK;

		if (ANGLE(m_fTargetAngle) >= 90.f || ANGLE(m_fTargetAngle) <= -90.f)
		{
			m_eDir = LEFT;
			m_tInfo.fX -= m_fSpeed;
		}
		else
		{
			m_eDir = RIGHT;
			m_tInfo.fX += m_fSpeed;
		}

	}
}

void CMonster::WariGari()
{
	if (m_iMoveTime + 3000 > GetTickCount())
	{
		m_eCurState = WALK;
		m_fSpeed = 1.f;

		if (RIGHT == m_eDir)
		{
			m_tInfo.fX += m_fSpeed;
		}
		else
		{
			m_tInfo.fX -= m_fSpeed;
		}
	}
	else if(m_iMoveTime + 3000 < GetTickCount() && m_iMoveTime + 5000 > GetTickCount())
	{
		m_eCurState = IDLE;

	}
	else if(m_iMoveTime + 5000 < GetTickCount())
	{
		m_iMoveTime = GetTickCount();

		if (RIGHT == m_eDir)
			m_eDir = LEFT;
		else
			m_eDir = RIGHT;
	}
}


void CMonster::LineCollision()
{
	float	fY(0.f);

	bool	bLineCol = CLineMgr::Get_Instance()->Collision_Line(this, m_tInfo.fX, &fY);
	if (bLineCol)
	{
		m_bGround = true;
		m_tInfo.fY = fY;
	}
	else
	{
		m_bGround = false;
	}
}

void CMonster::Set_HealthBar()
{
	m_fHpRate = m_iHp * 0.01f * 40.f;
}

