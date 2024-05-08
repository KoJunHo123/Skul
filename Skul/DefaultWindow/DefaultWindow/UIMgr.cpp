#include "stdafx.h"
#include "UiMgr.h"

#include "BmpMgr.h"
#include "ObjMgr.h"
#include "Player.h"
#include "Berserker.h"

CUIMgr* CUIMgr::m_pInstance = nullptr;

CUIMgr::CUIMgr()
	: m_pPlayer(nullptr)
	, m_fHpRate(0.f)
	, m_tInfo{94, WINCY - 80, 168, 66}
	, m_iLeftMonster(nullptr)
	, m_iBoneCount(0)
{
}

CUIMgr::~CUIMgr()
{
}

void CUIMgr::Initialize()
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/UI/Player_Frame.bmp", L"Player_Frame");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/UI/Hp_Bar.bmp", L"Hp_Bar");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/UI/Enemy_Icon.bmp", L"Enemy_Icon");

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/UI/Skul_Icon/Skul_Icon.bmp", L"Skul_Icon");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/UI/Skul_Icon/Berserker_Icon.bmp", L"Berserker_Icon");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/UI/Skul_Icon/Berserker_2_Icon.bmp", L"Berserker_2_Icon");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/UI/Skul_Icon/Berserker_2_Polymorph_Icon.bmp", L"Berserker_2_Polymorph_Icon");

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/UI/Skill_Icon/SkullThrowing.bmp", L"SkullThrowing");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/UI/Skill_Icon/SkullBack.bmp", L"SkullBack");

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/UI/Skill_Icon/Bonehowl.bmp", L"Bonehowl");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/UI/Skill_Icon/MadAxe.bmp", L"MadAxe");

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/UI/Skill_Icon/Bonehowl_2.bmp", L"Bonehowl_2");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/UI/Skill_Icon/MadAxe_2.bmp", L"MadAxe_2");

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/UI/Skill_Icon/Bonehowl_3.bmp", L"Bonehowl_3");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/UI/Skill_Icon/MadAxe_3.bmp", L"MadAxe_3");

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/UI/Bone_Icon.bmp", L"Bone_Icon");

	//CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/UI/Skul_Icon/Skul_Serve_Icon.bmp", L"Skul_Serve_Icon");
	//CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/UI/Skul_Icon/Berserker_Serve_Icon.bmp", L"Berserker_Serve_Icon");
	//CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/UI/Skul_Icon/Berserker_2_Serve_Icon.bmp", L"Berserker_2_Serve_Icon");
	//CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/UI/Skul_Icon/Berserker_2_Polymorph_Serve_Icon.bmp", L"Berserker_2_Polymorph_Serve_Icon");
}

void CUIMgr::Update()
{
	if(m_pPlayer)
	{
		m_fHpRate = m_pPlayer->Get_PlayerHp() * 1.18f;
	}
}

void CUIMgr::Late_Update()
{
	if (m_pPlayer)
	{
		
	}
}

