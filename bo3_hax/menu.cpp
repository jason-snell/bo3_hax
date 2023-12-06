#include "main.h"


float menuX = 250.0f, menuY = 150.0f;
float width = 500.0f, height = 380.0f;
bool moveMenuStarted = false;
bool leftClicked = false;

int textFloat = 0;

bool testBool = false;

base menuBase = base();

void menu::createMenu()
{
	menuBase.addTab("Aimbot");
	menuBase.addBool("Aimbot", &vAimbot.aimbotOn);
	menuBase.addBool("Auto-Shoot", &vAimbot.autoshoot);
	menuBase.addBool("No Recoil", &vAimbot.rcs);
	menuBase.addBool("No Spread", &vAimbot.noSpread);
	menuBase.addList("Target Type", &vAimbot.targetType, targetType, 3);
	menuBase.addList("Aimbot Type", &vAimbot.aimbotType, aimbotType, 2);
	menuBase.addInt("FOV Radius", &vAimbot.fovRadius, 10, 300, 1);

	menuBase.addTab("ESP");
	menuBase.addList("Enemy Boxes", &vEsp.enemyBoxType, boxType, 5);
	menuBase.addList("Friendly Boxes", &vEsp.friendlyBoxType, boxType, 5);
	menuBase.addList("Names", &vEsp.nameEsp, nameEsp, 4);
	menuBase.addList("Enemy Snaplines", &vEsp.enemySnaplines, snaplines, 4);
	menuBase.addList("Friendly Snaplines", &vEsp.friendlySnaplines, snaplines, 4);
	menuBase.addList("Health Bars", &vEsp.healthBar, nameEsp, 4);
	menuBase.addList("Bones", &vEsp.bones, nameEsp, 4);
	menuBase.addBool("Item ESP", &vEsp.itemEsp);

	menuBase.addTab("Misc");
	menuBase.addButton("Disconnect", func::Disconnect);
	menuBase.addButton("CallVote", func::callVote);

	menuBase.addTab("Recovery");
	menuBase.addList("Crypto Key Amount", &vars.cryptoKeyAmount, cryptoKeyAmount, 6);
	menuBase.addBool("Give Crypto Keys", &vars.giveCryptoKeys);
	menuBase.addList("Crate Type", &vars.crateType, crateType, 2);
	menuBase.addBool("Buy Rare Crates", &vars.buyRareCrates);
	menuBase.addButton("Burn Duplicates", func::burnDuplicates);
}

bool isDropdownClicked = false;

