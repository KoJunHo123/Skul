#include "stdafx.h"
#include "AnimationMgr.h"

#include "Obj.h"
#include "Player.h"

CAnimationMgr* CAnimationMgr::m_pInstance = nullptr;

CAnimationMgr::CAnimationMgr()
{
}

CAnimationMgr::~CAnimationMgr()
{
}

void CAnimationMgr::SetPlayerFrame(CObj* _obj)
{
	switch (_obj->Get_CurState())
	{
	case REBONE:
		_obj->Get_Frame().iFrameStart = 0;
		_obj->Get_Frame().iFrameEnd = 23;
		_obj->Get_Frame().iMotion = 0;
		_obj->Get_Frame().dwSpeed = 50;
		_obj->Get_Frame().dwTime = GetTickCount();
		break;

	case IDLE:
		_obj->Get_Frame().iFrameStart = 0;
		_obj->Get_Frame().iFrameEnd = 3;
		_obj->Get_Frame().iMotion = 0;
		_obj->Get_Frame().dwSpeed = 120;
		_obj->Get_Frame().dwTime = GetTickCount();
		break;

	case WALK:
		_obj->Get_Frame().iFrameStart = 0;
		_obj->Get_Frame().iFrameEnd = 7;
		_obj->Get_Frame().iMotion = 1;
		_obj->Get_Frame().dwSpeed = 100;
		_obj->Get_Frame().dwTime = GetTickCount();
		break;

	case DASH:
		_obj->Get_Frame().iFrameStart = 0;
		_obj->Get_Frame().iFrameEnd = 0;
		_obj->Get_Frame().iMotion = 2;
		_obj->Get_Frame().dwSpeed = 100;
		_obj->Get_Frame().dwTime = GetTickCount();
		break;

	case JUMP:
		_obj->Get_Frame().iFrameStart = 0;
		_obj->Get_Frame().iFrameEnd = 1;
		_obj->Get_Frame().iMotion = 3;
		_obj->Get_Frame().dwSpeed = 100;
		_obj->Get_Frame().dwTime = GetTickCount();
		break;

	case FALLING_START:
		_obj->Get_Frame().iFrameStart = 0;
		_obj->Get_Frame().iFrameEnd = 1;
		_obj->Get_Frame().iMotion = 4;
		_obj->Get_Frame().dwSpeed = 100;
		_obj->Get_Frame().dwTime = GetTickCount();
		break;

	case FALLING:
		_obj->Get_Frame().iFrameStart = 0;
		_obj->Get_Frame().iFrameEnd = 2;
		_obj->Get_Frame().iMotion = 5;
		_obj->Get_Frame().dwSpeed = 100;
		_obj->Get_Frame().dwTime = GetTickCount();
		break;

	case ATTACK:
		CSoundMgr::Get_Instance()->StopSound(SOUND_NORMAL_ATTACK);
		CSoundMgr::Get_Instance()->PlaySound(L"Legacy_Attack_Heavy.wav", SOUND_NORMAL_ATTACK, 1.f);
		_obj->Get_Frame().iFrameStart = 0;
		_obj->Get_Frame().iFrameEnd = 4;
		_obj->Get_Frame().iMotion = 6;
		_obj->Get_Frame().dwSpeed = 100;
		_obj->Get_Frame().dwTime = GetTickCount();
		break;

	case ATTACK_2:
		CSoundMgr::Get_Instance()->StopSound(SOUND_NORMAL_ATTACK);
		CSoundMgr::Get_Instance()->PlaySound(L"Legacy_Attack_Heavy.wav", SOUND_NORMAL_ATTACK, 1.f);
		_obj->Get_Frame().iFrameStart = 0;
		_obj->Get_Frame().iFrameEnd = 3;
		_obj->Get_Frame().iMotion = 7;
		_obj->Get_Frame().dwSpeed = 100;
		_obj->Get_Frame().dwTime = GetTickCount();
		break;

	case JUMP_ATTACK:
		CSoundMgr::Get_Instance()->StopSound(SOUND_NORMAL_JUMP_ATTACK);
		CSoundMgr::Get_Instance()->PlaySound(L"Legacy_Attack_Heavy.wav", SOUND_NORMAL_JUMP_ATTACK, 1.f);
		_obj->Get_Frame().iFrameStart = 0;
		_obj->Get_Frame().iFrameEnd = 3;
		_obj->Get_Frame().iMotion = 8;
		_obj->Get_Frame().dwSpeed = 75;
		_obj->Get_Frame().dwTime = GetTickCount();
		break;

	case SKILL_1:
		_obj->Get_Frame().iFrameStart = 0;
		_obj->Get_Frame().iFrameEnd = 3;
		_obj->Get_Frame().iMotion = 9;
		_obj->Get_Frame().dwSpeed = 100;
		_obj->Get_Frame().dwTime = GetTickCount();
		break;

	case EXCHANGE:
		_obj->Get_Frame().iFrameStart = 0;
		_obj->Get_Frame().iFrameEnd = 6;
		_obj->Get_Frame().iMotion = 10;
		_obj->Get_Frame().dwSpeed = 100;
		_obj->Get_Frame().dwTime = GetTickCount();
		break;

	case DEAD:
		break;
	}

	_obj->Set_PreState(_obj->Get_CurState());
}

