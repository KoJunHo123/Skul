#include "stdafx.h"
#include "ElderEnt.h"
#include "BmpMgr.h"
#include "AnimationMgr.h"
#include "BattleMgr.h"
#include "CollisionMgr.h"
#include "EffectMgr.h"
#include "Player.h"
#include "LineMgr.h"

CElderEnt::CElderEnt()
    // 몸뚱아리 초기화
    : m_body(nullptr)
    , m_leftHand{}
    , m_rightHand{}
    , m_Head{}
    , m_Mouth{}
    , m_pMoveHand(nullptr)
    , m_GrapeShootPos{}
    // 페이즈
    , m_iPhase(0)
    // 패턴
    , m_iPattern(0)
    // 공격 횟수 : 기본 3회
    , m_iAttackCount(3)
    , m_iGrapeShoot(3)
    // 몸뚱아리 꿈틀거리는 거 속도 제어
    , m_fMouthMove(2.f)
    , m_fBodyShakeSpeed(0.f)
    // 몸뚱아리 꿈틀거리는 거 방향
    , m_bHeadUp(true)
    , m_bMouthOpen(true)
    , m_shake(false)
    // 공격 상태(전, 중, 후)
    , m_bAttackReady(false)
    , m_bAttack(false)
    , m_bAttackOver(false)

    // 공격 상태 별 속도
    , m_fAttackReadySpeed(4.f)
    , m_fAttackSpeed(10.f)

    , m_fTargetAngle(0.f)

    // 움직임 속도 프레임 제한
    , m_iMoveTime(GetTickCount())
    // 공격 전에 몸 부르르 떨리는 간격
    , m_iAttackDelay(GetTickCount())
    // 손으로 땅 찍고 잠깐 부르르 떠는 간격
    , m_iHandSlamDelay(GetTickCount())
    , m_iCameraShakeDelay(GetTickCount())
    , m_iPatternDelay(GetTickCount())
{
    m_eMonsterID = ELDERENT;
    m_iHp = 1000;

    m_fSpeed = 2.f;
}

CElderEnt::~CElderEnt()
{
}

void CElderEnt::Initialize()
{
    // 초기 위치
    *m_body = { 450, 280 };
    m_Head = { (*m_body).fX, (*m_body).fY - 50, 100, 250 };
    m_Mouth = { m_Head.fX, m_Head.fY + 75, 100, 50 };
    m_leftHand = { (*m_body).fX - 180, (*m_body).fY + 50, 100, 100 };
    m_rightHand = { (*m_body).fX + 200, (*m_body).fY + 50, 100, 100 };

    CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Boss/ElderEnt/Head.bmp", L"ElderEnt_Head");
    CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Boss/ElderEnt/Mouth.bmp", L"ElderEnt_Mouth");
    CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Boss/ElderEnt/Left_Hand.bmp", L"ElderEnt_Left_Hand");
    CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Boss/ElderEnt/Right_Hand.bmp", L"ElderEnt_Right_Hand");

    CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Boss/Tree/LeftSideTree.bmp", L"LeftSideTree");
    CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Boss/Tree/RightSideTree.bmp", L"RightSideTree");

    CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Boss/Boss_Hp_Frame.bmp", L"Boss_Hp_Frame");
    CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Boss/Boss_Hp_Bar.bmp",       L"Boss_Hp_Bar"  );

    m_tFrame = { 0, 5, 1, 250, GetTickCount() };
    
    m_eCurState = IDLE;
    m_ePreState = IDLE;

    m_bBoss = true;

    m_GrapeShootPos[0] = { 250, 200, 0, 0 };
    m_GrapeShootPos[1] = { 300, 200, 0, 0 };
    m_GrapeShootPos[2] = { 350, 200, 0, 0 };
    m_GrapeShootPos[3] = { 400, 200, 0, 0 };
    m_GrapeShootPos[4] = { 550, 200, 0, 0 };
    m_GrapeShootPos[5] = { 600, 200, 0, 0 };
    m_GrapeShootPos[6] = { 650, 200, 0, 0 };
    m_GrapeShootPos[7] = { 700, 200, 0, 0 };
}

