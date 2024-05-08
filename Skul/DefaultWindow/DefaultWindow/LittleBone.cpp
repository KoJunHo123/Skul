#include "stdafx.h"
#include "LittleBone.h"
#include "KeyMgr.h"
#include "BmpMgr.h"
#include "AnimationMgr.h"
#include "CameraMgr.h"
#include "LineMgr.h"
#include "BattleMgr.h"
#include "SoundMgr.h"

CLittleBone::CLittleBone()
{
}


CLittleBone::~CLittleBone()
{
	Release();
}

void CLittleBone::Initialize()
{
	m_tInfo.fCX = 30.f;
	m_tInfo.fCY = 30.f;
	CCameraMgr::Get_Instance()->CalculateDist(WINCX / 2.f, 400);

	m_fSpeed = 3.f;

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/NormalSkul/Skul_left.bmp", L"Skul_Left");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/NormalSkul/Skul_right.bmp", L"Skul_Right");

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/NoHead/NoHead_Left.bmp", L"NoHead_Left");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/NoHead/NoHead_Right.bmp", L"NoHead_Right");

	// 랜더링 순서 설정
	m_eRender = RENDER_PLAYER;

	// 시작 애니메이션 설정
	m_eCurState = IDLE;
	m_ePreState = IDLE;
	m_eDir = RIGHT;
	m_eSaveDir = RIGHT;

	m_pFrameKey = L"Skul_Right";

	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 23;
	m_tFrame.iMotion = 0;
	m_tFrame.dwSpeed = 50;
	m_tFrame.dwTime = GetTickCount();

	m_iHp = 100;
	m_bPlayer = true;
	m_bPressDown = false;

	m_eSkul = SKUL;
	m_bNowPlaying = true;
}

int CLittleBone::Update()
{
	if (m_bDead)
		return OBJ_DEAD;

	CoolTime();

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
		m_iJumpCount = 0;
	}

	CCameraMgr::Get_Instance()->CalculateDist(m_tInfo.fX, m_tInfo.fY);

	__super::Gravity();
	__super::Update_Rect();
	PlayerMoveFrame();

	return OBJ_NOEVENT;
}

void CLittleBone::Late_Update()
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
		/*if (m_ePreState == ATTACK || m_ePreState == ATTACK_2 || m_ePreState == JUMP_ATTACK)
		{
			m_bAttack = false;
			m_bSecondAttack = false;
			m_bJumpAttack = false;
		}*/

		CAnimationMgr::SetPlayerFrame(this);
	}

	if (m_bUsingSkill && m_eSaveDir == RIGHT && m_eCurState != SKILL_1)
	{
		m_pFrameKey = L"NoHead_Right";
	}
	else if (m_bUsingSkill && m_eSaveDir == LEFT && m_eCurState != SKILL_1)
	{
		m_pFrameKey = L"NoHead_Left";
	}
	else if (!m_bUsingSkill && m_eSaveDir == RIGHT)
	{
		m_pFrameKey = L"Skul_Right";
	}
	else if (!m_bUsingSkill && m_eSaveDir == LEFT)
	{
		m_pFrameKey = L"Skul_Left";
	}
}

void CLittleBone::Render(HDC hDC)
{
	Vec2 RenderPos = CCameraMgr::Get_Instance()->Get_RenderPos(m_tInfo.fX, m_tInfo.fY);
	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);

	// Rectangle(hDC, RenderPos.fX - m_tInfo.fCX / 2, RenderPos.fY - m_tInfo.fCY / 2, RenderPos.fX + m_tInfo.fCX / 2, RenderPos.fY + m_tInfo.fCY / 2);

	{
		GdiTransparentBlt(hDC,
			(int)((RenderPos.fX - 50)),
			(int)(RenderPos.fY - 50),
			100,
			100,
			hMemDC,
			m_tFrame.iFrameStart * 100,
			m_tFrame.iMotion * 100,
			100,
			100,
			RGB(255, 0, 255));
	}
	Check_Player(hDC);
}

void CLittleBone::Release()
{
}