void CAnimationMgr::SetBerserker_1_Frame(CObj* _obj)
{
	switch (_obj->Get_CurState())
	{
	case IDLE:
		_obj->Get_Frame().iFrameStart = 0;
		_obj->Get_Frame().iFrameEnd = 5;
		_obj->Get_Frame().iMotion = 0;
		_obj->Get_Frame().dwSpeed = 120;
		_obj->Get_Frame().dwTime = GetTickCount();
		break;

	case WALK:
		_obj->Get_Frame().iFrameStart = 0;
		_obj->Get_Frame().iFrameEnd = 7;
		_obj->Get_Frame().iMotion = 1;
		_obj->Get_Frame().dwSpeed = 100;
		_obj->Get_Frame().dwTime = GetTickCount();
		break;

	case DASH:
		_obj->Get_Frame().iFrameStart = 0;
		_obj->Get_Frame().iFrameEnd = 4;
		_obj->Get_Frame().iMotion = 2;
		_obj->Get_Frame().dwSpeed = 100;
		_obj->Get_Frame().dwTime = GetTickCount();
		break;

	case JUMP:
		_obj->Get_Frame().iFrameStart = 0;
		_obj->Get_Frame().iFrameEnd = 2;
		_obj->Get_Frame().iMotion = 3;
		_obj->Get_Frame().dwSpeed = 100;
		_obj->Get_Frame().dwTime = GetTickCount();
		break;

	case FALLING_START:
		_obj->Get_Frame().iFrameStart = 0;
		_obj->Get_Frame().iFrameEnd = 1;
		_obj->Get_Frame().iMotion = 4;
		_obj->Get_Frame().dwSpeed = 100;
		_obj->Get_Frame().dwTime = GetTickCount();
		break;

	case FALLING:
		_obj->Get_Frame().iFrameStart = 0;
		_obj->Get_Frame().iFrameEnd = 2;
		_obj->Get_Frame().iMotion = 5;
		_obj->Get_Frame().dwSpeed = 100;
		_obj->Get_Frame().dwTime = GetTickCount();
		break;

	case ATTACK:
		CSoundMgr::Get_Instance()->StopSound(SOUND_BERSERKER_ATTACK);
		CSoundMgr::Get_Instance()->PlaySound(L"Berserker_Attack.wav", SOUND_BERSERKER_ATTACK, 1.f);

		_obj->Get_Frame().iFrameStart = 0;
		_obj->Get_Frame().iFrameEnd = 6;
		_obj->Get_Frame().iMotion = 6;
		_obj->Get_Frame().dwSpeed = 70;
		_obj->Get_Frame().dwTime = GetTickCount();
		break;

	case ATTACK_2:
		CSoundMgr::Get_Instance()->StopSound(SOUND_BERSERKER_ATTACK);
		CSoundMgr::Get_Instance()->PlaySound(L"Berserker_Attack.wav", SOUND_BERSERKER_ATTACK, 1.f);

		_obj->Get_Frame().iFrameStart = 0;
		_obj->Get_Frame().iFrameEnd = 7;
		_obj->Get_Frame().iMotion = 7;
		_obj->Get_Frame().dwSpeed = 70;
		_obj->Get_Frame().dwTime = GetTickCount();
		break;

	case JUMP_ATTACK:
		CSoundMgr::Get_Instance()->StopSound(SOUND_BERSERKER_ATTACK);
		CSoundMgr::Get_Instance()->PlaySound(L"Berserker_Attack.wav", SOUND_BERSERKER_ATTACK, 1.f);

		_obj->Get_Frame().iFrameStart = 0;
		_obj->Get_Frame().iFrameEnd = 4;
		_obj->Get_Frame().iMotion = 8;
		_obj->Get_Frame().dwSpeed = 70;
		_obj->Get_Frame().dwTime = GetTickCount();
		break;

	case SKILL_1:
		_obj->Get_Frame().iFrameStart = 0;
		_obj->Get_Frame().iFrameEnd = 1;
		_obj->Get_Frame().iMotion = 10;
		_obj->Get_Frame().dwSpeed = 100;
		_obj->Get_Frame().dwTime = GetTickCount();
		break;

	case SKILL_2_INTRO:
		_obj->Get_Frame().iFrameStart = 0;
		_obj->Get_Frame().iFrameEnd = 1;
		_obj->Get_Frame().iMotion = 11;
		_obj->Get_Frame().dwSpeed = 100;
		_obj->Get_Frame().dwTime = GetTickCount();
		break;

	case SKILL_2:
		_obj->Get_Frame().iFrameStart = 0;
		_obj->Get_Frame().iFrameEnd = 6;
		_obj->Get_Frame().iMotion = 12;
		_obj->Get_Frame().dwSpeed = 100;
		_obj->Get_Frame().dwTime = GetTickCount();
		break;

	case RECOVERY:
		_obj->Get_Frame().iFrameStart = 0;
		_obj->Get_Frame().iFrameEnd = 0;
		_obj->Get_Frame().iMotion = 13;
		_obj->Get_Frame().dwSpeed = 75;
		_obj->Get_Frame().dwTime = GetTickCount();
		break;

	case EXCHANGE:
		_obj->Get_Frame().iFrameStart = 0;
		_obj->Get_Frame().iFrameEnd = 4;
		_obj->Get_Frame().iMotion = 8;
		_obj->Get_Frame().dwSpeed = 75;
		_obj->Get_Frame().dwTime = GetTickCount();
		break;

	case DEAD:
		break;
	}

	_obj->Set_PreState(_obj->Get_CurState());

}

