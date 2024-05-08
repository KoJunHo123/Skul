#pragma once
class CEffect
{
private:
	const TCHAR* m_pFrameKey;
	const TCHAR* m_pFilePath;

	INFO m_tInfo;
	INFO* m_pInfo;

	FRAME m_tFrame;

	bool m_bEffectOver;

	// 몬스터 소환용
	MONSTERID m_eID;

public:
	CEffect();
	CEffect(const TCHAR* _FrameKey, const TCHAR* _pFilePath, FRAME _frame, INFO _info );
	CEffect(const TCHAR* _FrameKey, const TCHAR* _pFilePath, FRAME _frame, INFO* _info);


	~CEffect();

public:
	const TCHAR* Get_FrameKey() { return m_pFrameKey; }
	bool Get_EffectOver() { return m_bEffectOver; }
	INFO Get_Info() { return m_tInfo; }

	void Set_MonsterID(MONSTERID _ID) { m_eID = _ID; }

public:
	void Initialize();
	void Update();
	void Late_Update();
	void Render(HDC hDC);
	void Release();

private:
	void Add_Monster();
};

