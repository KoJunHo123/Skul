#pragma once

#include "Obj.h"
#include "ElderEnt.h"

template<typename T>
class CAbstractFactory
{
public:
	static CObj*		Create()
	{
		CObj*		pObj = new T;
		pObj->Initialize();

		return pObj;
	}

	static CObj*		Create(float _fX, float _fY)
	{
		CObj*		pObj = new T;
		pObj->Set_Pos(_fX, _fY);
		pObj->Initialize();

		return pObj;
	}

	static CObj*		Create(float _fX, float _fY, float _fAngle)
	{
		CObj*		pObj = new T;
		pObj->Initialize();
		
		pObj->Set_Pos(_fX, _fY);
		pObj->Set_Angle(_fAngle);

		return pObj;
	}

	static CObj* CreateElder(Vec2* _body)
	{
		CObj* pObj = new T;
		static_cast<CElderEnt*>(pObj)->Set_BodyPos(_body);
		pObj->Initialize();

		return pObj;
	}


public:
	CAbstractFactory(){}
	~CAbstractFactory(){}
};