void menu::drawMenu()
{
	ShowCursor(vars.menuOpen);
	// Check if X Close is hovered
	bool isHoveringX = false;
	if (menuBase.isHovering(menuX + (width - 20.0f), menuY + 5.0f, menuX + (width - 20.0f) + 15.0f, menuY + 20.0f))
		isHoveringX = true;
	else isHoveringX = false;

	if (!moveMenuStarted && isHoveringX && (GetAsyncKeyState(VK_LBUTTON) & 0x8000)) // Close Menu
		vars.menuOpen = false;

	static vector2 diff = vector2();
	if (menuBase.isHovering(menuX, menuY, menuX + width, menuY + 25.0f) && !isHoveringX && !moveMenuStarted)
	{
		if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
		{
			moveMenuStarted = true;
			diff = vector2(vars.cursorPos.x - menuX, vars.cursorPos.y - menuY);
		}
	}

	if (moveMenuStarted)
	{
		menuX = vars.cursorPos.x - diff.x;
		menuY = vars.cursorPos.y - diff.y;

		if (menuX < 0.0f)
			menuX = 0.0f;
		else if (menuX + width > 1280)
			menuX = 1280 - width;

		if (menuY < 0.0f)
			menuY = 0.0f;
		else if (menuY + height > 720)
			menuY = 720 - height;

		if (!(GetAsyncKeyState(VK_LBUTTON) & 0x8000))
			moveMenuStarted = false;
	}

	draw::rect(menuX, menuY, width, 25.0f, "white", darkMenuColor); // Move Bar
	draw::rect(menuX + (width - 20.0f), menuY + 5.0f, 15.0f, 15.0f, "white", xButtonColor); // X Button

	if (isHoveringX)
		draw::rect(menuX + (width - 20.0f), menuY + 5.0f, 15.0f, 15.0f, "white", red); // X Button

	draw::text("X", menuX + (width - 13.0f), menuY + 5.0f, 1, 0.5f, White, 'c', 0, false); // X Button Text
	draw::text("LTPFs BO3 HACK", menuX + (width / 2.0f), menuY + 1.0f, 1, 0.8f, White, 'c', 0, false); // Title
	draw::rect(menuX, menuY + 25, width, height - 25.0f, "white", lightMenuColor); // Background

	draw::rect(menuX, menuY + 50.0f, width, 1.0f, "white", darkMenuColor);
	draw::rect(menuX, menuY + 30.0f, width, 15.0f, "white", darkMenuColor);

	float tabWidth = width / (float)menuBase.tabIndex;

	for (int i = 0; i < menuBase.tabIndex; i++)
	{
		draw::text(menuBase.tabText[i], menuX + (tabWidth * i) + (tabWidth / 2.0f), menuY + 29.0f, 1, 0.5f, White, 'c', 0, false);
		if (menuBase.isHovering(menuX + (tabWidth * i) + 5.0f, menuY + 30.0f, menuX + (tabWidth * i) + tabWidth + 5.0f, menuY + 45.0f) && !moveMenuStarted)
		{
			if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
				menuBase.currentMenu = i;
		}
	}

	for (int i = menuBase.menuOptionIndex[menuBase.currentMenu] - 1; i >= 0; i--)
	{
		static bool sliderClicked[30] = { false }, dropDownClicked[30] = { false };
		char intBuffer[16] = { 0 };
		static int speedInc = 1;
		static int speedTimer = 0;
		static int clicked = false;
		draw::text(menuBase.menuText[menuBase.currentMenu][i], menuX + 10.0f, menuY + 55.0f + (i * 25.0f), 1, 0.7f, White, 'l', 0, false);
		switch (menuBase.optionType[menuBase.currentMenu][i])
		{
		case TYPE_OPTION_BOOL:
			draw::checkBox(menuX + (width - 28.0f), menuY + 57.0f + (i * 25.0f), *menuBase.menuBools[menuBase.currentMenu][i], mint);
			if (menuBase.isHovering(menuX + (width - 28.0f), menuY + 57.0f + (i * 25.0f), menuX + (width - 28.0f) + 15.0f, menuY + 57.0f + (i * 25.0f) + 15.0f))
			{
				if ((GetAsyncKeyState(VK_LBUTTON) & 0x8000) && !leftClicked)
				{
					leftClicked = true;
					*menuBase.menuBools[menuBase.currentMenu][i] = !*menuBase.menuBools[menuBase.currentMenu][i];
				}
				if (leftClicked && !(GetAsyncKeyState(VK_LBUTTON) & 0x8000))
					leftClicked = false;
			}
			break;
		case TYPE_OPTION_LIST:
			if (!dropDownClicked[i])
			{
				draw::rect(menuX + (width - 110.0f), menuY + 57.0f + (i * 25.0f), 100.0f, 18.0f, "white", darkMenuColor);
				draw::text((char*)menuBase.lists[menuBase.currentMenu][i][*menuBase.listInts[menuBase.currentMenu][i]], menuX + (width - 110.0f) + 50.0f, menuY + 57.0f + (i * 25.0f), 1, 0.6f, White, 'c', 0, false);
			}

			if (!dropDownClicked[i] && (menuBase.isHovering(menuX + (width - 110.0f), menuY + 57.0f + (i * 25.0f), menuX + (width - 110.0f) + 100.0f, menuY + 57.0f + (i * 25.0f) + 18.0f) && !isDropdownClicked))
			{
				if ((GetAsyncKeyState(VK_LBUTTON) & 0x8000) && !leftClicked)
				{
					dropDownClicked[i] = true;
					isDropdownClicked = true;
					leftClicked = true;
				}
				if (leftClicked && !(GetAsyncKeyState(VK_LBUTTON) & 0x8000))
					leftClicked = false;
			}
			else if (dropDownClicked[i])
			{
				for (int c = 0; c < menuBase.listOptionCount[menuBase.currentMenu][i] + 1; c++)
				{
					bool isHovering = false;
					if (menuBase.isHovering(menuX + (width - 110.0f), menuY + 57.0f + (i * 25.0f) + (c * 19.0f), menuX + (width - 110.0f) + 100.0f, menuY + 57.0f + (i * 25.0f) + (c * 19.0f) + 18.0f))
					{
						isHovering = true;
						if ((GetAsyncKeyState(VK_LBUTTON) & 0x8000) && !leftClicked)
						{
							*menuBase.listInts[menuBase.currentMenu][i] = c;
							dropDownClicked[i] = false;
							isDropdownClicked = false;
							leftClicked = true;
						}
						if (leftClicked && !(GetAsyncKeyState(VK_LBUTTON) & 0x8000))
							leftClicked = false;
					}
					draw::rect(menuX + (width - 110.0f), menuY + 57.0f + (i * 25.0f) + (c * 18.0f), 100.0f, 18.0f, "white", isHovering ? Black : darkMenuColor);
					draw::text((char*)menuBase.lists[menuBase.currentMenu][i][c], menuX + (width - 110.0f) + 50.0f, menuY + 57.0f + (i * 25.0f) + (c * 18.0f), 1, 0.6f, White, 'c', 0, false);
				}
			}
			break;
		case TYPE_OPTION_INT:
			draw::rect(menuX + (width - 110.0f), menuY + 57.0f + (i * 25.0f), 18.0f, 18.0f, "white", darkMenuColor);
			draw::text("<", menuX + (width - 110.0f) + 9.0f, menuY + 57.0f + (i * 25.0f), 1, 0.6f, White, 'c', 0, false);

			draw::rect(menuX + (width - 110.0f) + 82.0f, menuY + 57.0f + (i * 25.0f), 18.0f, 18.0f, "white", darkMenuColor);
			draw::text(">", menuX + (width - 110.0f) + 91.0f, menuY + 57.0f + (i * 25.0f), 1, 0.6f, White, 'c', 0, false);

			draw::rect(menuX + (width - 110.0f) + 19.0f, menuY + 57.0f + (i * 25.0f), 62.0f, 18.0f, "white", darkMenuColor);
			sprintf(intBuffer, "%i", *menuBase.listInts[menuBase.currentMenu][i]);
			draw::text(intBuffer, menuX + (width - 110.0f) + 50.0f, menuY + 57.0f + (i * 25.0f), 1, 0.6f, White, 'c', 0, false);

			if (menuBase.isHovering(menuX + (width - 110.0f), menuY + 57.0f + (i * 25.0f), menuX + (width - 110.0f) + 18.0f, menuY + 57.0f + (i * 25.0f) + 18.0f))
			{
				if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
				{
					if (speedTimer % 50 == 0)
						speedInc += 2;
					speedTimer++;
					if (speedTimer % 10 == 0)
						*menuBase.listInts[menuBase.currentMenu][i] -= speedInc;
					if (*menuBase.listInts[menuBase.currentMenu][i] < menuBase.intMin[menuBase.currentMenu][i])
						*menuBase.listInts[menuBase.currentMenu][i] = menuBase.intMin[menuBase.currentMenu][i];
				}
				if (!(GetAsyncKeyState(VK_LBUTTON) & 0x8000))
				{
					speedInc = 1;
					clicked = false;
					speedTimer = 0;
				}
			}
			else if (menuBase.isHovering(menuX + (width - 110.0f) + 82.0f, menuY + 57.0f + (i * 25.0f), menuX + (width - 110.0f) + 82.0f + 18.0f, menuY + 57.0f + (i * 25.0f) + 18.0f))
			{
				if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
				{
					if (speedTimer % 50 == 0)
						speedInc += 2;
					speedTimer++;
					if (speedTimer % 10 == 0)
						*menuBase.listInts[menuBase.currentMenu][i] += speedInc;
					if (*menuBase.listInts[menuBase.currentMenu][i] > menuBase.intMax[menuBase.currentMenu][i])
						*menuBase.listInts[menuBase.currentMenu][i] = menuBase.intMax[menuBase.currentMenu][i];
				}
				if (!(GetAsyncKeyState(VK_LBUTTON) & 0x8000))
				{
					speedInc = 1;
					clicked = false;
					speedTimer = 0;
				}
			}

			break;
		case TYPE_OPTION_FLOAT:
			break;
		case TYPE_OPTION_CALL:
			bool isHovering = false;
			if (menuBase.isHovering(menuX + (width - 110.0f), menuY + 57.0f + (i * 25.0f), menuX + (width - 110.0f) + 100.0f, menuY + 57.0f + (i * 25.0f) + 18.0f))
			{
				isHovering = true;
				if ((GetAsyncKeyState(VK_LBUTTON) & 0x8000) && !leftClicked)
				{
					leftClicked = true;
					if (menuBase.arg1[menuBase.currentMenu][i] == -1 && menuBase.arg2[menuBase.currentMenu][i] == -1)
					{
						void(*function)() = (void(*)())menuBase.funcs[menuBase.currentMenu][i];
						function();
					}
					else if (menuBase.arg1[menuBase.currentMenu][i] != -1 && menuBase.arg2[menuBase.currentMenu][i] == -1)
					{
						void(*function)(int) = (void(*)(int))menuBase.funcs[menuBase.currentMenu][i];
						function(menuBase.arg1[menuBase.currentMenu][i]);
					}
					else if (menuBase.arg1[menuBase.currentMenu][i] != -1 && menuBase.arg2[menuBase.currentMenu][i] != -1 && menuBase.arg3[menuBase.currentMenu][i] == -1)
					{
						void(*function)(int, int) = (void(*)(int, int))menuBase.funcs[menuBase.currentMenu][i];
						function(menuBase.arg1[menuBase.currentMenu][i], menuBase.arg2[menuBase.currentMenu][i]);
					}
					else if (menuBase.arg1[menuBase.currentMenu][i] != -1 && menuBase.arg2[menuBase.currentMenu][i] != -1 && menuBase.arg3[menuBase.currentMenu][i] != -1)
					{
						void(*function)(int, int, int) = (void(*)(int, int, int))menuBase.funcs[menuBase.currentMenu][i];
						function(menuBase.arg1[menuBase.currentMenu][i], menuBase.arg2[menuBase.currentMenu][i], menuBase.arg3[menuBase.currentMenu][i]);
					}
				}
				if (!(GetAsyncKeyState(VK_LBUTTON) & 0x8000) && leftClicked)
					leftClicked = false;
			}
			draw::rect(menuX + (width - 110.0f), menuY + 57.0f + (i * 25.0f), 100.0f, 18.0f, "white", isHovering ? mint : darkMenuColor);
			break;
		}
	}

	draw::rect(menuX + (tabWidth * menuBase.currentMenu) + 5.0f, menuY + 44.0f, tabWidth - 10.0f, 1.0f, "white", mint);

	//if (!strcmp((char*)func::GetActiveWindowTitle().c_str(), "Modern Warfare 2"))
	//	CG_DrawRotatedPicPhysical(addr->screenplacement, vars->pos.x - (60.0f / 2.0f), vars->pos.y - (60.0f / 2.0f), 60.0f, 60.0f, 0.0f, white, Material_RegisterHandle("ui_cursor", 0));
}