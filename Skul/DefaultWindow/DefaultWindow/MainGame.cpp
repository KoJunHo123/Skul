#include "stdafx.h"
#include "MainGame.h"
#include "BmpMgr.h"
#include "SceneMgr.h"
#include "KeyMgr.h"
#include "ObjMgr.h"
#include "BmpMgr.h"
#include "AnimationMgr.h"
#include "CameraMgr.h"
#include "LineMgr.h"
#include "BattleMgr.h"
#include "UIMgr.h"
#include "SoundMgr.h"
#include "EffectMgr.h"

CMainGame::CMainGame()
	: m_hDC(nullptr)
	, m_dwTime(GetTickCount())
	, m_iFPS(0)
	, m_szFPS{}
{
}

CMainGame::~CMainGame()
{
	Release();
}

void CMainGame::Initialize()
{
	m_hDC = GetDC(g_hWnd);
	CSceneMgr::Get_Instance()->Scene_Change(SC_TITLE);
	CSoundMgr::Get_Instance()->Initialize();

}

void CMainGame::Update()
{

	CSceneMgr::Get_Instance()->Update();
}

void CMainGame::LateUpdate()
{
	CSceneMgr::Get_Instance()->Late_Update();
}

void CMainGame::Render()
{
#pragma region 프레임 출력
	++m_iFPS;

	if (m_dwTime + 1000 < GetTickCount())
	{
		swprintf_s(m_szFPS, L"FPS : %d", m_iFPS);
		SetWindowText(g_hWnd, m_szFPS);

		m_iFPS = 0;
		m_dwTime = GetTickCount();
	}
#pragma endregion


	CSceneMgr::Get_Instance()->Render(m_hDC);

}

void CMainGame::Release()
{
	ReleaseDC(g_hWnd, m_hDC);

	CSceneMgr::Get_Instance()->Destroy();
	CKeyMgr::Get_Instance()->Destroy();
	CBmpMgr::Get_Instance()->Destroy();
	CObjMgr::Get_Instance()->Destroy();
	CAnimationMgr::Get_Instance()->Destroy();
	CCameraMgr::Get_Instance()->Destroy();
	CLineMgr::Get_Instance()->Destroy();
	CBattleMgr::Get_Instance()->Destroy();
	CUIMgr::Get_Instance()->Destroy();
	CSoundMgr::Get_Instance()->Destroy_Instance();
	CEffectMgr::Get_Instance()->Destroy();

}
