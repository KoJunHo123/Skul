#pragma once
#include "Scene.h"

class CSkullEnforce : public CScene
{
public:
	CSkullEnforce();
	~CSkullEnforce();

public:
	// CScene��(��) ���� ��ӵ�
	void Initialize() override;

	int Update() override;

	void Late_Update() override;

	void Render(HDC hDC) override;

	void Release() override;

};
