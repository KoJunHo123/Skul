#pragma once
#include "Scene.h"

class CStage_2 : public CScene
{
public:
	CStage_2();
	~CStage_2();

public:
	// CScene��(��) ���� ��ӵ�
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

