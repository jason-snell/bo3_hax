#pragma once

class tools
{
public:
	static void allowPatch(signed long long lpAddress, unsigned int dwSize, bool patch);
	static signed long long getAddr(signed long long addr);
	static signed char clampChar(int i);
	static void saveIni();
	static void loadIni();
};

