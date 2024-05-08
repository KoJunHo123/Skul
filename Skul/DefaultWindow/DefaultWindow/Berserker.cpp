#include "stdafx.h"
#include "Berserker.h"

#include "KeyMgr.h"
#include "BmpMgr.h"
#include "AnimationMgr.h"
#include "CameraMgr.h"
#include "LineMgr.h"
#include "BattleMgr.h"

CBerserker::CBerserker()
	: m_iTier(0)
	, m_bStop(false)
{
}


CBerserker::~CBerserker()
{
	Release();
}

void CBerserker::Initialize()
{
	m_tInfo.fCX = 30.f;
	m_tInfo.fCY = 30.f;
	CCameraMgr::Get_Instance()->CalculateDist(WINCX / 2.f, 400);

	m_fSpeed = 3.f;

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/Berserker/Berserker_1_Left.bmp", L"Berserker_1_Left");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/Berserker/Berserker_1_Right.bmp", L"Berserker_1_Right");

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/Berserker/Berserker_2_Left.bmp", L"Berserker_2_Left");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/Berserker/Berserker_2_Right.bmp", L"Berserker_2_Right");

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/Berserker/Berserker_2_Demon_Left.bmp", L"Berserker_2_Demon_Left");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/Berserker/Berserker_2_Demon_Right.bmp", L"Berserker_2_Demon_Right");



	// 랜더링 순서 설정
	m_eRender = RENDER_PLAYER;

	// 시작 애니메이션 설정
	m_eCurState = IDLE;
	m_ePreState = IDLE;
	m_eDir = RIGHT;
	m_eSaveDir = RIGHT;

	m_pFrameKey = L"Skul_Right";

	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 3;
	m_tFrame.dwSpeed = 200;
	m_tFrame.dwTime = GetTickCount();

	m_iHp = 100;
	m_bPlayer = true;
	m_bPressDown = false;

	m_eSkul = BERSERKER;
	m_bNowPlaying = false;
}

int CBerserker::Update()
{
	if (m_bDead)
		return OBJ_DEAD;

	CoolTime();

	if(!m_bStop)
	{
		if (IDLE == m_eCurState)
		{
			if (m_bAttack)
				m_bAttack = false;
			if (m_bJumpAttack)
				m_bJumpAttack = false;
			if (!m_bCanAction)
				m_bCanAction = true;
			if (m_bSecondAttack)
				m_bSecondAttack = false;
		}


		if (m_bCanAction)
		{
			Key_Input();
			SkillKey_Input();
		}

		if (m_bGround)
		{
			// 우리 섯커형기준으로는 1
			m_iJumpCount = 0;
		}

		CCameraMgr::Get_Instance()->CalculateDist(m_tInfo.fX, m_tInfo.fY);


		__super::Gravity();
		__super::Update_Rect();
		PlayerMoveFrame();
	}
	else
		CSoundMgr::Get_Instance()->PlaySound(L"Berserker_Demonization.wav", SOUND_BERSERKER_DEMONIZATION, 1.f);

	return OBJ_NOEVENT;
}

void CBerserker::Late_Update()
{
	if (!m_bStop)
	{

		DashMove();
		LineCollision();
		SetMotionEvent();

		if (m_fYSpeed < 0 && !m_bDashMove && !m_bJumpAttack && m_eCurState != FALLING && m_eCurState != SKILL_1)
		{
			m_eCurState = FALLING_START;
		}

		if (m_eCurState != m_ePreState)
		{
			if (0 == m_iTier)
				CAnimationMgr::SetBerserker_1_Frame(this);
			else if (1 == m_iTier)
				CAnimationMgr::SetBerserker_2_Frame(this);
			else
				CAnimationMgr::SetBerserker_Demon_Frame(this);
		}

		else if (!m_bUsingSkill && m_eSaveDir == RIGHT && m_iTier == 0)
		{
			m_pFrameKey = L"Berserker_1_Right";
		}
		else if (!m_bUsingSkill && m_eSaveDir == LEFT && m_iTier == 0)
		{
			m_pFrameKey = L"Berserker_1_Left";
		}
		else if (!m_bUsingSkill && m_eSaveDir == RIGHT && m_iTier == 1)
		{
			m_pFrameKey = L"Berserker_2_Right";
		}
		else if (!m_bUsingSkill && m_eSaveDir == LEFT && m_iTier == 1)
		{
			m_pFrameKey = L"Berserker_2_Left";
		}
		else if (!m_bUsingSkill && m_eSaveDir == RIGHT && m_iTier == 2)
		{
			m_pFrameKey = L"Berserker_2_Demon_Right";
		}
		else if (!m_bUsingSkill && m_eSaveDir == LEFT && m_iTier == 2)
		{
			m_pFrameKey = L"Berserker_2_Demon_Left";
		}

	}
}

