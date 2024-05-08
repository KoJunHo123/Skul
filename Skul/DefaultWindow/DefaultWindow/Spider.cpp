#include "stdafx.h"
#include "Spider.h"

#include "Player.h"
#include "Berserker.h"
#include "BmpMgr.h"
#include "CameraMgr.h"
#include "KeyMgr.h"
#include "UIMgr.h"

void CSpider::Initialize()
{
	m_tInfo.fCX = 150.f;
	m_tInfo.fCY = 150.f;

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/NPC/Spider.bmp", L"Spider");
	m_eRender = RENDER_NPC;

	m_tFrame = { 0, 8, 0, 100, GetTickCount() };
}

int CSpider::Update()
{
	Upgrade_Skul();
	__super::Move_Frame();
	return 0;
}

void CSpider::Late_Update()
{
}

void CSpider::Render(HDC hDC)
{
	Vec2 RenderPos = CCameraMgr::Get_Instance()->Get_RenderPos(m_tInfo.fX, m_tInfo.fY);
	HDC hSpiderDC = CBmpMgr::Get_Instance()->Find_Image(L"Spider");

	/*Rectangle(hDC, RenderPos.fX - m_tInfo.fCX / 2, RenderPos.fY - m_tInfo.fCY / 2
		, RenderPos.fX + m_tInfo.fCX / 2, RenderPos.fY + m_tInfo.fCY / 2);*/

	GdiTransparentBlt(hDC, RenderPos.fX - m_tInfo.fCX / 2, RenderPos.fY - m_tInfo.fCY / 2, 150, 150,
		hSpiderDC, m_tFrame.iFrameStart * 150, 0, 150, 150, RGB(255, 0, 255));


}

void CSpider::Release()
{
}

void CSpider::Upgrade_Skul()
{
	if (m_pTarget->Get_Info().fX <	m_tInfo.fX + m_tInfo.fCX / 2
		&& m_pTarget->Get_Info().fX > m_tInfo.fX - m_tInfo.fCX / 2
		&& m_pTarget->Get_Info().fY < m_tInfo.fY + m_tInfo.fCY / 2
		&& m_pTarget->Get_Info().fY > m_tInfo.fY - m_tInfo.fCY / 2)
	{
		if (BERSERKER == static_cast<CPlayer*>(m_pTarget)->Get_SkulType() 
			&& CKeyMgr::Get_Instance()->Key_Down('F')
			&& 0 == static_cast<CBerserker*>(m_pTarget)->Get_Tier()
			&& CUIMgr::Get_Instance()->Get_Bone() >= 100)
		{
			static_cast<CBerserker*>(m_pTarget)->Up_Tier();
			CUIMgr::Get_Instance()->Use_Bone(100);
		}
	}
}

void CSpider::EnforceSkul()
{
}