int CElderEnt::Update()
{
    if(m_bDead)
    {
        CSoundMgr::Get_Instance()->StopAll();
        CSoundMgr::Get_Instance()->PlayBGM(L"DemonCastle.wav", 1.f);
        // CLineMgr::Destroy();
        return OBJ_DEAD;
    }

    m_tInfo = m_Head;

    if(m_eCurState == IDLE && m_iPatternDelay + 3000 < GetTickCount())
    {
        int state = GetRandomNum(0, 2);
        switch(state)
        {
        case 0:
            m_eCurState = ATTACK;
            break;

        case 1:
            m_eCurState = ATTACK_2;
            break;

        case 2: 
            m_eCurState = SKILL_1;
            break;
        }

    }
#pragma region 테스트용
    if (GetAsyncKeyState('Q'))
        m_eCurState = IDLE;

    else if (GetAsyncKeyState('W'))
        m_eCurState = ATTACK;

    else if (GetAsyncKeyState('E'))
        m_eCurState = ATTACK_2;

    else if (GetAsyncKeyState('R'))
        m_eCurState = SKILL_1;

    else if (GetAsyncKeyState('F'))
        m_eCurState = REBONE;
#pragma endregion 

    // 기본 상태
    Boss_Idle();
    // 패턴별 시작 모션
    Boss_HandSlam();
    Boss_HandSweep();
    Boss_Grape();

    // 몸 부르르
    Body_Shake();

    // 공격 모션
    AttackMotion();

    // 공격 후 모션
    After_Attack();

    // 공격 후 복귀 모션
    Return_IdlePos();

    __super::Update_Rect();
    Ent_Move_Frame();
    return OBJ_NOEVENT;
}

void CElderEnt::Late_Update()
{
    m_fHpRate = (float)m_iHp * 0.001 * 272.f;


    if (m_iHp <= 0)
    {
        if(m_iPhase == 0)
        {
            m_iHp += 1000;
            m_tFrame.iFrameStart = 0;
            m_iGrapeShoot = 10;
        }
        else if (m_iPhase >= 1)
        {
            m_bDead = true;
        }
        ++m_iPhase;
    }
    CAnimationMgr::SetElderEntFrame(this);
}

