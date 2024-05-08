#pragma once

#include "Monster.h"

class CSoldier : public CMonster
{
public:
	CSoldier();
	~CSoldier();


public:
	// CMonster��(��) ���� ��ӵ�
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

