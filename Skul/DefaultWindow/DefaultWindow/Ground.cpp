#include "stdafx.h"
#include "Ground.h"
#include "CameraMgr.h"

CGround::CGround()
{
}

CGround::~CGround()
{
}

void CGround::Initialize()
{
	m_eRender = RENDER_GAMEOBJECT;
	m_bPlayer = false;
	m_bGroundClass = true;
}

int CGround::Update()
{
	__super::Update_Rect();
	return 0;
}

void CGround::Late_Update()
{
}

void CGround::Render(HDC hDC)
{
	/*Vec2 RenderPos = CCameraMgr::Get_Instance()->Get_RenderPos(m_tInfo.fX, m_tInfo.fY);

	Rectangle(hDC, RenderPos.fX - m_tInfo.fCX / 2, RenderPos.fY - m_tInfo.fCY / 2, RenderPos.fX + m_tInfo.fCX / 2, RenderPos.fY + m_tInfo.fCY / 2);*/

}

void CGround::Release()
{
}

void CGround::Set_Rect(RECT _rect)
{
	m_tRect = _rect;

	m_tInfo.fCX = (float)(m_tRect.right - m_tRect.left);
	m_tInfo.fCY = (float)(m_tRect.bottom - m_tRect.top) ;

	m_tInfo.fX = (float)m_tRect.right - m_tInfo.fCX/2;
	m_tInfo.fY = (float)m_tRect.bottom - m_tInfo.fCY/2;
}
