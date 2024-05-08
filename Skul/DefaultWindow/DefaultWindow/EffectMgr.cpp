#include "stdafx.h"
#include "EffectMgr.h"

#include "ObjMgr.h"
#include "Berserker.h"

CEffectMgr* CEffectMgr::m_pInstance = nullptr;

CEffectMgr::CEffectMgr()
{
}

CEffectMgr::~CEffectMgr()
{
	Release();
}

void CEffectMgr::Add_Effect(EFFECTTYPE _effect, INFO _info)
{
	const TCHAR* FrameKey(nullptr);
	const TCHAR* FilePath(nullptr);
	FRAME tFrame{};

	switch (_effect)
	{
	case GRAPE_READY:
		FrameKey = L"Grape_Ready";
		FilePath = L"../Image/Boss/Grape/Grape_Ready.bmp";
		tFrame = {0, 45, 0, 50, GetTickCount()};
		_info.fCX = 300;
		_info.fCY = 300;
		break;

	case GRAPE_ELECT:
		FrameKey = L"Grape_Elect";
		FilePath = L"../Image/Boss/Grape/Grape_Elect.bmp";
		tFrame = { 0, 23, 0, 50, GetTickCount() };
		_info.fCX = 200;
		_info.fCY = 200;
		break;

	case GRAPE_SHOOT:
		FrameKey = L"Grape_Shoot";
		FilePath = L"../Image/Boss/Grape/Grape_Shoot.bmp";
		tFrame = { 0, 23, 0, 40, GetTickCount() };
		_info.fCX = 320;
		_info.fCY = 320;
		break;

	case GRAPE_BOOM:
		FrameKey = L"Grape_Boom";
		FilePath = L"../Image/Boss/Grape/Grape_Boom.bmp";
		tFrame = { 0, 36, 0, 50, GetTickCount() };
		_info.fCX = 440;
		_info.fCY = 240;
		break;

	case HANDSLAM_BOOM:
		FrameKey = L"HandSlam_Boom";
		FilePath = L"../Image/Boss/Slam/HandSlam_Boom.bmp";
		tFrame = { 0, 27, 0, 50, GetTickCount() };
		_info.fCX = 420;
		_info.fCY = 300;
		_info.fY -= 50;
		break;

	case PLAYER_DASH_RIGHT:
		FrameKey = L"Dash_Smoke_Right";
		FilePath = L"../Image/Player/Dash_Smoke_Right.bmp";
		tFrame = { 0, 12, 0, 50, GetTickCount() };
		_info.fCX = 100.f;
		_info.fCY = 100.f;
		_info.fY += 10.f;
		_info.fX -= 5.f;
		break;

	case PLAYER_DASH_LEFT:
		FrameKey = L"Dash_Smoke_Left";
		FilePath = L"../Image/Player/Dash_Smoke_Left.bmp";
		tFrame = { 0, 12, 0, 50, GetTickCount() };
		_info.fCX = 100;
		_info.fCY = 100;
		_info.fY += 10;
		_info.fX += 5.f;
		break;


	case PLAYER_DOUBLEJUMP:
		FrameKey = L"DoubleJump_Smoke";
		FilePath = L"../Image/Player/DoubleJump_Smoke.bmp";
		tFrame = { 0, 9, 0, 50, GetTickCount() };
		_info.fCX = 100;
		_info.fCY = 30;
		_info.fY += 5;
		break;

	case PLAYER_HIT:
		FrameKey = L"Player_Hit";
		FilePath = L"../Image/Player/Player_Hit.bmp";
		tFrame = { 0, 10, 0, 50, GetTickCount() };
		_info.fCX = 100;
		_info.fCY = 100;
		break;

	case NORMAL_ATT_LEFT:
		FrameKey = L"Normal_Attack_Left";
		FilePath = L"../Image/Player/Attack/Normal_Attack/Normal_Attack_Left.bmp";
		tFrame = { 0, 10, 0, 50, GetTickCount() };
		_info.fCX = 200;
		_info.fCY = 200;
		break;

	case NORMAL_ATT_RIGHT:
		FrameKey = L"Normal_Attack_Right";
		FilePath = L"../Image/Player/Attack/Normal_Attack/Normal_Attack_Right.bmp";
		tFrame = { 0, 10, 0, 50, GetTickCount() };
		_info.fCX = 200;
		_info.fCY = 200;
		break;

	case MONSTER_APPEAR:
		FrameKey = L"Monster_Appear";
		FilePath = L"../Image/Monster/Monster_Appear.bmp";
		tFrame = { 0, 10, 0, 50, GetTickCount() };
		_info.fCX = 150;
		_info.fCY = 150;
		break;

	case MONSTER_DEAD:
		FrameKey = L"Monster_Dead";
		FilePath = L"../Image/Monster/Monster_Dead.bmp";
		tFrame = { 0, 4, 0, 50, GetTickCount() };
		_info.fCX = 150;
		_info.fCY = 150;
		break;

	case BERSERKER_ATT:
		FrameKey = L"Berserker_Attack";
		FilePath = L"../Image/Player/Berserker/Berserker_Attack.bmp";
		tFrame = { 0, 4, 0, 40, GetTickCount() };
		_info.fCX = 100;
		_info.fCY = 100;
		break;

	case BONE_HOWL:
		FrameKey = L"BoneHowl";
		FilePath = L"../Image/Player/Berserker/BoneHowl.bmp";
		tFrame = { 0, 12, 0, 40, GetTickCount() };
		_info.fCX = 200;
		_info.fCY = 200;
		break;

	case MAD_AXE:
		FrameKey = L"Berserker_1_MadAxe_Real";
		FilePath = L"../Image/Player/Berserker/Berserker_1_MadAxe_Real.bmp";
		tFrame = { 0, 39, 0, 40, GetTickCount() };
		_info.fCX = 300;
		_info.fCY = 200;
		break;

	case MAD_AXE_2_LEFT:
		FrameKey = L"Berserker_2_MadAxe_Left";
		FilePath = L"../Image/Player/Berserker/Berserker_2_MadAxe_Left.bmp";
		tFrame = { 0, 12, 0, 40, GetTickCount() };
		_info.fCX = 500;
		_info.fCY = 200;
		break;

	case MAD_AXE_2_RIGHT:
		FrameKey = L"Berserker_2_MadAxe_Right";
		FilePath = L"../Image/Player/Berserker/Berserker_2_MadAxe_Right.bmp";
		tFrame = { 0, 12, 0, 40, GetTickCount() };
		_info.fCX = 500;
		_info.fCY = 200;
		break;

	case DEMON_AURA:
		FrameKey = L"Berserker_Aura";
		FilePath = L"../Image/Player/Berserker/Berserker_Aura.bmp";
		tFrame = { 0, 46, 0, 80, GetTickCount() };
		_info.fCX = 100;
		_info.fCY = 100;
		break;

	case ARCHER_ARROW_SIGN:
		FrameKey = L"Berserker_Aura";
		FilePath = L"../Image/Monster/Archer/Archer_AttackSign.bmp";
		tFrame = { 0, 18, 0, 100, GetTickCount() };
		_info.fCX = 500;
		_info.fCY = 100;
		break;


	default:
		break;
	}


	m_EffectList.push_back(new CEffect(FrameKey, FilePath, tFrame, _info));
	m_EffectList.back()->Initialize();
}

