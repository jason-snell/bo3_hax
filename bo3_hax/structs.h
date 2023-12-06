#pragma once

struct centity_s
{
	char pad_0x0000[0x40]; //0x0000
	vector3 origin; //0x0040 
	vector3 viewAngles; //0x004C 
	char pad_0x0058[0x2E4]; //0x0058
	vector3 origin2; //0x033C 
	char pad_0x0348[0x18]; //0x0348
	vector3 viewAngles2; //0x0360 
	char pad_idk[0xC];
	int weaponId; // 0x0378
	char pad_idk2[0x7C];
	int clientNumber; //0x03F8 
	char pad_idk3[4];
	char eFlags; //0x0400
	char pad_idk4[0x7D];
	char alive; //0x047E
	char pad_idk5[0x119];
	short eType; //0x0598
	char pad_0x03FC[0x366]; //0x03FC

	bool isAlive()
	{
		return !(eFlags & 0x20);
	}
}; //Size=0x0900

struct cg_t
{
	char pad_0x0000[0x50]; //0x0000
	int clientNumber; //0x0050 
	char pad_0x0054[0x2C]; //0x0054
	vector3 origin; //0x0080 
	vector2 velocity; //0x008C 
	char pad_0x0094[0x324]; //0x0094
	int health; //0x03B8 
	char pad_0x03BC[0x4]; //0x03BC
	int maxHealth; //0x03C0 
	char pad_0x03C4[0x11B064]; //0x03C4
	float aimSpreadScale; // 0x11B428
}; //Size=0x0BCC

struct refDef_s
{
	char pad_0x0000[0xC]; //0x0000
	int width; //0x000C 
	int height; //0x0010 
	char pad_0x0014[0x64]; //0x0014
	vector2 tanHalfFov; //0x0078 
	char pad_0x0080[0x8]; //0x0080
	vector3 viewOrigin; //0x0088 
	char pad_0x0094[0x10]; //0x0094
	vector3 viewAxis[3]; //0x00A4 
	char pad_0x00C8[0x38]; //0x00C8
}; //Size=0x0100

struct clientInfo_t
{
	char pad_0x0000[0xC]; //0x0000
	char clientName[32]; //0x52D6E9C0 
	int team; //0x002C 
	char pad_0x0030[0x64]; //0x0030
	int score; //0x0094 
	char pad_0x0098[0x14]; //0x0098
	int deaths; //0x00AC 
	char pad_0x00B0[0x28]; //0x00B0
	int kills; //0x00D8 
	char pad_0x00DC[0x18]; //0x00DC
	int health; //0x00F4 
	char pad_0x00F8[0xDD8]; //0x00F8

	bool isAlive()
	{
		return health != 0;
	}
}; //Size=0x0ED0

struct usercmd_s
{
	int serverTime; //0x0000 
	int buttons; //0x0004 
	char pad_0x0008[0x8]; //0x0008
	int viewAngles[3]; //0x0010 
	char pad_0x001C[0x4]; //0x001C
	__int64 weapon; //0x0020 
	char pad_0x0028[0x10]; //0x0028
	signed char forwardmove; //0x0038 
	signed char sidemove; //0x0039 
	char pad_0x003A[0x16]; //0x003A
}; //Size=0x0050

struct clientActive_t
{
	char pad_0x0000[0xE0]; //0x0000
	vector3 origin; //0x00E0
	char pad_0x00EC[0x94];
	vector3 spawnAngles; //0x0180
	char pad_0x01C8[0xB73C];
	vector3 viewAngles; //0xB8C8 
	char pad_0xB8D4[0x10001C]; //0xB8D4
	usercmd_s cmds[128]; //0x10B8F0
	int cmdNumber; //0x10E0F0

	usercmd_s * GetCmd(int Index)
	{
		return &cmds[(Index & 0x7F)];
	}
}; //Size=0xD040

struct trace_t
{
	char pad[0x10];
	float fraction; // 0x0010
	char padding[0x256];
};

struct col_context_t
{
	int mask;
	int *prims;
	int nprims;
	int *ignoreEntParams;
	int passEntityNum0;
	int passEntityNum1;
	int staticmodels;
	int locational;
	char *priorityMap;
	int(__cdecl *collide_entity_func)(int);
};

struct boundsData
{
	float x;
	float y;
	float width;
	float height;

	boundsData()
	{
		x = 0.0f;
		y = 0.0f;
		width = 0.0f;
		height = 0.0f;
	}

	boundsData(float x, float y, float w, float h)
	{
		this->x = x;
		this->y = y;
		this->width = w;
		this->height = h;
	}
};

extern centity_s *centity;
extern cg_t *cg;
extern refDef_s *refDef;
extern clientInfo_t *clientInfo;
extern clientActive_t *ca;

extern int R_TextHeight(void *font);

extern void(*R_AddCmdDrawStretchPic)(float x, float y, float w, float h, float s0, float t0, float s1, float t1, const float *color, void *material);
extern void*(*Material_RegisterHandle)(const char *name, int imageTrack, bool errorIfMissing, int waitTime);
extern void(*CG_DrawRotatedPicW)(void *scrPlace, float x, float y, float w, float width, float height, int horzAlign, int vertAlign, float angle, const float *color, void *material, int idk);
extern void*(*ScrPlace_GetView)(int localClientNum);
extern void*(*Com_GetClientDObj)(int handle, int localClientNum);
extern void(*DObjPhysicsGetBounds)(void *obj, vector3 &mins, vector3 &maxs);
extern int(*CG_DObjGetWorldTagPos)(int *pose, void *dobj, __int64 tagName, vector3 &pos);
extern __int64(*GScr_AllocString)(const char *tag);
extern void(*CG_TraceCapsule)(trace_t *results, vector3 &start, vector3 &mins, vector3 &maxs, vector3 &end, int passEntityNum, int contentMask, void *context);
extern void(*CG_GameMessage)(int localClientNum, const char *msg);
extern void(*BG_GetSpreadForWeapon)(__int64 ps, __int64 weaponid, float *minSpread, float *maxSpread);
extern void*(*BG_GetWeaponDef)(__int64 weaponId);
extern __int64(*DB_FindXAssetHeader)(int type, const char *name, bool errorIfMissing, int waitTime);
extern void(*CL_DrawTextPhysical)(const char *text, int maxChars, void *font, float x, float y, float w, float xScale, float yScale, const float *color, int style, float padding);
extern void*(*R_RegisterFont)(__int64 a1, int fontIndex);
extern int(*R_TextWidth)(int localClientNum, const char *text, int maxChars, void *font);
extern bool(*GiveCryptoKey)(int a1, int a2, unsigned int a3);

extern void initFunctions();

extern __int64 centityAddr, cgAddr, refDefAddr, clientInfoAddr, clientActiveAddr;