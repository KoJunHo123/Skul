#include "stdafx.h"
#include "Door.h"

#include "BmpMgr.h"
#include "KeyMgr.h"
#include "SceneMgr.h"

CDoor::CDoor()
	: m_eDoor(DOOR_END)
	, m_bActivate(false)
	, m_tRectInfo{}
{
}

CDoor::CDoor(DOORTYPE _door)
	: m_eDoor(_door)
	, m_bActivate(false)
	, m_tRectInfo{0, 0, 100, 130}
{
}

CDoor::~CDoor()
{
}

void CDoor::Initialize()
{
	m_tFrame = { 0, 7, 0, 100, GetTickCount() };
	m_bDoor = true;
	m_eRender = RENDER_GAMEOBJECT;
	m_tRectInfo.fX = m_tInfo.fX;
	m_tRectInfo.fY = m_tInfo.fY;
	switch (m_eDoor)
	{
	case DUNGEON_ENT_DOOR:
		m_tInfo.fCX = 300.f;
		m_tInfo.fCY = 200.f;
		CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Door/Dungeon_Entrance_Door.bmp", L"Dungeon_Entrance_Door");
		m_pFrameKey = L"Dungeon_Entrance_Door";
		break;

	case STAGE_DOOR:
		m_tInfo.fCX = 215.f;
		m_tInfo.fCY = 159.f;
		CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Door/Stage_Door.bmp", L"Stage_Door");
		CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Door/Deactivate.bmp", L"Deactivate");
		m_pFrameKey = L"Deactivate";
		m_tFrame.iFrameEnd = 0;
		break;

	case BOSS_ENT_DOOR:
		m_tInfo.fCX = 400.f;
		m_tInfo.fCY = 200.f;
		CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Door/Boss_Entrance_Door.bmp", L"Boss_Entrance_Door");
		m_pFrameKey = L"Boss_Entrance_Door";
		break;

	default:
		break;
	}

}

int CDoor::Update()
{
	m_tRectInfo.fY = m_tInfo.fY + 20.f;

	__super::Move_Frame();
	return 0;
}

void CDoor::Late_Update()
{

}

void CDoor::Render(HDC hDC)
{
	HDC hDoorDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);

	Vec2 RemderPos = CCameraMgr::Get_Instance()->Get_RenderPos(m_tInfo.fX, m_tInfo.fY);
	

	GdiTransparentBlt(hDC, RemderPos.fX - m_tInfo.fCX / 2, RemderPos.fY - m_tInfo.fCY / 2, m_tInfo.fCX, m_tInfo.fCY,
		hDoorDC, m_tInfo.fCX * m_tFrame.iFrameStart, 0, m_tInfo.fCX, m_tInfo.fCY, RGB(255, 0, 255));
	


	// Rectangle(hDC, RemderPos.fX - m_tRectInfo.fCX / 2, RemderPos.fY - m_tRectInfo.fCY / 2, RemderPos.fX + m_tRectInfo.fCX / 2, RemderPos.fY + m_tRectInfo.fCY / 2);
}

void CDoor::Release()
{
}

void CDoor::Door_Activate()
{
	if (!m_bActivate && STAGE_DOOR == m_eDoor)
	{
		m_bActivate = true;
		m_pFrameKey = L"Stage_Door";
		m_tFrame.iFrameEnd = 7;
		m_tInfo.fCX = 200.f;
		m_tInfo.fCY = 200.f;
	}
}

bool CDoor::Get_Coll()
{
	if (m_pTarget->Get_Info().fX < m_tRectInfo.fX + m_tRectInfo.fCX / 2
		&& m_pTarget->Get_Info().fX > m_tRectInfo.fX - m_tRectInfo.fCX / 2
		&& m_pTarget->Get_Info().fY < m_tRectInfo.fY + m_tRectInfo.fCY / 2
		&& m_pTarget->Get_Info().fY > m_tRectInfo.fY - m_tRectInfo.fCY / 2)
	{
		return true;
	}
	return false;
}
