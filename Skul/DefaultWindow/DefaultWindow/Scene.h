#pragma once

#include "Define.h"
#include "ObjMgr.h"
#include "Ground.h"
#include "AbstractFactory.h"
#include "BmpMgr.h"
#include "CameraMgr.h"
#include "CollisionMgr.h"
#include "LineMgr.h"
#include "BattleMgr.h"
#include "KeyMgr.h"
#include "UIMgr.h"
#include "SoundMgr.h"

#include "LittleBone.h"
#include "Berserker.h"
#include "Door.h"
#include "Reward.h"


class CScene
{
public:
	CScene();
	virtual ~CScene();

public:
	virtual		void		Initialize()	PURE;
	virtual		int			Update()		PURE;
	virtual		void		Late_Update()	PURE;
	virtual		void		Render(HDC hDC)	PURE;
	virtual		void		Release()		PURE;

	

	void Monster_Died() { --m_iLeftMonster; }

protected:
	Vec2 m_mapSize;
	list<CObj*>* m_pRenderList;
	int m_iLeftMonster;
};