void CAnimationMgr::SetBerserker_2_Frame(CObj* _obj)
{
	switch (_obj->Get_CurState())
	{
	case IDLE:
		_obj->Get_Frame().iFrameStart = 0;
		_obj->Get_Frame().iFrameEnd = 7;
		_obj->Get_Frame().iMotion = 0;
		_obj->Get_Frame().dwSpeed = 120;
		_obj->Get_Frame().dwTime = GetTickCount();
		break;

	case WALK:
		_obj->Get_Frame().iFrameStart = 0;
		_obj->Get_Frame().iFrameEnd = 7;
		_obj->Get_Frame().iMotion = 1;
		_obj->Get_Frame().dwSpeed = 100;
		_obj->Get_Frame().dwTime = GetTickCount();
		break;

	case DASH:
		_obj->Get_Frame().iFrameStart = 0;
		_obj->Get_Frame().iFrameEnd = 0;
		_obj->Get_Frame().iMotion = 2;
		_obj->Get_Frame().dwSpeed = 100;
		_obj->Get_Frame().dwTime = GetTickCount();
		break;

	case JUMP:
		_obj->Get_Frame().iFrameStart = 0;
		_obj->Get_Frame().iFrameEnd = 2;
		_obj->Get_Frame().iMotion = 3;
		_obj->Get_Frame().dwSpeed = 100;
		_obj->Get_Frame().dwTime = GetTickCount();
		break;

	case FALLING_START:
		_obj->Get_Frame().iFrameStart = 0;
		_obj->Get_Frame().iFrameEnd = 1;
		_obj->Get_Frame().iMotion = 4;
		_obj->Get_Frame().dwSpeed = 100;
		_obj->Get_Frame().dwTime = GetTickCount();
		break;

	case FALLING:
		_obj->Get_Frame().iFrameStart = 0;
		_obj->Get_Frame().iFrameEnd = 2;
		_obj->Get_Frame().iMotion = 5;
		_obj->Get_Frame().dwSpeed = 100;
		_obj->Get_Frame().dwTime = GetTickCount();
		break;

	case ATTACK:
		CSoundMgr::Get_Instance()->StopSound(SOUND_BERSERKER_ATTACK);
		CSoundMgr::Get_Instance()->PlaySound(L"Berserker_Attack.wav", SOUND_BERSERKER_ATTACK, 1.f);

		_obj->Get_Frame().iFrameStart = 0;
		_obj->Get_Frame().iFrameEnd = 8;
		_obj->Get_Frame().iMotion = 6;
		_obj->Get_Frame().dwSpeed = 70;
		_obj->Get_Frame().dwTime = GetTickCount();
		break;

	case ATTACK_2:
		CSoundMgr::Get_Instance()->StopSound(SOUND_BERSERKER_ATTACK);
		CSoundMgr::Get_Instance()->PlaySound(L"Berserker_Attack.wav", SOUND_BERSERKER_ATTACK, 1.f);

		_obj->Get_Frame().iFrameStart = 0;
		_obj->Get_Frame().iFrameEnd = 10;
		_obj->Get_Frame().iMotion = 7;
		_obj->Get_Frame().dwSpeed = 70;
		_obj->Get_Frame().dwTime = GetTickCount();
		break;

	case SKILL_1:
		_obj->Get_Frame().iFrameStart = 0;
		_obj->Get_Frame().iFrameEnd = 1;
		_obj->Get_Frame().iMotion = 8;
		_obj->Get_Frame().dwSpeed = 100;
		_obj->Get_Frame().dwTime = GetTickCount();
		break;

	case JUMP_ATTACK:
		CSoundMgr::Get_Instance()->StopSound(SOUND_BERSERKER_ATTACK);
		CSoundMgr::Get_Instance()->PlaySound(L"Berserker_Attack.wav", SOUND_BERSERKER_ATTACK, 1.f);

		_obj->Get_Frame().iFrameStart = 0;
		_obj->Get_Frame().iFrameEnd = 4;
		_obj->Get_Frame().iMotion = 9;
		_obj->Get_Frame().dwSpeed = 70;
		_obj->Get_Frame().dwTime = GetTickCount();
		break;

	case SKILL_2_INTRO:
		_obj->Get_Frame().iFrameStart = 0;
		_obj->Get_Frame().iFrameEnd = 1;
		_obj->Get_Frame().iMotion = 11;
		_obj->Get_Frame().dwSpeed = 100;
		_obj->Get_Frame().dwTime = GetTickCount();
		break;

	case SKILL_2_READY:
		_obj->Get_Frame().iFrameStart = 0;
		_obj->Get_Frame().iFrameEnd = 3;
		_obj->Get_Frame().iMotion = 12;
		_obj->Get_Frame().dwSpeed = 100;
		_obj->Get_Frame().dwTime = GetTickCount();
		break;


	case SKILL_2:
		_obj->Get_Frame().iFrameStart = 0;
		_obj->Get_Frame().iFrameEnd = 5;
		_obj->Get_Frame().iMotion = 13;
		_obj->Get_Frame().dwSpeed = 100;
		_obj->Get_Frame().dwTime = GetTickCount();
		break;

	case RECOVERY:
		_obj->Get_Frame().iFrameStart = 0;
		_obj->Get_Frame().iFrameEnd = 0;
		_obj->Get_Frame().iMotion = 14;
		_obj->Get_Frame().dwSpeed = 75;
		_obj->Get_Frame().dwTime = GetTickCount();
		break;

	case EXCHANGE:
		_obj->Get_Frame().iFrameStart = 0;
		_obj->Get_Frame().iFrameEnd = 4;
		_obj->Get_Frame().iMotion = 9;
		_obj->Get_Frame().dwSpeed = 75;
		_obj->Get_Frame().dwTime = GetTickCount();
		break;

	case DEAD:
		break;
	}

	_obj->Set_PreState(_obj->Get_CurState());
}

