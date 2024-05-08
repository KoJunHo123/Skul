#include "stdafx.h"
#include "RangedAttack.h"
#include "BmpMgr.h"
#include "CameraMgr.h"
#include "CollisionMgr.h"
#include "ObjMgr.h"

CRangedAttack::CRangedAttack()
{
}

CRangedAttack::CRangedAttack(INFO* _info, ATTACKTYPE _type, DIRECTION _dir, int _damage, bool _playerAttack, bool* _attacking, CObj* _target)
	: CAttack(_info, _type, _dir, _damage, _playerAttack, _attacking)
	, m_pTarget(_target)
	, m_fAngle(0.f)
	, m_fSpeed(0.f)
	, m_fYSpeed(0.f)
	, m_fXSpeed(5.f)
	, m_iCrushCount(0)
	, m_bCrushed(false)
{
}

CRangedAttack::~CRangedAttack()
{
}

void CRangedAttack::Initialize()
{
	StartInfo = *m_pInfo;

	switch (m_eAttackType)
	{

	case PLAYER_SKILL_1:
		CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/Skill/Skul_Head.bmp", L"Skul_Head");
		m_tAttackInfo = StartInfo;
		m_tAttackInfo.fCX = 15.f;
		m_tAttackInfo.fCY = 13.f;
		m_fSpeed = 10.f;
		m_tFrame = { 0, 0, 0, 50, GetTickCount()};
		break;

	case ELDERENT_GRAPE:
		CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Boss/Grape/Grape.bmp", L"Grape");
		m_tAttackInfo = StartInfo;
		m_tAttackInfo.fCX = 80.f;
		m_tAttackInfo.fCY = 80.f;
		m_fSpeed = 3.f;
		m_tFrame = { 0, 51, 0, 50, GetTickCount() };
		Calculate_Dir();
		break;

	case ELDERENT_BABYGRAPE:
		CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Boss/Grape/Baby_Grape.bmp", L"Baby_Grape");
		m_tAttackInfo = StartInfo;
		m_tAttackInfo.fCX = 36.f;
		m_tAttackInfo.fCY = 36.f;
		m_fSpeed = 5.f;
		break;

	case ARCHER_ATTACK:
		if (m_eDir == LEFT)
			CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/Archer/Arrow_Left.bmp", L"Arrow_Left");
		else
			CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/Archer/Arrow_Right.bmp", L"Arrow_Right");
		m_tAttackInfo = StartInfo;
		m_tAttackInfo.fCX = 25.f;
		m_tAttackInfo.fCY = 6.f;

		m_fSpeed = 10.f;
		break;

	default:
		break;
	}
}

int CRangedAttack::Update()
{
	switch (m_eAttackType)
	{
	case PLAYER_SKILL_1:
		if (abs(m_tAttackInfo.fX - StartInfo.fX) > 500 && 0 == m_iCrushCount)
			++m_iCrushCount;


		if (1 == m_iCrushCount)
		{
			CSoundMgr::Get_Instance()->PlaySound(L"hit_blood.wav", SOUND_HIT, 1.f);

			m_fXSpeed = 4.f;
			if(m_eDir == RIGHT)
			{
				m_fAngle = 45.f;
			}
			else
			{
				m_fAngle = 135.f;
			}
			m_tAttackInfo.fX -= m_fXSpeed * cos(RADIAN(m_fAngle));
			m_tAttackInfo.fY -= m_fYSpeed * sin(RADIAN(m_fAngle));
			m_fYSpeed -= 0.5f;
		}
		else if (2 <= m_iCrushCount)
		{
			m_fXSpeed = 0.f;
			m_fYSpeed = 0.f;
		}
		else
		{
			m_tAttackInfo.fX += m_fSpeed * cos(RADIAN(m_fAngle));
		}

		break;

	case ELDERENT_GRAPE:
		m_tAttackInfo.fX += m_fSpeed * cos(m_fAngle);
		m_tAttackInfo.fY -= m_fSpeed * sin(m_fAngle);
		break;

	case ELDERENT_BABYGRAPE:
		m_tAttackInfo.fX += m_fSpeed * cos(RADIAN(m_fAngle));
		m_tAttackInfo.fY -= m_fSpeed * sin(RADIAN(m_fAngle));
		break;

	case ARCHER_ATTACK:
		if (m_eDir == RIGHT)
			m_tAttackInfo.fX += m_fSpeed;
		else
			m_tAttackInfo.fX -= m_fSpeed;
		break;

	default:
		break;
	}

	__super::Move_frame();
	__super::Update_Rect();
	return 0;
}

void CRangedAttack::Late_Update()
{
	switch (m_eAttackType)
	{
	case PLAYER_SKILL_1:
		
		break;

	}
}

void CRangedAttack::Render(HDC hDC)
{
	Vec2 RenderPos = CCameraMgr::Get_Instance()->Get_RenderPos(m_tAttackInfo.fX, m_tAttackInfo.fY);

	// Ellipse(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
	switch (m_eAttackType)
	{
	case PLAYER_SKILL_1:		
	{
		HDC hBabyDC = CBmpMgr::Get_Instance()->Find_Image(L"Skul_Head");

		GdiTransparentBlt(hDC,
			RenderPos.fX - 7, RenderPos.fY - 7,
			15, 13,
			hBabyDC,
			0, 0,
			15, 13, RGB(255, 0, 255));
	}
		break;


	case ELDERENT_GRAPE:
	{
		HDC hBabyDC = CBmpMgr::Get_Instance()->Find_Image(L"Grape");

		GdiTransparentBlt(hDC,
			RenderPos.fX - 50, RenderPos.fY - 50,
			100, 100,
			hBabyDC,
			m_tFrame.iFrameStart * 100, 0,
			100, 100, RGB(0, 0, 0));
	}
		break;

	case ELDERENT_BABYGRAPE:
	{
		HDC hBabyDC = CBmpMgr::Get_Instance()->Find_Image(L"Baby_Grape");

		GdiTransparentBlt(hDC,
			RenderPos.fX - 18, RenderPos.fY - 18,
			35, 36,
			hBabyDC, 0, 0, 35, 36, RGB(255, 0, 255));
	}
		break;

	case ARCHER_ATTACK:
	{
		HDC hBabyDC = nullptr;

		if (m_eDir == RIGHT)
			hBabyDC = CBmpMgr::Get_Instance()->Find_Image(L"Arrow_Right");
		else
			hBabyDC = CBmpMgr::Get_Instance()->Find_Image(L"Arrow_Left");

		GdiTransparentBlt(hDC,
			RenderPos.fX - 12.5f, RenderPos.fY - 3.f,
			25, 6,
			hBabyDC, 0, 0, 25, 6, RGB(0, 0, 0));
	}
		break;

	default:
		break;
	}

}

void CRangedAttack::Release()
{
}

void CRangedAttack::Calculate_Dir()
{
	float x = m_pTarget->Get_Info().fX - m_tAttackInfo.fX;
	float y = m_pTarget->Get_Info().fY - m_tAttackInfo.fY;

	float hypo = sqrt(pow(x,2) + pow(y,2));

	m_fAngle = acosf(x / hypo);

	if (y > 0)
		m_fAngle *= -1;
}
