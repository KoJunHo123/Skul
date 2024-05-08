#pragma once

#include "Obj.h"
#include "Define.h"

class CObjMgr
{
private:
	CObjMgr();
	~CObjMgr();

public:
	CObj*		Get_Player();
	CObj*		Get_Target(OBJID eID, CObj* pObj);
	CObj*		Get_Ground();
	CObj*		Get_Monster();
	CObj*		Get_Door();
	CObj*		Get_Reward();
	CObj*		Get_Drop();
	CObj*		Get_Cage();
	CObj*		Get_NPC();

	int			Get_PlayerCount() { return m_ObjList[OBJ_PLAYER].size(); }
	int			Get_MonsterCount() { return m_ObjList[OBJ_MONSTER].size(); }
	int			Get_NowHead() { return m_iNowHead; }

	list<CObj*>		Get_GroundList() { return m_ObjList[OBJ_GROUND]; }
	void		Set_MonsterCount(int* _iMonsterCount) { m_iMonsterCount = _iMonsterCount; }
	

public:
	void		Add_Object(OBJID eID, CObj* pObj);
	void		Update();		
	void		Late_Update();
	void		Render(HDC hDC);		
	void		Release();
	void		Delete_ID(OBJID eID);
	void		Delete_ExceptPlayer();


private:
	list<CObj*>	m_ObjList[OBJ_END];
	list<CObj*>	m_RenderList[RENDER_END];

	void		ChangeHead();


public:
	static CObjMgr*		Get_Instance()
	{
		if (!m_pInstance)
			m_pInstance = new CObjMgr;

		return m_pInstance;
	}
	static void		Destroy()
	{
		if (m_pInstance)
		{
			delete m_pInstance;
			m_pInstance = nullptr;
		}
	}

private:
	static CObjMgr*		m_pInstance;
	int					m_iNowHead;
	int*				m_iMonsterCount;
};

