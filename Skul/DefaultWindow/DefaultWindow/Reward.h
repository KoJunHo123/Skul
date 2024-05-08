#pragma once
#include "Obj.h"
class CReward : public CObj
{
private:
	REWARDTYPE	m_eReward;
	
	INFO		m_tRectInfo;

	bool		m_bActivate;
	bool		m_bGetReward;

public:
	CReward();
	~CReward();

public:
	// CObj을(를) 통해 상속됨
	void Initialize() override;
	int Update() override;
	void Late_Update() override;
	void Render(HDC hDC) override;
	void Release() override;

public:
	bool Get_Activate() { return m_bActivate; }

	void Reward_Activate() { m_bActivate = true; }
	bool Get_Coll();
	void Get_Reward();

};

