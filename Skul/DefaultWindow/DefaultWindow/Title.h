#pragma once
#include "Scene.h"
class CTitle : public CScene
{
public:
	CTitle();
	~CTitle();

public:
	// CScene��(��) ���� ��ӵ�
	void Initialize() override;
	int Update() override;
	void Late_Update() override;
	void Render(HDC hDC) override;
	void Release() override;
};