void CElderEnt::Render(HDC hDC)
{
    Vec2 RenderPosHead = CCameraMgr::Get_Instance()->Get_RenderPos(m_Head.fX, m_Head.fY);
    Vec2 RenderPosMouse = CCameraMgr::Get_Instance()->Get_RenderPos(m_Mouth.fX, m_Mouth.fY);
    Vec2 RenderPosRight = CCameraMgr::Get_Instance()->Get_RenderPos(m_rightHand.fX, m_rightHand.fY);
    Vec2 RenderPosLeft = CCameraMgr::Get_Instance()->Get_RenderPos(m_leftHand.fX, m_leftHand.fY);

#pragma region 판정 확인용
    //Rectangle(hDC, RenderPosRight.fX - m_rightHand.fCX / 2, RenderPosRight.fY - m_rightHand.fCY / 2, RenderPosRight.fX + m_rightHand.fCX / 2, RenderPosRight.fY + m_rightHand.fCY / 2);
    //Rectangle(hDC, RenderPosLeft.fX - m_leftHand.fCX / 2, RenderPosLeft.fY - m_leftHand.fCY / 2, RenderPosLeft.fX + m_leftHand.fCX / 2, RenderPosLeft.fY + m_leftHand.fCY / 2);
    //Rectangle(hDC, RenderPosHead.fX - m_Head.fCX / 2, RenderPosHead.fY - m_Head.fCY / 2, RenderPosHead.fX + m_Head.fCX / 2, RenderPosHead.fY + m_Head.fCY / 2);
    //Rectangle(hDC, RenderPosMouse.fX - m_Mouth.fCX / 2, RenderPosMouse.fY - m_Mouth.fCY / 2, RenderPosMouse.fX + m_Mouth.fCX / 2, RenderPosMouse.fY + m_Mouth.fCY / 2);
#pragma endregion

#pragma region 체력 확인용
    TCHAR szTemp[64];
    wsprintf(szTemp, L"HP : %d", m_iHp);
    TextOut(hDC, 0, 0, szTemp, lstrlen(szTemp));
#pragma endregion

    HDC headDC = CBmpMgr::Get_Instance()->Find_Image(L"ElderEnt_Head");
    HDC mouthDC = CBmpMgr::Get_Instance()->Find_Image(L"ElderEnt_Mouth");
    HDC left_handDC = CBmpMgr::Get_Instance()->Find_Image(L"ElderEnt_Left_Hand");
    HDC right_handDC = CBmpMgr::Get_Instance()->Find_Image(L"ElderEnt_Right_Hand");
    
    // 대가리
    GdiTransparentBlt(hDC,
        (int)((RenderPosHead.fX - 150 - 10)),
        (int)(RenderPosHead.fY - 150),
        300,
        300,
        headDC,
        m_iPhase * 300,
        0,
        300,
        300,
        RGB(255, 0, 255));

    // 아가리
    GdiTransparentBlt(hDC,
        (int)((RenderPosMouse.fX - 100 + 5)),
        (int)(RenderPosMouse.fY - 100),
        200,
        200,
        mouthDC,
        m_iPhase * 200,
        0,
        200,
        200,
        RGB(255, 0, 255));

    // 왼손
    GdiTransparentBlt(hDC,
        (int)(RenderPosLeft.fX - 100 - 10),
        (int)(RenderPosLeft.fY - 100 - 30),
        200,
        200,
        left_handDC,
        m_tFrame.iFrameStart * 200,
        m_tFrame.iMotion * 200 + (800 * m_iPhase),
        200,
        200,
        RGB(255, 0, 255));

    // 오른손
    GdiTransparentBlt(hDC,
        (int)(RenderPosRight.fX - 100 + 10),
        (int)(RenderPosRight.fY - 100 - 20),
        200,
        200,
        right_handDC,
        m_tFrame.iFrameStart * 200,
        m_tFrame.iMotion * 200 + (800 * m_iPhase),
        200,
        200,
        RGB(255, 0, 255));

    HDC hHpFrameDC = CBmpMgr::Get_Instance()->Find_Image(L"Boss_Hp_Frame");
    HDC hHpBarDC = CBmpMgr::Get_Instance()->Find_Image(L"Boss_Hp_Bar");
        
        
    GdiTransparentBlt(hDC, 250, 0, 306, 80, hHpFrameDC, 0, 0, 306, 80, RGB(255, 0, 255));
    GdiTransparentBlt(hDC, 267, 36, (int)m_fHpRate, 9, hHpBarDC, 0, 0, 272, 9, RGB(0, 0, 0));
   
    // 손 땅에서 올라올 때만.
    if(m_leftHand.fY > 350 && m_eCurState == REBONE)
    {
        HDC hGroundDC = CBmpMgr::Get_Instance()->Find_Image(L"BossMapGround");
        Vec2 dist = CCameraMgr::Get_Instance()->Get_Distance();
        GdiTransparentBlt(hDC,
            -dist.fX, -dist.fY,
            900, 560,
            hGroundDC,
            0, 0,
            900, 560,
            RGB(0, 0, 0));
    }
}

void CElderEnt::Release()
{
}


void CElderEnt::Boss_Idle()
{
    if(m_eCurState == IDLE)
    {
        if (m_iMoveTime + 100 < GetTickCount())
        {
            Mouth_Move();
            if (m_bHeadUp)
            {
                m_leftHand.fY -= m_fSpeed * 0.5f;
                m_rightHand.fY -= m_fSpeed * 0.5f;
                m_body->fY -= m_fSpeed * 0.3f;
            }
            else
            {
                m_leftHand.fY += m_fSpeed * 0.5f;
                m_rightHand.fY += m_fSpeed * 0.5f;
                m_body->fY += m_fSpeed * 0.3f;
            }

            m_iMoveTime = GetTickCount();
        }
    }

}

void CElderEnt::Boss_HandSlam()
{
    if(m_eCurState == ATTACK && m_iMoveTime + 100 < GetTickCount())
    {
        Mouth_Move();

        // 팔 드는 중
        if (!m_bAttackReady && !m_bAttack && !m_bAttackOver)
        {
            m_Head.fY -= m_fAttackReadySpeed;
            m_Mouth.fY -= m_fAttackReadySpeed;
            m_body->fY -= m_fAttackReadySpeed * 0.5f;
            m_leftHand.fY -= m_fAttackReadySpeed * 7.f;
            m_rightHand.fY -= m_fAttackReadySpeed * 7.f;
            
            m_fAttackReadySpeed -= 0.4f;

            // 팔 멈춤
            if (m_fAttackReadySpeed <= 0.f)
            {
                m_fAttackReadySpeed = 4.f;
                m_bAttackReady = true;
                m_iAttackDelay = GetTickCount();
            }
        }
        m_iMoveTime = GetTickCount();
    }
}

