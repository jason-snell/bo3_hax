#include "main.h"

PBYTE hook::DetourImport(signed long long imp, PBYTE hook)
{
	tools::allowPatch(imp, 8, true);
	signed long long original = *(signed long long*)tools::getAddr(imp);
	*(signed long long*)tools::getAddr(imp) = (signed long long)hook;
	tools::allowPatch(imp, 8, false);
	return (PBYTE)original;
}

bool pointersInitialized = false;
bool f5Clicked = false, forcePointerReset = false;

bool isInGame()
{
	auto CL_AllLocalClientsDisconnected = (bool(*)())tools::getAddr(0x283B370);
	return !CL_AllLocalClientsDisconnected();
}

void hook::CG_DrawCrosshairHook(int a1)
{
	draw::text("LTPFs BO3 Hack", 5.0f, 5.0f, 1, 0.8f, White, 'L', 0, true, lightBlack);

	if (!f5Clicked && (GetAsyncKeyState(VK_INSERT) & 0x8000))
	{
		f5Clicked = true;
		vars.menuOpen = !vars.menuOpen;
		tools::saveIni();
	}
	if (f5Clicked && !(GetAsyncKeyState(VK_INSERT) & 0x8000))
		f5Clicked = false;

	if (GetAsyncKeyState(VK_F5) & 0x8000 || vars.giveCryptoKeys)
	{
		GiveCryptoKey(0, 1, atoi(cryptoKeyAmount[vars.cryptoKeyAmount]));
	}

	if (GetAsyncKeyState(VK_F6) & 0x8000 || vars.buyRareCrates)
	{
		auto sub_1E82510 = (bool(*)(int a1, int a2, unsigned int a3))tools::getAddr(0x1E82510);
		sub_1E82510(0, vars.crateType, 2);
	}

	if (!forcePointerReset && (GetAsyncKeyState(VK_F1) & 0x8000) && (GetAsyncKeyState(VK_F2) & 0x8000))
	{
		forcePointerReset = true;
		pointersInitialized = false;
		unHookCa = false;
		unHookCg = false;
	}
	if (forcePointerReset && !(GetAsyncKeyState(VK_F1) & 0x8000) && !(GetAsyncKeyState(VK_F2) & 0x8000))
		forcePointerReset = false;

	if (pointersInitialized && isInGame())
	{
		centity = (centity_s*)(__int64)centityAddr;
		cg = (cg_t*)(__int64)cgAddr;
		refDef = (refDef_s*)(__int64)refDefAddr;
		clientInfo = (clientInfo_t*)(__int64)clientInfoAddr;
		ca = (clientActive_t*)(__int64)clientActiveAddr;

		draw::line((refDef->width / 2.0f) - 10.0f, refDef->height / 2.0f, (refDef->width / 2.0f) + 10.0f, refDef->height / 2.0f, Black, 1.0f);
		draw::line(refDef->width / 2.0f, (refDef->height / 2.0f) - 10.0f, refDef->width / 2.0f, (refDef->height / 2.0f) + 10.0f, Black, 1.0f);																			

		if (vAimbot.targetType == AIMBOT_FOV)
			draw::circle(vector2(refDef->width / 2.0f, refDef->height / 2.0f), (float)vAimbot.fovRadius, (float)vAimbot.fovRadius, red);

		if (vAimbot.rcs && *(__int64*)(cgAddr + 0x11A8B0 + 0x2C0) != 0)
		{
			void *weaponDef = BG_GetWeaponDef(*(__int64*)(cgAddr + 0x11A8B0 + 0x2C0));
			if (weaponDef)
			{
				*(float*)((__int64)weaponDef + 0x1230) = 0.0f;
				*(float*)((__int64)weaponDef + 0x1234) = 0.0f;
				*(float*)((__int64)weaponDef + 0x1238) = 0.0f;
				*(float*)((__int64)weaponDef + 0x123C) = 0.0f;
				*(float*)((__int64)weaponDef + 0x1240) = 0.0f;
				*(float*)((__int64)weaponDef + 0x1294) = 0.0f;
				*(float*)((__int64)weaponDef + 0x12A0) = 0.0f;
			}
		}

		func::precacheData();
		esp::draw();
	}

	if (vars.menuOpen)
	{
		//auto sub_1E82CE0 = (bool(*)(int a1, int a2, unsigned int a3))tools::getAddr(0x1E82CE0);
		//sub_1E82CE0(0, 1, 1000);

		//auto sub_1E82510 = (bool(*)(int a1, int a2, unsigned int a3))tools::getAddr(0x1E82510);
		//sub_1E82510(0, 0, 2);

		menu::drawMenu();
	}
}

