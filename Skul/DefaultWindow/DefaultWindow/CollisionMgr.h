#pragma once

#include "Obj.h"

class CCollisionMgr
{
public:
	CCollisionMgr();
	~CCollisionMgr();

public:
public:
	static void	Collision_Rect(list<CObj*> _Dst, list<CObj*> _Src);

	static void	Collision_RectEx(list<CObj*> _Dst, list<CObj*> _Src);
	static bool Check_Rect(CObj* pDst, CObj* pSrc, float* pX, float* pY);

	static bool Collision_ObjList_Info(list<CObj*> _Dst, INFO* _info);
	static bool	Collision_Info(CObj* _obj, INFO* _info);
	static bool Check_Info(CObj* pDst, INFO _info, float* pX, float* pY);

	static void	Collision_Sphere(list<CObj*> _Dst, list<CObj*> _Src);
	static bool Check_Sphere(CObj* pDst, CObj* pSrc);

};