void CEffectMgr::Add_Unique_Effect(EFFECTTYPE _effect, INFO _info)
{
	const TCHAR* FrameKey(nullptr);
	const TCHAR* FilePath(nullptr);
	FRAME tFrame{};

	switch (_effect)
	{
	case GRAPE_READY:
		FrameKey = L"Grape_Ready";
		FilePath = L"../Image/Boss/Grape/Grape_Ready.bmp";
		tFrame = { 0, 45, 0, 50, GetTickCount() };
		_info.fCX = 300;
		_info.fCY = 300;
		_info.fY -= 10.f;
		break;

	case GRAPE_READY_2:
		FrameKey = L"Grape_Ready_2";
		FilePath = L"../Image/Boss/Grape/Grape_Ready_2p.bmp";
		tFrame = { 0, 43, 0, 50, GetTickCount() };
		_info.fCX = 300;
		_info.fCY = 300;
		_info.fY -= 10.f;
		break;

	case GRAPE_ELECT:
		FrameKey = L"Grape_Elect";
		FilePath = L"../Image/Boss/Grape/Grape_Elect.bmp";
		tFrame = { 0, 23, 0, 50, GetTickCount() };
		_info.fCX = 200;
		_info.fCY = 200;
		break;

	case GRAPE_SHOOT:
		FrameKey = L"Grape_Shoot";
		FilePath = L"../Image/Boss/Grape/Grape_Shoot.bmp";
		tFrame = { 0, 23, 0, 40, GetTickCount() };
		_info.fCX = 320;
		_info.fCY = 320;
		break;

	case GRAPE_BOOM:
		FrameKey = L"Grape_Boom";
		FilePath = L"../Image/Boss/Grape/Grape_Boom.bmp";
		tFrame = { 0, 36, 0, 50, GetTickCount() };
		_info.fCX = 440;
		_info.fCY = 240;
		break;

	case HANDSLAM_BOOM:
		FrameKey = L"HandSlam_Boom";
		FilePath = L"../Image/Boss/Slam/HandSlam_Boom.bmp";
		tFrame = { 0, 27, 0, 50, GetTickCount() };
		_info.fCX = 420;
		_info.fCY = 300;
		_info.fY -= 50;
		break;

	case PLAYER_DASH_RIGHT:
		FrameKey = L"Dash_Smoke_Right";
		FilePath = L"../Image/Player/Dash_Smoke_Right.bmp";
		tFrame = { 0, 12, 0, 50, GetTickCount() };
		_info.fCX = 100;
		_info.fCY = 100;
		break;

	case PLAYER_DASH_LEFT:
		FrameKey = L"Dash_Smoke_Left";
		FilePath = L"../Image/Player/Dash_Smoke_Left.bmp";
		tFrame = { 0, 12, 0, 50, GetTickCount() };
		_info.fCX = 100;
		_info.fCY = 100;
		break;


	case PLAYER_DOUBLEJUMP:
		FrameKey = L"DoubleJump_Smoke";
		FilePath = L"../Image/Player/DoubleJump_Smoke.bmp";
		tFrame = { 0, 9, 0, 50, GetTickCount() };
		_info.fCX = 100;
		_info.fCY = 30;
		_info.fY -= 50;
		break;

	case PLAYER_HIT:
		FrameKey = L"Player_Hit";
		FilePath = L"../Image/Player/Player_Hit.bmp";
		tFrame = { 0, 10, 0, 50, GetTickCount() };
		_info.fCX = 100;
		_info.fCY = 100;
		break;

	case MONSTER_APPEAR:
		FrameKey = L"Monster_Apear";
		FilePath = L"../Image/Monster/Monster_Apear.bmp";
		tFrame = { 0, 10, 0, 50, GetTickCount() };
		_info.fCX = 150;
		_info.fCY = 150;
		break;

	case MONSTER_DEAD:
		FrameKey = L"Monster_Dead";
		FilePath = L"../Image/Monster/Monster_Dead.bmp";
		tFrame = { 0, 4, 0, 50, GetTickCount() };
		_info.fCX = 150;
		_info.fCY = 150;
		break;

	case BERSERKER_ATT:
		FrameKey = L"Berserker_Attack";
		FilePath = L"../Image/Player/Berserker/Berserker_Attack.bmp";
		tFrame = { 0, 4, 0, 50, GetTickCount() };
		_info.fCX = 150;
		_info.fCY = 150;
		break;

	case MAD_AXE:
		FrameKey = L"Berserker_1_MadAxe_Real";
		FilePath = L"../Image/Player/Berserker/Berserker_1_MadAxe_Real.bmp";
		tFrame = { 0, 39, 0, 40, GetTickCount() };
		_info.fCX = 300;
		_info.fCY = 200;
		break;

	case MAD_AXE_2_LEFT:
		FrameKey = L"Berserker_2_MadAxe_Left";
		FilePath = L"../Image/Player/Berserker/Berserker_2_MadAxe_Left.bmp";
		tFrame = { 0, 12, 0, 40, GetTickCount() };
		_info.fCX = 500;
		_info.fCY = 200;
		break;

	case MAD_AXE_2_RIGHT:
		FrameKey = L"Berserker_2_MadAxe_Right";
		FilePath = L"../Image/Player/Berserker/Berserker_2_MadAxe_Right.bmp";
		tFrame = { 0, 12, 0, 40, GetTickCount() };
		_info.fCX = 500;
		_info.fCY = 200;
		break;

	case DEMONIZATION:
		FrameKey = L"Berserker_Demonization";
		FilePath = L"../Image/Player/Berserker/Berserker_Demonization.bmp";
		tFrame = { 0, 46, 0, 50, GetTickCount() };
		_info.fCX = 100;
		_info.fCY = 200;
		break;

	case DEMON_MADAXE:
		FrameKey = L"Berserker_Demon_MadAxe";
		FilePath = L"../Image/Player/Berserker/Berserker_Demon_MadAxe.bmp";
		tFrame = { 0, 20, 0, 50, GetTickCount() };
		_info.fCX = 300;
		_info.fCY = 400;
		break;

	case DEMON_AURA:
		FrameKey = L"Berserker_Aura";
		FilePath = L"../Image/Player/Berserker/Berserker_Aura.bmp";
		tFrame = { 0, 46, 0, 80, GetTickCount() };
		_info.fCX = 100;
		_info.fCY = 100;
		break;

	default:
		break;
	}

	bool dupl_Check(false);
	for (auto& elem : m_EffectList)
	{
		if (elem->Get_FrameKey() == FrameKey)
			dupl_Check = true;
	}
	
	if(!dupl_Check)
	{
		m_EffectList.push_back(new CEffect(FrameKey, FilePath, tFrame, _info));
		m_EffectList.back()->Initialize();
	}

}

