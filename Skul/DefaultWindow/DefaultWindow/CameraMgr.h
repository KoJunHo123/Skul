#pragma once

class CCameraMgr
{
private:
	static CCameraMgr* m_pInstance;

	CCameraMgr();
	~CCameraMgr();

public:
	static CCameraMgr* Get_Instance()
	{
		if (!m_pInstance)
		{
			m_pInstance = new CCameraMgr;
		}
		return m_pInstance;
	}

	static void Destroy()
	{
		if(m_pInstance)
		{
			delete m_pInstance;
			m_pInstance = nullptr;
		}
	}

public:
	void CalculateDist(float _x, float _y);
	Vec2 Get_RenderPos(float _fX, float _fY);

	void Set_MapSize(float _x, float _y) 
	{ 
		m_mapSize.fX = _x; 
		m_mapSize.fY = _y; 
	}
	Vec2 Get_MapSize() { return m_mapSize; }
	Vec2 Get_Distance() { return m_distance; }
	Vec2 Get_BackDistance();

	void ShakeCamera();
private:
	void StopCamera();

private:
	// 중점으로부터의 이동거리.
	Vec2	m_distance;
	Vec2	m_mapSize;

	bool	m_bCameraShake;
	int		m_iCameraShakeDelay;
};