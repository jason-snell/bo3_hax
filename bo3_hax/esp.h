#pragma once

enum
{
	FRIENDLY,
	ENEMY,
	BOTH
};

enum
{
	BOX_OFF,
	BOX_2D,
	BOX_3D,
	BOX_CORNER,
	BOX_2DFILLED,
};

enum
{
	NAME_OFF,
	NAME_FRIENDLY,
	NAME_ENEMY,
	NAME_BOTH
};

enum
{
	SNAPLINE_OFF,
	SNAPLINE_TOP,
	SNAPLINE_CENTER,
	SNAPLINE_BOTTOM
};

enum
{
	HEALTHBAR_OFF,
	HEALTHBAR_FRIENDLY,
	HEALTHBAR_ENEMY,
	HEALTHBAR_BOTH
};

enum
{
	CRYPTO_1,
	CRYPTO_10,
	CRYPTO_20,
	CRYPTO_30,
	CRYPTO_35,
	CRYPTO_40,
};

enum
{
	CRATE_COMMON,
	CRATE_RARE
};

static const char *teamOptions[] = { "Friendly", "Enemy", "Both" };
static const char *boxType[] = { "Off", "2D", "3D", "Corner", "2D Filled" };
static const char *nameEsp[] = { "Off", "Friendly", "Enemy", "Both" };
static const char *snaplines[] = { "Off", "Top", "Center", "Bottom" };
static const char *cryptoKeyAmount[] = { "1", "10", "20", "30", "35", "40" };
static const char *crateType[] = { "Common", "Rare" };

struct espVars
{
	float *enemyColor, *visibleColor, *friendlyColor;
	int enemyBoxType, friendlyBoxType, nameEsp, friendlySnaplines, enemySnaplines, healthBar, bones;
	bool itemEsp;
};

extern espVars vEsp;

class esp
{
public:
	static boundsData boundingBox(int c, float *color, int boxType);
	static void bones(int clientNum, float *color);
	static void player(int client);
	static void draw();
};