void CElderEnt::Boss_HandSweep()
{
    if (m_eCurState == ATTACK_2 && m_iMoveTime + 100 < GetTickCount())
    {
        Mouth_Move();
        // 팔 벌림
        if (!m_bAttackReady && !m_bAttack && !m_bAttackOver)
        {
            m_leftHand.fX -= m_fAttackReadySpeed * 7.f;
            m_rightHand.fX += m_fAttackReadySpeed * 7.f;


            if (m_leftHand.fX < -200 && m_rightHand.fX > 1100)
            {
                m_bAttackReady = true;
                m_leftHand.fY = 350.f;
                m_rightHand.fY = 350.f;
                m_iAttackDelay = GetTickCount();

            }
        }
        m_iMoveTime = GetTickCount();
    }
}

void CElderEnt::Boss_Grape()
{

    if (m_eCurState == SKILL_1 && m_iMoveTime + 100 < GetTickCount())
    {
        Mouth_Move();    


        if (!m_bAttackReady && !m_bAttack && !m_bAttackOver)
        {
            CSoundMgr::Get_Instance()->PlaySound(L"ElderEnt_EnergyBomb_Ready.wav", SOUND_ELDERENT_GRAPE_READY, 1.f);

            if (m_iPhase == 0)
                CEffectMgr::Get_Instance()->Add_Unique_Effect(GRAPE_READY, m_Head);
            else
                CEffectMgr::Get_Instance()->Add_Unique_Effect(GRAPE_READY_2, m_Head);

            m_Head.fY -= m_fAttackReadySpeed * 1.2f;
            m_Mouth.fY -= m_fAttackReadySpeed * 1.2f;
            m_body->fY -= m_fAttackReadySpeed * 0.6f;

            m_fAttackReadySpeed -= 0.4f;

            if (m_fAttackReadySpeed <= 0.f)
            {
                m_fAttackReadySpeed = 4.f;
                m_bAttackReady = true;
                m_iAttackDelay = GetTickCount();
            }
        }
        m_iMoveTime = GetTickCount();
    }
}


// 몸 부르르 여기서 각도도 반환.
void CElderEnt::Body_Shake()
{
    int iDelay = 0;
    if (m_eCurState == ATTACK)
        iDelay = 500;
    else if (m_eCurState == ATTACK_2)
        iDelay = 1000;
    else if (m_eCurState == SKILL_1 && m_iPhase == 0)
        iDelay = 1000;
    else if (m_eCurState == SKILL_1 && m_iPhase == 1)
        iDelay = 100;

    if (m_iAttackDelay + iDelay > GetTickCount() && m_bAttackReady)
    {
        m_body->fX -= m_fBodyShakeSpeed * 0.5f;
        m_body->fY += m_fBodyShakeSpeed * 0.5f;

        m_Head.fX -= m_fBodyShakeSpeed;
        m_Head.fY += m_fBodyShakeSpeed;

        m_Mouth.fX -= m_fBodyShakeSpeed;
        m_Mouth.fY += m_fBodyShakeSpeed;

        if (m_fBodyShakeSpeed < -0.8f || m_fBodyShakeSpeed > 0.8f)
            m_shake = !m_shake;

        if (m_shake)
        {
            m_fBodyShakeSpeed += 0.8f;
        }
        else
        {
            m_fBodyShakeSpeed -= 0.8f;
        }
    }
    else if (m_iAttackDelay + iDelay < GetTickCount() && m_bAttackReady)
    {
        Check_PlayerPos();
        
        DIRECTION dir = DIR_END;
        if (m_eCurState == ATTACK)
        {
            CBattleMgr::Get_Instance()->Add_MeleeAttack(m_pMoveHand, ELDERENT_SLEM, dir, 20, false, &m_bAttack);
        }
        else if (m_eCurState == ATTACK_2)
        {
            int ranNum = GetRandomNum(0, 1);

            if (0 == ranNum)
                m_pMoveHand = &m_leftHand;
            else
                m_pMoveHand = &m_rightHand;

            if(m_pMoveHand == &m_leftHand)
                CBattleMgr::Get_Instance()->Add_MeleeAttack(m_pMoveHand, ELDERENT_SWEEP, LEFT, 20, false, &m_bAttack);
            else
                CBattleMgr::Get_Instance()->Add_MeleeAttack(m_pMoveHand, ELDERENT_SWEEP, RIGHT, 20, false, &m_bAttack);
        }
        else if (m_eCurState == SKILL_1)
        {
            if (0 == m_iPhase)
            {
                CBattleMgr::Get_Instance()->Add_RangedAttack(&m_Head, ELDERENT_GRAPE, LEFT, 20, false, &m_bAttack, m_pTarget);
                CBattleMgr::Get_Instance()->Get_LastAttack()->Initialize();
                CEffectMgr::Get_Instance()->Add_Unique_Effect(GRAPE_SHOOT, m_Head);
                for (int i = 0; i < 8; ++i)
                {
                    CBattleMgr::Get_Instance()->Add_RangedAttack(&m_Head, ELDERENT_BABYGRAPE, LEFT, 20, false, &m_bAttack, m_pTarget);
                    static_cast<CRangedAttack*>(CBattleMgr::Get_Instance()->Get_LastAttack())->Set_Angle(22.5f + 45.f * i);
                    CBattleMgr::Get_Instance()->Get_LastAttack()->Initialize();
                }
            }
            else
            {
                int i = GetRandomNum(0, 8);

                CBattleMgr::Get_Instance()->Add_RangedAttack(m_GrapeShootPos + i, ELDERENT_GRAPE, LEFT, 20, false, &m_bAttack, m_pTarget);
                CBattleMgr::Get_Instance()->Get_LastAttack()->Initialize();
                CEffectMgr::Get_Instance()->Add_Effect(GRAPE_SHOOT, m_GrapeShootPos[i]);
            }

            CSoundMgr::Get_Instance()->StopSound(SOUND_ELDERENT_GRAPE_FIRE);
            CSoundMgr::Get_Instance()->PlaySound(L"ElderEnt_EnergyBomb_Fire.wav", SOUND_ELDERENT_GRAPE_FIRE, 1.f);
        }

        m_bAttackReady = false;
        m_bAttack = true;
    }
}


