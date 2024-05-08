#include "stdafx.h"
#include "Obj.h"
#include "EffectMgr.h"


int CObj::m_iPlayerHp = 100;

CObj::CObj() 
	: m_fSpeed(0.f)
	, m_fYSpeed(0.f)
	, m_bDead(false)
	, m_iHp(0)
	, m_eRender(RENDER_END)
	, m_eDir(DIR_END)
	, m_eSaveDir(DIR_END)
	, m_eCurState(STATE_END)
	, m_ePreState(STATE_END)
	, m_pFrameKey(nullptr)
	, m_bGround(false)
	, m_bPlayer(false)
	, m_bBoss(false)
	, m_bMonster(false)
	, m_bDoor(false)
	, m_bCage(false)
	, m_iHittedDelay(GetTickCount())
	, m_bGroundClass(false)
	, m_bAttacking(false)
{
	ZeroMemory(&m_tInfo, sizeof(INFO));
	ZeroMemory(&m_tRect, sizeof(RECT));
	ZeroMemory(&m_tFrame, sizeof(FRAME));
}

CObj::~CObj()
{
}

void CObj::Update_Rect()
{
	m_tRect.left	= long(m_tInfo.fX - (m_tInfo.fCX * 0.5f));
	m_tRect.top		= long(m_tInfo.fY - (m_tInfo.fCY * 0.5f));
	m_tRect.right	= long(m_tInfo.fX + (m_tInfo.fCX * 0.5f));
	m_tRect.bottom	= long(m_tInfo.fY + (m_tInfo.fCY * 0.5f));

}

void CObj::Gravity()
{
	if (!m_bGround)
	{
		m_fYSpeed -= 0.35f;
	}
	else
	{
		m_fYSpeed = 0.f;
	}

	// 떨어지는 속도 제한
	if (m_fYSpeed < -7.f)
		m_fYSpeed = -7.f;

	m_tInfo.fY -= m_fYSpeed;
}


bool CObj::Hit(int _damage, DIRECTION _dir, int _knockback)
{
	if (m_bPlayer && !m_bGroundClass)
	{
		if (m_iHittedDelay + 500 < GetTickCount())
		{
			m_iPlayerHp -= _damage;

			if (RIGHT == _dir)
			{
				m_tInfo.fX += _knockback;
			}
			else
			{
				m_tInfo.fX -= _knockback;
			}
			CEffectMgr::Get_Instance()->Add_Effect(PLAYER_HIT, m_tInfo);
			m_iHittedDelay = GetTickCount();

			CSoundMgr::Get_Instance()->StopSound(SOUND_PLAYER_HIT);
			CSoundMgr::Get_Instance()->PlaySound(L"Skul_Hit.wav", SOUND_PLAYER_HIT, 1.f);
			return true;
		}
	}
	else if(m_bBoss || m_bGroundClass || m_bCage)
	{
		if (m_iHittedDelay + 300 < GetTickCount())
		{
			m_iHp -= _damage;
			m_iHittedDelay = GetTickCount();

			CSoundMgr::Get_Instance()->StopSound(SOUND_HIT);
			CSoundMgr::Get_Instance()->PlaySound(L"hit_blood.wav", SOUND_HIT, 1.f);
			return true;
		}
	}

	else
	{
		if (m_iHittedDelay + 300 < GetTickCount())
		{
			m_iHp -= _damage;

			int ranNum = GetRandomNum(0, 1);

			if (ranNum)
			{
				m_eCurState = HIT_1;
			}
			else
			{
				m_eCurState = HIT_2;
			}

			if (RIGHT == _dir)
			{
				m_tInfo.fX += _knockback;
				m_eDir = LEFT;
			}
			else
			{
				m_tInfo.fX -= _knockback;
				m_eDir = RIGHT;
			}

			m_iHittedDelay = GetTickCount();

			CSoundMgr::Get_Instance()->StopSound(SOUND_HIT);
			CSoundMgr::Get_Instance()->PlaySound(L"hit_blood.wav", SOUND_HIT, 1.f);
			return true;
		}
	}

	return false;
}

void CObj::Move_Frame()
{
	// 넘길 때 되면
	if (m_tFrame.dwTime + m_tFrame.dwSpeed < GetTickCount())
	{
		// 다음 프레임으로 넘어감
		++m_tFrame.iFrameStart;
		m_tFrame.dwTime = GetTickCount();

		// 끝나면 처음으로
		if (m_tFrame.iFrameStart > m_tFrame.iFrameEnd)
		{
			m_tFrame.iFrameStart = 0;
		}
	}
}


// 외부 함수 선언
int GetRandomNum(int _first, int _second)
{

	// 시드값을 얻기 위한 진짜 난수 생성.
	random_device rd;

	// 메르센 트위스터 유사 난수 생성 알고리즘(객체가 큼(2kb 이상), 메모리 부족하면 minstd_rand()가 나을수도...?)
	// mt19937
	minstd_rand gen(rd());

	// (a, b) 사이의 균일한 정수 분포 생성
	uniform_int_distribution<int> dis(_first, _second);

	return dis(gen);
}

