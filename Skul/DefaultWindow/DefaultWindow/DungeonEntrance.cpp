#include "stdafx.h"
#include "DungeonEntrance.h"
#include "SceneMgr.h"

float		g_fVolume(0.5f);

CDungeonEntrance::CDungeonEntrance()
{
}

CDungeonEntrance::~CDungeonEntrance()
{
	Release();
}

void CDungeonEntrance::Initialize()
{
	// CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Map/Dungeon_Entrance/Duegeon_Entrance_Ground.bmp", L"Duegeon_Entrance_Ground");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Map/Dungeon_Entrance/Dungeon_Entrance.bmp", L"Dungeon_Entrance");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Map/Dungeon_Entrance/Dungeon_Entrance_Castle.bmp", L"Dungeon_Entrance_Castle");

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Map/Stage_back.bmp", L"Stage_back");

	m_mapSize = { 1085, 780 };
	CCameraMgr::Get_Instance()->Set_MapSize(m_mapSize.fX, m_mapSize.fY);


	//// 테스트용
	//CObjMgr::Get_Instance()->Add_Object(OBJ_PLAYER, CAbstractFactory<CLittleBone>::Create());
	//CUIMgr::Get_Instance()->Set_Player(CObjMgr::Get_Instance()->Get_Player());
	CObjMgr::Get_Instance()->Get_Player()->Set_Pos(m_mapSize.fX / 2, 0);

	// 문 세팅..
	CObjMgr::Get_Instance()->Add_Object(OBJ_DOOR, new CDoor(DUNGEON_ENT_DOOR));
	CObjMgr::Get_Instance()->Get_Door()->Set_Pos(550, 625);
	CObjMgr::Get_Instance()->Get_Door()->Set_Target(CObjMgr::Get_Instance()->Get_Player());
	CObjMgr::Get_Instance()->Get_Door()->Initialize();

#pragma region
	// 지형 확정
	CObjMgr::Get_Instance()->Add_Object(OBJ_GROUND, CAbstractFactory<CGround>::Create());
	static_cast<CGround*>(CObjMgr::Get_Instance()->Get_Ground())->Set_Rect({ 0, 700, 1200, 785 });

	CObjMgr::Get_Instance()->Add_Object(OBJ_GROUND, CAbstractFactory<CGround>::Create());
	static_cast<CGround*>(CObjMgr::Get_Instance()->Get_Ground())->Set_Rect({ -100, 0, 0, 1000 });


	CObjMgr::Get_Instance()->Add_Object(OBJ_GROUND, CAbstractFactory<CGround>::Create());
	static_cast<CGround*>(CObjMgr::Get_Instance()->Get_Ground())->Set_Rect({ 1088, 0, 1150, 1000 });
#pragma endregion

	CSoundMgr::Get_Instance()->PlayBGM(L"Chapter1.wav", 1.f);

}

int CDungeonEntrance::Update()
{
	CObjMgr::Get_Instance()->Update();
	CBattleMgr::Get_Instance()->Update();


	return 0;
}

void CDungeonEntrance::Late_Update()
{
	CObjMgr::Get_Instance()->Late_Update();
	CBattleMgr::Get_Instance()->Late_Update();

	if (static_cast<CDoor*>(CObjMgr::Get_Instance()->Get_Door())->Get_Coll())
		if (CKeyMgr::Get_Instance()->Key_Down('F'))
		{
			CSceneMgr::Get_Instance()->Scene_Change(SC_STAGE1);
		}
		

	
}

void CDungeonEntrance::Render(HDC hDC)
{
	// HDC	hGroundDC = CBmpMgr::Get_Instance()->Find_Image(L"Duegeon_Entrance_Ground");
	HDC	hDungeon_EntranceDC = CBmpMgr::Get_Instance()->Find_Image(L"Dungeon_Entrance");
	HDC hStage_back_DC = CBmpMgr::Get_Instance()->Find_Image(L"Stage_back");
	HDC hEntrance_Castle_DC = CBmpMgr::Get_Instance()->Find_Image(L"Dungeon_Entrance_Castle");

	Vec2 Dist = CCameraMgr::Get_Instance()->Get_Distance();
	Vec2 BackDist = CCameraMgr::Get_Instance()->Get_BackDistance();
	GdiTransparentBlt(hDC, -BackDist.fX * 0.5f, -BackDist.fY * 0.5f , 960, 400, hStage_back_DC, 0, 200, 960 , 400, RGB(255, 0, 255));
	GdiTransparentBlt(hDC, -BackDist.fX * 0.5f - 200, -BackDist.fY * 0.5f - 700, 1050, 1260, hEntrance_Castle_DC, 0, 0, 1050, 1260, RGB(255, 0, 255));
	GdiTransparentBlt(hDC, -Dist.fX, -Dist.fY, m_mapSize.fX, m_mapSize.fY, hDungeon_EntranceDC, 0, 0, m_mapSize.fX, m_mapSize.fY, RGB(255, 0, 255));

	CObjMgr::Get_Instance()->Render(hDC);
	CBattleMgr::Get_Instance()->Render(hDC);
}

void CDungeonEntrance::Release()
{
	CObjMgr::Get_Instance()->Delete_ExceptPlayer();
	CBmpMgr::Get_Instance()->Delete_Image(L"Dungeon_Entrance" );
	CBmpMgr::Get_Instance()->Delete_Image(L"Stage_back");
	CBmpMgr::Get_Instance()->Delete_Image(L"Dungeon_Entrance_Castle");
}