void CAnimationMgr::SetBerserker_Demon_Frame(CObj* _obj)
{
	switch (_obj->Get_CurState())
	{
	case IDLE:
		_obj->Get_Frame().iFrameStart = 0;
		_obj->Get_Frame().iFrameEnd = 15;
		_obj->Get_Frame().iMotion = 0;
		_obj->Get_Frame().dwSpeed = 120;
		_obj->Get_Frame().dwTime = GetTickCount();
		break;

	case WALK:
		_obj->Get_Frame().iFrameStart = 0;
		_obj->Get_Frame().iFrameEnd = 15;
		_obj->Get_Frame().iMotion = 1;
		_obj->Get_Frame().dwSpeed = 100;
		_obj->Get_Frame().dwTime = GetTickCount();
		break;

	case DASH:
		_obj->Get_Frame().iFrameStart = 0;
		_obj->Get_Frame().iFrameEnd = 1;
		_obj->Get_Frame().iMotion = 2;
		_obj->Get_Frame().dwSpeed = 100;
		_obj->Get_Frame().dwTime = GetTickCount();
		break;

	case JUMP:
		_obj->Get_Frame().iFrameStart = 0;
		_obj->Get_Frame().iFrameEnd = 5;
		_obj->Get_Frame().iMotion = 3;
		_obj->Get_Frame().dwSpeed = 100;
		_obj->Get_Frame().dwTime = GetTickCount();
		break;

	case FALLING_START:
		_obj->Get_Frame().iFrameStart = 0;
		_obj->Get_Frame().iFrameEnd = 3;
		_obj->Get_Frame().iMotion = 4;
		_obj->Get_Frame().dwSpeed = 100;
		_obj->Get_Frame().dwTime = GetTickCount();
		break;

	case FALLING:
		_obj->Get_Frame().iFrameStart = 0;
		_obj->Get_Frame().iFrameEnd = 5;
		_obj->Get_Frame().iMotion = 5;
		_obj->Get_Frame().dwSpeed = 100;
		_obj->Get_Frame().dwTime = GetTickCount();
		break;

	case ATTACK:
		CSoundMgr::Get_Instance()->StopSound(SOUND_BERSERKER_ATTACK);
		CSoundMgr::Get_Instance()->PlaySound(L"Berserker_Attack.wav", SOUND_BERSERKER_ATTACK, 1.f);

		_obj->Get_Frame().iFrameStart = 0;
		_obj->Get_Frame().iFrameEnd = 11;
		_obj->Get_Frame().iMotion = 6;
		_obj->Get_Frame().dwSpeed = 20;
		_obj->Get_Frame().dwTime = GetTickCount();
		break;

	case ATTACK_2:
		CSoundMgr::Get_Instance()->StopSound(SOUND_BERSERKER_ATTACK);
		CSoundMgr::Get_Instance()->PlaySound(L"Berserker_Attack.wav", SOUND_BERSERKER_ATTACK, 1.f);

		_obj->Get_Frame().iFrameStart = 0;
		_obj->Get_Frame().iFrameEnd = 11;
		_obj->Get_Frame().iMotion = 7;
		_obj->Get_Frame().dwSpeed = 20;
		_obj->Get_Frame().dwTime = GetTickCount();
		break;

	case SKILL_1:
		_obj->Get_Frame().iFrameStart = 0;
		_obj->Get_Frame().iFrameEnd = 2;
		_obj->Get_Frame().iMotion = 8;
		_obj->Get_Frame().dwSpeed = 20;
		_obj->Get_Frame().dwTime = GetTickCount();
		break;

	case JUMP_ATTACK:
		CSoundMgr::Get_Instance()->StopSound(SOUND_BERSERKER_ATTACK);
		CSoundMgr::Get_Instance()->PlaySound(L"Berserker_Attack.wav", SOUND_BERSERKER_ATTACK, 1.f);

		
		_obj->Get_Frame().iFrameStart = 0;
		_obj->Get_Frame().iFrameEnd = 9;
		_obj->Get_Frame().iMotion = 9;
		_obj->Get_Frame().dwSpeed = 20;
		_obj->Get_Frame().dwTime = GetTickCount();
		break;

	case SKILL_2_INTRO:
		_obj->Get_Frame().iFrameStart = 0;
		_obj->Get_Frame().iFrameEnd = 2;
		_obj->Get_Frame().iMotion = 11;
		_obj->Get_Frame().dwSpeed = 80;
		_obj->Get_Frame().dwTime = GetTickCount();
		break;

	case SKILL_2_READY:
		_obj->Get_Frame().iFrameStart = 0;
		_obj->Get_Frame().iFrameEnd = 7;
		_obj->Get_Frame().iMotion = 12;
		_obj->Get_Frame().dwSpeed = 80;
		_obj->Get_Frame().dwTime = GetTickCount();
		break;


	case SKILL_2:
		_obj->Get_Frame().iFrameStart = 0;
		_obj->Get_Frame().iFrameEnd = 5;
		_obj->Get_Frame().iMotion = 13;
		_obj->Get_Frame().dwSpeed = 80;
		_obj->Get_Frame().dwTime = GetTickCount();
		break;

	case RECOVERY:
		_obj->Get_Frame().iFrameStart = 0;
		_obj->Get_Frame().iFrameEnd = 1;
		_obj->Get_Frame().iMotion = 14;
		_obj->Get_Frame().dwSpeed = 75;
		_obj->Get_Frame().dwTime = GetTickCount();
		break;

	case EXCHANGE:
		_obj->Get_Frame().iFrameStart = 0;
		_obj->Get_Frame().iFrameEnd = 4;
		_obj->Get_Frame().iMotion = 9;
		_obj->Get_Frame().dwSpeed = 75;
		_obj->Get_Frame().dwTime = GetTickCount();
		break;

	case DEAD:
		break;
	}

	_obj->Set_PreState(_obj->Get_CurState());


}


