#include "stdafx.h"
#include "BmpMgr.h"

CBmpMgr*		CBmpMgr::m_pInstance = nullptr;

CBmpMgr::CBmpMgr()
{
}


CBmpMgr::~CBmpMgr()
{
	Release();
}

// 파일 경로, 저장할 키 받아서 맵에 할당.
void CBmpMgr::Insert_Bmp(const TCHAR * pFilePath, const TCHAR * pImgKey)
{
	// 넣어준 키 값이 일치하는 맵의 이터레이터 반환
	auto	iter = find_if(m_mapBit.begin(), m_mapBit.end(), CStringCmp(pImgKey));

	// 일치하는 키가 없으면 거따 넣어주기. -> 예외처리 하려고 냅다 end에 안넣어줌.
	if (iter == m_mapBit.end())
	{
		// 동적할당 해서
		CMyBmp*		pMyBmp = new CMyBmp;
		// 이미지 받고
		pMyBmp->Load_Bmp(pFilePath);
		// 맵에 저장
		m_mapBit.insert({ pImgKey, pMyBmp });
	}
}

// 그림을 키로 찾아서 그 그림의 DC 반환
HDC CBmpMgr::Find_Image(const TCHAR * pImgKey)
{
	auto	iter = find_if(m_mapBit.begin(), m_mapBit.end(), CStringCmp(pImgKey));

	if (iter == m_mapBit.end())
		return nullptr;
	
	return iter->second->Get_MemDC();
}

void CBmpMgr::Delete_Image(const TCHAR* pImgKey)
{
	// 넣어준 키 값이 일치하는 맵의 이터레이터 반환
	auto	iter = find_if(m_mapBit.begin(), m_mapBit.end(), CStringCmp(pImgKey));
	
	DeleteMap()(*iter);
	m_mapBit.erase(iter);
}

// 할당한 거 싹다 해제.
void CBmpMgr::Release()
{
	for_each(m_mapBit.begin(), m_mapBit.end(), DeleteMap());
	m_mapBit.clear();
}
