#pragma once

enum OPTION_TYPE : int
{
	TYPE_OPTION_CALL,
	TYPE_OPTION_BOOL,
	TYPE_OPTION_FLOAT,
	TYPE_OPTION_INT,
	TYPE_OPTION_LIST,
};

class base
{
private:
	bool bMenuOpen;
public:
	const char *tabText[30] = { "" };
	const char *menuText[30][30] = { "" };
	bool *menuBools[30][30] = { false };
	int *listInts[30][30] = { 0 };
	const char **lists[30][30];
	int listOptionCount[30][30] = { 0 };
	int optionType[30][30];
	int menuOptionIndex[30] = { 0 };
	int intMin[15][30];
	int intMax[15][30];
	int intInc[15][30];
	void *funcs[15][30];
	int arg1[15][30];
	int arg2[15][30];
	int arg3[15][30];
	int tabIndex = 0, maxScroll = 0, currentMenu = 0;
	float menuPosX = 0, menuPosY = 0;

	base();
	~base();
	void addTab(const char *text);
	void addBool(const char *optionName, bool *b);
	void addList(const char *optionName, int *intValue, const char **list, int listSize);
	void addInt(const char *optionName, int *intValue, int min, int max, int inc);
	void addButton(const char *optionName, void *function, int arg1 = -1, int arg2 = -1, int arg3 = -1);
	bool menuOpen();
	void openMenu();
	void closeMenu();
	bool isHovering(float x, float y, float endX, float endY);
};