void CElderEnt::AttackMotion()
{
    if (m_bAttack)
    {
        switch (m_eCurState)
        {
        case ATTACK:
            // 요기가 몸 먼저 나가는 거
            if (m_fAttackSpeed > 5)
            {
                m_Head.fY += m_fAttackSpeed * 0.5f;
                m_Mouth.fY += m_fAttackSpeed * 0.5f;

                m_body->fY += m_fAttackSpeed * 0.3f;
                m_fAttackSpeed -= 0.3f;
            }
            // 요기가 손떨구는 거
            else
            {
                // 다 이유가 있음
                if (m_iPhase == 0)
                    m_fAttackSpeed = -20.f;
                else
                    m_fAttackSpeed = -30.f;

                m_pMoveHand->fX -= cosf(m_fTargetAngle) * m_fAttackSpeed;
                m_pMoveHand->fY -= sinf(m_fTargetAngle) * m_fAttackSpeed;

                // 요기가 멈추는 거
                if (m_pMoveHand->fY > 360)
                {
                    CSoundMgr::Get_Instance()->StopSound(SOUND_ELDERENT_FISTSLAM);
                    CSoundMgr::Get_Instance()->PlaySound(L"ElderEnt_FistSlam.wav", SOUND_ELDERENT_FISTSLAM, 1.f);
                    // 여기서 카메라 흔들고 이펙트 터치고 다 하면 됨.
                    m_fAttackSpeed = 10.f;
                    m_bAttackOver = true;
                    m_bAttack = false;
                    if (m_iPhase == 0)
                        m_iHandSlamDelay = GetTickCount();
                    else
                        m_iHandSlamDelay = 0;

                    m_iCameraShakeDelay = GetTickCount();

                    --m_iAttackCount;
                }
            }
            break;

        case ATTACK_2:
            if (m_fAttackSpeed > 3)
            {
                if(m_pMoveHand == &m_rightHand)
                {
                    m_Head.fX += m_fAttackSpeed * 0.5f;
                    m_Mouth.fX += m_fAttackSpeed * 0.5f;
                    m_body->fX += m_fAttackSpeed * 0.3f;
                }
                else
                {
                    m_Head.fX -= m_fAttackSpeed * 0.5f;
                    m_Mouth.fX -= m_fAttackSpeed * 0.5f;
                    m_body->fX -= m_fAttackSpeed * 0.3f;
                }
                m_fAttackSpeed -= 0.3f;
            }
            else
            {
                CSoundMgr::Get_Instance()->PlaySound(L"ElderEnt_Sweeping.wav", SOUND_ELDERENT_SWEEPING, 1.f);

                if (m_iPhase == 0)
                    m_fAttackSpeed = -15.f;
                else
                    m_fAttackSpeed = -25.f;

                if (m_pMoveHand == &m_rightHand)
                {
                    m_Head.fX += m_fAttackSpeed * 0.1f;
                    m_Mouth.fX += m_fAttackSpeed * 0.1f;
                    m_body->fX += m_fAttackSpeed * 0.05f;

                    m_pMoveHand->fX += m_fAttackSpeed;
                }
                else
                {
                    m_Head.fX  -= m_fAttackSpeed * 0.1f;
                    m_Mouth.fX -= m_fAttackSpeed * 0.1f;
                    m_body->fX -= m_fAttackSpeed * 0.05f;

                    m_pMoveHand->fX -= m_fAttackSpeed;
                }

                if ((m_pMoveHand == &m_rightHand && m_pMoveHand->fX < -200.f) || (m_pMoveHand == &m_leftHand && m_pMoveHand->fX > 1100.f))
                {
                    m_fAttackSpeed = 10.f;
                    m_bAttackOver = true;
                    m_bAttack = false;
                    m_iHandSlamDelay = GetTickCount();
                    --m_iAttackCount;
                }

            }
            break;

        case SKILL_1:
            CEffectMgr::Get_Instance()->Add_Unique_Effect(GRAPE_ELECT, m_Head);
            m_Head.fY -=    m_fAttackSpeed * 0.5f;
            m_Mouth.fY -=   m_fAttackSpeed * 0.5f;
            m_body->fY -=   m_fAttackSpeed * 0.1f;
                
            m_fAttackSpeed -= 1.f;
            
            if (m_fAttackSpeed < -10.5f)
            {
                m_bAttackOver = true;
                m_bAttack = false;
                m_fAttackSpeed = 10;
                --m_iGrapeShoot;
            }
            break;

        default:
            break;
        }
    }
}

