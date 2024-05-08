#pragma once
#include "Monster.h"

class CElderEnt : public CMonster
{
public:
	CElderEnt();
	~CElderEnt();

public:
	// CMonster을(를) 통해 상속됨
	void Initialize() override;
	int Update() override;
	void Late_Update() override;
	void Render(HDC hDC) override;
	void Release() override;
	void Attack() {};
public:
	void	Set_BodyPos(Vec2* _body) { m_body = _body; }
	int*	Get_Phase() { return &m_iPhase; }

private:
	void Boss_Idle();
	void Boss_HandSlam();
	void Boss_HandSweep();
	void Boss_Grape();

	void AttackMotion();

	void After_Attack();

	// 원래 위치로
	void Return_IdlePos();

	bool Set_Pos_Elder();

	// 보스 전용 프레임 관리
	void Ent_Move_Frame();
	// 공격 직전에
	void Body_Shake();

	// 입 움직임
	void Mouth_Move();

	// 플레이어 위치 확인해서 갈길 손, 플레이어로의 각도 계산
	void Check_PlayerPos();

private:
	Vec2* m_body;

	INFO m_leftHand;
	INFO m_rightHand;
	INFO m_Head;
	INFO m_Mouth;

	INFO* m_pMoveHand;

	INFO m_GrapeShootPos[8];

	int m_iPhase;
	int m_iPattern;
	int m_iAttackCount;
	int m_iGrapeShoot;


	float m_fMouthMove;
	float m_fBodyShakeSpeed;

	bool m_bHeadUp;
	bool m_bMouthOpen;
	bool m_shake;

	bool m_bAttackReady;
	bool m_bAttack;	// 요거 true일 때 맞으면 공격 판정.
	bool m_bAttackOver;

	float m_fAttackReadySpeed;
	float m_fAttackSpeed;
	float m_fReturnIdleSpeed;

	float m_fTargetAngle;

	int m_iMoveTime;
	int m_iAttackDelay;
	int m_iHandSlamDelay;

	int m_iCameraShakeDelay;
	int m_iPatternDelay;
};

