#pragma once

#pragma region cmd 생성
//#ifdef UNICODE
//#pragma comment(linker, "/entry:wWinMainCRTStartup /subsystem:console")
//#else
//#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")
//#endif
#pragma endregion
extern	HWND		g_hWnd;

#define			WINCX		800
#define			WINCY		450

#define			PURE		= 0

#define			OBJ_NOEVENT		0
#define			OBJ_DEAD		1

#define			PI			3.141592f

#define			VK_MAX		0xff
#define			RADIAN(angle)	angle * (3.141592f / 180)		
#define			ANGLE(radian)	radian * (180 / 3.141592f)
#define			ObjMgr		CObjMgr::Get_Instance()

enum OBJSTATE
{
	IDLE, 
	WALK,
	JUMP,
	FALLING_START,
	FALLING,
	DASH,
	ATTACK,
	ATTACK_2,
	JUMP_ATTACK,
	HIT_1,
	HIT_2,
	DEAD,
	SKILL_1,
	SKILL_2_INTRO,
	SKILL_2_READY,
	SKILL_2,
	RECOVERY,
	EXCHANGE,
	REBONE,
	STATE_END
};

enum AGGROLEVEL
{
	UNRECOGNIZE,	// 미인식
	RECOGNIZE,		// 인식
	AGGRO_ATTACK,
	AGGRO_END
};

enum SCENEID
{
	SC_TITLE,
	SC_CASTLE,
	SC_DUNGEONENT,
	SC_STAGE1,
	SC_STAGE2,
	SC_SKULENF,
	SC_BOSSENT,
	SC_BOSS,
	SC_END
};

#pragma endregion
//enum OBJID { OBJ_PLAYER, OBJ_MONSTER, OBJ_BULLET, OBJ_MOUSE, OBJ_SHIELD, OBJ_END };
enum OBJID
{
	OBJ_PLAYER,
	OBJ_MONSTER,
	OBJ_ATTACK,
	OBJ_MOUSE,
	OBJ_GROUND,
	OBJ_DOOR,
	OBJ_REWARD,
	OBJ_DROP,
	OBJ_CAGE,
	OBJ_NPC,
	OBJ_END 
};

enum RENDERID 
{ 
	// 뒷배경
	RENDER_BACKGROUND, 
	// 지형
	RENDER_GAMEOBJECT,
	// 몬스터
	RENDER_MONSTER,
	// 이펙트
	RENDER_EFFECT, 
	RENDER_NPC,
	// 플레이어
	RENDER_PLAYER,
	RENDER_DROP,

	// UI
	RENDER_UI,

	RENDER_END
};

enum MONSTERID 
{
	ELDERENT,
	SOLDIER,
	ARCHER,
	MONSTERID_END
};

enum ATTACKTYPE
{
	PLAYER_ATTACK_1,
	PLAYER_ATTACK_2,
	PLAYER_SKILL_1,
	PLAYER_SKILL_2,

	BERSERKER_ATTACK_1,
	BERSERKER_ATTACK_2,
	BERSERKER_SKILL_1,
	BERSERKER_SKILL_2,

	BERSERKER_2_SKILL_2,
	DEMONIZATION_BOOM,
	DEMON_SKILL_2,

	SOLDIER_ATTACK,
	ARCHER_ATTACK,

	ELDERENT_SLEM,
	ELDERENT_SWEEP,
	ELDERENT_GRAPE,
	ELDERENT_BABYGRAPE,

	ATTACKTYPE_END
};

enum SKULTYPE
{
	SKUL,
	BERSERKER,
	SKUL_END
};

enum CHANNELID
{
	SOUND_EFFECT,
	
	SOUND_JUMP,
	SOUND_DASH,

	SOUND_NORMAL_ATTACK,
	SOUND_NORMAL_JUMP_ATTACK,
	SOUND_THORW_SKUL,
	SOUND_SKUL_BACK,

	SOUND_BERSERKER_ATTACK,	// 점프어택도 이걸로
	SOUND_BERSERKER_DEMON_ATTACK,
	
	SOUND_BERSERKER_MADAXE,
	SOUND_BERSERKER_MADAXE_DEMON,

	SOUND_BERSERKER_DEMONIZATION,

	SOUND_HIT,
	SOUND_PLAYER_HIT,

	SOUND_CHANGE,
	
