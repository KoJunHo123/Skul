#include "stdafx.h"
#include "ObjMgr.h"
#include "CollisionMgr.h"
#include "BattleMgr.h"
#include "SceneMgr.h"
#include "SoundMgr.h"

CObjMgr*		CObjMgr::m_pInstance = nullptr;

CObjMgr::CObjMgr()
	: m_iNowHead(0)
{
}


CObjMgr::~CObjMgr()
{
	Release();
}


CObj* CObjMgr::Get_Player()
{
	if(!m_ObjList[OBJ_PLAYER].empty())
	{
		if (m_iNowHead == 0)
			return m_ObjList[OBJ_PLAYER].front();
		else
			return m_ObjList[OBJ_PLAYER].back();
	}
}

CObj* CObjMgr::Get_Ground()
{
	if (!m_ObjList[OBJ_GROUND].empty())
		return m_ObjList[OBJ_GROUND].back();

	return nullptr;
}

CObj* CObjMgr::Get_Monster()
{
	if (!m_ObjList[OBJ_MONSTER].empty())
		return m_ObjList[OBJ_MONSTER].back();

	return nullptr;
}

CObj* CObjMgr::Get_Door()
{
	if (!m_ObjList[OBJ_DOOR].empty())
		return m_ObjList[OBJ_DOOR].back();

	return nullptr;
}

CObj* CObjMgr::Get_Reward()
{
	if (!m_ObjList[OBJ_REWARD].empty())
		return m_ObjList[OBJ_REWARD].back();

	return nullptr;
}

CObj* CObjMgr::Get_Drop()
{
	if (!m_ObjList[OBJ_DROP].empty())
		return m_ObjList[OBJ_DROP].back();

	return nullptr;
}

CObj* CObjMgr::Get_Cage()
{
	if (!m_ObjList[OBJ_CAGE].empty())
		return m_ObjList[OBJ_CAGE].back();

	return nullptr;
}

CObj* CObjMgr::Get_NPC()
{
	if (!m_ObjList[OBJ_NPC].empty())
		return m_ObjList[OBJ_NPC].back();

	return nullptr;
}


CObj * CObjMgr::Get_Target(OBJID eID, CObj * pObj)
{
	if(m_ObjList[eID].empty())
		return nullptr;

	CObj*	pTarget = nullptr;

	float	fDistance(0.f);

	for (auto& iter : m_ObjList[eID])
	{
		if(iter->Get_Dead())
			continue;

		float	fWidth	  = pObj->Get_Info().fX - iter->Get_Info().fX;
		float	fHeight	  = pObj->Get_Info().fY - iter->Get_Info().fY;
		float	fDiagonal = sqrtf(fWidth * fWidth + fHeight * fHeight);

		if ((!pTarget) || (fDistance > fDiagonal))
		{
			pTarget = iter;
			fDistance = fDiagonal;
		}
	}
	return pTarget;
}


void CObjMgr::Add_Object(OBJID eID, CObj * pObj)
{
	if (OBJ_END <= eID || nullptr == pObj)
		return;

	m_ObjList[eID].push_back(pObj);
}

void CObjMgr::Update()
{
	for (size_t i = 0; i < OBJ_END; ++i)
	{
		for (auto iter = m_ObjList[i].begin();
			iter != m_ObjList[i].end(); )
		{
			int		iResult(0);
			if (OBJ_PLAYER == i)
			{
				// 기본 대가리면
				if (m_iNowHead == 0 && static_cast<CPlayer*>(*iter)->Get_SkulType() == SKUL)
					iResult = (*iter)->Update();
				else if(m_iNowHead == 1 && static_cast<CPlayer*>(*iter)->Get_SkulType() == BERSERKER)
					iResult = (*iter)->Update();
			}
			else
				iResult = (*iter)->Update();

			if (OBJ_DEAD == iResult)
			{
				if ((*iter)->Get_Monster())
					CSceneMgr::Get_Instance()->Get_CurScene()->Monster_Died();


				Safe_Delete<CObj*>(*iter);
				iter = m_ObjList[i].erase(iter);
			}
			else
				++iter;
		}
	}
}

