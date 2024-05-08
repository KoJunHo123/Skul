#include "stdafx.h"
#include "MeleeAttack.h"
#include "CameraMgr.h"

CMeleeAttack::CMeleeAttack()
{
}

CMeleeAttack::CMeleeAttack(INFO* _info, ATTACKTYPE _type, DIRECTION _dir, int _damage, bool _playerAttack, bool* _attacking)
    : CAttack(_info, _type, _dir, _damage, _playerAttack, _attacking)
{
}

CMeleeAttack::~CMeleeAttack()
{
}

void CMeleeAttack::Initialize()
{
    switch (m_eAttackType)
    {
    case PLAYER_ATTACK_1:
    case PLAYER_ATTACK_2:
        m_tAttackInfo = *m_pInfo;

        if (m_eDir == RIGHT)
            m_tAttackInfo.fX += 20.f;
        else
            m_tAttackInfo.fX -= 20.f;
        break;

    case BERSERKER_ATTACK_1:
        m_tAttackInfo = *m_pInfo;

        if (m_eDir == RIGHT)
            m_tAttackInfo.fX += 40.f;
        else
            m_tAttackInfo.fX -= 40.f;

        m_tAttackInfo.fCX = 80.f;
        m_tAttackInfo.fCY = 100.f;
        break;

    case BERSERKER_ATTACK_2:
        m_tAttackInfo = *m_pInfo;

        if (m_eDir == RIGHT)
            m_tAttackInfo.fX += 50.f;
        else
            m_tAttackInfo.fX -= 50.f;

        m_tAttackInfo.fCX = 70.f;
        m_tAttackInfo.fCY = 100.f;
        break;

    case BERSERKER_SKILL_1:
        m_tAttackInfo = *m_pInfo;
        m_tAttackInfo.fCX = m_pInfo->fCX * 5.f;
        m_tAttackInfo.fCY = m_pInfo->fCY * 5.f;
        break;

    case BERSERKER_SKILL_2:
        m_tAttackInfo = *m_pInfo;

        if (m_eDir == RIGHT)
            m_tAttackInfo.fX += 40.f;
        else
            m_tAttackInfo.fX -= 40.f;

        m_tAttackInfo.fY -= 10.f;
        m_tAttackInfo.fCX = 80.f;
        m_tAttackInfo.fCY = 80.f;
        break;

    case BERSERKER_2_SKILL_2:
        m_tAttackInfo = *m_pInfo;

        if (m_eDir == RIGHT)
            m_tAttackInfo.fX += 60.f;
        else
            m_tAttackInfo.fX -= 60.f;

        m_tAttackInfo.fY -= 30.f;
        m_tAttackInfo.fCX = 200.f;
        m_tAttackInfo.fCY = 80.f;
        break;

    case SOLDIER_ATTACK:
        m_tAttackInfo = *m_pInfo;

        if (m_eDir == RIGHT)
            m_tAttackInfo.fX += 15.f;
        else
            m_tAttackInfo.fX -= 15.f;
        break;

    case ELDERENT_SLEM:
        m_tAttackInfo = *m_pInfo;
        break;

    case ELDERENT_SWEEP:
        m_tAttackInfo = *m_pInfo;
        break;

    case DEMONIZATION_BOOM:
        m_tAttackInfo = *m_pInfo;
        m_tAttackInfo.fCX = m_pInfo->fCX * 10.f;
        m_tAttackInfo.fCY = m_pInfo->fCY * 10.f;
        break;

    case DEMON_SKILL_2:
        m_tAttackInfo = *m_pInfo;

        if (m_eDir == RIGHT)
            m_tAttackInfo.fX += 70.f;
        else
            m_tAttackInfo.fX -= 70.f;

        m_tAttackInfo.fY -= 150.f;
        m_tAttackInfo.fCX = 120.f;
        m_tAttackInfo.fCY = 400.f;
        break;


    }
}

