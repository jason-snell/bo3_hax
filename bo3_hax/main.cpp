#include "main.h"

DWORD(*GetCurrentThreadIdStub)();

static DWORD oldProtect;

bool unHookCg = false, unHookCa = false;

void sub_1E82CE0(int a1, int a2, unsigned int a3)
{
	char buff[0x200] = { 0 };
	sprintf(buff, "a1: %i | a2: %i | a3: %i", a1, a2, a3);
	MessageBoxA(0, buff, 0, 0);
}

void R_AddCmdDrawUIQuadsInternalHook(void *r3, __int16 r4, void *r5, void *r6, void *r7, int r8)
{
	*(unsigned char*)r7 = 255;
	*(unsigned char*)((__int64)r7 + 1) = 255;
	*(unsigned char*)((__int64)r7 + 2) = 255;
	*(unsigned char*)((__int64)r7 + 3) = 255;
	//R_AddCmdDrawUIQuadsInternalDetour->CallOriginal(r3, r4, r5, r6, r7, r8);
}

LONG WINAPI OurCrashHandler(EXCEPTION_POINTERS * ExceptionInfo)
{
	if (ExceptionInfo->ExceptionRecord->ExceptionCode == STATUS_GUARD_PAGE_VIOLATION)
	{
		if (ExceptionInfo->ContextRecord->Rip == (DWORD64)tools::getAddr(0x13CFBF0))
		{
			hook::CG_DrawCrosshairHook(ExceptionInfo->ContextRecord->Rcx);
		}
		else if (ExceptionInfo->ContextRecord->Rip == (DWORD64)tools::getAddr(0x13000A0))
		{
			hook::CL_WritePacketHook(ExceptionInfo->ContextRecord->Rcx);
		}
		else if (ExceptionInfo->ContextRecord->Rip == (DWORD64)tools::getAddr(0x5E6560))
		{
			hook::CG_AddHudGrenade_PositionCheckHookHook(ExceptionInfo->ContextRecord->Rcx, (centity_s*)ExceptionInfo->ContextRecord->Rdx);
		}
		else if (ExceptionInfo->ContextRecord->Rip == (DWORD64)tools::getAddr(0x13664F0))
		{
			hook::CL_SavePredictedVehicleForServerTimeHook(ExceptionInfo->ContextRecord->Rcx, ExceptionInfo->ContextRecord->Rdx, ExceptionInfo->ContextRecord->R8);
		}
		else if (ExceptionInfo->ContextRecord->Rip == (DWORD64)tools::getAddr(0x1CDA250))
		{
			R_AddCmdDrawUIQuadsInternalHook((void*)ExceptionInfo->ContextRecord->Rcx, ExceptionInfo->ContextRecord->Rdx, (void*)ExceptionInfo->ContextRecord->R8, (void*)ExceptionInfo->ContextRecord->R9, (void*)ExceptionInfo->ContextRecord->R10, ExceptionInfo->ContextRecord->R11);
			//sub_1E82CE0(ExceptionInfo->ContextRecord->Rcx, ExceptionInfo->ContextRecord->Rdx, ExceptionInfo->ContextRecord->R8);
		}

		ExceptionInfo->ContextRecord->EFlags |= 0x100;
		return EXCEPTION_CONTINUE_EXECUTION;
	}

	if (ExceptionInfo->ExceptionRecord->ExceptionCode == STATUS_SINGLE_STEP)
	{
		// CG_DrawCrosshairHook
		VirtualProtect((void*)tools::getAddr(0x13CFBF0), 1, PAGE_EXECUTE_READ | PAGE_GUARD, &oldProtect);

		// CL_WritePacketHook
		VirtualProtect((void*)tools::getAddr(0x13000A0), 1, PAGE_EXECUTE_READ | PAGE_GUARD, &oldProtect);

		//test hook
		VirtualProtect((void*)tools::getAddr(0x1CDA250), 1, PAGE_EXECUTE_READ | PAGE_GUARD, &oldProtect);

		// CG_AddHudGrenade_PositionCheckHook
		if(unHookCg)
			VirtualProtect((void*)tools::getAddr(0x5E6560), 1, PAGE_EXECUTE_READ, &oldProtect);
		else
			VirtualProtect((void*)tools::getAddr(0x5E6560), 1, PAGE_EXECUTE_READ | PAGE_GUARD, &oldProtect);

		// CL_SavePredictedVehicleForServerTimeHook
		if(unHookCa)
			VirtualProtect((void*)tools::getAddr(0x13664F0), 1, PAGE_EXECUTE_READ, &oldProtect);
		else
			VirtualProtect((void*)tools::getAddr(0x13664F0), 1, PAGE_EXECUTE_READ | PAGE_GUARD, &oldProtect);

		return EXCEPTION_CONTINUE_EXECUTION;
	}
	return EXCEPTION_CONTINUE_SEARCH;
}

int count = 0;
DWORD GetCurrentThreadIdHook()
{
	count++;
	if (count == 30000)
	{
		initFunctions();
		tools::loadIni();
		menu::createMenu();

		AddVectoredExceptionHandler(true, OurCrashHandler);
		VirtualProtect((void*)tools::getAddr(0x13CFBF0), 1, PAGE_EXECUTE_READ | PAGE_GUARD, &oldProtect); // CG_DrawCrosshairHook
		VirtualProtect((void*)tools::getAddr(0x13000A0), 1, PAGE_EXECUTE_READ | PAGE_GUARD, &oldProtect); // CL_WritePacketHook
		VirtualProtect((void*)tools::getAddr(0x5E6560), 1, PAGE_EXECUTE_READ | PAGE_GUARD, &oldProtect); // CG_AddHudGrenade_PositionCheckHook
		VirtualProtect((void*)tools::getAddr(0x13664F0), 1, PAGE_EXECUTE_READ | PAGE_GUARD, &oldProtect); // CL_SavePredictedPlayerVehicleForServerTimeHook

		VirtualProtect((void*)tools::getAddr(0x1CDA250), 1, PAGE_EXECUTE_READ | PAGE_GUARD, &oldProtect);
	}

	return GetCurrentThreadIdStub();
}

bool __stdcall DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpReserved)
{
	switch (fdwReason)
	{
	case DLL_PROCESS_ATTACH:
		GetCurrentThreadIdStub = (decltype(GetCurrentThreadIdStub))hook::DetourImport(0x1AAEACF4, (PBYTE)GetCurrentThreadIdHook);
		return true;
		break;
	case DLL_PROCESS_DETACH:
		return false;
		break;
	}
	return true;
}