void CAnimationMgr::SetSoldierFrame(CObj* _obj)
{
	if (_obj->Get_CurState() != _obj->Get_PreState())
	{
		switch (_obj->Get_CurState())
		{
		case IDLE:
			_obj->Get_Frame().iFrameStart = 0;
			_obj->Get_Frame().iFrameEnd = 5;
			_obj->Get_Frame().iMotion = 0;
			_obj->Get_Frame().dwSpeed = 250;
			_obj->Get_Frame().dwTime = GetTickCount();
			break;

		case WALK:
			_obj->Get_Frame().iFrameStart = 0;
			_obj->Get_Frame().iFrameEnd = 7;
			_obj->Get_Frame().iMotion = 1;
			_obj->Get_Frame().dwSpeed = 100;
			_obj->Get_Frame().dwTime = GetTickCount();
			break;

		case ATTACK:
			_obj->Get_Frame().iFrameStart = 0;
			_obj->Get_Frame().iFrameEnd = 3;
			_obj->Get_Frame().iMotion = 2;
			_obj->Get_Frame().dwSpeed = 100;
			_obj->Get_Frame().dwTime = GetTickCount();
			break;

		case HIT_1:
			_obj->Get_Frame().iFrameStart = 0;
			_obj->Get_Frame().iFrameEnd = 0;
			_obj->Get_Frame().iMotion = 3;
			_obj->Get_Frame().dwSpeed = 500;
			_obj->Get_Frame().dwTime = GetTickCount();
			break;

		case HIT_2:
			_obj->Get_Frame().iFrameStart = 1;
			_obj->Get_Frame().iFrameEnd = 1;
			_obj->Get_Frame().iMotion = 3;
			_obj->Get_Frame().dwSpeed = 500;
			_obj->Get_Frame().dwTime = GetTickCount();
			break;

		default:
			break;
		}

		_obj->Set_PreState(_obj->Get_CurState());
	}

}

