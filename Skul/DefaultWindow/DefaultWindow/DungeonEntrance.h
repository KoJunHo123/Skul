#pragma once
#include "Scene.h"
class CDungeonEntrance : public CScene
{
public:
	CDungeonEntrance();
	~CDungeonEntrance();


public:
	// CScene��(��) ���� ��ӵ�
	void Initialize() override;
	int Update() override;
	void Late_Update() override;
	void Render(HDC hDC) override;
	void Release() override;
};
