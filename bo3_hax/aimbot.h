#pragma once

struct AimbotVars
{
	bool visible[18];
	__int64 bestBone[18];
	int closestClient;

	bool autoshoot, rcs, autocrouch, visiblecheck, noSpread, aimbotOn;
	int fovRadius, targetType, aimbotType;
	int ySpeed, xSpeed, yType, xType;
	bool xAa, yAa;
};

extern AimbotVars vAimbot;

class aimbot
{
public:
	static int closesetClient();
	static void handler(usercmd_s *currentCmd, usercmd_s *nextCmd);
private:
	static float AngleNormalize360(const float angle);
	static void BG_seedRandWithGameTime(unsigned int *pHoldrand);
	static float BG_random(unsigned int *pHoldrand);
	static void RandomBulletDir(unsigned int randSeed, float *x, float *y);
	static void handleSpread(usercmd_s *cmd, usercmd_s *oldCmd);
	static void movementFix(usercmd_s *cmd, vector3 aimAngles);
};