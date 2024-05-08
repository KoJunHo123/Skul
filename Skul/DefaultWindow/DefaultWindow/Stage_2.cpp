#include "stdafx.h"
#include "Stage_2.h"
#include "SceneMgr.h"
#include "Caged.h"

CStage_2::CStage_2()
	: m_bMonster_1(false)
	, m_bMonster_2(false)
	, m_bMonster_3(false)
{
}

CStage_2::~CStage_2()
{
	Release();
}

void CStage_2::Initialize()
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Map/Normal_Map_Back_Back.bmp", L"Normal_Map_Back_Back");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Map/Normal_Map_4.bmp", L"Normal_Map_4");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Map/Stage_2/Stage_2.bmp", L"Stage_2");


	m_mapSize = { 1305, 729 };
	CCameraMgr::Get_Instance()->Set_MapSize(m_mapSize.fX, m_mapSize.fY);

	
	// 테스트
	//CObjMgr::Get_Instance()->Add_Object(OBJ_PLAYER, CAbstractFactory<CLittleBone>::Create());
	//CObjMgr::Get_Instance()->Add_Object(OBJ_PLAYER, CAbstractFactory<CBerserker>::Create());
	//CUIMgr::Get_Instance()->Set_Player(CObjMgr::Get_Instance()->Get_Player());
	
	CObjMgr::Get_Instance()->Get_Player()->Set_Pos(80, 510);

#pragma region 지형
	// 지형 확정
	CObjMgr::Get_Instance()->Add_Object(OBJ_GROUND, CAbstractFactory<CGround>::Create());
	static_cast<CGround*>(CObjMgr::Get_Instance()->Get_Ground())->Set_Rect({ 0,525, 180,720});

	CObjMgr::Get_Instance()->Add_Object(OBJ_GROUND, CAbstractFactory<CGround>::Create());
	static_cast<CGround*>(CObjMgr::Get_Instance()->Get_Ground())->Set_Rect({ 180, 585, 325, 725});

	CObjMgr::Get_Instance()->Add_Object(OBJ_GROUND, CAbstractFactory<CGround>::Create());
	static_cast<CGround*>(CObjMgr::Get_Instance()->Get_Ground())->Set_Rect({ 320, 645, 485, 720	});

	CObjMgr::Get_Instance()->Add_Object(OBJ_GROUND, CAbstractFactory<CGround>::Create());
	static_cast<CGround*>(CObjMgr::Get_Instance()->Get_Ground())->Set_Rect({ 485, 530, 1185, 655});

	CObjMgr::Get_Instance()->Add_Object(OBJ_GROUND, CAbstractFactory<CGround>::Create());
	static_cast<CGround*>(CObjMgr::Get_Instance()->Get_Ground())->Set_Rect({ 1185, 405, 1300, 525});

	CObjMgr::Get_Instance()->Add_Object(OBJ_GROUND, CAbstractFactory<CGround>::Create());
	static_cast<CGround*>(CObjMgr::Get_Instance()->Get_Ground())->Set_Rect({ 1100, 175, 1300, 325});

	CObjMgr::Get_Instance()->Add_Object(OBJ_GROUND, CAbstractFactory<CGround>::Create());
	static_cast<CGround*>(CObjMgr::Get_Instance()->Get_Ground())->Set_Rect({ 1060, 0, 1300, 165	});

	CObjMgr::Get_Instance()->Add_Object(OBJ_GROUND, CAbstractFactory<CGround>::Create());
	static_cast<CGround*>(CObjMgr::Get_Instance()->Get_Ground())->Set_Rect({ 1115, 315,  1170, 365});

	CObjMgr::Get_Instance()->Add_Object(OBJ_GROUND, CAbstractFactory<CGround>::Create());
	static_cast<CGround*>(CObjMgr::Get_Instance()->Get_Ground())->Set_Rect({ 1145, 345, 1195, 380});

	CObjMgr::Get_Instance()->Add_Object(OBJ_GROUND, CAbstractFactory<CGround>::Create());
	static_cast<CGround*>(CObjMgr::Get_Instance()->Get_Ground())->Set_Rect({ 1160 ,370, 1205 ,395});

	CObjMgr::Get_Instance()->Add_Object(OBJ_GROUND, CAbstractFactory<CGround>::Create());
	static_cast<CGround*>(CObjMgr::Get_Instance()->Get_Ground())->Set_Rect({ -100 ,0, 0 ,800 });

	CObjMgr::Get_Instance()->Add_Object(OBJ_GROUND, CAbstractFactory<CGround>::Create());
	static_cast<CGround*>(CObjMgr::Get_Instance()->Get_Ground())->Set_Rect({ 1300 ,1400, 0 ,800 });

	CLineMgr::Get_Instance()->AddLine({ 340, 436 }, { 478, 436 });
	CLineMgr::Get_Instance()->AddLine({ 484, 379 }, { 540, 379 });
	CLineMgr::Get_Instance()->AddLine({ 573, 320 }, { 1095, 320 });
#pragma endregion

#pragma region 문짝
	CObjMgr::Get_Instance()->Add_Object(OBJ_DOOR, new CDoor(STAGE_DOOR));
	CObjMgr::Get_Instance()->Get_Door()->Set_Pos(820, 260);
	CObjMgr::Get_Instance()->Get_Door()->Set_Target(CObjMgr::Get_Instance()->Get_Player());
	CObjMgr::Get_Instance()->Get_Door()->Initialize();
