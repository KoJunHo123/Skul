#include "stdafx.h"
#include "Effect.h"
#include "BmpMgr.h"
#include "CameraMgr.h"
#include "ObjMgr.h"
#include "AbstractFactory.h"
#include "Soldier.h"
#include "Archer.h"

CEffect::CEffect()
	: m_pFrameKey(nullptr)
	, m_pFilePath(nullptr)
	, m_tFrame{}
	, m_tInfo{}
	, m_bEffectOver(false)
	, m_pInfo(nullptr)
{
}

CEffect::CEffect(const TCHAR* _FrameKey, const TCHAR* _FilePath, FRAME _frame, INFO _info)
	: m_pFrameKey(_FrameKey)
	, m_pFilePath(_FilePath)
	, m_tFrame(_frame)
	, m_tInfo(_info)
	, m_bEffectOver(false)
	, m_pInfo(nullptr)
{
}

CEffect::CEffect(const TCHAR* _FrameKey, const TCHAR* _pFilePath, FRAME _frame, INFO* _info)
	: m_pFrameKey(_FrameKey)
	, m_pFilePath(_pFilePath)
	, m_tFrame(_frame)
	, m_tInfo{}
	, m_bEffectOver(false)
	, m_pInfo(_info)
{
}

CEffect::~CEffect()
{
}

void CEffect::Initialize()
{
	CBmpMgr::Get_Instance()->Insert_Bmp(m_pFilePath, m_pFrameKey);
}

void CEffect::Update()
{	
	if (m_pInfo != nullptr)
	{
		m_tInfo = *m_pInfo;

		if (m_pFrameKey == L"Berserker_Aura")
		{
			m_tInfo.fCX = 100.f;
			m_tInfo.fCY = 100.f;
			m_tInfo.fY += m_pInfo->fCY * 0.5f;
		}
	}



	if (m_tFrame.dwTime + m_tFrame.dwSpeed < GetTickCount())
	{
		Add_Monster();

		// 다음 프레임으로 넘어감
		++m_tFrame.iFrameStart;
		m_tFrame.dwTime = GetTickCount();

		// 끝나면 처음으로
		if (m_tFrame.iFrameStart > m_tFrame.iFrameEnd)
		{
			m_tFrame.iFrameStart = 0;
			m_bEffectOver = true;
		}
		else
			m_bEffectOver = false;
	}
}

void CEffect::Late_Update()
{
}

void CEffect::Render(HDC hDC)
{
	HDC hEffectDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);

	Vec2 RenderPos = CCameraMgr::Get_Instance()->Get_RenderPos(m_tInfo.fX, m_tInfo.fY);

	if (m_pFrameKey == L"Normal_Attack_Right" || m_pFrameKey == L"Normal_Attack_Left")
	{
		GdiTransparentBlt
		(
			hDC, RenderPos.fX - 50, RenderPos.fY - 50, 100, 100,
			hEffectDC, m_tFrame.iFrameStart * m_tInfo.fCX, 0,
			m_tInfo.fCX, m_tInfo.fCY, RGB(0, 0, 0)
		);
	}
	else if (m_pFrameKey == L"Berserker_Attack")
	{
		GdiTransparentBlt
		(
			hDC, RenderPos.fX - 75, RenderPos.fY - 75, 150, 150,
			hEffectDC, m_tFrame.iFrameStart * m_tInfo.fCX, 0,
			m_tInfo.fCX, m_tInfo.fCY, RGB(0, 0, 0)
		);

	}
	else if (m_pFrameKey == L"Berserker_1_MadAxe_Real")
	{
		GdiTransparentBlt
		(
			hDC, RenderPos.fX - m_tInfo.fCX / 2, RenderPos.fY - m_tInfo.fCY / 2 - 25.f, m_tInfo.fCX, m_tInfo.fCY,
			hEffectDC, m_tFrame.iFrameStart * m_tInfo.fCX, 0,
			m_tInfo.fCX, m_tInfo.fCY, RGB(0, 0, 0)
		);
	}
	else 
	{
		GdiTransparentBlt
		(
			hDC, RenderPos.fX - m_tInfo.fCX / 2, RenderPos.fY - m_tInfo.fCY / 2, m_tInfo.fCX, m_tInfo.fCY,
			hEffectDC, m_tFrame.iFrameStart * m_tInfo.fCX, 0,
			m_tInfo.fCX, m_tInfo.fCY, RGB(0, 0, 0)
		);
	}

}

void CEffect::Release()
{
}

void CEffect::Add_Monster()
{
	if (m_pFrameKey == L"Monster_Appear" && m_tFrame.iFrameStart == 5)
	{
		if (m_eID == SOLDIER)
		{
			CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, CAbstractFactory<CSoldier>::Create(m_tInfo.fX, m_tInfo.fY));
			CObjMgr::Get_Instance()->Get_Monster()->Set_Target(CObjMgr::Get_Instance()->Get_Player());
		}
		else if (m_eID == ARCHER)
		{
			CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, CAbstractFactory<CArcher>::Create(m_tInfo.fX, m_tInfo.fY));
			CObjMgr::Get_Instance()->Get_Monster()->Set_Target(CObjMgr::Get_Instance()->Get_Player());
		}
	}

}
