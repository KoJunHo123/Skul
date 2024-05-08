#include "stdafx.h"
#include "Player.h"
#include "KeyMgr.h"
#include "BmpMgr.h"
#include "AnimationMgr.h"
#include "CameraMgr.h"
#include "LineMgr.h"


CPlayer::CPlayer()
	: m_dashDelay(GetTickCount())
	, m_bCanAction(true)
	, m_bCanDown(false)
	, m_fDashSpeed(0.f)
	, m_iJumpCount(0)
	, m_bSecondDash(false)
	, m_bDownJump(false)
	, m_bDashMove(false)
	, m_bUsingSkill(false)
	, m_bInfoColl(false)
	, m_bCameraShake(false)
	, m_bAttack(false)
	, m_bSecondAttack(false)
	, m_bJumpAttack(false)
	, m_iMoveRange(0)
	, m_iShakeTime(GetTickCount())
	, m_bNowPlaying(false)
	, m_iACoolTime(0)
	, m_iSCoolTime(0)
	, m_iACoolTimeCheck(GetTickCount())
	, m_iSCoolTimeCheck(GetTickCount())
{
}


CPlayer::~CPlayer()
{
	Release();
}


void CPlayer::Release()
{
}

void CPlayer::Key_Input()
{
	//GetKeyState()
	// 
	// 호출 시점에 매개변수로 넘겨주는 정보가 눌렸는지 아닌지를 검사하는 함수
	
	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_RIGHT) && !(BERSERKER == m_eSkul && JUMP_ATTACK == m_eCurState))
		{
			if (!m_bAttack && !m_bSecondAttack)
			{
				m_eDir = RIGHT;
				m_eSaveDir = RIGHT;
				m_tInfo.fX += m_fSpeed;

				if (m_bGround == true)
					m_eCurState = WALK;

				m_iMoveRange = 0;
			}
			else if ((m_bAttack || m_bSecondAttack) && m_tFrame.iFrameStart == 0 && m_tFrame.dwTime + m_tFrame.dwSpeed < GetTickCount())
			{
				m_eDir = RIGHT;
				m_eSaveDir = RIGHT;

				m_iMoveRange = 10;
			}
		}
		if (CKeyMgr::Get_Instance()->Key_Pressing(VK_LEFT) && !(BERSERKER == m_eSkul && JUMP_ATTACK == m_eCurState))
		{
			if (!m_bAttack && !m_bSecondAttack)
			{
				m_eDir = LEFT;
				m_eSaveDir = LEFT;
				m_tInfo.fX -= m_fSpeed;

				if (m_bGround == true)
					m_eCurState = WALK;

				m_iMoveRange = 0;
			}
			else if ((m_bAttack || m_bSecondAttack) && m_tFrame.iFrameStart == 0 && m_tFrame.dwTime + m_tFrame.dwSpeed < GetTickCount())
			{
				m_eDir = LEFT;
				m_eSaveDir = LEFT;

				m_iMoveRange = -10;
			}
		}
	if (CKeyMgr::Get_Instance()->Key_Up(VK_RIGHT) || CKeyMgr::Get_Instance()->Key_Up(VK_LEFT))
	{
		if (m_bGround == true)
			m_eCurState = IDLE;
	}

	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_DOWN))
	{
		m_eDir = DOWN;
	}
	if (CKeyMgr::Get_Instance()->Key_Up(VK_DOWN))
	{
		m_eDir = m_eSaveDir;
	}


	if (CKeyMgr::Get_Instance()->Key_Down('Z'))
	{
		if (m_dashDelay + 750 < GetTickCount() || m_bSecondDash)
		{
			m_eCurState = DASH;
			if (m_eSaveDir == RIGHT)
			{
				m_fDashRange = m_tInfo.fX + 100;
				m_bDashMove = true;
				m_bCanAction = false;
				CEffectMgr::Get_Instance()->Add_Effect(PLAYER_DASH_RIGHT, m_tInfo);

			}
			else if (m_eSaveDir == LEFT)
			{
				m_fDashRange = m_tInfo.fX - 100;
				m_bDashMove = true;
				m_bCanAction = false;
				CEffectMgr::Get_Instance()->Add_Effect(PLAYER_DASH_LEFT, m_tInfo);
			}

			if (m_bSecondDash)
				m_bSecondDash = false;
			else
				m_bSecondDash = true;

			CSoundMgr::Get_Instance()->StopSound(SOUND_DASH);
			CSoundMgr::Get_Instance()->PlaySound(L"Default_Dash.wav", SOUND_DASH, 1.f);

			m_dashDelay = GetTickCount();
		}

		if (m_bSecondAttack)
			m_bSecondAttack = false;


	}

	if (CKeyMgr::Get_Instance()->Key_Down('C'))
	{
		if (DOWN == m_eDir)
		{
			m_tInfo.fY += 5.f;
			++m_iJumpCount;
		}
		else if (m_iJumpCount < 2)
		{
			m_eCurState = JUMP;
			m_bGround = false;
			m_fYSpeed = 7;

			if (1 == m_iJumpCount)
			{
				CEffectMgr::Get_Instance()->Add_Effect(PLAYER_DOUBLEJUMP, m_tInfo);
			}
			++m_iJumpCount;

			CSoundMgr::Get_Instance()->StopSound(SOUND_JUMP);
			CSoundMgr::Get_Instance()->PlaySound(L"Default_Jump.wav", SOUND_JUMP, 1.f);
		}
		if (m_bSecondAttack)
			m_bSecondAttack = false;

	}

}