void CElderEnt::After_Attack()
{
    if(m_bAttackOver)
    {
        switch (m_eCurState)
        {
        case ATTACK:
            if (m_iCameraShakeDelay + 1000 > GetTickCount())
            {
                CCameraMgr::Get_Instance()->ShakeCamera();
            }

            if (m_iHandSlamDelay + 2000 > GetTickCount())
            {
                CCollisionMgr::Collision_Info(m_pTarget, m_pMoveHand);
            }
            else if (m_iHandSlamDelay + 3000 > GetTickCount() && m_iHandSlamDelay + 2000 < GetTickCount())
            {
                CCollisionMgr::Collision_Info(m_pTarget, m_pMoveHand);
                m_pMoveHand->fX -= m_fBodyShakeSpeed * 0.5f;
                m_pMoveHand->fY += m_fBodyShakeSpeed * 0.5f;

                if (m_fBodyShakeSpeed < -0.8f || m_fBodyShakeSpeed > 0.8f)
                    m_shake = !m_shake;

                if (m_shake)
                {
                    m_fBodyShakeSpeed += 0.8f;
                }
                else
                {
                    m_fBodyShakeSpeed -= 0.8f;
                }
            }
            else if (m_iHandSlamDelay + 3000 < GetTickCount() )
            {
                static_cast<CPlayer*>(m_pTarget)->Set_InfoColl(false);
                m_pMoveHand->fX -= cos(m_fTargetAngle) * 10 * 0.5f;
                m_pMoveHand->fY -= sin(m_fTargetAngle) * 10 * 0.5f;
                if (m_fAttackSpeed > 5)
                {
                    m_Head.fY -= m_fAttackSpeed * 0.5f;
                    m_Mouth.fY -= m_fAttackSpeed * 0.5f;
                    m_body->fY -= m_fAttackSpeed * 0.3f;

                    m_fAttackSpeed -= 0.3f;
                }

                if ((m_pMoveHand != &m_leftHand && m_pMoveHand->fY <= m_leftHand.fY) || (m_pMoveHand != &m_rightHand && m_pMoveHand->fY <= m_rightHand.fY))
                {
                    m_bAttackOver = false;
                    m_bAttackReady = true;

                    if (m_iPhase == 0)
                        m_iAttackDelay = GetTickCount();
                    else
                        m_iAttackDelay = 0;

                    m_fAttackSpeed = 10.f;
                    if (0 == m_iAttackCount)
                    {
                        m_eCurState = REBONE;
                        m_bAttackReady = false;
                    }
                }
            }
            break;

        case ATTACK_2:
            if(Set_Pos_Elder() && m_iHandSlamDelay + 400 < GetTickCount())
            {
                m_bAttackOver = false;
                m_bAttackReady = true;

                if (m_iPhase == 0)
                    m_iAttackDelay = GetTickCount();
                else
                    m_iAttackDelay = 0;

                m_rightHand.fX = 1100;
                m_leftHand.fX = -200;
                m_rightHand.fY = 350.f;
                m_leftHand.fY = 350.f;
            }
            if (0 == m_iAttackCount)
            {
                // 여기다가 맵 바닥만 슬쩍 그렸다 지우자.
                m_eCurState = REBONE;
                m_bAttackOver = false;
                m_bAttackReady = false;
                m_rightHand.fX = 650.f;
                m_leftHand.fX = 270.f;
                m_rightHand.fY = 500.f;
                m_leftHand.fY = 500.f;
            }
            break;

        case SKILL_1:
            if(0 != m_iGrapeShoot)
            {
                m_iAttackDelay = GetTickCount();
                m_bAttackOver = false;
                m_bAttackReady = true;
            }
            else if(0 == m_iGrapeShoot)
            {
                CEffectMgr::Get_Instance()->Delete_Effect(GRAPE_ELECT);
                m_eCurState = REBONE;

                m_bAttackOver = false;
                m_bAttackReady = false;
                // 여기는 REBONE 말고 그로기.
                // 그로기 끝나면 리본.
            }
            break;

        default:
            break;
        }
    }
}

