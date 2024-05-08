#pragma once

#include "Player.h"

class CLittleBone : public CPlayer
{
public:
	CLittleBone();
	virtual ~CLittleBone();

public:
	virtual void Initialize();
	virtual int  Update();
	virtual	void Late_Update();
	virtual void Render(HDC hDC);
	virtual void Release();
	virtual void SkillKey_Input();
	virtual void PlayerMoveFrame();

private:
};

