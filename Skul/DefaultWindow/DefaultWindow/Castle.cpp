#include "stdafx.h"
#include "Castle.h"
#include "SceneMgr.h"

#include "Soldier.h"
#include "Archer.h"

CCastle::CCastle()
{
}

CCastle::~CCastle()
{
	Release();
}

void CCastle::Initialize()
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Map/Castle/Castle_Back.bmp",		L"Castle_Back");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Map/Castle/Castle_In.bmp",		L"Castle_In");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Map/Castle/Castle_Out.bmp",		L"Castle_Out");


	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Map/Castle/Chandelier_1.bmp",	L"Chandelier_1");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Map/Castle/Chandelier_2.bmp",	L"Chandelier_2");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Map/Castle/Castle_Cloud.bmp",	L"Castle_Cloud");


	CObjMgr::Get_Instance()->Add_Object(OBJ_PLAYER, CAbstractFactory<CLittleBone>::Create());
	CObjMgr::Get_Instance()->Get_Player()->Set_Pos(200, 280);
	CUIMgr::Get_Instance()->Set_Player(CObjMgr::Get_Instance()->Get_Player());


	CObjMgr::Get_Instance()->Add_Object(OBJ_GROUND, CAbstractFactory<CGround>::Create());
	static_cast<CGround*>(CObjMgr::Get_Instance()->Get_Ground())->Set_Rect({ 0, 280, 2880, 600 });

#pragma region 테스트용
	/*CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, CAbstractFactory<CSoldier>::Create(200, 250));
	CObjMgr::Get_Instance()->Get_Monster()->Set_Target(CObjMgr::Get_Instance()->Get_Player());

	CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, CAbstractFactory<CArcher>::Create(200, 250));
	CObjMgr::Get_Instance()->Get_Monster()->Set_Target(CObjMgr::Get_Instance()->Get_Player());*/
#pragma endregion

	m_mapSize = { 3000, 450 };
	CCameraMgr::Get_Instance()->Set_MapSize(m_mapSize.fX, m_mapSize.fY);

	CSoundMgr::Get_Instance()->PlayBGM(L"DemonCastle.wav", 1.f);

}

int CCastle::Update()
{
	CObjMgr::Get_Instance()->Update();

	return 0;
}

void CCastle::Late_Update()
{
	CObjMgr::Get_Instance()->Late_Update();

	if (500 < CObjMgr::Get_Instance()->Get_Player()->Get_Info().fY)
	{
		CSceneMgr::Get_Instance()->Scene_Change(SC_DUNGEONENT);
	}
}

void CCastle::Render(HDC hDC)
{
	HDC	hBackDC = CBmpMgr::Get_Instance()->Find_Image(L"Castle_Back");
	HDC hCastleCloudDC = CBmpMgr::Get_Instance()->Find_Image(L"Castle_Cloud");

	HDC hCastleOutDC = CBmpMgr::Get_Instance()->Find_Image(L"Castle_Out");
	HDC hChandelier_1DC = CBmpMgr::Get_Instance()->Find_Image(L"Chandelier_1");
	HDC hChandelier_2DC = CBmpMgr::Get_Instance()->Find_Image(L"Chandelier_2");
	HDC hCastleInDC = CBmpMgr::Get_Instance()->Find_Image(L"Castle_In");


	Vec2 backDist = CCameraMgr::Get_Instance()->Get_BackDistance();
	Vec2 Dist = CCameraMgr::Get_Instance()->Get_Distance();

	BitBlt(hDC, 0, 0, WINCX, WINCY, hBackDC, 0, 0, SRCCOPY);
	GdiTransparentBlt(hDC, -backDist.fX * 0.5f, -backDist.fY * 0.5f, 850, 200, hCastleCloudDC, 0, 0, 850, 200, RGB(255, 0, 255));
	GdiTransparentBlt(hDC, -backDist.fX * 0.75f, -backDist.fY * 0.75f, 1300, 400, hCastleOutDC, 0, 0, 1300, 400, RGB(255, 0, 255));

	GdiTransparentBlt(hDC, -backDist.fX + 400, -backDist.fY, 211, 217, hChandelier_1DC, 0, 0, 211, 217, RGB(255, 0, 255));
	GdiTransparentBlt(hDC, -backDist.fX + 800, -backDist.fY, 211, 226, hChandelier_2DC, 0, 0, 211, 226, RGB(255, 0, 255));
	GdiTransparentBlt(hDC, -backDist.fX + 1200, -backDist.fY, 211, 217, hChandelier_1DC, 0, 0, 211, 217, RGB(255, 0, 255));


	GdiTransparentBlt(hDC, -Dist.fX, -Dist.fY, 3000, 417, hCastleInDC, 0, 0, 3000, 417, RGB(255, 0, 255));



	CObjMgr::Get_Instance()->Render(hDC);
}

void CCastle::Release()
{
	CObjMgr::Get_Instance()->Delete_ExceptPlayer();

	CBmpMgr::Get_Instance()->Delete_Image(L"Castle_Back");
	CBmpMgr::Get_Instance()->Delete_Image(L"Castle_In");
	CBmpMgr::Get_Instance()->Delete_Image(L"Castle_Out");
	CBmpMgr::Get_Instance()->Delete_Image(L"Chandelier_1");
	CBmpMgr::Get_Instance()->Delete_Image(L"Chandelier_2");
	CBmpMgr::Get_Instance()->Delete_Image(L"Castle_Cloud");

	CSoundMgr::Get_Instance()->StopAll();
}