void CObjMgr::Late_Update()
{
	ChangeHead();
	for (size_t i = 0; i < OBJ_END; ++i)
	{
		for (auto& iter : m_ObjList[i])
		{
			if (m_ObjList[i].empty())
				break;

			if (OBJ_PLAYER == i)
			{
				// 기본 대가리면
				if (m_iNowHead == 0 && static_cast<CPlayer*>(iter)->Get_SkulType() == SKUL)
					iter->Late_Update();
				else if (m_iNowHead == 1 && static_cast<CPlayer*>(iter)->Get_SkulType() == BERSERKER)
					iter->Late_Update();
			}
			else
				iter->Late_Update();


			RENDERID eID = iter->Get_GroupID();
			m_RenderList[eID].push_back(iter);
		}
	}

	CCollisionMgr::Collision_RectEx(m_ObjList[OBJ_PLAYER], m_ObjList[OBJ_GROUND]);
	CCollisionMgr::Collision_RectEx(m_ObjList[OBJ_MONSTER], m_ObjList[OBJ_GROUND]);

	CBattleMgr::Get_Instance()->Collision_Attack(m_ObjList[OBJ_PLAYER]);
	CBattleMgr::Get_Instance()->Collision_Attack(m_ObjList[OBJ_GROUND]);
	CBattleMgr::Get_Instance()->Collision_Attack(m_ObjList[OBJ_MONSTER]);

	if(!m_ObjList[OBJ_CAGE].empty() && m_ObjList[OBJ_CAGE].back()->Get_Hp() > 0)
		CBattleMgr::Get_Instance()->Collision_Attack(m_ObjList[OBJ_CAGE]);

	// CBattleMgr::Get_Instance()->Collision_Attack(m_ObjList[OBJ_MONSTER]);

}

void CObjMgr::Render(HDC hDC)
{

	for (size_t i = 0; i < RENDER_END; ++i)
	{
		m_RenderList[i].sort([](CObj* pDst, CObj* pSrc)->bool 
		{
			return pDst->Get_Info().fY < pSrc->Get_Info().fY;
		});

		for (auto& iter : m_RenderList[i])
		{
			if(i == RENDER_PLAYER)
			{
				if (m_iNowHead == 0 && static_cast<CPlayer*>(iter)->Get_SkulType() == SKUL)
					iter->Render(hDC);
				else if (m_iNowHead == 1 && static_cast<CPlayer*>(iter)->Get_SkulType() == BERSERKER)
					iter->Render(hDC);
			}
			else
				iter->Render(hDC);
		}

		m_RenderList[i].clear();
	}

}

void CObjMgr::Release()
{
	for (size_t i = 0; i < OBJ_END; ++i)
	{
		for_each(m_ObjList[i].begin(), m_ObjList[i].end(), Safe_Delete<CObj*>);
		m_ObjList[i].clear();
	}
}

void CObjMgr::Delete_ID(OBJID eID)
{
	for (auto& pObj : m_ObjList[eID])
		Safe_Delete(pObj);

	m_ObjList[eID].clear();
}

void CObjMgr::Delete_ExceptPlayer()
{
	for (size_t i = 0; i < OBJ_END; ++i)
	{
		if (i != OBJ_PLAYER)
		{
			Delete_ID((OBJID)i);
		}
	}

	for (size_t i = 0; i < RENDER_END; ++i)
	{
		if (i != RENDER_PLAYER)
		{
			m_RenderList[i].clear();
		}
	}

}

void CObjMgr::ChangeHead()
{

	if(CKeyMgr::Get_Instance()->Key_Down(VK_SPACE))
	{
		if(m_ObjList[OBJ_PLAYER].size() == 2)
		{
			if (m_iNowHead == 1)
			{
				m_iNowHead = 0;
				(*m_ObjList[OBJ_PLAYER].begin())->Set_Info((*++(m_ObjList[OBJ_PLAYER].begin()))->Get_Info());

				static_cast<CPlayer*>((*++(m_ObjList[OBJ_PLAYER].begin())))->Set_NowPlaying(false);
				static_cast<CPlayer*>((*m_ObjList[OBJ_PLAYER].begin()))->Set_NowPlaying(true);

				CUIMgr::Get_Instance()->Set_Player(m_ObjList[OBJ_PLAYER].front());

				for (size_t i = 0; i < OBJ_END; ++i)
				{
					for (auto& elem : m_ObjList[i])
					{
						if(i != OBJ_PLAYER && elem->Get_Target() == m_ObjList[OBJ_PLAYER].back())
							elem->Set_Target(m_ObjList[OBJ_PLAYER].front());
					}
				}

			}
			else if (m_iNowHead == 0)
			{
				m_iNowHead = 1;
				(*++(m_ObjList[OBJ_PLAYER].begin()))->Set_Info((*m_ObjList[OBJ_PLAYER].begin())->Get_Info());

				static_cast<CPlayer*>((*++(m_ObjList[OBJ_PLAYER].begin())))->Set_NowPlaying(true);
				static_cast<CPlayer*>((*m_ObjList[OBJ_PLAYER].begin()))->Set_NowPlaying(false);

				CUIMgr::Get_Instance()->Set_Player(m_ObjList[OBJ_PLAYER].back());

				CSoundMgr::Get_Instance()->PlaySound(L"Berserker.wav", SOUND_CHANGE, 1.f);

				for (size_t i = 0; i < OBJ_END; ++i)
				{
					for (auto& elem : m_ObjList[i])
					{
						if (i != OBJ_PLAYER && elem->Get_Target() == m_ObjList[OBJ_PLAYER].front())
							elem->Set_Target(m_ObjList[OBJ_PLAYER].back());
					}
				}
			}
		}
	}

}