void CEffectMgr::Add_Follow_Effect(EFFECTTYPE _effect, INFO* _info)
{
	const TCHAR* FrameKey(nullptr);
	const TCHAR* FilePath(nullptr);
	FRAME tFrame{};

	switch (_effect)
	{
	case DEMON_AURA:
		FrameKey = L"Berserker_Aura";
		FilePath = L"../Image/Player/Berserker/Berserker_Aura.bmp";
		tFrame = { 0, 46, 0, 80, GetTickCount() };
		break;
	}
	m_EffectList.push_back(new CEffect(FrameKey, FilePath, tFrame, _info));
	m_EffectList.back()->Initialize();


}



void CEffectMgr::Delete_Effect(EFFECTTYPE _effect)
{
	const TCHAR* FrameKey(nullptr);

	switch (_effect)
	{
	case GRAPE_READY:
		FrameKey = L"Grape_Ready";
		break;

	case GRAPE_ELECT:
		FrameKey = L"Grape_Elect";
		break;

	case GRAPE_SHOOT:
		FrameKey = L"Grape_Shoot";
		break;

	case GRAPE_BOOM:
		FrameKey = L"Grape_Boom";
		break;

	case HANDSLAM_BOOM:
		FrameKey = L"HandSlam_Boom";
		break;

	default:
		break;
	}

	for (list<CEffect*>::iterator iter = m_EffectList.begin(); iter != m_EffectList.end();)
	{
		if ((*iter)->Get_FrameKey() == FrameKey)
		{
			delete* iter;
			*iter = nullptr;
			iter = m_EffectList.erase(iter);
			return;
		}
		else
			++iter;
	}

}