const char *cmds[] = { "SCORE", "KILLS", "DEATHS", "ASSISTS", "DEFENDS", "PLANTS", "DEFUSES", "RETURNS", "CAPTURES", "OBJTIME", "DESTRUCTIONS", "DISABLES", "ESCORTS", "CARRIES", "THROWS", "RATIO",
	"SURVIVED", "STABS", "TOMAHAWKS", "HUMILIATED", "X2SCORE", "HEADSHOTS", "DOWNS", "POINTS", "KILLS_CONFIRMED", "KILLS_DENIED", "SHOTS_MISSED", "SHOTS_HIT", "TIMEPLAYED", "VICTORY", "GEMS", "SKULLS"
};

bool clicked = false;
int num = 0;

void hook::CL_WritePacketHook(int localClientNum)
{
	if (pointersInitialized && isInGame())
	{
		centity = (centity_s*)(__int64)centityAddr;
		cg = (cg_t*)(__int64)cgAddr;
		refDef = (refDef_s*)(__int64)refDefAddr;
		clientInfo = (clientInfo_t*)(__int64)clientInfoAddr;
		ca = (clientActive_t*)(__int64)clientActiveAddr;

		vars.viewOrigin = func::CG_GetPlayerViewOrigin();

		if (!vAimbot.aimbotOn)
			return;

		usercmd_s *cmd = ca->GetCmd(ca->cmdNumber + 1);
		usercmd_s *oldCmd = ca->GetCmd(ca->cmdNumber);

		ca->cmdNumber++;
		*cmd = *oldCmd;
		cmd->serverTime += 1;

		aimbot::handler(cmd, oldCmd);
	}
}

void hook::CG_AddHudGrenade_PositionCheckHookHook(__int64 cg, centity_s *cent)
{
	static bool once = false;
	if (cg != 0)
	{
		if (!once)
		{
			cgAddr = cg;
			refDefAddr = cgAddr + 0x131CF0;
			centityAddr = (__int64)cent - (cent->clientNumber * sizeof(centity_s));
			clientInfoAddr = refDefAddr + 0x1B5D50;

			char cgStr[64] = { 0 };
			sprintf(cgStr, "cg: %llX", cgAddr);
			CG_GameMessage(0, cgStr);

			char refDefStr[64] = { 0 };
			sprintf(refDefStr, "refDef: %llX", refDefAddr);
			CG_GameMessage(0, refDefStr);

			char centityStr[64] = { 0 };
			sprintf(centityStr, "centity: %llX", centityAddr);
			CG_GameMessage(0, centityStr);

			char clientInfoStr[64] = { 0 };
			sprintf(clientInfoStr, "clientInfo: %llX", clientInfoAddr);
			CG_GameMessage(0, clientInfoStr);

			char clientActiveStr[64] = { 0 };
			sprintf(clientActiveStr, "cmdNum: %llX", clientActiveAddr + 0x10E0F0);
			CG_GameMessage(0, clientActiveStr);
			once = true;
			pointersInitialized = true;
			unHookCg = true;
		}
	}
}

void hook::CL_SavePredictedVehicleForServerTimeHook(__int64 cl, const int serverTime, __int64 predictedPlayerState)
{
	static bool once = false;
	if (cl != 0)
	{
		if (!once)
		{
			clientActiveAddr = cl;
			once = true;
			unHookCa = true;
		}
	}
}