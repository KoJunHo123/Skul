#include "stdafx.h"
#include "Caged.h"

#include "BmpMgr.h"
#include "CameraMgr.h"
#include "UIMgr.h"

CCaged::CCaged()
	:m_bCageDestroyed(false)
{
}

CCaged::~CCaged()
{
}

void CCaged::Initialize()
{
	m_iHp = 30;
	m_bCage = true;

	m_tInfo.fCX = 150;
	m_tInfo.fCY = 100;
	m_eRender = RENDER_GAMEOBJECT;

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/NPC/Cage.bmp", L"Cage");
	m_tFrame = { 0,0,0,0,GetTickCount() };

}

int CCaged::Update()
{
	if (m_iHp <= 0 && false == m_bCageDestroyed)
	{
		++m_tFrame.iFrameStart;
		CUIMgr::Get_Instance()->Add_Bone(100);
		m_bCageDestroyed = true;
	}


	__super::Update_Rect();
	return 0;
}

void CCaged::Late_Update()
{
}

void CCaged::Render(HDC hDC)
{
	HDC hCageDC = CBmpMgr::Get_Instance()->Find_Image(L"Cage");
	Vec2 RenderPos = CCameraMgr::Get_Instance()->Get_RenderPos(m_tInfo.fX, m_tInfo.fY);

	GdiTransparentBlt(hDC, RenderPos.fX - 100, RenderPos.fY - 75, 200, 150, 
		hCageDC, m_tFrame.iFrameStart * 200, 0, 200, 150, RGB(255, 0, 255));

	/*Rectangle(hDC, RenderPos.fX - m_tInfo.fCX / 2, RenderPos.fY - m_tInfo.fCY / 2, 
		RenderPos.fX + m_tInfo.fCX / 2, RenderPos.fY + m_tInfo.fCY / 2);*/
}

void CCaged::Release()
{
	CBmpMgr::Get_Instance()->Delete_Image(L"Cage");
}
