#include "main.h"

variables vars;

bool func::worldToScreen(vector3 &worldLocation, vector2 &Screen)
{
	vector3 Local = vector3();
	vector3 Transform = vector3();

	Local = worldLocation - refDef->viewOrigin, Transform;
	Transform.x = Local.dotProduct(refDef->viewAxis[1]);
	Transform.y = Local.dotProduct(refDef->viewAxis[2]);
	Transform.z = Local.dotProduct(refDef->viewAxis[0]);

	if (Transform.z < 0.01f)
		return false;

	Screen.x = (refDef->width / 2.0f) * (1.0f - (Transform.x / refDef->tanHalfFov.x / Transform.z));
	Screen.y = (refDef->height / 2.0f) * (1.0f - (Transform.y / refDef->tanHalfFov.y / Transform.z));
	return (Transform.z > 0.0f);
}

bool func::notTeam(int i)
{
	return (clientInfo[cg->clientNumber].team != clientInfo[i].team || clientInfo[i].team == 0);
}

void func::rotatePoint(vector3 point, vector3 center, vector3 angles, vector3 &out)
{
	float zTheta = D3DXToRadian(angles.y);
	float yTheta = D3DXToRadian(angles.x);
	float xTheta = D3DXToRadian(angles.z);
	vector3 rotatedPoint = vector3();
	vector3 dir = point - center;
	rotatedPoint.x = point.x;
	rotatedPoint.y = center.y + (dir.y * cos(xTheta) - dir.z * sin(xTheta));
	rotatedPoint.z = center.z + (dir.y * sin(xTheta) + dir.z * cos(xTheta));
	dir = rotatedPoint - center;
	rotatedPoint.x = center.x + (dir.x * cos(yTheta) + dir.z * sin(yTheta));
	rotatedPoint.z = center.z + (dir.z * cos(yTheta) - dir.x * sin(yTheta));
	dir = rotatedPoint - center;
	out.x = center.x + (dir.x * cos(zTheta) - dir.y * sin(zTheta));
	out.y = center.y + (dir.x * sin(zTheta) + dir.y * cos(zTheta));
	out.z = rotatedPoint.z;
}

bool func::getTagPos(int i, __int64 tagName, vector3 &pos)
{
	void *DObj = Com_GetClientDObj(i, 0);

	if (!DObj || !tagName)
		return false;

	return CG_DObjGetWorldTagPos((int*)&centity[i], DObj, tagName, pos);
}

void func::col_context(col_context_t *col)
{
	col->mask = 0;
	col->prims = 0;
	col->nprims = 0;
	col->ignoreEntParams = 0;
	col->passEntityNum0 = 1023;
	col->passEntityNum1 = 1023;
	col->locational = 0;
	col->staticmodels = 0;
	col->priorityMap = 0;
	col->collide_entity_func = 0;
}

bool func::visible(int i, __int64 bone)
{
	vector3 bonePos = vector3();

	if (!func::getTagPos(i, bone, bonePos))
		return false;

	vector3 min = vector3(), max = vector3();
	col_context_t context = { 0 };
	col_context(&context);
	vector3 viewOrigin = CG_GetPlayerViewOrigin();
	trace_t trace = { 0 };
	CG_TraceCapsule(&trace, viewOrigin, min, max, bonePos, cg->clientNumber, 0x280F803, &context);

	return trace.fraction >= 0.95f;
}

vector3 func::CG_GetPlayerViewOrigin()
{
	vector3 viewOrigin = vector3();

	auto BG_GetPlayerViewOrigin = (void(*)(__int64 ps, vector3 &origin, int time))tools::getAddr(0x267DFC0);
	BG_GetPlayerViewOrigin((__int64)(cgAddr + 0x11A8B0), viewOrigin, *(int*)(cgAddr + 0x11A88C));
	return viewOrigin;
}

void func::precacheData()
{
	static bool once = false;
	if (!once)
	{
		// precache bones
		for (int i = 0; i < 17; i++)
			vars.bone[i] = GScr_AllocString(boneNames[i]);

		vEsp.enemyColor = red;
		vEsp.friendlyColor = Green;
		vEsp.visibleColor = yellow;

		once = true;
	}
}

bool func::isInside(vector2 circlePos, int rad, vector2 point)
{
	if ((point.x - circlePos.x) * (point.x - circlePos.x) +
		(point.y - circlePos.y) * (point.y - circlePos.y) <= rad * rad)
		return true;
	else
		return false;
}

void func::Disconnect()
{
	auto Cbuf_InsertText = (void(*)(int localClientNum, const char *text))tools::getAddr(0x20ECFC0);
	Cbuf_InsertText(0, "disconnect;");
}

void func::callVote()
{
	auto Cbuf_InsertText = (void(*)(int localClientNum, const char *text))tools::getAddr(0x135D4C0);
	Cbuf_InsertText(0, "callvote map mp_nuketown_x\x0wait 15000\x0Ddisconnect\x0Dstatsetbyname PLEVEL 5\x0D");
}

void func::burnDuplicates()
{
	auto sub_1E823F0 = (bool(*)(int a1, int a2))tools::getAddr(0x1E823F0);
	sub_1E823F0(0, 1);
}