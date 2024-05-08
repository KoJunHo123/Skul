#pragma once

#include "Monster.h"

class CArcher : public CMonster
{
public:
	CArcher();
	~CArcher();


public:
	// CMonster��(��) ���� ��ӵ�
	void Initialize() override;
	int Update() override;
	void Late_Update() override;
	void Render(HDC hDC) override;
	void Release() override;

	void Attack() override;

private:
	void Archer_MoveFrame();


private:
	int		m_iAttackReady;
};

