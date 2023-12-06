#pragma once

// LeoVehHook class

class hook
{
public:
	static PBYTE DetourImport(signed long long imp, PBYTE hook);
	static void CG_DrawCrosshairHook(int a1);
	static void CL_WritePacketHook(int localClientNum);
	static void CG_AddHudGrenade_PositionCheckHookHook(__int64 cg, centity_s *cent);
	static void CL_SavePredictedVehicleForServerTimeHook(__int64 cl, const int serverTime, __int64 predictedPlayerState);
};