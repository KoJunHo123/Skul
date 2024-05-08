#include "stdafx.h"
#include "Soldier.h"

#include "BattleMgr.h"
#include "AnimationMgr.h"
#include "EffectMgr.h"
#include "BmpMgr.h"

CSoldier::CSoldier()
{

}

CSoldier::~CSoldier()
{
}

void CSoldier::Initialize()
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/Soldier/Soldier_Left.bmp", L"Soldier_Left");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/Soldier/Soldier_Right.bmp", L"Soldier_Right");

	m_tInfo.fCX = 20;
	m_tInfo.fCY = 40;
	m_fSpeed = 3.f;
	m_fAggroRange = 200.f;
	m_fFollowRange = 200.f;
	m_fAttackRange = 30.f;
	m_eMonsterID = SOLDIER;
	m_iHp = 50;

	m_eCurState = IDLE;
	m_bMonster = true;
}

int CSoldier::Update()
{
	if (m_eDir == RIGHT)
		m_pFrameKey = L"Soldier_Right";
	else
		m_pFrameKey = L"Soldier_Left";

	if (m_bDead)
	{
		CEffectMgr::Get_Instance()->Add_Effect(MONSTER_DEAD, m_tInfo);
		return OBJ_DEAD;
	}

	Set_HealthBar();

	if (m_eCurState != HIT_1 && m_eCurState != HIT_2)
	{
		Find_Target();

		switch (m_eAggro)
		{
		case UNRECOGNIZE:
			WariGari();
			break;

		case RECOGNIZE:
			m_fSpeed = 2.f;
			Follow_Target();
			break;

		case AGGRO_ATTACK:
			Attack();
			break;
		}
	}

	Gravity();
	Update_Rect();
	Soldier_MoveFrame();
	return OBJ_NOEVENT;

	return 0;
}

void CSoldier::Late_Update()
{
	CAnimationMgr::SetSoldierFrame(this);
	LineCollision();
	if (m_iHp <= 0)
		m_bDead = true;
}

void CSoldier::Render(HDC hDC)
{
	Vec2 RenderPos = CCameraMgr::Get_Instance()->Get_RenderPos(m_tInfo.fX, m_tInfo.fY);
	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);
	HDC hHPBarDC = CBmpMgr::Get_Instance()->Find_Image(L"HealthBar");

	GdiTransparentBlt(hDC,
		(int)(RenderPos.fX - 60),
		(int)(RenderPos.fY - 60),
		120,
		120,
		hMemDC,
		m_tFrame.iFrameStart * 100,
		m_tFrame.iMotion * 100,
		100,
		100,
		RGB(255, 0, 255));

	GdiTransparentBlt(hDC, RenderPos.fX - 10.f, RenderPos.fY + 23.f, m_fHpRate, 5, hHPBarDC, 0, 0, 40, 5, RGB(0, 0, 0));

}

void CSoldier::Release()
{
}

void CSoldier::Attack()
{
	m_eCurState = ATTACK;
}

void CSoldier::Soldier_MoveFrame()
{
	// 넘길 때 되면
	if (m_tFrame.dwTime + m_tFrame.dwSpeed < GetTickCount())
	{

		if (m_eCurState == ATTACK && m_tFrame.iFrameStart == 0 && m_iAttackDelay + 1000 > GetTickCount())
			return;

		// 다음 프레임으로 넘어감
		++m_tFrame.iFrameStart;
		m_tFrame.dwTime = GetTickCount();
		
		if (m_eCurState == ATTACK && m_tFrame.iFrameStart == 1)
		{
			m_bAttacking = true;
			CBattleMgr::Get_Instance()->Add_MeleeAttack(&m_tInfo, SOLDIER_ATTACK, m_eDir, 10, false, &m_bAttacking);
		}
		else
			m_bAttacking = false;

		// 끝나면 처음으로
		if (m_tFrame.iFrameStart > m_tFrame.iFrameEnd)
		{
			if (m_eCurState != HIT_2)
				m_tFrame.iFrameStart = 0;
			else
				m_tFrame.iFrameStart = 1;

			if (m_eCurState == ATTACK)
			{
				if (ANGLE(m_fTargetAngle) >= 90.f || ANGLE(m_fTargetAngle) <= -90.f)
					m_eDir = LEFT;
				else
					m_eDir = RIGHT;

				m_eCurState = IDLE;
				m_iAttackDelay = GetTickCount();
			}

			if (m_eCurState == HIT_1 || m_eCurState == HIT_2)
			{
				m_iBreakState = GetTickCount();
				m_eCurState = IDLE;
			}
		}
	}
}