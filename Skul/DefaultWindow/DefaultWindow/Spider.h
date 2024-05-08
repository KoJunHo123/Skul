#pragma once
#include "Npc.h"
class CSpider : public CNpc
{
public:
	// CNpc을(를) 통해 상속됨
	void Initialize() override;
	int Update() override;
	void Late_Update() override;
	void Render(HDC hDC) override;
	void Release() override;

	void Upgrade_Skul();

public:
	void EnforceSkul();
};

