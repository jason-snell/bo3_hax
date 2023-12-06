#include "main.h"

base::base()
{

}

base::~base()
{

}

void base::addTab(const char *text)
{
	tabText[tabIndex] = text;
	tabIndex++;
}

void base::addBool(const char *optionName, bool *b)
{
	int tempIndex = tabIndex - 1;
	optionType[tempIndex][menuOptionIndex[tempIndex]] = TYPE_OPTION_BOOL;
	menuText[tempIndex][menuOptionIndex[tempIndex]] = optionName;
	menuBools[tempIndex][menuOptionIndex[tempIndex]] = b;

	menuOptionIndex[tempIndex]++;
}

void base::addList(const char *optionName, int *intValue, const char **list, int listSize)
{
	int tempIndex = tabIndex - 1;
	optionType[tempIndex][menuOptionIndex[tempIndex]] = TYPE_OPTION_LIST;
	menuText[tempIndex][menuOptionIndex[tempIndex]] = optionName;
	listInts[tempIndex][menuOptionIndex[tempIndex]] = intValue;
	lists[tempIndex][menuOptionIndex[tempIndex]] = list;
	listOptionCount[tempIndex][menuOptionIndex[tempIndex]] = listSize - 1;
	menuOptionIndex[tempIndex]++;
}

void base::addInt(const char *optionName, int *intValue, int min, int max, int inc)
{
	int tempIndex = tabIndex - 1;
	optionType[tempIndex][menuOptionIndex[tempIndex]] = TYPE_OPTION_INT;
	menuText[tempIndex][menuOptionIndex[tempIndex]] = optionName;
	listInts[tempIndex][menuOptionIndex[tempIndex]] = intValue;
	intMin[tempIndex][menuOptionIndex[tempIndex]] = min;
	intMax[tempIndex][menuOptionIndex[tempIndex]] = max;
	intInc[tempIndex][menuOptionIndex[tempIndex]] = inc;
	menuOptionIndex[tempIndex]++;
}

void base::addButton(const char *optionName, void *function, int r3, int r4, int r5)
{
	int tempIndex = tabIndex - 1;
	optionType[tempIndex][menuOptionIndex[tempIndex]] = TYPE_OPTION_CALL;
	menuText[tempIndex][menuOptionIndex[tempIndex]] = optionName;
	funcs[tempIndex][menuOptionIndex[tempIndex]] = function;
	arg1[tempIndex][menuOptionIndex[tempIndex]] = r3;
	arg2[tempIndex][menuOptionIndex[tempIndex]] = r4;
	arg3[tempIndex][menuOptionIndex[tempIndex]] = r5;

	menuOptionIndex[tempIndex]++;
}

bool base::menuOpen()
{
	return bMenuOpen;
}

void base::openMenu()
{
	bMenuOpen = true;
}

void base::closeMenu()
{
	bMenuOpen = false;
}

bool base::isHovering(float x, float y, float endX, float endY)
{
	POINT pt = POINT();
	GetCursorPos(&pt);
	if (ScreenToClient(GetForegroundWindow(), &pt))
	{
		if (pt.x < 0 || pt.y < 0)
			return false;

		vars.cursorPos = vector2(pt.x, pt.y);
		return (vars.cursorPos.x >= x && vars.cursorPos.y >= y) && (vars.cursorPos.x <= endX && vars.cursorPos.y <= endY);
	}
}