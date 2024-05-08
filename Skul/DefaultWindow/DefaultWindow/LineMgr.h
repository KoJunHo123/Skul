#pragma once

#include "Line.h"
#include "Obj.h"

class CLineMgr
{
private:
	static CLineMgr* m_pInstance;
	list<CLine*> m_LineList;
	
private:
	CLineMgr();
	~CLineMgr();

public:
	static CLineMgr* Get_Instance()
	{
		if (!m_pInstance)
		{
			m_pInstance = new CLineMgr;
		}
		return m_pInstance;
	}

	static void Destroy()
	{
		if (m_pInstance)
		{
			delete m_pInstance;
			m_pInstance = nullptr;
		}
	}

public:
	void	AddLine(Vec2 _first, Vec2 _second){ m_LineList.push_back(new CLine(_first, _second)); }
	list<CLine*>& Get_LineList() { return m_LineList; }

public:
	void Initialize();
	void Update();
	void LateUpdate();
	void Render(HDC hDC);
	void Release();

	bool Collision_Line(CObj* _obj, float& fX, float* pY);
};

