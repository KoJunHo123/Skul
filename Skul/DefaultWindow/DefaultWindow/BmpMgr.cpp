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

// ���� ���, ������ Ű �޾Ƽ� �ʿ� �Ҵ�.
void CBmpMgr::Insert_Bmp(const TCHAR * pFilePath, const TCHAR * pImgKey)
{
	// �־��� Ű ���� ��ġ�ϴ� ���� ���ͷ����� ��ȯ
	auto	iter = find_if(m_mapBit.begin(), m_mapBit.end(), CStringCmp(pImgKey));

	// ��ġ�ϴ� Ű�� ������ �ŵ� �־��ֱ�. -> ����ó�� �Ϸ��� ���� end�� �ȳ־���.
	if (iter == m_mapBit.end())
	{
		// �����Ҵ� �ؼ�
		CMyBmp*		pMyBmp = new CMyBmp;
		// �̹��� �ް�
		pMyBmp->Load_Bmp(pFilePath);
		// �ʿ� ����
		m_mapBit.insert({ pImgKey, pMyBmp });
	}
}

// �׸��� Ű�� ã�Ƽ� �� �׸��� DC ��ȯ
HDC CBmpMgr::Find_Image(const TCHAR * pImgKey)
{
	auto	iter = find_if(m_mapBit.begin(), m_mapBit.end(), CStringCmp(pImgKey));

	if (iter == m_mapBit.end())
		return nullptr;
	
	return iter->second->Get_MemDC();
}

void CBmpMgr::Delete_Image(const TCHAR* pImgKey)
{
	// �־��� Ű ���� ��ġ�ϴ� ���� ���ͷ����� ��ȯ
	auto	iter = find_if(m_mapBit.begin(), m_mapBit.end(), CStringCmp(pImgKey));
	
	DeleteMap()(*iter);
	m_mapBit.erase(iter);
}

// �Ҵ��� �� �ϴ� ����.
void CBmpMgr::Release()
{
	for_each(m_mapBit.begin(), m_mapBit.end(), DeleteMap());
	m_mapBit.clear();
}
