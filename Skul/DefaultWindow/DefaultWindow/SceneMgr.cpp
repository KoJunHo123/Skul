#include "stdafx.h"
#include "SceneMgr.h"

#include "Title.h"
#include "Castle.h"
#include "Boss.h"
#include "DungeonEntrance.h"
#include "Stage_1.h"
#include "Stage_2.h"
#include "SkullEnforce.h"
#include "BossEntrance.h"
#include "EffectMgr.h"

CSceneMgr* CSceneMgr::m_pInstance = nullptr;

CSceneMgr::CSceneMgr() : m_pScene(nullptr), m_ePreScene(SC_END), m_eCurScene(SC_TITLE)
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/BackBuffer/BackBuffer.bmp", L"BackBuffer");
	CUIMgr::Get_Instance()->Initialize();
}


CSceneMgr::~CSceneMgr()
{
	Release();
}

void CSceneMgr::Scene_Change(SCENEID eID)
{
	m_eCurScene = eID;

	if (m_ePreScene != m_eCurScene)
	{
		Safe_Delete(m_pScene);

		switch (m_eCurScene)
		{
		case SC_TITLE:
			m_pScene = new CTitle;
			break;

		case SC_CASTLE:
			m_pScene = new CCastle;
			break;

		case SC_DUNGEONENT:
			m_pScene = new CDungeonEntrance;
			break;

		case SC_STAGE1:
			m_pScene = new CStage_1;
			break;

		case SC_STAGE2:
			m_pScene = new CStage_2;
			break;

		case SC_SKULENF:
			m_pScene = new CSkullEnforce;

			break;

		case SC_BOSSENT:
			m_pScene = new CBossEntrance;

			break;

		case SC_BOSS:
			m_pScene = new CBoss;
			break;

		case SC_END:
			break;
		}

		m_pScene->Initialize();

		m_ePreScene = m_eCurScene;
	}
}

void CSceneMgr::Update()
{
	m_pScene->Update();
	CUIMgr::Get_Instance()->Update();
	CEffectMgr::Get_Instance()->Update();
	CBattleMgr::Get_Instance()->Update();
}


void CSceneMgr::Late_Update()
{
	m_pScene->Late_Update();
	CUIMgr::Get_Instance()->Late_Update();
	CEffectMgr::Get_Instance()->Late_Update();
	CBattleMgr::Get_Instance()->Late_Update();
}

void CSceneMgr::Render(HDC hDC)
{
	HDC hBackBuffer = CBmpMgr::Get_Instance()->Find_Image(L"BackBuffer");
	
	HBRUSH myBrush = (HBRUSH)CreateSolidBrush(RGB(0, 0, 0));
	HBRUSH oldBrush = (HBRUSH)SelectObject(hBackBuffer, myBrush);
	
	Rectangle(hBackBuffer, 0, 0, WINCX, WINCY);

	SelectObject(hBackBuffer, oldBrush);
	DeleteObject(myBrush);


	m_pScene->Render(hBackBuffer);
	CBattleMgr::Get_Instance()->Render(hBackBuffer);
	CEffectMgr::Get_Instance()->Render(hBackBuffer);
	CUIMgr::Get_Instance()->Render(hBackBuffer);

	BitBlt(hDC, 0, 0, WINCX, WINCY, hBackBuffer, 0, 0, SRCCOPY);
}

void CSceneMgr::Release()
{
	Safe_Delete(m_pScene);
}
