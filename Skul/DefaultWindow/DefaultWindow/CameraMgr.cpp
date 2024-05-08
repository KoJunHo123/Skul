#include "stdafx.h"
#include "CameraMgr.h"

CCameraMgr* CCameraMgr::m_pInstance = nullptr;

CCameraMgr::CCameraMgr()
	: m_distance()
	, m_mapSize{}
	, m_bCameraShake(false)
	, m_iCameraShakeDelay(GetTickCount())
{
}

CCameraMgr::~CCameraMgr()
{
}

void CCameraMgr::CalculateDist(float _x, float _y)
{
	m_distance.fX = _x - WINCX / 2;
	m_distance.fY = _y - WINCY / 2;
	StopCamera();
}

Vec2 CCameraMgr::Get_RenderPos(float _fX, float _fY)
{
	Vec2 dis;
	dis.fX = _fX - m_distance.fX;
	dis.fY = _fY - m_distance.fY;

	return dis;
}

Vec2 CCameraMgr::Get_BackDistance()
{
	Vec2 Distance = { m_distance.fX / 2, m_distance.fY / 2 };

	return Distance;
}

void CCameraMgr::StopCamera()
{
	if (0 > m_distance.fX)
	{
		m_distance.fX = 0;
	}
	else if (m_mapSize.fX  - WINCX < m_distance.fX)
	{
		m_distance.fX = m_mapSize.fX - WINCX;
	}

	if (0 > m_distance.fY)
	{
		m_distance.fY = 0;
	}
	else if (m_mapSize.fY - WINCY < m_distance.fY)
	{
		m_distance.fY = m_mapSize.fY - WINCY;
	}
}

void CCameraMgr::ShakeCamera()
{
	if(m_iCameraShakeDelay + 50 < GetTickCount())
	{
		if (m_bCameraShake)
			m_distance.fX += 10.f;
		else
			m_distance.fX -= 10.f;

		m_bCameraShake = !m_bCameraShake;

		m_iCameraShakeDelay = GetTickCount();
	}
}