void CEffectMgr::Update()
{
	for (list<CEffect*>::iterator iter = m_EffectList.begin(); iter != m_EffectList.end();)
	{
		(*iter)->Update();


		if ((*iter)->Get_EffectOver() && (*iter)->Get_FrameKey() != L"Grape_Elect" && (*iter)->Get_FrameKey() != L"Berserker_Aura")
		{

			if ((*iter)->Get_FrameKey() == L"Berserker_Demonization")
			{
				Add_Effect(BONE_HOWL, (*iter)->Get_Info());

				CObj* pObj = CObjMgr::Get_Instance()->Get_Player();

				static_cast<CBerserker*>(pObj)->Be_Demon();
			}
			delete* iter;
			*iter = nullptr;
			iter = m_EffectList.erase(iter);
		}
		else
			++iter;
	}

}

void CEffectMgr::Late_Update()
{
	for (auto& elem : m_EffectList)
	{
		elem->Late_Update();
	}
}

void CEffectMgr::Render(HDC hDC)
{
	for (auto& elem : m_EffectList)
	{
		elem->Render(hDC);
	}
}

void CEffectMgr::Release()
{
	for_each(m_EffectList.begin(), m_EffectList.end(), Safe_Delete<CEffect*>);
	m_EffectList.clear();
}

void CEffectMgr::Add_Monster(MONSTERID _ID, INFO _info)
{
	Add_Effect(MONSTER_APPEAR, _info);
	m_EffectList.back()->Set_MonsterID(_ID);
}