	SOUND_ELDERENT_GRAPE_FIRE,
	SOUND_ELDERENT_GRAPE_READY,
	SOUND_ELDERENT_FISTSLAM,
	SOUND_ELDERENT_SWEEPING,

	SOUND_BGM,
	
	MAXCHANNEL
};

enum EFFECTTYPE
{
	// 플레이어 공격
	NORMAL_ATT_LEFT,
	NORMAL_ATT_RIGHT,
	BERSERKER_ATT,

	// 버서커 1차 스킬
	BONE_HOWL,
	MAD_AXE,

	// 버서커 2차 스킬
	DEMONIZATION, // BONE_HOWL이랑 동시에 나감.
	MAD_AXE_2_LEFT,
	MAD_AXE_2_RIGHT,

	DEMON_MADAXE,
	DEMON_AURA,

	// 플레이어 이동
	PLAYER_DASH_RIGHT,
	PLAYER_DASH_LEFT,
	PLAYER_DOUBLEJUMP,

	// 플레이어 피격
	PLAYER_HIT,

	// 화살
	ARCHER_ARROW_SIGN,


	// 보스 공격
	GRAPE_READY,
	GRAPE_READY_2,
	GRAPE_ELECT,
	GRAPE_SHOOT,

	// 보스 공격 위치
	GRAPE_BOOM,
	HANDSLAM_BOOM,

	// 몬스터 등장, 사망
	MONSTER_APPEAR,
	MONSTER_DEAD
};

enum DIRECTION
{
	LEFT,
	RIGHT,
	UP,
	DOWN,
	DIR_END
};

enum DOORTYPE
{
	DUNGEON_ENT_DOOR,
	STAGE_DOOR,
	BOSS_ENT_DOOR,
	DOOR_END
};

enum REWARDTYPE
{
	REWARD_SKUL,
	REWARD_END
};

typedef struct tagInfo
{
	float		fX;
	float		fY;

	float		fCX;
	float		fCY;

}INFO;

// 중점에서 플레이어 위치.
struct Vec2
{
	float fX;
	float fY;
};

typedef struct tagPoint
{
	float	fX;
	float	fY;

	tagPoint() { ZeroMemory(this, sizeof(tagPoint)); }
	tagPoint(float _fX, float _fY) : fX(_fX), fY(_fY) {}

}LINEPOINT;

typedef struct tagLine
{
	LINEPOINT		tLPoint;
	LINEPOINT		tRPoint;

	tagLine() { ZeroMemory(this, sizeof(tagLine)); }
	tagLine(LINEPOINT& _tLPoint, LINEPOINT& _tRPoint)
		: tLPoint(_tLPoint), tRPoint(_tRPoint) {}

}LINE;

extern int GetRandomNum(int _first, int _second);

template<typename T>
void Safe_Delete(T& Temp)
{
	if (Temp)
	{
		delete Temp;
		Temp = nullptr;
	}
}

template<typename T>
void Safe_Delete_Array(T& Temp)
{
	if (Temp)
	{
		delete[] Temp;
		Temp = nullptr;
	}
}

typedef struct tagFrame
{
	int		iFrameStart;	// 몇 번 인덱스부터 시작할 것인가
	int		iFrameEnd;		// 몇 번 인덱스로 끝날 것인가.
	int		iMotion;		// 몇 번째 모션인가
	DWORD	dwSpeed;		// 인덱스 넘기는 속도(다음 인덱스 부르는데 걸리는 시간)
	DWORD	dwTime;			// GetTickCount 받아오는 용도.
} FRAME;

struct Line
{
	Vec2 first;
	Vec2 second;
};

struct DeleteObj
{
	template<typename T>
	void		operator()(T& Obj)
	{
		if (Obj)
		{
			delete Obj;
			Obj = nullptr;
		}
	}
};

struct DeleteMap
{
	template<typename T>
	void		operator()(T& MyPair)
	{
		if (MyPair.second)
		{
			delete MyPair.second;
			MyPair.second = nullptr;
		}
	}
};



// 일치하는 키 찾는 조건자
class CStringCmp
{
public:
	CStringCmp(const TCHAR* pString) : m_pString(pString) {}

public:
	template<typename T>
	bool operator()(T& MyPair)
	{
		// 문자열 두개 비교 -> 왼쪽이 작으면 음수, 같으면 0, 오른쪽이 작으면 양수
		return !lstrcmp(m_pString, MyPair.first);	// 같으면 true, 다르면 false 반환
	}

private:
	const	TCHAR* m_pString;
};