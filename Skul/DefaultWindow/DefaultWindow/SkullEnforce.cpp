#include "stdafx.h"
#include "SkullEnforce.h"
#include "SceneMgr.h"

#include "Spider.h"

CSkullEnforce::CSkullEnforce()
{
}

CSkullEnforce::~CSkullEnforce()
{
	Release();
}

void CSkullEnforce::Initialize()
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Map/Normal_Map_Back_Back.bmp", L"Normal_Map_Back_Back");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Map/Normal_Map_4.bmp", L"Normal_Map_4");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Map/Skull_Enforce/Skull_Enforce.bmp", L"Skull_Enforce");

	m_mapSize = { 1500, 900 };
	CCameraMgr::Get_Instance()->Set_MapSize(m_mapSize.fX, m_mapSize.fY);


	CObjMgr::Get_Instance()->Get_Player()->Set_Pos(50, 635);

#pragma region ¹®Â¦
	// ¹®Â¦
	CObjMgr::Get_Instance()->Add_Object(OBJ_DOOR, new CDoor(STAGE_DOOR));
	CObjMgr::Get_Instance()->Get_Door()->Set_Pos(1250, 590);
	CObjMgr::Get_Instance()->Get_Door()->Set_Target(CObjMgr::Get_Instance()->Get_Player());
	CObjMgr::Get_Instance()->Get_Door()->Initialize();
#pragma endregion

	// °Å¹Ì·Ã
	CObjMgr::Get_Instance()->Add_Object(OBJ_NPC, CAbstractFactory<CSpider>::Create(650, 700));
	CObjMgr::Get_Instance()->Get_NPC()->Set_Target(CObjMgr::Get_Instance()->Get_Player());
	
	m_iLeftMonster = 0;
	CUIMgr::Get_Instance()->Set_LeftMonster(&m_iLeftMonster);

#pragma region ÁöÇü
	CObjMgr::Get_Instance()->Add_Object(OBJ_GROUND, CAbstractFactory<CGround>::Create());
	static_cast<CGround*>(CObjMgr::Get_Instance()->Get_Ground())->Set_Rect({ 0, 650, 310, 900 });

	CObjMgr::Get_Instance()->Add_Object(OBJ_GROUND, CAbstractFactory<CGround>::Create());
	static_cast<CGround*>(CObjMgr::Get_Instance()->Get_Ground())->Set_Rect({ 300, 760, 890, 900});

	CObjMgr::Get_Instance()->Add_Object(OBJ_GROUND, CAbstractFactory<CGround>::Create());
	static_cast<CGround*>(CObjMgr::Get_Instance()->Get_Ground())->Set_Rect({ 880, 650, 1500, 765});
#pragma endregion
}

int CSkullEnforce::Update()
{
	CObjMgr::Get_Instance()->Update();
	if (CKeyMgr::Get_Instance()->Key_Down('G'))
	{
		CSceneMgr::Get_Instance()->Scene_Change(SC_BOSSENT);
	}

	return 0;
}

void CSkullEnforce::Late_Update()
{
	CObjMgr::Get_Instance()->Late_Update();

	if (0 == m_iLeftMonster)
	{
		if (CObjMgr::Get_Instance()->Get_Door())
			static_cast<CDoor*>(CObjMgr::Get_Instance()->Get_Door())->Door_Activate();
	}

	if (CObjMgr::Get_Instance()->Get_Door() && static_cast<CDoor*>(CObjMgr::Get_Instance()->Get_Door())->Get_Activate())
	{
		if (static_cast<CDoor*>(CObjMgr::Get_Instance()->Get_Door())->Get_Coll())
			if (CKeyMgr::Get_Instance()->Key_Down('F'))
			{
				CSceneMgr::Get_Instance()->Scene_Change(SC_BOSSENT);
			}
	}

}

void CSkullEnforce::Render(HDC hDC)
{	
	// HDC	hGroundDC = CBmpMgr::Get_Instance()->Find_Image(L"Dungeon_Entrance_Ground");
	HDC	hBackDC = CBmpMgr::Get_Instance()->Find_Image(L"Normal_Map_Back_Back");
	HDC hNoraml_MapDC = CBmpMgr::Get_Instance()->Find_Image(L"Normal_Map_4");
	HDC hSkull_Enforce_DC = CBmpMgr::Get_Instance()->Find_Image(L"Skull_Enforce");

	Vec2 Dist = CCameraMgr::Get_Instance()->Get_Distance();
	Vec2 BackDist = CCameraMgr::Get_Instance()->Get_BackDistance();

	GdiTransparentBlt(hDC, -BackDist.fX * 0.5f, -BackDist.fY * 0.5f - 200, 960, 800, hBackDC, 0, 0, 960, 800, RGB(255, 0, 255));
	GdiTransparentBlt(hDC, -BackDist.fX, -BackDist.fY - 200, 1150, 800, hNoraml_MapDC, 0, 0, 1150, 800, RGB(255, 0, 255));
	GdiTransparentBlt(hDC, -Dist.fX, -Dist.fY, m_mapSize.fX, m_mapSize.fY, hSkull_Enforce_DC, 0, 0, m_mapSize.fX, m_mapSize.fY, RGB(0, 0, 0));

	CObjMgr::Get_Instance()->Render(hDC);

}

void CSkullEnforce::Release()
{
	CObjMgr::Get_Instance()->Delete_ExceptPlayer();
	CLineMgr::Get_Instance()->Destroy();
	CSoundMgr::Get_Instance()->StopAll();
}
