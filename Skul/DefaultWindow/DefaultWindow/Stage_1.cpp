#include "stdafx.h"
#include "Stage_1.h"
#include "SceneMgr.h"


CStage_1::CStage_1()
	: m_bMonster_1(false)
	, m_bMonster_2(false)
	, m_bMonster_3(false)
{ 
}

CStage_1::~CStage_1()
{
	Release();
}

void CStage_1::Initialize()
{
    CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Map/Normal_Map_Back_Back.bmp", L"Normal_Map_Back_Back");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Map/Normal_Map_4.bmp", L"Normal_Map_4");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Map/Stage_1/Stage_1.bmp", L"Stage_1");

	m_mapSize = { 1490, 750 };
	CCameraMgr::Get_Instance()->Set_MapSize(m_mapSize.fX, m_mapSize.fY);

	 // 테스트용
	CObjMgr::Get_Instance()->Get_Player()->Set_Pos(200, 180);

#pragma region 지형
	// 지형 확정
	CObjMgr::Get_Instance()->Add_Object(OBJ_GROUND, CAbstractFactory<CGround>::Create());
	static_cast<CGround*>(CObjMgr::Get_Instance()->Get_Ground())->Set_Rect({ 0, 420, 315, 550 });

	CObjMgr::Get_Instance()->Add_Object(OBJ_GROUND, CAbstractFactory<CGround>::Create());
	static_cast<CGround*>(CObjMgr::Get_Instance()->Get_Ground())->Set_Rect({ 300, 550, 370, 685 });
	
	CObjMgr::Get_Instance()->Add_Object(OBJ_GROUND, CAbstractFactory<CGround>::Create());
	static_cast<CGround*>(CObjMgr::Get_Instance()->Get_Ground())->Set_Rect({ 350, 685, 980, 1000 });

	CObjMgr::Get_Instance()->Add_Object(OBJ_GROUND, CAbstractFactory<CGround>::Create());
	static_cast<CGround*>(CObjMgr::Get_Instance()->Get_Ground())->Set_Rect({ 970, 605, 1060, 685 });

	CObjMgr::Get_Instance()->Add_Object(OBJ_GROUND, CAbstractFactory<CGround>::Create());
	static_cast<CGround*>(CObjMgr::Get_Instance()->Get_Ground())->Set_Rect({ 1060, 420, 1500, 600 });

	CObjMgr::Get_Instance()->Add_Object(OBJ_GROUND, CAbstractFactory<CGround>::Create());
	static_cast<CGround*>(CObjMgr::Get_Instance()->Get_Ground())->Set_Rect({ 1030, 470, 1060, 535 });

	CObjMgr::Get_Instance()->Add_Object(OBJ_GROUND, CAbstractFactory<CGround>::Create());
	static_cast<CGround*>(CObjMgr::Get_Instance()->Get_Ground())->Set_Rect({ 975, 470, 1035, 510 });

	// 맵 끝
	CObjMgr::Get_Instance()->Add_Object(OBJ_GROUND, CAbstractFactory<CGround>::Create());
	static_cast<CGround*>(CObjMgr::Get_Instance()->Get_Ground())->Set_Rect({ -100, 0, 0, 800 });

	CObjMgr::Get_Instance()->Add_Object(OBJ_GROUND, CAbstractFactory<CGround>::Create());
	static_cast<CGround*>(CObjMgr::Get_Instance()->Get_Ground())->Set_Rect({ 1497, 0, 1597, 1000 });

#pragma endregion

	CLineMgr::Get_Instance()->AddLine({ 310, 470 }, { 425, 470 });
	CLineMgr::Get_Instance()->AddLine({ 375, 600 }, { 450, 600 });
	CLineMgr::Get_Instance()->AddLine({ 830, 520 }, { 890, 520 });

#pragma region 문짝
	CObjMgr::Get_Instance()->Add_Object(OBJ_DOOR, new CDoor(STAGE_DOOR));
	CObjMgr::Get_Instance()->Get_Door()->Set_Pos(850, 620);
	CObjMgr::Get_Instance()->Get_Door()->Set_Target(CObjMgr::Get_Instance()->Get_Player());
	CObjMgr::Get_Instance()->Get_Door()->Initialize();
#pragma endregion

#pragma region 보상
	CObjMgr::Get_Instance()->Add_Object(OBJ_REWARD, CAbstractFactory<CReward>::Create(450, 620));
	CObjMgr::Get_Instance()->Get_Reward()->Set_Target(CObjMgr::Get_Instance()->Get_Player());
#pragma endregion

	CUIMgr::Get_Instance()->Set_LeftMonster(&m_iLeftMonster);

	m_iLeftMonster = 14;
}

int CStage_1::Update()
{
	CObjMgr::Get_Instance()->Update();

	if (CKeyMgr::Get_Instance()->Key_Down('G'))
	{
		CSceneMgr::Get_Instance()->Scene_Change(SC_STAGE2);
	}


    return 0;
}

