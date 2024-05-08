#pragma once
#include "Scene.h"

class CStage_1 : public CScene
{
public:
	CStage_1();
	~CStage_1();

public:
	// CScene을(를) 통해 상속됨
	void Initialize() override;
	int Update() override;
	void Late_Update() override;
	void Render(HDC hDC) override;
	void Release() override;

private:
	void Set_Monster();

private:
	bool m_bMonster_1;
	bool m_bMonster_2;
	bool m_bMonster_3;

};

