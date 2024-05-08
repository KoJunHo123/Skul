#pragma once
#include "Obj.h"

class CGround : public CObj
{
private:
public:
	CGround();
	~CGround();

public:
	// CObj��(��) ���� ��ӵ�
	void Initialize() override;
	int Update() override;
	void Late_Update() override;
	void Render(HDC hDC) override;
	void Release() override;

	void Set_Rect(RECT _rect);
};

