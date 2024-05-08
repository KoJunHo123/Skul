#pragma once
#include "Player.h"
class CBerserker : public CPlayer
{
private:
	int m_iTier;
	bool m_bStop;


public:
	CBerserker();
	~CBerserker();

public:
	// CPlayer을(를) 통해 상속됨
	void Initialize() override;
	int Update() override;
	void Late_Update() override;
	void Render(HDC hDC) override;
	void Release() override;

	void Be_Demon();
	int Get_Tier() { return m_iTier; }
	void Up_Tier() { ++m_iTier; }

private:
	void SkillKey_Input() override;
	void PlayerMoveFrame() override;
	void DealTime();
};

