#pragma once
#include "Drop.h"

class CDropSkul : public CDrop
{
public:
	CDropSkul();
	~CDropSkul();

public:
	// CDrop을(를) 통해 상속됨
	void Initialize() override;
	int Update() override;
	void Late_Update() override;
	void Render(HDC hDC) override;
	void Release() override;
};

