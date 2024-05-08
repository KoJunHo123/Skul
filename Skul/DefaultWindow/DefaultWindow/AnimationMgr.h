#pragma once

class CObj;

class CAnimationMgr
{
private:
	static CAnimationMgr* m_pInstance;

private:
	CAnimationMgr();
	~CAnimationMgr();

public:
	static CAnimationMgr* Get_Instance()
	{
		if (!m_pInstance)
		{
			m_pInstance = new CAnimationMgr;
		}
		return m_pInstance;
	}

	static void Destroy()
	{
		if (m_pInstance)
		{
			delete m_pInstance;
		}
	}

public:
	static void SetPlayerFrame(CObj* _obj);
	static void SetBerserker_1_Frame(CObj* _obj);
	static void SetBerserker_2_Frame(CObj* _obj);
	static void SetBerserker_Demon_Frame(CObj* _obj);
	
	static void SetSoldierFrame(CObj* _obj);
	static void SetArcherFrame(CObj* _obj);

	static void SetElderEntFrame(CObj* _obj);
	
};