void CUIMgr::Render(HDC hDC)
{
	if(m_pPlayer)
	{
		HDC hFrameDC = CBmpMgr::Get_Instance()->Find_Image(L"Player_Frame");
		HDC hHpBarDC = CBmpMgr::Get_Instance()->Find_Image(L"Hp_Bar");

		GdiTransparentBlt(hDC, m_tInfo.fX - m_tInfo.fCX / 2, m_tInfo.fY - m_tInfo.fCY / 2, m_tInfo.fCX, m_tInfo.fCY,
			hFrameDC, 0, 0, m_tInfo.fCX, m_tInfo.fCY, RGB(255, 0, 255));
		
		GdiTransparentBlt(hDC, m_tInfo.fX - m_tInfo.fCX / 2 + 43, m_tInfo.fY - m_tInfo.fCY / 2 + 45, m_fHpRate, 8,
			hHpBarDC, 0, 0, 118, 8, RGB(0, 0, 0));


		//GdiTransparentBlt(hDC, 0, 0, 168, 66,
		//	hFrameDC, 0, 0, 168, 66, RGB(255, 0, 255));
		// BitBlt(hDC, 0, 0, 118, 8, hHpBarDC, 0, 0, SRCCOPY);

		HDC hCharIconDC(nullptr);
		HDC hSkill_1_DC(nullptr);
		HDC hSkill_2_DC(nullptr);

		CObj* player = CObjMgr::Get_Instance()->Get_Player();

		float skill_2_xSize(0.f);
		float skill_2_ySize(0.f);
		if (SKUL == static_cast<CPlayer*>(player)->Get_SkulType())
		{
			hCharIconDC = CBmpMgr::Get_Instance()->Find_Image(L"Skul_Icon");
			hSkill_1_DC = CBmpMgr::Get_Instance()->Find_Image(L"SkullThrowing");
			hSkill_2_DC = CBmpMgr::Get_Instance()->Find_Image(L"SkullBack");
			
			skill_2_xSize = 22.f;
			skill_2_ySize = 22.f;
		}
		else if (BERSERKER == static_cast<CPlayer*>(player)->Get_SkulType() && 0 == static_cast<CBerserker*>(player)->Get_Tier())
		{
			hCharIconDC = CBmpMgr::Get_Instance()->Find_Image(L"Berserker_Icon");
			hSkill_1_DC = CBmpMgr::Get_Instance()->Find_Image(L"Bonehowl");
			hSkill_2_DC = CBmpMgr::Get_Instance()->Find_Image(L"MadAxe");

			skill_2_xSize = 24.f;
			skill_2_ySize = 24.f;
		}
		else if (BERSERKER == static_cast<CPlayer*>(player)->Get_SkulType() && 1 == static_cast<CBerserker*>(player)->Get_Tier())
		{
			hCharIconDC = CBmpMgr::Get_Instance()->Find_Image(L"Berserker_2_Icon");
			hSkill_1_DC = CBmpMgr::Get_Instance()->Find_Image(L"Bonehowl_2");
			hSkill_2_DC = CBmpMgr::Get_Instance()->Find_Image(L"MadAxe_2");
			
			skill_2_xSize = 24.f;
			skill_2_ySize = 24.f;
		}
		else
		{
			hCharIconDC = CBmpMgr::Get_Instance()->Find_Image(L"Berserker_2_Polymorph_Icon");
			hSkill_1_DC = CBmpMgr::Get_Instance()->Find_Image(L"Bonehowl_3");
			hSkill_2_DC = CBmpMgr::Get_Instance()->Find_Image(L"MadAxe_3");

			skill_2_xSize = 24.f;
			skill_2_ySize = 24.f;
		}

		GdiTransparentBlt(hDC, int(m_tInfo.fX - 22.5f - 55), int(m_tInfo.fY - 22.5f - 10), 45, 45, hCharIconDC, 0, 0, 45, 45, RGB(255, 0, 255));
		GdiTransparentBlt(hDC, int(m_tInfo.fX - 22.5f - 3.f), int(m_tInfo.fY - 22.5f + 6.f), 24, 24, hSkill_1_DC, 0, 0, 24, 24, RGB(255, 0, 255));
		GdiTransparentBlt(hDC, int(m_tInfo.fX - 22.5f + 27.f), int(m_tInfo.fY - 22.5f + 6.f), skill_2_xSize, skill_2_ySize, hSkill_2_DC, 0, 0, skill_2_xSize, skill_2_ySize, RGB(255, 0, 255));
		
		TCHAR szTemp[64];

		// 쿨타임
		if (static_cast<CPlayer*>(m_pPlayer)->Get_ACoolTime() > 0)
		{
			wsprintf(szTemp, L"%d", static_cast<CPlayer*>(m_pPlayer)->Get_ACoolTime());
			TextOut(hDC, int(m_tInfo.fX - 25.5f), int(m_tInfo.fY - 22.5f + 6.f), szTemp, lstrlen(szTemp));
		}

		if (static_cast<CPlayer*>(m_pPlayer)->Get_SCoolTime() > 0)
		{
			wsprintf(szTemp, L"%d", static_cast<CPlayer*>(m_pPlayer)->Get_SCoolTime());
			TextOut(hDC, int(m_tInfo.fX - 22.5f + 27.f), int(m_tInfo.fY - 22.5f + 6.f), szTemp, lstrlen(szTemp));
		}

		// 몬스터 아이콘
		HDC hMonsterIconDC = CBmpMgr::Get_Instance()->Find_Image(L"Enemy_Icon");
		GdiTransparentBlt(hDC, 700, 390, 12, 10, hMonsterIconDC, 0, 0, 12, 10, RGB(255, 0, 255));

		if(m_iLeftMonster)
		{
			wsprintf(szTemp, L"%d", *m_iLeftMonster);
			TextOut(hDC, 715, 390, szTemp, lstrlen(szTemp));
		}
		else if(nullptr == m_iLeftMonster || 0 > *m_iLeftMonster)
		{
			wsprintf(szTemp, L"%d", 0);
			TextOut(hDC, 715, 390, szTemp, lstrlen(szTemp));
		}


		// 뼈 개수
		HDC hBoneCountDC = CBmpMgr::Get_Instance()->Find_Image(L"Bone_Icon");
		GdiTransparentBlt(hDC, 680, 373, 30, 9, hBoneCountDC, 0, 0, 30, 9, RGB(255, 0, 255));
		wsprintf(szTemp, L"%d", m_iBoneCount);
		TextOut(hDC, 715, 370, szTemp, lstrlen(szTemp));
	}
	
}

void CUIMgr::Release()
{
}
