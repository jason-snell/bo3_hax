#include "main.h"

AimbotVars vAimbot;

float aimbot::AngleNormalize360(const float angle)
{
	float v1;
	float result;

	v1 = (float)((float)(angle * 0.0027777778) - floorf(angle * 0.0027777778)) * 360.0;
	result = v1 - 360.0;
	if ((float)(v1 - 360.0) < 0.0)
		result = v1;
	return result;
}

void spinBot(usercmd_s *cmd, int speed)
{
	static int yAmount = 0;

	yAmount += speed;

	if (yAmount > 360)
		yAmount = 0;
	else if (yAmount < 0)
		yAmount = (int)359;

	cmd->viewAngles[1] = AngleToShort(yAmount - ca->spawnAngles.y);
	cmd->viewAngles[0] = AngleToShort(69.0f);
}

void aimbot::BG_seedRandWithGameTime(unsigned int *pHoldrand)
{
	*pHoldrand ^= ((unsigned __int8)*pHoldrand << 16) ^ ((unsigned __int8)*pHoldrand << 8) ^ ((unsigned __int8)*pHoldrand << 24);
}

float aimbot::BG_random(unsigned int *pHoldrand)
{
	unsigned int v1;

	v1 = 0x343FD * *pHoldrand + 0x269EC3;
	*pHoldrand = v1;
	return (float)(v1 >> 17) * 0.000030517578;
}

void aimbot::RandomBulletDir(unsigned int randSeed, float *x, float *y)
{
	float theta = BG_random(&randSeed) * XM_2PI;
	float radius = BG_random(&randSeed);
	*x = radius * sinf(theta);
	*y = radius * cosf(theta);
}

void aimbot::handleSpread(usercmd_s *cmd, usercmd_s *oldCmd)
{
	if (GetAsyncKeyState(VK_LBUTTON))
		return;

	float min = 0.0f, max = 0.0f;
	BG_GetSpreadForWeapon((__int64)(cgAddr + 0x11A8B0), cmd->weapon, &min, &max);
	float Spread = min + ((max - min) * cg->aimSpreadScale * 0.0039215f);
	vector2 spread = vector2();

	unsigned int serverTime = cmd->serverTime;
	BG_seedRandWithGameTime(&serverTime);
	RandomBulletDir(serverTime, &spread.x, &spread.y);

	oldCmd->viewAngles[0] += AngleToShort(spread.x * Spread);
	oldCmd->viewAngles[1] += AngleToShort(spread.y * Spread);
}

void aimbot::movementFix(usercmd_s *cmd, vector3 origin)
{
	vector3 Vector = VectorToAngles(origin - vars.viewOrigin);
	vector3 aimAngles = Vector - ca->spawnAngles;

	float differenceY = (aimAngles.y - ca->viewAngles.y);
	int forward = cos(differenceY * 0.017453292f) * cmd->forwardmove + cos((differenceY + 90.0f) * 0.017453292f) * cmd->sidemove;
	int right = sin(differenceY * 0.017453292f) * cmd->forwardmove + sin((differenceY + 90.0f) * 0.017453292f) * cmd->sidemove;
	cmd->forwardmove = tools::clampChar(forward);
	cmd->sidemove = tools::clampChar(right);
}

int aimbot::closesetClient()
{
	int closest = -1;
	float currentDistance = FLT_MAX;

	for (int i = 0; i < 18; i++)
	{
		vAimbot.visible[i] = false;
		vAimbot.bestBone[i] = 0;

		if (clientInfo[i].isAlive() && cg->clientNumber != i && func::notTeam(i) && centity[i].isAlive())
		{
			for (int c = 0; c < 17; c++)
			{
				if (vAimbot.targetType == AIMBOT_RAGE)
				{
					if (func::visible(i, vars.bone[c]))
					{
						float distance = centity[i].origin.distance(centity[cg->clientNumber].origin);
						if (distance < currentDistance)
						{
							vAimbot.visible[i] = true;
							vAimbot.bestBone[i] = vars.bone[c];

							closest = i;
							currentDistance = distance;
							break;
						}
					}
				}
				else if (vAimbot.targetType == AIMBOT_FOV)
				{
					vector2 screen = vector2();
					vector3 outBone = vector3();

					if(!func::getTagPos(i, vars.bone[c], outBone))
						continue;

					if (!func::worldToScreen(outBone, screen))
						continue;

					if (func::visible(i, vars.bone[c]) && func::isInside(vector2(refDef->width / 2.0f, refDef->height / 2.0f), vAimbot.fovRadius, screen) || (GetAsyncKeyState(VK_LBUTTON) & 0x8000))
					{
						vAimbot.visible[i] = true;
						vAimbot.bestBone[i] = vars.bone[c];

						closest = i;
						break;
					}
				}
			}
		}
	}

	return closest;
}

void aimbot::handler(usercmd_s *currentCmd, usercmd_s *oldCmd)
{
	vector3 bonePos = vector3();

	vAimbot.closestClient = closesetClient();
	if (vAimbot.closestClient != -1 && func::getTagPos(vAimbot.closestClient, vAimbot.bestBone[vAimbot.closestClient], bonePos))
	{
		vector3 angles = VectorToAngles(bonePos - vars.viewOrigin) - ca->spawnAngles;

		if (vAimbot.aimbotType == AIMBOT_SILENT)
		{
			oldCmd->viewAngles[0] = AngleToShort(angles.x);
			oldCmd->viewAngles[1] = AngleToShort(angles.y);
			movementFix(oldCmd, centity[vAimbot.closestClient].origin);
		}
		else if (vAimbot.aimbotType == AIMBOT_SNAP)
		{
			oldCmd->viewAngles[0] = AngleToShort(angles.x);
			oldCmd->viewAngles[1] = AngleToShort(angles.y);
			ca->viewAngles = angles;
		}

		if(vAimbot.noSpread)
			handleSpread(currentCmd, oldCmd);

		if (oldCmd->buttons &= ~0x80000000)
			currentCmd->buttons |= 0x80000000;
		else if (vAimbot.autoshoot)
			currentCmd->buttons |= 0x80000000;
	}


	spinBot(currentCmd, 50);
}