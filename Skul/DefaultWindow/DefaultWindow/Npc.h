#pragma once
#include "Obj.h"

class CNpc : public CObj
{
public:
	CNpc();
	~CNpc();


public:
	// CObj��(��) ���� ��ӵ�
	void Initialize() PURE;
	int Update() PURE;
	void Late_Update() PURE;
	void Render(HDC hDC) PURE;
	void Release() PURE;
};