void CBerserker::Render(HDC hDC)
{
	if (!m_bStop)
	{
		Vec2 RenderPos = CCameraMgr::Get_Instance()->Get_RenderPos(m_tInfo.fX, m_tInfo.fY);
		HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);

		// Rectangle(hDC, RenderPos.fX - m_tInfo.fCX / 2, RenderPos.fY - m_tInfo.fCY / 2, RenderPos.fX + m_tInfo.fCX / 2, RenderPos.fY + m_tInfo.fCY / 2);


		GdiTransparentBlt(hDC,
			(int)((RenderPos.fX - 100 - 2.f)),
			(int)(RenderPos.fY - 100 - 10.f),
			200,
			200,
			hMemDC,
			m_tFrame.iFrameStart * 200,
			m_tFrame.iMotion * 200,
			200,
			200,
			RGB(255, 0, 255));


		// Check_Player(hDC);
	}
}

void CBerserker::Release()
{
}

void CBerserker::Be_Demon()
{
	m_iTier = 2;
	m_bStop = false;
	m_eCurState = IDLE;
	m_tFrame = {0, 7, 0, 120, GetTickCount()};
	CEffectMgr::Get_Instance()->Add_Follow_Effect(DEMON_AURA, &m_tInfo);
	CBattleMgr::Get_Instance()->Add_MeleeAttack(&m_tInfo, DEMONIZATION_BOOM, m_eDir, 100, m_bPlayer, &m_bAttacking);
}

void CBerserker::SkillKey_Input()
{
	if (CKeyMgr::Get_Instance()->Key_Down('X'))
	{
		if (!m_bGround)
		{
			m_eCurState = JUMP_ATTACK;
			m_bJumpAttack = true;
			m_fYSpeed -= 7.f;
		}
		else
		{
			if (!m_bSecondAttack && m_eCurState != ATTACK)
			{
				if (m_eCurState != ATTACK_2)
					m_eCurState = ATTACK;
				m_bAttack = true;
			}
			else
			{
				m_bSecondAttack = true;
			}
		}
	}

	if (CKeyMgr::Get_Instance()->Key_Down('A') && m_iACoolTime == 0)
	{
		m_eCurState = SKILL_1;
		m_iACoolTime = 5;
		m_bCanAction = false;
	}
	
	if (CKeyMgr::Get_Instance()->Key_Down('S') && m_iSCoolTime == 0)
	{
		m_eCurState = SKILL_2_INTRO;
		m_iSCoolTime = 10;
		m_bCanAction = false;
	}

}

void CBerserker::PlayerMoveFrame()
{
	// 넘길 때 되면
	if (m_tFrame.dwTime + m_tFrame.dwSpeed < GetTickCount())
	{
		// 다음 프레임으로 넘어감
		++m_tFrame.iFrameStart;
		m_tFrame.dwTime = GetTickCount();

		// 끝나면 처음으로
		if (m_tFrame.iFrameStart > m_tFrame.iFrameEnd)
		{
			m_tFrame.iFrameStart = 0;

			// 떨어지는 애니메이션
			if (m_eCurState == FALLING_START)
			{
				m_eCurState = FALLING;
			}

			if (m_eCurState == ATTACK)
			{
				if (m_bSecondAttack)
				{
					m_eCurState = ATTACK_2;
					m_tInfo.fX += m_iMoveRange;
					m_bSecondAttack = false;
				}
				else
				{
					m_bAttack = false;
					m_eCurState = IDLE;
				}
			}
			else if (m_eCurState == ATTACK_2)
			{
				if (m_bAttack == true)
				{
					m_eCurState = ATTACK;
					m_tInfo.fX += m_iMoveRange;
					m_bAttack = false;
				}
				else
				{
					m_bSecondAttack = false;
					m_eCurState = IDLE;

				}
			}
			else if (m_eCurState == JUMP_ATTACK && !m_bGround)
			{
				m_tFrame.iFrameStart = m_tFrame.iFrameEnd;
			}
			else if (m_eCurState == JUMP_ATTACK && m_bGround)
			{
				m_eCurState = IDLE;
				m_bJumpAttack = false;
			}

			if (m_eCurState == SKILL_1)
			{
				m_eCurState = IDLE;
				m_bCanAction = true;
			}

			if (m_eCurState == SKILL_2_INTRO)
			{
				if (m_iTier != 0)
					m_eCurState = SKILL_2_READY;
				else m_eCurState = SKILL_2;
			}
			else if (m_eCurState == SKILL_2_READY)
			{
				m_eCurState = SKILL_2;
			}
			else if (m_eCurState == SKILL_2)
			{
				m_eCurState = IDLE;
				m_bCanAction = true;
			}


			if (m_eCurState == DEAD)
			{
				m_bDead = true;
			}
		}

		DealTime();

	}
}

