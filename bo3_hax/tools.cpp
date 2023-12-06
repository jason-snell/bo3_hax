#include "main.h"

unsigned long oldProtect = NULL;

void tools::allowPatch(signed long long lpAddress, unsigned int dwSize, bool patch)
{
	if (patch)
		VirtualProtect((void*)lpAddress, dwSize, PAGE_EXECUTE_READWRITE, &oldProtect);
	else
		VirtualProtect((void*)lpAddress, dwSize, oldProtect, &oldProtect);
}

signed long long tools::getAddr(signed long long addr)
{
	return (signed long long)GetModuleHandleA(NULL) + addr;
}

signed char tools::clampChar(int i)
{
	if (i < -128) {
		return -128;
	}
	if (i > 127) {
		return 127;
	}
	return i;
}

void tools::saveIni()
{
	CSimpleIni ini;
	ini.SetUnicode();

	ini.SetBoolValue("aimbot", "aimbot_on", vAimbot.aimbotOn);
	ini.SetBoolValue("aimbot", "auto_shoot", vAimbot.autoshoot);
	ini.SetBoolValue("aimbot", "no_recoil", vAimbot.rcs);
	ini.SetBoolValue("aimbot", "no_spread", vAimbot.noSpread);
	ini.SetLongValue("aimbot", "target_type", vAimbot.targetType);
	ini.SetLongValue("aimbot", "aimbot_type", vAimbot.aimbotType);
	ini.SetLongValue("aimbot", "fov_radius", vAimbot.fovRadius);

	ini.SetLongValue("esp", "enemy_boxes", vEsp.enemyBoxType);
	ini.SetLongValue("esp", "friendly_boxes", vEsp.friendlyBoxType);
	ini.SetLongValue("esp", "names", vEsp.nameEsp);
	ini.SetLongValue("esp", "enemy_snaplines", vEsp.enemySnaplines);
	ini.SetLongValue("esp", "friendly_snaplines", vEsp.friendlySnaplines);
	ini.SetLongValue("esp", "healthbars", vEsp.healthBar);
	ini.SetLongValue("esp", "bones", vEsp.bones);
	ini.SetBoolValue("esp", "itemesp", vEsp.itemEsp);

	ini.SaveFile("settings.ini");
}

void tools::loadIni()
{
	CSimpleIni ini;
	ini.SetUnicode();

	if (ini.LoadFile("settings.ini") < 0)
		saveIni();

	vAimbot.aimbotOn = ini.GetBoolValue("aimbot", "aimbot_on", 0);
	vAimbot.autoshoot = ini.GetBoolValue("aimbot", "auto_shoot", 0);
	vAimbot.rcs = ini.GetBoolValue("aimbot", "no_recoil", 0);
	vAimbot.noSpread = ini.GetBoolValue("aimbot", "no_spread", 0);
	vAimbot.targetType = ini.GetLongValue("aimbot", "target_type", 0);
	vAimbot.aimbotType = ini.GetLongValue("aimbot", "aimbot_type", 0);
	vAimbot.fovRadius = ini.GetLongValue("aimbot", "fov_radius", 0);

	vEsp.enemyBoxType = ini.GetLongValue("esp", "enemy_boxes", 0);
	vEsp.friendlyBoxType = ini.GetLongValue("esp", "friendly_boxes", 0);
	vEsp.nameEsp = ini.GetLongValue("esp", "names", 0);
	vEsp.enemySnaplines = ini.GetLongValue("esp", "enemy_snaplines", 0);
	vEsp.friendlySnaplines = ini.GetLongValue("esp", "friendly_snaplines", 0);
	vEsp.healthBar = ini.GetLongValue("esp", "healthbars", 0);
	vEsp.bones = ini.GetLongValue("esp", "bones", 0);
	vEsp.itemEsp = ini.GetBoolValue("esp", "itemesp", 0);
}