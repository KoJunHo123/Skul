#pragma once

#include "Obj.h"

class CDrop : public CObj
{
protected:
	float		m_fWarigariSpeed;
	bool		m_bUpDown;
	bool		m_bStop;
	INFO		m_tRectInfo;

public:
	CDrop();
	virtual ~CDrop();

public:
	bool Get_Coll();

protected:
	void MoveWariGari();

public:
	// CObj을(를) 통해 상속됨
	void Initialize() PURE;
	int Update() PURE;
	void Late_Update() PURE;
	void Render(HDC hDC) PURE;
	void Release() PURE;
};