void CElderEnt::Return_IdlePos()
{
    if(m_eCurState == REBONE)
    {
        if (Set_Pos_Elder())
        {
            // 걍 다 초기화
            m_eCurState = IDLE;
            m_fSpeed = 0.f;
            m_fAttackReadySpeed = 4.f;
            m_fAttackSpeed = 10.f;
            m_iAttackCount = 3;
            m_fMouthMove = 2.f;
            m_fBodyShakeSpeed = 0.f;
            m_bAttackReady = false;
            m_bAttack = false;
            m_bAttackOver = false;
            m_iPatternDelay = GetTickCount();

            if (m_iPhase == 0)
                m_iGrapeShoot = 3;
            else
                m_iGrapeShoot = 10;

        }
    }
}

bool CElderEnt::Set_Pos_Elder()
{
    float bodyX = CCameraMgr::Get_Instance()->Get_MapSize().fX * 0.5f;
    float bodyY = CCameraMgr::Get_Instance()->Get_MapSize().fY * 0.5f;

    bool check = true;

    // 몸
    if (m_body->fX < bodyX - 1)
    {
        m_body->fX += 1.f;
        check = false;
    }
    else if (m_body->fX > bodyX + 1)
    {
        m_body->fX -= 1.f;
        check = false;
    }

    if (m_body->fY < bodyY - 1)
    {
        m_body->fY += 1.f;
        check = false;
    }
    else if (m_body->fY > bodyY + 1)
    {
        m_body->fY -= 1.f;
        check = false;
    }
    // 대가리
    if (m_Head.fX < bodyX - 1)
    {
        m_Head.fX += 2.f;
        check = false;
    }
    else if (m_Head.fX > bodyX + 1)
    {
        m_Head.fX -= 2.f;
        check = false;
    }
    if (m_Head.fY < bodyY - 50 - 1)
    {
        m_Head.fY += 2.f;
        check = false;
    }
    else if (m_Head.fY > bodyY - 50 + 1)
    {
        m_Head.fY -= 2.f;
        check = false;
    }

    // 입
    if (m_Mouth.fX < m_Head.fX - 1)
    {
        m_Mouth.fX += 2.f;
        check = false;
    }
    else if (m_Mouth.fX > m_Head.fX + 1)
    {
        m_Mouth.fX -= 2.f;
        check = false;
    }
    if (m_Mouth.fY < m_Head.fY + 75 - 1)
    {
        m_Mouth.fY += 2.f;
        check = false;
    }
    else if (m_Mouth.fY > m_Head.fY + 75 + 1)
    {
        m_Mouth.fY -= 2.f;
        check = false;
    }

    
    if (!(m_eCurState == ATTACK_2 && m_iAttackCount != 0))
    {
        // 왼손
        if (m_leftHand.fX < bodyX - 180 - 5)
        {
            m_leftHand.fX += 5.f;
            check = false;
        }
        else if (m_leftHand.fX > bodyX - 180 + 5)
        {
            m_leftHand.fX -= 5.f;
            check = false;
        }
        if (m_leftHand.fY < bodyY + 50 - 5)
        {
            m_leftHand.fY += 5.f;
            check = false;
        }
        else if (m_leftHand.fY > bodyY + 50 + 5)
        {
            m_leftHand.fY -= 5.f;
            check = false;
        }

        // 오른손
        if (m_rightHand.fX < bodyX + 200 - 5)
        {
            m_rightHand.fX += 5.f;
            check = false;
        }
        else if (m_rightHand.fX > bodyX + 200 + 5)
        {
            m_rightHand.fX -= 5.f;
            check = false;
        }
        if (m_rightHand.fY < bodyY + 50 - 5)
        {
            m_rightHand.fY += 5.f;
            check = false;
        }
        else if (m_rightHand.fY > bodyY + 50 + 5)
        {
            m_rightHand.fY -= 5.f;
            check = false;
        }
    }

    if (true == check)
    {
        *m_body = { 450, 280 };
        m_Head = { (*m_body).fX, (*m_body).fY - 50, 100, 250 };
        m_Mouth = { m_Head.fX, m_Head.fY + 75, 100, 50 };
        m_leftHand = { (*m_body).fX - 180, (*m_body).fY + 50, 100, 100 };
        m_rightHand = { (*m_body).fX + 200, (*m_body).fY + 50, 100, 100 };
        return true;
    }
    return false;
}

