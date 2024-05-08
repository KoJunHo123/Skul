#pragma once

#include "Obj.h"
#include "EffectMgr.h"

class CPlayer :	public CObj
{
public:
	CPlayer();
	virtual ~CPlayer();

public:
	virtual void Initialize() PURE;
	virtual int  Update() PURE;
	virtual	void Late_Update()PURE;
	virtual void Render(HDC hDC)PURE;
	virtual void Release()PURE;

	virtual void		SkillKey_Input() PURE;
	virtual void		PlayerMoveFrame() PURE;

public:
	void		Set_Action(bool _action) { m_bCanAction = _action; }
	void		Set_Attack(bool _att) { m_bAttack = _att; }
	void		Set_JumpAttack(bool _jAtt) { m_bJumpAttack = _jAtt; }
	void		Set_DashRange(float _dashRange) { m_fDashRange = _dashRange; }
	void		Set_InfoColl(bool _info) { m_bInfoColl = _info; }

	SKULTYPE	Get_SkulType() { return m_eSkul; }
	bool		Get_NowPlaying() { return m_bNowPlaying;}
	void		Set_NowPlaying(bool _playing) { m_bNowPlaying = _playing; }

	int			Get_ACoolTime() { return m_iACoolTime; }
	int			Get_SCoolTime() { return m_iSCoolTime; }
	void		Set_ACoolTime(int _cool) { m_iACoolTime = _cool; }
	void		Set_SCoolTime(int _cool) { m_iSCoolTime = _cool; }

protected:
	void		Key_Input();
	void		Check_Player(HDC hDC);
	void		SetMotionEvent();
	void		DashMove();
	void		LineCollision();

	void		CoolTime();
	
protected:
	float		m_fDashSpeed;
	float		m_fDashRange;

	// 플레이어로의 각도
	float		m_fTargetAngle;

	int			m_iJumpCount;
	int			m_iDamage;
	int			m_iMoveRange;

	// 시벌..
	bool		m_bCanAction;
	bool		m_bCanDown;
	bool		m_bSecondJump;
	bool		m_bSecondDash;
	bool		m_bDownJump;
	bool		m_bDashMove;

	bool		m_bAttack;
	bool		m_bSecondAttack;
	bool		m_bJumpAttack;

	bool		m_bPressDown;
	bool		m_bUsingSkill;

	bool		m_bInfoColl;
	bool		m_bCameraShake;
	int			m_iShakeTime;
	bool		m_bNowPlaying;


	unsigned int	m_iACoolTime;
	unsigned int	m_iSCoolTime;

	int			m_iACoolTimeCheck;
	int			m_iSCoolTimeCheck;


	DWORD		m_dashDelay;
	
	SKULTYPE		m_eSkul;

};