#pragma endregion

	m_iLeftMonster = 17;
	CUIMgr::Get_Instance()->Set_LeftMonster(&m_iLeftMonster);
	CObjMgr::Get_Instance()->Set_MonsterCount(&m_iLeftMonster);


	CObjMgr::Get_Instance()->Add_Object(OBJ_CAGE, CAbstractFactory<CCaged>::Create( 1100, 480));

}

int CStage_2::Update()
{
	CObjMgr::Get_Instance()->Update();

	if (CKeyMgr::Get_Instance()->Key_Down('G'))
	{
		CSceneMgr::Get_Instance()->Scene_Change(SC_SKULENF);
	}

	return 0;
}

void CStage_2::Late_Update()
{	
	Set_Monster();


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
				CSceneMgr::Get_Instance()->Scene_Change(SC_SKULENF);
			}
	}

}

void CStage_2::Render(HDC hDC)
{
	// HDC	hGroundDC = CBmpMgr::Get_Instance()->Find_Image(L"Dungeon_Entrance_Ground");
	HDC	hBackDC = CBmpMgr::Get_Instance()->Find_Image(L"Normal_Map_Back_Back");
	HDC hNoraml_MapDC = CBmpMgr::Get_Instance()->Find_Image(L"Normal_Map_4");
	HDC hStage_2_DC = CBmpMgr::Get_Instance()->Find_Image(L"Stage_2");

	Vec2 Dist = CCameraMgr::Get_Instance()->Get_Distance();
	Vec2 BackDist = CCameraMgr::Get_Instance()->Get_BackDistance();

	GdiTransparentBlt(hDC, -BackDist.fX * 0.5f, -BackDist.fY * 0.5f - 200, 960, 800, hBackDC, 0, 0, 960, 800, RGB(255, 0, 255));

	GdiTransparentBlt(hDC, -BackDist.fX, -BackDist.fY - 200, 1150, 800, hNoraml_MapDC, 0, 0, 1150, 800, RGB(255, 0, 255));

	GdiTransparentBlt(hDC, -Dist.fX, -Dist.fY, m_mapSize.fX, m_mapSize.fY, hStage_2_DC, 0, 0, m_mapSize.fX, m_mapSize.fY, RGB(0, 0, 0));


	CObjMgr::Get_Instance()->Render(hDC);
	CLineMgr::Get_Instance()->Render(hDC);
}

void CStage_2::Release()
{
	CObjMgr::Get_Instance()->Delete_ExceptPlayer();
	CLineMgr::Get_Instance()->Release();
	//CBmpMgr::Get_Instance()->Release();

	// CObjMgr::Get_Instance()->Destroy();

}

void CStage_2::Set_Monster()
{

	CObj* player = CObjMgr::Get_Instance()->Get_Player();

	if (!m_bMonster_1 && player->Get_Info().fX > 150 )
	{
		CEffectMgr::Get_Instance()->Add_Monster(SOLDIER,	{ 280, 570, 0, 0 });
		CEffectMgr::Get_Instance()->Add_Monster(SOLDIER,	{ 400, 640, 0, 0 });

		m_bMonster_1 = true;

	}

	if (!m_bMonster_2 && player->Get_Info().fX > 600 && player->Get_Info().fY > 350)
	{
		CEffectMgr::Get_Instance()->Add_Monster(SOLDIER,	{ 580, 515, 0, 0 });
		CEffectMgr::Get_Instance()->Add_Monster(SOLDIER,	{ 630, 515, 0, 0 });
		CEffectMgr::Get_Instance()->Add_Monster(SOLDIER,	{ 680, 515, 0, 0 });
		CEffectMgr::Get_Instance()->Add_Monster(SOLDIER,	{ 730, 515, 0, 0 });
		CEffectMgr::Get_Instance()->Add_Monster(SOLDIER,	{ 780, 515, 0, 0 });
		CEffectMgr::Get_Instance()->Add_Monster(SOLDIER,	{ 830, 515, 0, 0 });
		CEffectMgr::Get_Instance()->Add_Monster(SOLDIER,	{ 880, 515, 0, 0 });
		CEffectMgr::Get_Instance()->Add_Monster(ARCHER,		{ 930, 515, 0, 0 });
		CEffectMgr::Get_Instance()->Add_Monster(ARCHER,	{ 980, 515, 0, 0 });
		m_bMonster_2 = true;
	}


	if (!m_bMonster_3 && player->Get_Info().fX > 600 && player->Get_Info().fY < 350)
	{
		CEffectMgr::Get_Instance()->Add_Monster(SOLDIER,	{ 700, 300, 0, 0 });
		CEffectMgr::Get_Instance()->Add_Monster(SOLDIER,	{ 750, 300, 0, 0 });
		CEffectMgr::Get_Instance()->Add_Monster(SOLDIER,	{ 800, 300, 0, 0 });
		CEffectMgr::Get_Instance()->Add_Monster(SOLDIER,	{ 850, 300, 0, 0 });
		CEffectMgr::Get_Instance()->Add_Monster(ARCHER,		{ 900, 300, 0, 0 });
		CEffectMgr::Get_Instance()->Add_Monster(ARCHER,		{ 950, 300, 0, 0 });
		m_bMonster_3 = true;
	}

}