void CLittleBone::SkillKey_Input()
{
	if (CKeyMgr::Get_Instance()->Key_Down('X'))
	{
		if (!m_bGround)
		{
			m_eCurState = JUMP_ATTACK;
			m_bJumpAttack = true;

		}
		else
		{
			if (!m_bSecondAttack && m_eCurState != ATTACK)
			{
				if(m_eCurState != ATTACK_2)
					m_eCurState = ATTACK;
				m_bAttack = true;
			}
			else
			{
				m_bSecondAttack = true;
			}
		}
	}

	if (CKeyMgr::Get_Instance()->Key_Down('A') && !m_bUsingSkill && m_iACoolTime == 0)
	{
		m_eCurState = SKILL_1;
		CBattleMgr::Get_Instance()->Add_RangedAttack(&m_tInfo, PLAYER_SKILL_1, m_eDir, 10, m_bPlayer, &m_bUsingSkill, this);
		
		if(m_eSaveDir == RIGHT)
			static_cast<CRangedAttack*>(CBattleMgr::Get_Instance()->Get_LastAttack())->Set_Angle(0);
		else
			static_cast<CRangedAttack*>(CBattleMgr::Get_Instance()->Get_LastAttack())->Set_Angle(180);
		CBattleMgr::Get_Instance()->Get_LastAttack()->Initialize();

		m_iACoolTime = 5;
		m_bUsingSkill = true;
		m_bCanAction = false;
		CSoundMgr::Get_Instance()->StopSound(SOUND_THORW_SKUL);
		CSoundMgr::Get_Instance()->PlaySound(L"Skul_SkullThrowing.wav", SOUND_THORW_SKUL, 1.f);
	}
	else if (CKeyMgr::Get_Instance()->Key_Down('S') && m_bUsingSkill)
	{
		m_bUsingSkill = false;		
		CEffectMgr::Get_Instance()->Add_Effect(MONSTER_DEAD, m_tInfo);

		m_tInfo.fX = CBattleMgr::Get_Instance()->Find_SkullHead().fX;
		m_tInfo.fY = CBattleMgr::Get_Instance()->Find_SkullHead().fY;
		CEffectMgr::Get_Instance()->Add_Effect(MONSTER_DEAD, m_tInfo);

		CSoundMgr::Get_Instance()->StopSound(SOUND_SKUL_BACK);
		CSoundMgr::Get_Instance()->PlaySound(L"Skul_SkullBack.wav", SOUND_SKUL_BACK, 1.f);

	}
}

void CLittleBone::PlayerMoveFrame()
{
	// 넘길 때 되면
	if (m_tFrame.dwTime + m_tFrame.dwSpeed < GetTickCount())
	{
		// 다음 프레임으로 넘어감
		++m_tFrame.iFrameStart;
		m_tFrame.dwTime = GetTickCount();

		if (m_eCurState == ATTACK && m_tFrame.iFrameStart == 2)
		{
			m_bAttacking = true;
			CBattleMgr::Get_Instance()->Add_MeleeAttack(&m_tInfo, PLAYER_ATTACK_1, m_eSaveDir, 10, m_bPlayer, &m_bAttacking);
		}
		else if (m_eCurState == ATTACK_2 && m_tFrame.iFrameStart == 1)
		{
			m_bAttacking = true;
			CBattleMgr::Get_Instance()->Add_MeleeAttack(&m_tInfo, PLAYER_ATTACK_1, m_eSaveDir, 10, m_bPlayer, &m_bAttacking);
		}
		else if (m_eCurState == JUMP_ATTACK && m_tFrame.iFrameStart == 1)
		{
			m_bAttacking = true;
			CBattleMgr::Get_Instance()->Add_MeleeAttack(&m_tInfo, PLAYER_ATTACK_1, m_eSaveDir, 10, m_bPlayer, &m_bAttacking);
		}
		else
			m_bAttacking = false;


		// 끝나면 처음으로
		if (m_tFrame.iFrameStart > m_tFrame.iFrameEnd)
		{
			m_tFrame.iFrameStart = 0;

			// 떨어지는 애니메이션
			if (m_eCurState == FALLING_START)
			{
				m_eCurState = FALLING;
			}

			// 공격 애니메이션
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
			if (m_eCurState == JUMP_ATTACK)
			{
				m_bJumpAttack = false;
				m_eCurState = FALLING_START;
			}

			if (m_eCurState == SKILL_1)
			{
				m_eCurState = IDLE;
				m_bCanAction = true;
				// m_bUsingSkill = false;
			}

			if (m_eCurState == DEAD)
			{
				m_bDead = true;
			}
		}
	}
}
