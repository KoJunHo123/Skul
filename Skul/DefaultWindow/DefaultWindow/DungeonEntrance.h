#pragma once
#include "Scene.h"
class CDungeonEntrance : public CScene
{
public:
	CDungeonEntrance();
	~CDungeonEntrance();


public:
	// CScene을(를) 통해 상속됨
	void Initialize() override;
	int Update() override;
	void Late_Update() override;
	void Render(HDC hDC) override;
	void Release() override;
};