void CAnimationMgr::SetArcherFrame(CObj* _obj)
{
	if (_obj->Get_CurState() != _obj->Get_PreState())
	{
		switch (_obj->Get_CurState())
		{
		case IDLE:
			_obj->Get_Frame().iFrameStart = 0;
			_obj->Get_Frame().iFrameEnd = 4;
			_obj->Get_Frame().iMotion = 0;
			_obj->Get_Frame().dwSpeed = 250;
			_obj->Get_Frame().dwTime = GetTickCount();
			break;

		case WALK:
			_obj->Get_Frame().iFrameStart = 0;
			_obj->Get_Frame().iFrameEnd = 5;
			_obj->Get_Frame().iMotion = 1;
			_obj->Get_Frame().dwSpeed = 100;
			_obj->Get_Frame().dwTime = GetTickCount();
			break;

		case ATTACK:
			_obj->Get_Frame().iFrameStart = 0;
			_obj->Get_Frame().iFrameEnd = 3;
			_obj->Get_Frame().iMotion = 2;
			_obj->Get_Frame().dwSpeed = 100;
			_obj->Get_Frame().dwTime = GetTickCount();
			break;

		case HIT_1:
			_obj->Get_Frame().iFrameStart = 0;
			_obj->Get_Frame().iFrameEnd = 0;
			_obj->Get_Frame().iMotion = 3;
			_obj->Get_Frame().dwSpeed = 500;
			_obj->Get_Frame().dwTime = GetTickCount();
			break;

		case HIT_2:
			_obj->Get_Frame().iFrameStart = 1;
			_obj->Get_Frame().iFrameEnd = 1;
			_obj->Get_Frame().iMotion = 3;
			_obj->Get_Frame().dwSpeed = 500;
			_obj->Get_Frame().dwTime = GetTickCount();
			break;

		default:
			break;
		}

		_obj->Set_PreState(_obj->Get_CurState());
	}

}

