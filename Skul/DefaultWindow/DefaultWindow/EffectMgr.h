#pragma once

#include "Effect.h"

class CEffectMgr
{
private:
	static CEffectMgr* m_pInstance;
	list<CEffect*> m_EffectList;

private:
	CEffectMgr();
	~CEffectMgr();

public:
	static CEffectMgr* Get_Instance()
	{
		if (!m_pInstance)
			m_pInstance = new CEffectMgr;

		return m_pInstance;
	}

	static void Destroy()
	{
		if (m_pInstance)
		{
			delete m_pInstance;
			m_pInstance = nullptr;
		}
	}


public:
	void Add_Effect(EFFECTTYPE _effect, INFO _info);
	void Add_Unique_Effect(EFFECTTYPE _effect, INFO _info);
	void Add_Follow_Effect(EFFECTTYPE _effect, INFO* _info);

	void Delete_Effect(EFFECTTYPE _effect);

	void Update();
	void Late_Update();
	void Render(HDC hDC);
	void Release();

	void Add_Monster(MONSTERID _ID, INFO _info);
};

