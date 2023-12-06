#include "main.h"

centity_s *centity;
cg_t *cg;
refDef_s *refDef;
clientInfo_t *clientInfo;
clientActive_t *ca;

int R_TextHeight(void *font)
{
	return *(unsigned int*)((__int64)font + 8);
}

void(*R_AddCmdDrawStretchPic)(float x, float y, float w, float h, float s0, float t0, float s1, float t1, const float *color, void *material);
void*(*Material_RegisterHandle)(const char *name, int imageTrack, bool errorIfMissing, int waitTime);
void(*CG_DrawRotatedPicW)(void *scrPlace, float x, float y, float w, float width, float height, int horzAlign, int vertAlign, float angle, const float *color, void *material, int idk);
void*(*ScrPlace_GetView)(int localClientNum);
void*(*Com_GetClientDObj)(int handle, int localClientNum);
void(*DObjPhysicsGetBounds)(void *obj, vector3 &mins, vector3 &maxs);
int(*CG_DObjGetWorldTagPos)(int *pose, void *dobj, __int64 tagName, vector3 &pos);
__int64(*GScr_AllocString)(const char *tag);
void(*CG_TraceCapsule)(trace_t *results, vector3 &start, vector3 &mins, vector3 &maxs, vector3 &end, int passEntityNum, int contentMask, void *context);
void(*CG_GameMessage)(int localClientNum, const char *msg);
void(*BG_GetSpreadForWeapon)(__int64 ps, __int64 weaponid, float *minSpread, float *maxSpread);
void*(*BG_GetWeaponDef)(__int64 weaponId);
__int64(*DB_FindXAssetHeader)(int type, const char *name, bool errorIfMissing, int waitTime);
void(*CL_DrawTextPhysical)(const char *text, int maxChars, void *font, float x, float y, float w, float xScale, float yScale, const float *color, int style, float padding);
void*(*R_RegisterFont)(__int64 a1, int fontIndex);
int(*R_TextWidth)(int localClientNum, const char *text, int maxChars, void *font);
bool(*GiveCryptoKey)(int a1, int a2, unsigned int a3);

void initFunctions()
{
	R_AddCmdDrawStretchPic = (decltype(R_AddCmdDrawStretchPic))tools::getAddr(0x1320850);
	Material_RegisterHandle = (decltype(Material_RegisterHandle))tools::getAddr(0x1CD4B90);
	CG_DrawRotatedPicW = (decltype(CG_DrawRotatedPicW))tools::getAddr(0x6F0360);
	ScrPlace_GetView = (decltype(ScrPlace_GetView))tools::getAddr(0x13E55A0);
	Com_GetClientDObj = (decltype(Com_GetClientDObj))tools::getAddr(0x214EBA0);
	DObjPhysicsGetBounds = (decltype(DObjPhysicsGetBounds))tools::getAddr(0x2337E60);
	CG_DObjGetWorldTagPos = (decltype(CG_DObjGetWorldTagPos))tools::getAddr(0x1ABD50);
	GScr_AllocString = (decltype(GScr_AllocString))tools::getAddr(0x12D7260);
	CG_TraceCapsule = (decltype(CG_TraceCapsule))tools::getAddr(0x12B4AF0);
	CG_GameMessage = (decltype(CG_GameMessage))tools::getAddr(0x8CB400);
	BG_GetSpreadForWeapon = (decltype(BG_GetSpreadForWeapon))tools::getAddr(0x26D1310);
	BG_GetWeaponDef = (decltype(BG_GetWeaponDef))tools::getAddr(0x26EAB80);
	DB_FindXAssetHeader = (decltype(DB_FindXAssetHeader))tools::getAddr(0x1420ED0);
	CL_DrawTextPhysical = (decltype(CL_DrawTextPhysical))tools::getAddr(0x134DB80);
	R_RegisterFont = (decltype(R_RegisterFont))tools::getAddr(0x228DF90);
	R_TextWidth = (decltype(R_TextWidth))tools::getAddr(0x1CAB2C0);
	GiveCryptoKey = (decltype(GiveCryptoKey))tools::getAddr(0x1E82CE0);
}

__int64 centityAddr = 0, cgAddr = 0, refDefAddr = 0, clientInfoAddr = 0, clientActiveAddr = 0;