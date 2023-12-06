#pragma once

struct variables
{
	vector3 viewOrigin;
	__int64 bone[17];

	bool menuOpen, giveCryptoKeys, buyRareCrates;
	int cryptoKeyAmount, crateType;
	vector2 cursorPos;
};

extern variables vars;

class func
{
public:
	static bool worldToScreen(vector3 &worldLocation, vector2 &Screen);
	static bool notTeam(int i);
	static bool getTagPos(int i, __int64 tagName, vector3 &pos);
	static void rotatePoint(vector3 point, vector3 center, vector3 angles, vector3 &out);
	static bool visible(int i, __int64 bone);
	static vector3 CG_GetPlayerViewOrigin();
	static void precacheData();
	static bool isInside(vector2 circlePos, int rad, vector2 point);
	static void Disconnect();
	static void callVote();
	static void burnDuplicates();
private:
	static void col_context(col_context_t *col);
};