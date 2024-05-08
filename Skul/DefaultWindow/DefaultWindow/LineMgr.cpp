#include "stdafx.h"
#include "LineMgr.h"
CLineMgr* CLineMgr::m_pInstance = nullptr;



CLineMgr::CLineMgr()
{
}

CLineMgr::~CLineMgr()
{
	Release();
}

void CLineMgr::Initialize()
{
	for (auto& elem : m_LineList)
	{
		elem->Initialize();
	}
}

void CLineMgr::Update()
{
	for (auto& elem : m_LineList)
	{
		elem->Update();
	}
}

void CLineMgr::LateUpdate()
{
	for (auto& elem : m_LineList)
	{
		elem->Late_Update();
	}
}

void CLineMgr::Render(HDC hDC)
{
	for (auto& elem : m_LineList)
	{
		elem->Render(hDC);
	}
}

void CLineMgr::Release()
{
	for (auto& elem : m_LineList)
	{
		elem->Release();
	}

	for_each(m_LineList.begin(), m_LineList.end(), Safe_Delete<CLine*>);
	m_LineList.clear();
}

bool CLineMgr::Collision_Line(CObj* _obj, float& fX, float* pY)
{
	if (m_LineList.empty())
		return false;

	CLine* pTargetLine = nullptr;

	for (auto& iter : m_LineList)
	{
		if (fX >= iter->Get_Line().first.fX &&
			fX < iter->Get_Line().second.fX)
		{
			pTargetLine = iter;

			if (!pTargetLine)
				return false;


			float x1 = pTargetLine->Get_Line().first.fX;
			float y1 = pTargetLine->Get_Line().first.fY;
			float x2 = pTargetLine->Get_Line().second.fX;
			float y2 = pTargetLine->Get_Line().second.fY;

			float Y = ((y2 - y1) / (x2 - x1)) * (fX - x1) + y1;

			float testy = (_obj->Get_Info().fY + _obj->Get_Info().fCY / 2);

			if (testy < Y + 4 && testy >(Y - 4))
			{
				*pY = Y - _obj->Get_Info().fCY / 2;
				return true;
			}

		}
	}

	return false;

}