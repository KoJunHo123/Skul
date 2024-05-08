#include "stdafx.h"
#include "Title.h"
#include "SceneMgr.h"


CTitle::CTitle()
{
}

CTitle::~CTitle()
{
	Release();
}

void CTitle::Initialize()
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Title/Title.bmp", L"Title");
}

int CTitle::Update()
{
	return 0;
}

void CTitle::Late_Update()
{
	if (CKeyMgr::Get_Instance()->Key_Press_Anything())
	{
		CSceneMgr::Get_Instance()->Scene_Change(SC_CASTLE);
	}
}

void CTitle::Render(HDC hDC)
{
	HDC hTitle = CBmpMgr::Get_Instance()->Find_Image(L"Title");

	BitBlt(hDC, 0, 0, WINCX, WINCY, hTitle, 10, 10, SRCCOPY);


}

void CTitle::Release()
{
	CBmpMgr::Get_Instance()->Delete_Image(L"Title");
}
