#include "stdafx.h"
#include "Drop.h"

CDrop::CDrop()
	: m_fWarigariSpeed(0.f)
	, m_bUpDown(true)
	, m_bStop(false)
{
}

CDrop::~CDrop()
{
}

void CDrop::MoveWariGari()
{
	if (m_fWarigariSpeed <= -0.5f)
		m_bUpDown = false;
	else if(m_fWarigariSpeed >= 0.5f)
		m_bUpDown = true;

	m_tInfo.fY -= m_fWarigariSpeed;
	
	if (m_bUpDown)
		m_fWarigariSpeed -= 0.01f;
	else
		m_fWarigariSpeed += 0.01f;
}

bool CDrop::Get_Coll()
{
	if (m_pTarget->Get_Info().fX <	m_tRectInfo.fX + m_tRectInfo.fCX / 2
		&& m_pTarget->Get_Info().fX > m_tRectInfo.fX - m_tRectInfo.fCX / 2
		&& m_pTarget->Get_Info().fY < m_tRectInfo.fY + m_tRectInfo.fCY / 2
		&& m_pTarget->Get_Info().fY > m_tRectInfo.fY - m_tRectInfo.fCY / 2)
	{
		return true;
	}
	return false;
}