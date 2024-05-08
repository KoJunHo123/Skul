#include "stdafx.h"
#include "Boss.h"
#include "LittleBone.h"
#include "Berserker.h"
#include "SceneMgr.h"
#include "EffectMgr.h"

#include "ElderEnt.h"

CBoss::CBoss()
	: m_iPhase(nullptr)
{
	m_mapSize = { 900, 560 };
	m_bodyPos = { (m_mapSize.fX / 2), (m_mapSize.fY / 2) };
}				

CBoss::~CBoss()
{

}


void CBoss::Initialize()
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Map/BossMap/1Phase.bmp", L"BossMap_1Phase");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Map/BossMap/2Phase.bmp", L"BossMap_2Phase");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Map/BossMap/clear.bmp", L"clear");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Map/BossMap/Ground.bmp", L"BossMapGround");


	// 몸뚱아리만 따로..?
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Boss/ElderEnt/Body.bmp", L"ElderEnt_Body");

	// 테스트용
	//CObjMgr::Get_Instance()->Add_Object(OBJ_PLAYER, CAbstractFactory<CLittleBone>::Create());
	//CObjMgr::Get_Instance()->Add_Object(OBJ_PLAYER, CAbstractFactory<CBerserker>::Create());
	//CUIMgr::Get_Instance()->Set_Player(CObjMgr::Get_Instance()->Get_Player());

	CObjMgr::Get_Instance()->Get_Player()->Set_Pos(m_mapSize.fX / 2, m_mapSize.fY / 2);



	CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, CAbstractFactory<CElderEnt>::CreateElder(&m_bodyPos));
	CObjMgr::Get_Instance()->Get_Monster()->Set_Target(CObjMgr::Get_Instance()->Get_Player());
	m_iPhase = static_cast<CElderEnt*>(CObjMgr::Get_Instance()->Get_Monster())->Get_Phase();
	
#pragma region 지형 생성
	// 바닥
	CObjMgr::Get_Instance()->Add_Object(OBJ_GROUND, CAbstractFactory<CGround>::Create());
	static_cast<CGround*>(CObjMgr::Get_Instance()->Get_Ground())->Set_Rect({ 0, 400, 900, 600 });

	CObjMgr::Get_Instance()->Add_Object(OBJ_GROUND, CAbstractFactory<CGround>::Create());
	static_cast<CGround*>(CObjMgr::Get_Instance()->Get_Ground())->Set_Rect({ -100, 0, 0, 600 });

	CObjMgr::Get_Instance()->Add_Object(OBJ_GROUND, CAbstractFactory<CGround>::Create());
	static_cast<CGround*>(CObjMgr::Get_Instance()->Get_Ground())->Set_Rect({ 900, 0, 1000, 600 });
	CCameraMgr::Get_Instance()->Set_MapSize(900, 560);
#pragma endregion

	// 순서 지켜야하는 쓰래기 코드...
	CLineMgr::Get_Instance()->AddLine({ m_bodyPos.fX - 102, m_bodyPos.fY + 65},  { m_bodyPos.fX - 25, m_bodyPos.fY + 65} );
	CLineMgr::Get_Instance()->AddLine({ m_bodyPos.fX + 60, m_bodyPos.fY + 35 },  { m_bodyPos.fX + 130, m_bodyPos.fY + 35 } );

	CSoundMgr::Get_Instance()->PlayBGM(L"Chapter1_Boss.wav", 1.f);
}

int CBoss::Update()
{
	CObjMgr::Get_Instance()->Update();

	// 순서 지켜야하는 쓰래기 코드...
	list<CLine*>::iterator iter = CLineMgr::Get_Instance()->Get_LineList().begin();
	(*iter++)->Set_Line({ m_bodyPos.fX - 102, m_bodyPos.fY + 65 }, { m_bodyPos.fX - 25, m_bodyPos.fY + 65 });
	(*iter)->Set_Line({ m_bodyPos.fX + 60, m_bodyPos.fY + 35 }, { m_bodyPos.fX + 130, m_bodyPos.fY + 35 });

	return 0;
}

void CBoss::Late_Update()
{
	CObjMgr::Get_Instance()->Late_Update();
}

void CBoss::Render(HDC hDC)
{
	HDC	h1PhaseDC = CBmpMgr::Get_Instance()->Find_Image(L"BossMap_1Phase");
	HDC h2PhaseDC = CBmpMgr::Get_Instance()->Find_Image(L"BossMap_2Phase");
	HDC hCleadDC = CBmpMgr::Get_Instance()->Find_Image(L"clear");
	HDC hGroundDC = CBmpMgr::Get_Instance()->Find_Image(L"BossMapGround");

	Vec2 dist = CCameraMgr::Get_Instance()->Get_Distance();
	Vec2 backDist = CCameraMgr::Get_Instance()->Get_BackDistance();
	
	if(*m_iPhase == 0)
		BitBlt(hDC, -backDist.fX, -backDist.fY, WINCX + backDist.fX, WINCX - backDist.fY, h1PhaseDC, 0, 0, SRCCOPY);
	else if(*m_iPhase == 1)
		BitBlt(hDC, -backDist.fX, -backDist.fY, WINCX + backDist.fX, WINCX - backDist.fY, h2PhaseDC, 0, 0, SRCCOPY);
	else
		BitBlt(hDC, -backDist.fX, -backDist.fY, WINCX + backDist.fX, WINCX - backDist.fY, hCleadDC, 0, 0, SRCCOPY);
	
	// 클리어 맵 할 것.

	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"ElderEnt_Body");

	GdiTransparentBlt(hDC,
		(int)(-dist.fX + m_bodyPos.fX - 250),
		(int)(-dist.fY + m_bodyPos.fY - 250),
		500,
		500,
		hMemDC,
		*m_iPhase * 500, 0,
		500,
		500,
		RGB(255, 0, 255));

	GdiTransparentBlt(hDC,
		-dist.fX, -dist.fY,
		m_mapSize.fX, m_mapSize.fY,
		hGroundDC,
		0, 0,
		m_mapSize.fX, m_mapSize.fY,
		RGB(0, 0, 0));
	
	CObjMgr::Get_Instance()->Render(hDC);
	// CLineMgr::Get_Instance()->Render(hBackBuffer);
}

void CBoss::Release()
{
	CObjMgr::Get_Instance()->Delete_ExceptPlayer();
	CLineMgr::Get_Instance()->Destroy();
}

