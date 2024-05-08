#pragma once

#include "Monster.h"

class CSoldier : public CMonster
{
public:
	CSoldier();
	~CSoldier();


public:
	// CMonster을(를) 통해 상속됨
	void Initialize() override;
	int Update() override;
	void Late_Update() override;
	void Render(HDC hDC) override;
	void Release() override;

	void Attack() override;
	
private:
	void Soldier_MoveFrame();


private:
	int		m_iAttackReady;
};