void CElderEnt::Ent_Move_Frame()
{
    if (m_tFrame.dwTime + m_tFrame.dwSpeed < GetTickCount())
    {
        // 다음 프레임으로 넘어감
        ++m_tFrame.iFrameStart;
        m_tFrame.dwTime = GetTickCount();
       
        if (m_eCurState == SKILL_1 && m_leftHand.fY < (*m_body).fY + 100.f)
        {
            m_leftHand.fY += 35.f;
            m_rightHand.fY += 30.f;
        }

        // 끝나면 처음으로
        if (m_tFrame.iFrameStart > m_tFrame.iFrameEnd)
        {
            if (m_eCurState == IDLE || m_eCurState == REBONE || m_eCurState == ATTACK)
                m_tFrame.iFrameStart = 0;
            else if (m_eCurState == ATTACK_2 || m_eCurState == SKILL_1)
                m_tFrame.iFrameStart = m_tFrame.iFrameEnd;
        }
    }
}

// 아가리 벌렸다가 닫았다가
void CElderEnt::Mouth_Move()
{
    if (m_bMouthOpen)
    {
        m_Mouth.fY += m_fMouthMove;
    }
    else
    {
        m_Mouth.fY -= m_fMouthMove;
    }

    if (m_fMouthMove < 0.1f)
    {
        m_bMouthOpen = !m_bMouthOpen;
        m_fMouthMove = 3.f;
    }
    m_fMouthMove -= 0.4f;

    if (m_bHeadUp)
    {
        m_Head.fY -= m_fSpeed;
        m_Mouth.fY -= m_fSpeed;
    }
    else
    {
        m_Head.fY += m_fSpeed;
        m_Mouth.fY += m_fSpeed;
    }
    if (m_fSpeed < 0.1f)
    {
        m_bHeadUp = !m_bHeadUp;
        m_fSpeed = 2.f;
    }
    m_fSpeed -= 0.2f;
}

void CElderEnt::Check_PlayerPos()
{
    if (m_body->fX - m_pTarget->Get_Info().fX < 0)
        m_pMoveHand = &m_rightHand;
    else
        m_pMoveHand = &m_leftHand;
    
    m_pTarget->Get_Info();
    m_pMoveHand;

    float x = m_pTarget->Get_Info().fX - (*m_pMoveHand).fX;
    float y = m_pTarget->Get_Info().fY - (*m_pMoveHand).fY;

    float hypo = sqrt(pow(x, 2) + pow(y, 2));

    m_fTargetAngle = acos(x/hypo);

    if (y < 0)
        m_fTargetAngle *= -1;
}