int CMeleeAttack::Update()
{
    switch (m_eAttackType)
    {
    case PLAYER_ATTACK_1:
    case PLAYER_ATTACK_2:
        m_tAttackInfo = *m_pInfo;

        if (m_eDir == RIGHT)
            m_tAttackInfo.fX += 20.f;
        else
            m_tAttackInfo.fX -= 20.f;

        m_tAttackInfo.fCX = 50.f;
        m_tAttackInfo.fCY = 50.f;

        break;

    case BERSERKER_ATTACK_1:
        m_tAttackInfo = *m_pInfo;

        if (m_eDir == RIGHT)
            m_tAttackInfo.fX += 40.f;
        else
            m_tAttackInfo.fX -= 40.f;

        m_tAttackInfo.fCX = 80.f;
        m_tAttackInfo.fCY = 100.f;
        break;

    case BERSERKER_ATTACK_2:
        m_tAttackInfo = *m_pInfo;

        if (m_eDir == RIGHT)
            m_tAttackInfo.fX += 50.f;
        else
            m_tAttackInfo.fX -= 50.f;

        m_tAttackInfo.fCX = 70.f;
        m_tAttackInfo.fCY = 100.f;
        break;

    case BERSERKER_SKILL_1:
        m_tAttackInfo = *m_pInfo;
        m_tAttackInfo.fCX = m_pInfo->fCX * 5.f;
        m_tAttackInfo.fCY = m_pInfo->fCY * 5.f;
        break;

    case BERSERKER_SKILL_2:
        m_tAttackInfo = *m_pInfo;

        if (m_eDir == RIGHT)
            m_tAttackInfo.fX += 60.f;
        else
            m_tAttackInfo.fX -= 60.f;

        m_tAttackInfo.fY -= 10.f;
        m_tAttackInfo.fCX = 80.f;
        m_tAttackInfo.fCY = 80.f;
        break;

    case BERSERKER_2_SKILL_2:
        m_tAttackInfo = *m_pInfo;

        if (m_eDir == RIGHT)
            m_tAttackInfo.fX += 60.f;
        else
            m_tAttackInfo.fX -= 60.f;

        m_tAttackInfo.fY -= 30.f;
        m_tAttackInfo.fCX = 200.f;
        m_tAttackInfo.fCY = 80.f;
        break;

    case SOLDIER_ATTACK:
        m_tAttackInfo = *m_pInfo;

        if (m_eDir == RIGHT)
            m_tAttackInfo.fX += 15.f;
        else
            m_tAttackInfo.fX -= 15.f;

        m_tAttackInfo.fCX = 20.f;
        m_tAttackInfo.fCY = 20.f;


        break;

    case ELDERENT_SLEM:
        m_tAttackInfo = *m_pInfo;
        break;

    case ELDERENT_SWEEP:
        m_tAttackInfo = *m_pInfo;
        break;

    case DEMONIZATION_BOOM:
        m_tAttackInfo = *m_pInfo;
        m_tAttackInfo.fCX = m_pInfo->fCX * 10.f;
        m_tAttackInfo.fCY = m_pInfo->fCY * 10.f;
        break;

    case DEMON_SKILL_2:
        m_tAttackInfo = *m_pInfo;

        if (m_eDir == RIGHT)
            m_tAttackInfo.fX += 70.f;
        else
            m_tAttackInfo.fX -= 70.f;

        m_tAttackInfo.fY -= 150.f;
        m_tAttackInfo.fCX = 120.f;
        m_tAttackInfo.fCY = 400.f;
        break;


    }

    __super::Update_Rect();
    return 0;
}

void CMeleeAttack::Late_Update()
{
}

void CMeleeAttack::Render(HDC hDC)
{
    /*Vec2 RenderPos = CCameraMgr::Get_Instance()->Get_RenderPos(m_tAttackInfo.fX, m_tAttackInfo.fY);

    Rectangle(hDC, RenderPos.fX - m_tAttackInfo.fCX * 0.5f, RenderPos.fY - m_tAttackInfo.fCY * 0.5f,
        RenderPos.fX + m_tAttackInfo.fCX * 0.5f, RenderPos.fY + m_tAttackInfo.fCY * 0.5f);*/
}

void CMeleeAttack::Release()
{
}
