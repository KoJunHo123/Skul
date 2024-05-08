#pragma once
#include "Attack.h"

class CMeleeAttack : public CAttack
{
private:

public:
	CMeleeAttack();
	CMeleeAttack(INFO* _info, ATTACKTYPE _type, DIRECTION _dir, int _damage, bool _playerAttack, bool* _attacking);
	~CMeleeAttack();

public:
	// CAttack��(��) ���� ��ӵ�
	void Initialize() override;
	int Update() override;
	void Late_Update() override;
	void Render(HDC hDC) override;
	void Release() override;
};

