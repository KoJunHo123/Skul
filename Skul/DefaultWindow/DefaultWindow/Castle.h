#pragma once
#include "Scene.h"

class CCastle : public CScene
{
public:
	CCastle();
	~CCastle();
public:
	// CScene��(��) ���� ��ӵ�
	void Initialize() override;
	int Update() override;
	void Late_Update() override;
	void Render(HDC hDC) override;
	void Release() override;

};
