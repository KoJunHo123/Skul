#pragma once
#include "Attack.h"

class CRangedAttack : public CAttack
{
public:
	CRangedAttack();
	CRangedAttack(INFO* _info, ATTACKTYPE _type, DIRECTION _dir, int _damage, bool _playerAttack, bool* _attacking, CObj* _target);
	~CRangedAttack();

public:
	// CAttack을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;

public:
	void Set_Angle(float _angle) { m_fAngle = _angle; }
	void CrushedCountUp() { ++m_iCrushCount; }
	bool CrushMoment()
	{
		bool bCrush = m_bCrushed;
		m_bCrushed = true;
		return bCrush;
	}

	void Set_YSpeed(float _speed) { m_fYSpeed = _speed; }
	float Get_YSpeed() { return m_fYSpeed; }

private:
	void Calculate_Dir();

private:
	CObj* m_pTarget;
	INFO StartInfo;

	float m_fAngle;
	float m_fSpeed;
	
	float m_fYSpeed;
	float m_fXSpeed;

	int m_iCrushCount;
	bool m_bCrushed;
};

