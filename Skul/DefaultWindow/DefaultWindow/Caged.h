#pragma once
#include "Obj.h"

class CCaged : public CObj
{
private:
	bool m_bCageDestroyed;

public:
	CCaged();
	~CCaged();

private:
	// CObj을(를) 통해 상속됨
	void Initialize() override;
	int Update() override;
	void Late_Update() override;
	void Render(HDC hDC) override;
	void Release() override;
};

