#include "stdafx.h"
#include "BattleMgr.h"
#include "CollisionMgr.h"
#include "ObjMgr.h"
#include "EffectMgr.h"
#include "Player.h"

CBattleMgr* CBattleMgr::m_pInstance = nullptr;

CBattleMgr::CBattleMgr()
	: m_iCheckTime(GetTickCount())
{
}

CBattleMgr::~CBattleMgr()
{
	Release();
}

// 내 위치, 공격 종류, 방향, 데미지, 플레이어 or 몬스터 공격
void CBattleMgr::Add_MeleeAttack(INFO* _info, ATTACKTYPE _type, DIRECTION _dir, int _damage, bool _playerAttack, bool* _attacking)
{
	m_AttackList.push_back(new CMeleeAttack(_info, _type, _dir, _damage, _playerAttack, _attacking));
}

// 내 위치, 공격 종류, 방향, 데미지, 플레이어 or 몬스터 공격, 타겟
void CBattleMgr::Add_RangedAttack(INFO* _info, ATTACKTYPE _type, DIRECTION _dir, int _damage, bool _playerAttack, bool* _attacking, CObj* _target)
{
	m_AttackList.push_back(new CRangedAttack(_info, _type, _dir, _damage, _playerAttack, _attacking, _target));
}

void CBattleMgr::Initialize()
{
	for (auto& elem : m_AttackList)
	{
		elem->Initialize();
	}
}

void CBattleMgr::Update()
{
	for (auto& elem : m_AttackList)
	{
		elem->Update();
	}
}

void CBattleMgr::Late_Update()
{
	for (list<CAttack*>::iterator iter = m_AttackList.begin(); iter != m_AttackList.end();)
	{
		(*iter)->Late_Update();
		if (!*((*iter)->Get_Attacking()))
		{
			if((*iter)->Get_AttackType() != ELDERENT_BABYGRAPE && (*iter)->Get_AttackType() != ELDERENT_GRAPE && (*iter)->Get_AttackType() != ARCHER_ATTACK)
			{
				delete* iter;
				(*iter) = nullptr;
				iter = m_AttackList.erase(iter);
			}
			else
			{
				++iter;
			}
		}
		else
		{
			++iter;
		}
	}
}

void CBattleMgr::Render(HDC hDC)
{
	for (auto& elem : m_AttackList)
	{
		elem->Render(hDC);
	}
}

void CBattleMgr::Release()
{
	for (auto& elem : m_AttackList)
	{
		elem->Release();
	}

	for_each(m_AttackList.begin(), m_AttackList.end(), Safe_Delete<CAttack*>);
}



void CBattleMgr::Collision_Attack(list<CObj*> _obj)
{
	RECT	rcRect{};
	for (auto& obj : _obj)
	{
		if (obj->Get_Player() && !static_cast<CPlayer*>(obj)->Get_NowPlaying())
			continue;

		for (list<CAttack*>::iterator iter = m_AttackList.begin(); iter != m_AttackList.end(); )
		{
			if (IntersectRect(&rcRect, &((*iter)->Get_Rect()), &(obj->Get_Rect())))
			{
				float fCX = rcRect.right - rcRect.left;
				float fCY = rcRect.bottom - rcRect.top;
				float fX = rcRect.right - fCX;
				float fY = rcRect.bottom - fCY;
				INFO rectInfo = { fX, fY, fCX, fCY };

				if (obj->Get_Player() != (*iter)->Get_PlayerAttack() || obj->Get_GroundClass())
				{
					int knockback(20);
					INFO _info = (*iter)->Get_Info();

					bool hit = false;

					// 공격 종류별로
					// 나무햄 대가리 찍기
					if (ELDERENT_SLEM == (*iter)->Get_AttackType())
					{
						knockback = 30;
						if (obj->Get_GroundClass())
							CEffectMgr::Get_Instance()->Add_Effect(HANDSLAM_BOOM, _info);
					}
					// 나무햄 포도 ㅗ하기
					else if (ELDERENT_GRAPE == (*iter)->Get_AttackType())
					{
						CEffectMgr::Get_Instance()->Add_Effect(GRAPE_BOOM, _info);
						CSoundMgr::Get_Instance()->StopSound(SOUND_ELDERENT_FISTSLAM);
						CSoundMgr::Get_Instance()->PlaySound(L"ElderEnt_FistSlam.wav", SOUND_ELDERENT_FISTSLAM, 1.f);

					}
					else if (PLAYER_SKILL_1 == (*iter)->Get_AttackType())
					{
						if(!static_cast<CRangedAttack*>(*iter)->CrushMoment())
						{
							static_cast<CRangedAttack*>(*iter)->CrushedCountUp();
							static_cast<CRangedAttack*>(*iter)->Set_YSpeed(5.f);

							if((*iter)->Get_Dir() == RIGHT)
								CEffectMgr::Get_Instance()->Add_Effect(NORMAL_ATT_RIGHT, (*iter)->Get_Info());
							else
								CEffectMgr::Get_Instance()->Add_Effect(NORMAL_ATT_LEFT, (*iter)->Get_Info());
						}
						else if (0 > static_cast<CRangedAttack*>(*iter)->Get_YSpeed())
						{
							static_cast<CRangedAttack*>(*iter)->CrushedCountUp();
						}
					}

#pragma region Hit에 방향 넘겨주기
					

					if (!obj->Get_GroundClass())
					{
						bool hitSuccess = obj->Hit((*iter)->Get_Damage(), (*iter)->Get_Dir(), knockback);

						if(hitSuccess && PLAYER_ATTACK_1 == (*iter)->Get_AttackType())
						{
							if ((*iter)->Get_Dir() == RIGHT)
								CEffectMgr::Get_Instance()->Add_Effect(NORMAL_ATT_LEFT, rectInfo);
							else
								CEffectMgr::Get_Instance()->Add_Effect(NORMAL_ATT_RIGHT, rectInfo);
						}
						else if (hitSuccess && (BERSERKER_ATTACK_1 == (*iter)->Get_AttackType() || BERSERKER_ATTACK_2 == (*iter)->Get_AttackType()
							|| BERSERKER_SKILL_1 == (*iter)->Get_AttackType() || BERSERKER_SKILL_2 == (*iter)->Get_AttackType()
							|| BERSERKER_2_SKILL_2 == (*iter)->Get_AttackType()))
						{
							CEffectMgr::Get_Instance()->Add_Effect(BERSERKER_ATT, rectInfo);
						}
					}
#pragma endregion

#pragma region 충돌해서 없어져야 하는 거는 지워주기
					if ((*iter)->Get_AttackType() == ELDERENT_BABYGRAPE || (*iter)->Get_AttackType() == ELDERENT_GRAPE || (*iter)->Get_AttackType() == ARCHER_ATTACK)
					{

						delete* iter;
						(*iter) = nullptr;
						iter = m_AttackList.erase(iter);
					}
					else
						++iter;
#pragma endregion
				}
				else
					++iter;
			}
			else
				++iter;
		}
	}
}

INFO CBattleMgr::Find_SkullHead()
{
	for (auto& elem : m_AttackList)
	{
		if (elem->Get_AttackType() == PLAYER_SKILL_1)
			return elem->Get_Info();
	}
}