void CBerserker::DealTime()
{
	// 1차
	if(m_iTier == 0)
	{
		if (m_eCurState == ATTACK && (m_tFrame.iFrameStart == 4))
		{
			m_bAttacking = true;
			CBattleMgr::Get_Instance()->Add_MeleeAttack(&m_tInfo, BERSERKER_ATTACK_1, m_eDir, 15, m_bPlayer, &m_bAttacking);
		}
		else if (m_eCurState == ATTACK_2 && (m_tFrame.iFrameStart == 5))
		{
			m_bAttacking = true;
			CBattleMgr::Get_Instance()->Add_MeleeAttack(&m_tInfo, BERSERKER_ATTACK_2, m_eDir, 15, m_bPlayer, &m_bAttacking);
		}
		else if (m_eCurState == JUMP_ATTACK && m_tFrame.iFrameStart >= 2)
		{
			m_bAttacking = true;
			CBattleMgr::Get_Instance()->Add_MeleeAttack(&m_tInfo, BERSERKER_ATTACK_2, m_eDir, 15, m_bPlayer, &m_bAttacking);
		}
		else if (m_eCurState == SKILL_1 && m_tFrame.iFrameStart == 1)
		{
			m_bAttacking = true;
			CEffectMgr::Get_Instance()->Add_Effect(BONE_HOWL, m_tInfo);
			CBattleMgr::Get_Instance()->Add_MeleeAttack(&m_tInfo, BERSERKER_SKILL_1, m_eDir, 20, m_bPlayer, &m_bAttacking);
		}
		else if (m_eCurState == SKILL_2 && m_tFrame.iFrameStart >= 4)
		{
			m_bAttacking = true;

			INFO tMadAxe_Info = m_tInfo;

			if (m_eSaveDir == RIGHT)
				tMadAxe_Info.fX += 60.f;
			else
				tMadAxe_Info.fX -= 60.f;

			tMadAxe_Info.fY -= 10.f;
			CEffectMgr::Get_Instance()->Add_Unique_Effect(MAD_AXE, tMadAxe_Info);
			CBattleMgr::Get_Instance()->Add_MeleeAttack(&m_tInfo, BERSERKER_SKILL_2, m_eDir, 10, m_bPlayer, &m_bAttacking);

			if(m_tFrame.iFrameStart == 4)
			{
				CSoundMgr::Get_Instance()->StopSound(SOUND_BERSERKER_MADAXE);
				CSoundMgr::Get_Instance()->PlaySound(L"Mad_Axe.wav", SOUND_BERSERKER_MADAXE, 1.f);
			}
		}
		else
			m_bAttacking = false;
	}
	// 2차
	else if(m_iTier == 1)
	{
		if (m_eCurState == ATTACK && (m_tFrame.iFrameStart == 4))
		{
			m_bAttacking = true;
			CBattleMgr::Get_Instance()->Add_MeleeAttack(&m_tInfo, BERSERKER_ATTACK_1, m_eDir, 20, m_bPlayer, &m_bAttacking);
		}
		else if (m_eCurState == ATTACK_2 && (m_tFrame.iFrameStart == 5))
		{
			m_bAttacking = true;
			CBattleMgr::Get_Instance()->Add_MeleeAttack(&m_tInfo, BERSERKER_ATTACK_2, m_eDir, 20, m_bPlayer, &m_bAttacking);
		}
		else if (m_eCurState == JUMP_ATTACK && m_tFrame.iFrameStart >= 2)
		{
			m_bAttacking = true;
			CBattleMgr::Get_Instance()->Add_MeleeAttack(&m_tInfo, BERSERKER_ATTACK_2, m_eDir, 20, m_bPlayer, &m_bAttacking);
		}
		else if (m_eCurState == SKILL_1 && m_tFrame.iFrameStart == 1)
		{
			m_bAttacking = true;
			m_bStop = true;
			// 악마 되는 거
			CEffectMgr::Get_Instance()->Add_Unique_Effect(DEMONIZATION, m_tInfo);
		}
		else if (m_eCurState == SKILL_2 && m_tFrame.iFrameStart >= 0)
		{
			m_bAttacking = true;

			INFO tMadAxe_Info = m_tInfo;

			if (m_eSaveDir == RIGHT)
				tMadAxe_Info.fX += 80.f;
			else
				tMadAxe_Info.fX -= 80.f;

			tMadAxe_Info.fY -= 30.f;
			if(m_eSaveDir == LEFT)
				CEffectMgr::Get_Instance()->Add_Unique_Effect(MAD_AXE_2_LEFT, tMadAxe_Info);
			else
				CEffectMgr::Get_Instance()->Add_Unique_Effect(MAD_AXE_2_RIGHT, tMadAxe_Info);

			CBattleMgr::Get_Instance()->Add_MeleeAttack(&m_tInfo, BERSERKER_2_SKILL_2, m_eDir, 40, m_bPlayer, &m_bAttacking);
			
			if (m_tFrame.iFrameStart == 0)
			{
				CSoundMgr::Get_Instance()->StopSound(SOUND_BERSERKER_MADAXE);
				CSoundMgr::Get_Instance()->PlaySound(L"Mad_Axe.wav", SOUND_BERSERKER_MADAXE, 1.f);
			}
		}
		else
			m_bAttacking = false;
	}
	else if (m_iTier == 2)
	{
		if (m_eCurState == ATTACK && (m_tFrame.iFrameStart == 6 ))
		{
			m_bAttacking = true;
			CBattleMgr::Get_Instance()->Add_MeleeAttack(&m_tInfo, BERSERKER_ATTACK_1, m_eDir, 40, m_bPlayer, &m_bAttacking);
		}
		else if (m_eCurState == ATTACK_2 && (m_tFrame.iFrameStart == 4))
		{
			m_bAttacking = true;
			CBattleMgr::Get_Instance()->Add_MeleeAttack(&m_tInfo, BERSERKER_ATTACK_2, m_eDir, 40, m_bPlayer, &m_bAttacking);
		}
		else if (m_eCurState == JUMP_ATTACK && m_tFrame.iFrameStart >= 4)
		{
			m_bAttacking = true;
			CBattleMgr::Get_Instance()->Add_MeleeAttack(&m_tInfo, BERSERKER_ATTACK_2, m_eDir, 40, m_bPlayer, &m_bAttacking);
		}
		else if (m_eCurState == SKILL_1 && m_tFrame.iFrameStart == 1)
		{
			m_bAttacking = true;
			CEffectMgr::Get_Instance()->Add_Effect(BONE_HOWL, m_tInfo);
			CBattleMgr::Get_Instance()->Add_MeleeAttack(&m_tInfo, BERSERKER_SKILL_1, m_eDir, 60, m_bPlayer, &m_bAttacking);
		}
		else if (m_eCurState == SKILL_2 && m_tFrame.iFrameStart >= 0)
		{
			m_bAttacking = true;
			
			INFO tMadAxe_Info = m_tInfo;

			if (m_eSaveDir == RIGHT)
				tMadAxe_Info.fX += 80.f;
			else
				tMadAxe_Info.fX -= 80.f;

			tMadAxe_Info.fY -= 150.f;
			CEffectMgr::Get_Instance()->Add_Unique_Effect(DEMON_MADAXE, tMadAxe_Info);

			CBattleMgr::Get_Instance()->Add_MeleeAttack(&m_tInfo, DEMON_SKILL_2, m_eDir, 100, m_bPlayer, &m_bAttacking);

			if (m_tFrame.iFrameStart == 0)
			{
				CSoundMgr::Get_Instance()->StopSound(SOUND_BERSERKER_MADAXE);
				CSoundMgr::Get_Instance()->PlaySound(L"Mad_Axe.wav", SOUND_BERSERKER_MADAXE, 1.f);
				CSoundMgr::Get_Instance()->StopSound(SOUND_BERSERKER_MADAXE_DEMON);
				CSoundMgr::Get_Instance()->PlaySound(L"Mad_Axe_2_Demon.wav", SOUND_BERSERKER_MADAXE_DEMON, 1.f);
			}
		}
		else
			m_bAttacking = false;
	}

}