void CAnimationMgr::SetElderEntFrame(CObj* _obj)
{
	if (_obj->Get_CurState() != _obj->Get_PreState())
	{
		switch (_obj->Get_CurState())
		{
		case IDLE:
			_obj->Get_Frame().iFrameStart = 0;
			_obj->Get_Frame().iFrameEnd = 5;
			_obj->Get_Frame().iMotion = 1;
			_obj->Get_Frame().dwSpeed = 250;
			_obj->Get_Frame().dwTime = GetTickCount();
			break;

			// ¶¥Âï
		case ATTACK:
			_obj->Get_Frame().iFrameStart = 0;
			_obj->Get_Frame().iFrameEnd = 0;
			_obj->Get_Frame().iMotion = 3;
			_obj->Get_Frame().dwSpeed = 100;
			_obj->Get_Frame().dwTime = GetTickCount();
			break;

			// ¶¥¾µ
		case ATTACK_2:
			_obj->Get_Frame().iFrameStart = 0;
			_obj->Get_Frame().iFrameEnd = 1;
			_obj->Get_Frame().iMotion = 2;
			_obj->Get_Frame().dwSpeed = 150;
			_obj->Get_Frame().dwTime = GetTickCount();
			break;

			// Æ÷µµ
		case SKILL_1:
			_obj->Get_Frame().iFrameStart = 0;
			_obj->Get_Frame().iFrameEnd = 1;
			_obj->Get_Frame().iMotion = 4;
			_obj->Get_Frame().dwSpeed = 150;
			_obj->Get_Frame().dwTime = GetTickCount();
			break;

		case REBONE:
			_obj->Get_Frame().iFrameStart = 0;
			_obj->Get_Frame().iFrameEnd = 0;
			_obj->Get_Frame().dwSpeed = 250;
			_obj->Get_Frame().dwTime = GetTickCount();
			if (_obj->Get_PreState() == ATTACK)
				_obj->Get_Frame().iMotion = 3;
			else if (_obj->Get_PreState() == ATTACK_2)
				_obj->Get_Frame().iMotion = 2;
			else if (_obj->Get_PreState() == SKILL_1)
				_obj->Get_Frame().iMotion = 4;
			else
				_obj->Get_Frame().iMotion = 1;

			break;

		}

		_obj->Set_PreState(_obj->Get_CurState());
	}

}