void CPlayer::SetMotionEvent()
{
	// Intro
	if (m_eCurState == REBONE && m_tFrame.iFrameStart == m_tFrame.iFrameEnd)
	{
		m_eCurState = IDLE;
		m_bCanAction = true;
		m_pFrameKey = L"Skul_Right";
	}

	if (!m_bCanAction && m_eCurState == DASH)
	{
		if ((m_eSaveDir == RIGHT && m_fDashRange < m_tInfo.fX - 5)
			|| (m_eSaveDir == LEFT && m_fDashRange > m_tInfo.fX + 5))
		{
			m_bCanAction = true;
			m_bDashMove = false;
			m_eCurState = IDLE;
		}
		else if (0 == m_fDashRange)
		{
			m_bCanAction = true;
			m_bDashMove = false;
			m_eCurState = IDLE;
		}
	}

	if (m_eCurState == FALLING && m_bGround)
	{
		m_eCurState = IDLE;
	}

}

void CPlayer::DashMove()
{
	if (m_bDashMove)
	{
		if (m_eSaveDir == RIGHT)
		{
			m_tInfo.fX += 7;	
		}
		else if(m_eSaveDir == LEFT)
		{
			m_tInfo.fX -= 7;
		
		}

		m_fYSpeed = 0.f;
	}
}

void CPlayer::LineCollision()
{
	float	fY(0.f);

	bool	bLineCol = CLineMgr::Get_Instance()->Collision_Line(this, m_tInfo.fX, &fY);
	if (bLineCol)
	{
		if ((m_eCurState == FALLING || m_eCurState == FALLING_START || m_eCurState == JUMP_ATTACK))
		{
			m_bGround = true;
			m_tInfo.fY = fY;
		}
	}
	else if(!m_bInfoColl)
	{
		m_bGround = false;
	}
}

void CPlayer::CoolTime()
{
	if (0 < m_iACoolTime && m_iACoolTimeCheck + 1000 < GetTickCount())
	{
		--m_iACoolTime;
		m_iACoolTimeCheck = GetTickCount();
	}
	
	if (0 < m_iSCoolTime && m_iSCoolTimeCheck + 1000 < GetTickCount())
	{
		--m_iSCoolTime;
		m_iSCoolTimeCheck = GetTickCount();
	}
}




void CPlayer::Check_Player(HDC hDC)
{
	TCHAR szTemp[64];
	
	// pos
	swprintf_s(szTemp, L"x : %d, y : %d", (int)m_tInfo.fX, (int)m_tInfo.fY);
	TextOut(hDC, 0, 0, szTemp, lstrlen(szTemp));

	// direction
	switch (m_eDir)
	{
	case RIGHT:
		wsprintf(szTemp, L"Direction : %s", L"RIGHT");
		break;

	case LEFT:
		wsprintf(szTemp, L"Direction : %s", L"LEFT");
		break;

	default:
		wsprintf(szTemp, L"Direction : %s", L"NONE");
		break;
	}
	TextOut(hDC, 0, 25, szTemp, lstrlen(szTemp));

	// state
	switch (m_eCurState)
	{
	case IDLE:
		wsprintf(szTemp, L"State : %s", L"IDLE");
		break;
	case WALK:
		wsprintf(szTemp, L"State : %s", L"WALK");
		break;
	case JUMP:
		wsprintf(szTemp, L"State : %s", L"JUMP");
		break;
	case FALLING_START:
		wsprintf(szTemp, L"State : %s", L"FALLING_START");
		break;
	case FALLING:
		wsprintf(szTemp, L"State : %s", L"FALLING");
		break;
	case DASH:
		wsprintf(szTemp, L"State : %s", L"DASH");
		break;
	case ATTACK:
		wsprintf(szTemp, L"State : %s", L"ATTACK");
		break;
	case ATTACK_2:
		wsprintf(szTemp, L"State : %s", L"ATTACK2");
		break;
	case JUMP_ATTACK:
		wsprintf(szTemp, L"State : %s", L"JUMP_ATTACK");
		break;
	case HIT_1:
		wsprintf(szTemp, L"State : %s", L"HIT");
		break;
	case DEAD:
		wsprintf(szTemp, L"State : %s", L"DEAD");
		break;
	default:
		wsprintf(szTemp, L"State : %s", L"NONE");
		break;
	}
	TextOut(hDC, 0, 50, szTemp, lstrlen(szTemp));

	if (m_bGround)
		wsprintf(szTemp, L"Ground : true");
	else
		wsprintf(szTemp, L"Ground : false");
	TextOut(hDC, 0, 75, szTemp, lstrlen(szTemp));

	wsprintf(szTemp, L"HP : %d", m_iHp);
	TextOut(hDC, 0, 100, szTemp, lstrlen(szTemp));
}

