#include "stdafx.h"
#include "CollisionMgr.h"
#include "LineMgr.h"
#include "Player.h"

CCollisionMgr::CCollisionMgr()
{
}


CCollisionMgr::~CCollisionMgr()
{
}


void CCollisionMgr::Collision_Rect(list<CObj*> _Dst, list<CObj*> _Src)
{
	RECT	rcRect{};

	for (auto& Dst : _Dst)
	{
		for (auto& Src : _Src)
		{
			if (IntersectRect(&rcRect, &(Dst->Get_Rect()), &(Src->Get_Rect())))
			{
				Dst->Set_Dead();
				Src->Set_Dead();
			}
		}
	}
}

void CCollisionMgr::Collision_RectEx(list<CObj*> _Dst, list<CObj*> _Src)
{
	float	fX(0.f), fY(0.f);

	for (auto& Dst : _Dst)
	{
		for (auto& Src : _Src)
		{
			if (Check_Rect(Dst, Src, &fX, &fY))
			{
				if (fX > fY) // 상하 충돌
				{
					// 상 충돌
					if (Dst->Get_Info().fY < Src->Get_Info().fY)
					{
						Dst->Set_Ground(true);
						
						if (Dst->Get_CurState() == FALLING || Dst->Get_CurState() == FALLING_START)
							Dst->Set_CurState(IDLE);


						Dst->Plus_PosY(-fY);
					}
					// 하 충돌
					else
					{
						Dst->Plus_PosY(fY);
					}
				}

				else 		// 좌우 충돌
				{
					// 좌 충돌
					if (Dst->Get_Info().fX < Src->Get_Info().fX)
					{
						Dst->Plus_PosX(-fX);
						if (Dst->Get_CurState() == DASH)
						{
							Dst->Set_PosX(Dst->Get_Info().fX + Dst->Get_Info().fCX/2);
							static_cast<CPlayer*>(Dst)->Set_DashRange(0.f);
						}
					}
					// 우 충돌
					else
					{
						Dst->Plus_PosX(fX);
						if (Dst->Get_CurState() == DASH)
						{
							Dst->Set_PosX(Dst->Get_Info().fX - Dst->Get_Info().fCX/2);
							static_cast<CPlayer*>(Dst)->Set_DashRange(0.f);
						}

					}
				}
			}
		}
	}

}

bool CCollisionMgr::Collision_ObjList_Info(list<CObj*> _Dst, INFO* _info)
{
	float	fX(0.f), fY(0.f);

	for (auto& Dst : _Dst)
	{
		if (Check_Info(Dst, *_info, &fX, &fY))
		{
			if (fX > fY) // 상하 충돌
			{
				// 상 충돌
				if (Dst->Get_Info().fY < (*_info).fY)
				{
					// Dst->Plus_PosY(-fY);
					return true;
				}
				// 하 충돌
				else
				{
					// Dst->Plus_PosY(fY);
					return true;
				}
			}

			else 		// 좌우 충돌
			{
				// 좌 충돌
				if (Dst->Get_Info().fX < (*_info).fX)
				{
					// Dst->Plus_PosX(-fX);
					_info->fY += 10;
					return true;
				}
				// 우 충돌
				else
				{
					//Dst->Plus_PosX(fX);
					_info->fY += 10;
					return true;
				}
			}
		}
	}
	return false;
}

bool CCollisionMgr::Check_Rect(CObj* pDst, CObj* pSrc, float* pX, float* pY)
{

	float	fWidth = abs(pDst->Get_Info().fX - pSrc->Get_Info().fX);
	float	fHeight = abs(pDst->Get_Info().fY - pSrc->Get_Info().fY);

	float	fRadiusX = (pDst->Get_Info().fCX + pSrc->Get_Info().fCX) * 0.5f;
	float	fRadiusY = (pDst->Get_Info().fCY + pSrc->Get_Info().fCY) * 0.5f;

	if ((fRadiusX >= fWidth) && (fRadiusY >= fHeight))
	{
		*pX = fRadiusX - fWidth;
		*pY = fRadiusY - fHeight;

		return true;
	}

	return false;
}



bool CCollisionMgr::Collision_Info(CObj* _obj, INFO* _info)
{
	float	fX(0.f), fY(0.f);

	if (Check_Info(_obj, *_info, &fX, &fY))
	{
		if (fX > fY) // 상하 충돌
		{
			// 상 충돌
			if (_obj->Get_Info().fY < _info->fY)
			{
				_obj->Set_Ground(true);
				static_cast<CPlayer*>(_obj)->Set_InfoColl(true);
				if (_obj->Get_CurState() == FALLING || _obj->Get_CurState() == FALLING_START)
					_obj->Set_CurState(IDLE);

				_obj->Plus_PosY(-fY);
				return true;
			}
			// 하 충돌
			else
			{
				_obj->Plus_PosY(fY);
				return true;

			}
		}

		else 		// 좌우 충돌
		{
			// 좌 충돌
			if (_obj->Get_Info().fX < _info->fX)
			{
				_obj->Plus_PosX(-fX);

				// 플레이어 뚝배기 공격


				return true;

			}
			// 우 충돌
			else
			{
				_obj->Plus_PosX(fX);
				return true;

			}
		}
	}
	else
	{
		static_cast<CPlayer*>(_obj)->Set_InfoColl(false);
	}


	return false;
}


bool CCollisionMgr::Check_Info(CObj* pDst, INFO _info, float* pX, float* pY)
{
	float	fWidth = abs(pDst->Get_Info().fX - _info.fX);
	float	fHeight = abs(pDst->Get_Info().fY - _info.fY);

	float	fRadiusX = (pDst->Get_Info().fCX + _info.fCX) * 0.5f;
	float	fRadiusY = (pDst->Get_Info().fCY + _info.fCY) * 0.5f;

	if ((fRadiusX >= fWidth) && (fRadiusY >= fHeight))
	{
		*pX = fRadiusX - fWidth;
		*pY = fRadiusY - fHeight;

		return true;
	}

	return false;
}

void CCollisionMgr::Collision_Sphere(list<CObj*> _Dst, list<CObj*> _Src)
{
	for (auto& Dst : _Dst)
	{
		for (auto& Src : _Src)
		{
			if (Check_Sphere(Dst, Src))
			{
				Dst->Set_Dead();
				Src->Set_Dead();
			}
		}
	}
}

bool CCollisionMgr::Check_Sphere(CObj* pDst, CObj* pSrc)
{
	float	fWidth = abs(pDst->Get_Info().fX - pSrc->Get_Info().fX);
	float	fHeight = abs(pDst->Get_Info().fY - pSrc->Get_Info().fY);

	float	fDiagonal = sqrt(fWidth * fWidth + fHeight * fHeight);

	float	fRadius = (pDst->Get_Info().fCX + pSrc->Get_Info().fCX) * 0.5f;

	return fRadius >= fDiagonal;
}

