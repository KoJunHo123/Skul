#include "stdafx.h"
#include "DropSkul.h"

#include "CameraMgr.h"
#include "BmpMgr.h"
#include "KeyMgr.h"
#include "ObjMgr.h"
#include "AbstractFactory.h"
#include "Berserker.h"

CDropSkul::CDropSkul()
{
}

CDropSkul::~CDropSkul()
{
}

void CDropSkul::Initialize()
{
	m_fYSpeed += 5.f;

	m_tInfo.fCX = 35.f;
	m_tInfo.fCY = 19.f;

	m_tRectInfo = { m_tInfo.fX + 160, m_tInfo.fY + 30, 50.f, 50.f };

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Drop/Berserker.bmp", L"Berserker_Head");

	m_eRender = RENDER_DROP;
}

int CDropSkul::Update()
{
	if (m_bDead)
		return OBJ_DEAD;

	if(!m_bStop)
	{
		m_tInfo.fY -= m_fYSpeed;

		m_fYSpeed -= 0.5f;
		if (m_fYSpeed < -5.f)
		{
			m_fYSpeed = 0.f;
			m_bStop = true;
		}
	}
	else
		MoveWariGari();

	return 0;
}

void CDropSkul::Late_Update()
{
	if (Get_Coll())
	{
		if (CKeyMgr::Get_Instance()->Key_Down('F'))
		{
			if(CObjMgr::Get_Instance()->Get_PlayerCount() <= 1)
			{
				CObjMgr::Get_Instance()->Add_Object(OBJ_PLAYER, CAbstractFactory<CBerserker>::Create(m_pTarget->Get_Info().fX, m_pTarget->Get_Info().fY));
				m_bDead = true;
			}
		}
	}
}

void CDropSkul::Render(HDC hDC)
{
	HDC hBerserkerHeadDC = CBmpMgr::Get_Instance()->Find_Image(L"Berserker_Head");

	Vec2 RenderPos = CCameraMgr::Get_Instance()->Get_RenderPos(m_tInfo.fX, m_tInfo.fY);
	 
	GdiTransparentBlt(hDC, RenderPos.fX - m_tInfo.fCX / 2 + 160, RenderPos.fY - m_tInfo.fCY / 2 + 30, m_tInfo.fCX, m_tInfo.fCY,
		hBerserkerHeadDC, 0, 0, m_tInfo.fCX, m_tInfo.fCY, RGB(255, 0, 255));

	//Rectangle(hDC, RenderPos.fX - m_tInfo.fCX / 2, RenderPos.fY - m_tInfo.fCY / 2, RenderPos.fX + m_tInfo.fCX / 2, RenderPos.fY + m_tInfo.fCY / 2);

}

void CDropSkul::Release()
{
}
