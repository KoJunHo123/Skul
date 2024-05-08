#include "stdafx.h"
#include "BossEntrance.h"
#include "SceneMgr.h"

CBossEntrance::CBossEntrance()
{
}

CBossEntrance::~CBossEntrance()
{
	Release();
}

void CBossEntrance::Initialize()
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Map/Boss_Entrance/Boss_Entrance_Sky.bmp", L"Boss_Entrance_Sky");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Map/Boss_Entrance/Boss_Entrance.bmp", L"Boss_Entrance");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Map/Boss_Entrance/Boss_Entrance_Back.bmp", L"Boss_Entrance_Back");

	m_mapSize = { 900, 560 };
	CCameraMgr::Get_Instance()->Set_MapSize(m_mapSize.fX, m_mapSize.fY);


	// 테스트용
	//CObjMgr::Get_Instance()->Add_Object(OBJ_PLAYER, CAbstractFactory<CLittleBone>::Create());
	//CObjMgr::Get_Instance()->Add_Object(OBJ_PLAYER, CAbstractFactory<CBerserker>::Create());
	//CUIMgr::Get_Instance()->Set_Player(CObjMgr::Get_Instance()->Get_Player());
	CObjMgr::Get_Instance()->Get_Player()->Set_Pos(370, 425);

	// 문
	CObjMgr::Get_Instance()->Add_Object(OBJ_DOOR, new CDoor(BOSS_ENT_DOOR));
	CObjMgr::Get_Instance()->Get_Door()->Set_Pos(450, 360);
	CObjMgr::Get_Instance()->Get_Door()->Set_Target(CObjMgr::Get_Instance()->Get_Player());
	CObjMgr::Get_Instance()->Get_Door()->Initialize();

#pragma region 지형
	CObjMgr::Get_Instance()->Add_Object(OBJ_GROUND, CAbstractFactory<CGround>::Create());
	static_cast<CGround*>(CObjMgr::Get_Instance()->Get_Ground())->Set_Rect({ 100, 440, 800, 560 });

	CObjMgr::Get_Instance()->Add_Object(OBJ_GROUND, CAbstractFactory<CGround>::Create());
	static_cast<CGround*>(CObjMgr::Get_Instance()->Get_Ground())->Set_Rect({ 0, 340, 150, 440 });

	CObjMgr::Get_Instance()->Add_Object(OBJ_GROUND, CAbstractFactory<CGround>::Create());
	static_cast<CGround*>(CObjMgr::Get_Instance()->Get_Ground())->Set_Rect({ 0, 100, 20, 350 });

	CObjMgr::Get_Instance()->Add_Object(OBJ_GROUND, CAbstractFactory<CGround>::Create());
	static_cast<CGround*>(CObjMgr::Get_Instance()->Get_Ground())->Set_Rect({ 750, 340, 900, 440 });

	CObjMgr::Get_Instance()->Add_Object(OBJ_GROUND, CAbstractFactory<CGround>::Create());
	static_cast<CGround*>(CObjMgr::Get_Instance()->Get_Ground())->Set_Rect({ 900, 100, 920, 350 });
#pragma endregion
	
}

int CBossEntrance::Update()
{
	CObjMgr::Get_Instance()->Update();
	if (CKeyMgr::Get_Instance()->Key_Down('G'))
	{
		CSceneMgr::Get_Instance()->Scene_Change(SC_BOSS);
	}


    return 0;
}

void CBossEntrance::Late_Update()
{
	CObjMgr::Get_Instance()->Late_Update();

	if (static_cast<CDoor*>(CObjMgr::Get_Instance()->Get_Door())->Get_Coll())
		if (CKeyMgr::Get_Instance()->Key_Down('F'))
		{
			CSceneMgr::Get_Instance()->Scene_Change(SC_BOSS);
		}
}

void CBossEntrance::Render(HDC hDC)
{
	HDC hSkyDC = CBmpMgr::Get_Instance()->Find_Image(L"Boss_Entrance_Sky");
	HDC hBackDC = CBmpMgr::Get_Instance()->Find_Image(L"Boss_Entrance_Back");
	HDC	hBoss_Entrance_DC = CBmpMgr::Get_Instance()->Find_Image(L"Boss_Entrance");

	Vec2 Dist = CCameraMgr::Get_Instance()->Get_Distance();
	Vec2 BackDist = CCameraMgr::Get_Instance()->Get_BackDistance();

	GdiTransparentBlt(hDC, -BackDist.fX * 0.5f, -BackDist.fY * 0.5f, 900, 560, hSkyDC, 0, 0, 900, 560, RGB(0, 0, 0));

	GdiTransparentBlt(hDC, -BackDist.fX, -BackDist.fY, 900, 560, hBackDC, 0, 0, 900, 560, RGB(255, 0, 255));

	GdiTransparentBlt(hDC, -Dist.fX, -Dist.fY, 900, 560, hBoss_Entrance_DC, 0, 0, 900, 560, RGB(0, 0, 0));


	CObjMgr::Get_Instance()->Render(hDC);

}

void CBossEntrance::Release()
{
	CObjMgr::Get_Instance()->Delete_ExceptPlayer();

}
