#define FIELD_L 20
#define FIELD_T 10
#define FIELD_W 480
#define FIELD_H 580

#define ITEM_GET_BORDER_Y 200
#define ITEM_GET_MAX_Y (FIELD_H + 200)

#define BARAN_DIV 32

#define PLAYERLEVEL_MAX 5
#define PLAYERPOWER_PER_LEVEL 100
#define PLAYERPOWER_MAX (PLAYERLEVEL_MAX * PLAYERPOWER_PER_LEVEL)

#define GetPlayerLevel() \
	(GDc.Player.Power / PLAYERPOWER_PER_LEVEL)

#define PLAYER_BORNFRAME_MAX 300
#define PLAYER_DEADFRAME_MAX 60
#define PLAYER_BOMBINGFRAME_MAX 180

#define BOMB_R 200.0

enum // EnemyKind_
{
	EK_ENEMY,
	EK_TAMA,
	EK_ITEM,

	EK_MAX, // num of member
};

// ---- �G�e ----

enum
{
	TK_SMALL,
	TK_NORMAL,
	TK_DOUBLE,
	TK_BIG,
	TK_LARGE,
	TK_KNIFE,
	TK_ECLIPSE,
	TK_ECLIPSE_DOUBLE,

	TAMA_KIND_NUM, // num of member
};

enum
{
	TC_RED,
	TC_ORANGE,
	TC_YELLOW,
	TC_GREEN,
	TC_CYAN,
	TC_INDIGO,
	TC_BLUE,
	TC_PURPLE,
	TC_PINK,
	TC_WHITE,

	TAMA_COLOR_NUM, // num of member
};

// ---- �A�C�e�� ----

enum
{
	IK_HEART,
	IK_STAR,
	IK_CANDY,
	IK_BOMB,

	ITEM_KIND_NUM, // num of member
};

// ----

#define FAIRY_COLOR_NUM 4
#define BIGFAIRY_COLOR_NUM 2
#define ONIBI_COLOR_NUM 3

#define FAIRYETC_KIND_NUM (FAIRY_COLOR_NUM + BIGFAIRY_COLOR_NUM + ONIBI_COLOR_NUM)
