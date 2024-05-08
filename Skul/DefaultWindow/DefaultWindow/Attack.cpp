#include "stdafx.h"
#include "Attack.h"

CAttack::CAttack()
	: m_pInfo{}
	, m_tAttackInfo{}
	, m_eAttackType(ATTACKTYPE_END)
	, m_bPlayerAttack(false)
	, m_iDamage(0)
{
}

CAttack::CAttack(INFO* _pInfo, ATTACKTYPE _attType, DIRECTION _dir, int _damage, bool _bPlayerAttack, bool* _attacking)
	: m_pInfo(_pInfo)
	, m_tAttackInfo{}
	, m_eAttackType(_attType)
	, m_eDir(_dir)
	, m_bPlayerAttack(_bPlayerAttack)
	, m_bAttacking(_attacking)
	, m_iDamage(_damage)
{
}


CAttack::~CAttack()
{
}

void CAttack::Initialize()
{
}

int CAttack::Update()
{
	return 0;
}

void CAttack::Late_Update()
{
}

void CAttack::Render(HDC hDC)
{
}

void CAttack::Release()
{
}


void CAttack::Update_Rect()
{
	m_tRect.left = long(m_tAttackInfo.fX - (m_tAttackInfo.fCX * 0.5f));
	m_tRect.top = long(m_tAttackInfo.fY - (m_tAttackInfo.fCY * 0.5f));
	m_tRect.right = long(m_tAttackInfo.fX + (m_tAttackInfo.fCX * 0.5f));
	m_tRect.bottom = long(m_tAttackInfo.fY + (m_tAttackInfo.fCY * 0.5f));
}

void CAttack::Move_frame()
{
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
