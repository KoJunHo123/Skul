#include "stdafx.h"
#include "Line.h"
#include "CameraMgr.h"

CLine::CLine()
	:m_line{}
{
}

CLine::CLine(Vec2 _first, Vec2 _second)
	: m_line{ _first, _second }
{
}

CLine::~CLine()
{
}

void CLine::Initialize()
{

}

void CLine::Update()
{
	
}

void CLine::Late_Update()
{
}

void CLine::Render(HDC hDC)
{
	//Vec2 RenderPos_first = CCameraMgr::Get_Instance()->Get_RenderPos(m_line.first.fX, m_line.first.fY);
	//Vec2 RenderPos_second = CCameraMgr::Get_Instance()->Get_RenderPos(m_line.second.fX, m_line.second.fY);
	//MoveToEx(hDC, RenderPos_first.fX, RenderPos_first.fY, nullptr);
	//LineTo(hDC, RenderPos_second.fX, RenderPos_second.fY);
}

void CLine::Release()
{

}

