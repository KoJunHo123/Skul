#pragma once
#include "Npc.h"
class CSpider : public CNpc
{
public:
	// CNpc��(��) ���� ��ӵ�
	void Initialize() override;
	int Update() override;
	void Late_Update() override;
	void Render(HDC hDC) override;
	void Release() override;

	void Upgrade_Skul();

public:
	void EnforceSkul();
};

