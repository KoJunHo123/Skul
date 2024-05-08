#include "stdafx.h"
#include "Reward.h"
#include "BmpMgr.h"
#include "CameraMgr.h"
#include "ObjMgr.h"
#include "AbstractFactory.h"

#include "DropSkul.h"

CReward::CReward()
	: m_eReward(REWARD_END)
	, m_bActivate(false)
	, m_tRectInfo{}
	, m_bGetReward(false)
{
}

CReward::~CReward()
{
}

void CReward::Initialize()
{
	m_eRender = RENDER_GAMEOBJECT;
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Reward/Altar.bmp", L"Altar");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Reward/Reward_Skul.bmp", L"Reward_Skul");

	m_pFrameKey = L"Reward_Skul";

	m_tFrame = {0, 0, 0, 100, GetTickCount()};


	m_tRectInfo.fX = m_tInfo.fX + 160;
	m_tRectInfo.fY = m_tInfo.fY + 50;
	m_tRectInfo.fCX = 70.f;
	m_tRectInfo.fCY = 70.f;

}

int CReward::Update()
{
	if (m_bDead)
		return OBJ_DEAD;

	__super::Move_Frame();
	return 0;
}

void CReward::Late_Update()
{
	if (m_tFrame.iMotion == 1 && m_tFrame.iFrameStart == m_tFrame.iFrameEnd)
	{
		--m_tFrame.iFrameStart;
	}

}

void CReward::Render(HDC hDC)
{
	HDC hAltarDC = CBmpMgr::Get_Instance()->Find_Image(L"Altar");
	HDC hRewardDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);

	Vec2 RenderPos = CCameraMgr::Get_Instance()->Get_RenderPos(m_tInfo.fX, m_tInfo.fY);

	GdiTransparentBlt(hDC, RenderPos.fX - m_tInfo.fCX / 2, RenderPos.fY - 45, 312, 125,
		hAltarDC, 0,0, 312, 125, RGB(255, 0, 255));

	if (m_bActivate)
		GdiTransparentBlt(hDC, RenderPos.fX + 110, RenderPos.fY - 20, 100, 100,
			hRewardDC, 200 * m_tFrame.iFrameStart, 200 * m_tFrame.iMotion, 200, 200, RGB(255, 0, 255));


	//Vec2 RenderPos_2 = CCameraMgr::Get_Instance()->Get_RenderPos(m_tRectInfo.fX, m_tRectInfo.fY);
	// Rectangle(hDC, RenderPos_2.fX - m_tRectInfo.fCX / 2, RenderPos_2.fY - m_tRectInfo.fCY / 2, RenderPos_2.fX + m_tRectInfo.fCX / 2, RenderPos_2.fY + m_tRectInfo.fCY / 2);
}

void CReward::Release()
{
}

bool CReward::Get_Coll()
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

void CReward::Get_Reward()
{
	if(!m_bGetReward)
	{
		m_tFrame = { 0, 10, 1, 100, GetTickCount() };
		CObjMgr::Get_Instance()->Add_Object(OBJ_DROP, CAbstractFactory<CDropSkul>::Create(m_tInfo.fX, m_tInfo.fY));
		CObjMgr::Get_Instance()->Get_Drop()->Set_Target(m_pTarget);
		m_bGetReward = true;
	}
}
