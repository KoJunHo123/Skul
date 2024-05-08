#pragma once
#include "Obj.h"

class CDoor : public CObj
{
private:
	DOORTYPE	m_eDoor;
	bool		m_bActivate;

	INFO		m_tRectInfo;


public:
	CDoor();
	CDoor(DOORTYPE _door);
	~CDoor();

public:
	// CObj��(��) ���� ��ӵ�
	void Initialize() override;
	int Update() override;
	void Late_Update() override;
	void Render(HDC hDC) override;
	void Release() override;

public:
	bool Get_Activate() { return m_bActivate; }
	void Door_Activate();
	bool Get_Coll();
};

