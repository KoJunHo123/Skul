#pragma once
#include "Drop.h"

class CDropSkul : public CDrop
{
public:
	CDropSkul();
	~CDropSkul();

public:
	// CDrop��(��) ���� ��ӵ�
	void Initialize() override;
	int Update() override;
	void Late_Update() override;
	void Render(HDC hDC) override;
	void Release() override;
};

