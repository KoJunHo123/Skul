#pragma once

#include "Define.h"
#include "SoundMgr.h"

class CObj
{
public:
	CObj();
	virtual ~CObj();

public:
	virtual		void		Initialize()	PURE;
	virtual		int			Update()		PURE;
	virtual		void		Late_Update()	PURE;
	virtual		void		Render(HDC hDC)	PURE;
	virtual		void		Release()		PURE;

protected:
	void		Move_Frame();
	void		Update_Rect();
	void		Gravity();

public:
	INFO Get_Info() { return m_tInfo; }
	RECT Get_Rect() { return m_tRect; }
	bool Get_Dead() { return m_bDead; }
	void Set_Dead() { m_bDead = true; }
	void Set_Info(INFO _info) { m_tInfo = _info; }
	void Set_Target(CObj* _target) { m_pTarget = _target; }
	RENDERID Get_GroupID() { return m_eRender; }
	DIRECTION Get_Dir() { return m_eSaveDir; }

	FRAME& Get_Frame() { return m_tFrame; }
	OBJSTATE	Get_CurState() { return m_eCurState; }
	OBJSTATE	Get_PreState() { return m_ePreState; }

	void		Set_CurState(OBJSTATE _state) { m_eCurState = _state; }
	void		Set_PreState(OBJSTATE _state) { m_ePreState = _state; }

	void		Set_Pos(float _fX, float _fY)
	{
		m_tInfo.fX = _fX;
		m_tInfo.fY = _fY;
	}

	void		Plus_PosY(float _fY) { m_tInfo.fY += _fY; }
	void		Plus_PosX(float _fX) { m_tInfo.fX += _fX; }

	void		Set_PosX(float _fX) { m_tInfo.fX = _fX; }
	void		Set_PosY(float _fY) { m_tInfo.fY = _fY; }

	bool		Hit(int _damage, DIRECTION _dir, int _knockback);
	int			Get_Hp() { return m_iHp; }
	int			Get_PlayerHp() { return m_iPlayerHp; }

	void Set_Ground(bool _bGround) { m_bGround = _bGround; }
	void Set_DeadAnim() { m_eCurState = DEAD; }
	bool Get_Player() { return m_bPlayer; }
	bool Get_GroundClass() { return m_bGroundClass; }
	bool Get_Door() { return m_bDoor; }
	bool Get_Monster() {return m_bMonster;}
	bool Get_Boss() { return m_bBoss; }
	bool Get_Cage() { return m_bCage; }

	CObj* Get_Target() { return m_pTarget; }

protected:
	INFO		m_tInfo;
	RECT		m_tRect;
	FRAME		m_tFrame;
	float		m_fSpeed;
	float		m_fYSpeed;

	CObj*		m_pTarget;
	// 체력
	static int	m_iPlayerHp;
	int			m_iHp;
	
	const TCHAR* m_pFrameKey;
	int			m_iHittedDelay;
	bool		m_bGround;
	bool		m_bDead;
	bool		m_bAttacking;

	bool		m_bPlayer;
	bool		m_bGroundClass;
	bool		m_bBoss;
	bool		m_bMonster;
	bool		m_bDoor;
	bool		m_bCage;

	// 애니메이션 용
	bool		m_bFallingStart;

	// 이넘은 뒤에 모아 놓기.
	RENDERID	m_eRender;
	DIRECTION	m_eDir;
	DIRECTION	m_eSaveDir;
	OBJSTATE	m_eCurState;
	OBJSTATE	m_ePreState;
};