void CStage_1::Late_Update()
{
	Set_Monster();

	CObjMgr::Get_Instance()->Late_Update();

	if (0 == m_iLeftMonster)
	{
		if(CObjMgr::Get_Instance()->Get_Door())
			static_cast<CDoor*>(CObjMgr::Get_Instance()->Get_Door())->Door_Activate();

		if(CObjMgr::Get_Instance()->Get_Reward())
			static_cast<CReward*>(CObjMgr::Get_Instance()->Get_Reward())->Reward_Activate();
	}


	// 활성화 된 상태에서
	if (CObjMgr::Get_Instance()->Get_Reward() && static_cast<CReward*>(CObjMgr::Get_Instance()->Get_Reward())->Get_Activate())
	{
		// 충돌한 상태에서
		if (static_cast<CReward*>(CObjMgr::Get_Instance()->Get_Reward())->Get_Coll())
			if (CKeyMgr::Get_Instance()->Key_Down('F'))
			{
				static_cast<CReward*>(CObjMgr::Get_Instance()->Get_Reward())->Get_Reward();
			}
	}
	if (CObjMgr::Get_Instance()->Get_Door() && static_cast<CDoor*>(CObjMgr::Get_Instance()->Get_Door())->Get_Activate())
	{
		if (static_cast<CDoor*>(CObjMgr::Get_Instance()->Get_Door())->Get_Coll())
			if (CKeyMgr::Get_Instance()->Key_Down('F'))
			{
				CSceneMgr::Get_Instance()->Scene_Change(SC_STAGE2);
			}
	}

}

void CStage_1::Render(HDC hDC)
{
	// HDC	hGroundDC = CBmpMgr::Get_Instance()->Find_Image(L"Dungeon_Entrance_Ground");
	HDC	hBackDC = CBmpMgr::Get_Instance()->Find_Image(L"Normal_Map_Back_Back");
	HDC hNoraml_MapDC = CBmpMgr::Get_Instance()->Find_Image(L"Normal_Map_4");
	HDC hStage_1_DC = CBmpMgr::Get_Instance()->Find_Image(L"Stage_1");

	Vec2 Dist = CCameraMgr::Get_Instance()->Get_Distance();
	Vec2 BackDist = CCameraMgr::Get_Instance()->Get_BackDistance();
	
	GdiTransparentBlt(hDC, -BackDist.fX * 0.5f, -BackDist.fY * 0.5f - 200, 960, 800, hBackDC, 0, 0, 960, 800, RGB(255, 0, 255));
	
	GdiTransparentBlt(hDC, -BackDist.fX, -BackDist.fY - 200, 1150, 800, hNoraml_MapDC, 0, 0, 1150, 800, RGB(255, 0, 255));
	
	GdiTransparentBlt(hDC, -Dist.fX, -Dist.fY, m_mapSize.fX, m_mapSize.fY, hStage_1_DC, 0, 0, m_mapSize.fX, m_mapSize.fY, RGB(255, 0, 255));
	

	CObjMgr::Get_Instance()->Render(hDC);




}

void CStage_1::Release()
{
	CObjMgr::Get_Instance()->Delete_ExceptPlayer();
	CLineMgr::Get_Instance()->Release();
}

void CStage_1::Set_Monster()
{

	CObj* player = CObjMgr::Get_Instance()->Get_Player();

	if (!m_bMonster_1 && player->Get_Info().fX > 200 && player->Get_Info().fY > 350)
	{
		CEffectMgr::Get_Instance()->Add_Monster(SOLDIER, { 200, 400, 0, 0 });
		CEffectMgr::Get_Instance()->Add_Monster(ARCHER, { 250, 400, 0, 0 });

		m_bMonster_1 = true;

	}

	if (!m_bMonster_2 && player->Get_Info().fX > 350 && player->Get_Info().fY > 600)
	{
		CEffectMgr::Get_Instance()->Add_Monster(SOLDIER, { 400, 670, 0, 0 });
		CEffectMgr::Get_Instance()->Add_Monster(SOLDIER, { 450, 670, 0, 0 });
		CEffectMgr::Get_Instance()->Add_Monster(SOLDIER, { 500, 670, 0, 0 });
		CEffectMgr::Get_Instance()->Add_Monster(SOLDIER, { 550, 670, 0, 0 });
		CEffectMgr::Get_Instance()->Add_Monster(ARCHER, { 600, 670, 0, 0 });
		CEffectMgr::Get_Instance()->Add_Monster(SOLDIER, { 650, 670, 0, 0 });
		CEffectMgr::Get_Instance()->Add_Monster(SOLDIER, { 700, 670, 0, 0 });
		CEffectMgr::Get_Instance()->Add_Monster(SOLDIER, { 750, 670, 0, 0 });
		CEffectMgr::Get_Instance()->Add_Monster(SOLDIER, { 800, 670, 0, 0 });
		CEffectMgr::Get_Instance()->Add_Monster(ARCHER, { 850, 670, 0, 0 });
		m_bMonster_2 = true;
	}


	if (!m_bMonster_3 && player->Get_Info().fX >  1060 && player->Get_Info().fY < 420)
	{
		CEffectMgr::Get_Instance()->Add_Monster(SOLDIER, { 1200, 400, 0, 0 });
		CEffectMgr::Get_Instance()->Add_Monster(ARCHER, { 1300, 400, 0, 0 });
		m_bMonster_3 = true;
	}

}
