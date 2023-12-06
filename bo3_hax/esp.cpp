#include "main.h"

espVars vEsp;

boundsData esp::boundingBox(int c, float *color, int boxType)
{
	vector3 min = vector3(), max = vector3();

	void *dobj = Com_GetClientDObj(c, 0);

	if (!dobj)
		return boundsData();

	DObjPhysicsGetBounds(dobj, min, max);

	vector3 center = centity[c].origin;

	min += center;
	max += center;

	vector3 crnr[] =
	{
		vector3(max.x, min.y, min.z),
		vector3(max.x, min.y, max.z),
		vector3(min.x, min.y, max.z),
		vector3(min.x, max.y, max.z),
		vector3(min.x, max.y, min.z),
		vector3(max.x, max.y, min.z)
	};

	vector3 angle = centity[c].viewAngles;

	for (int i = 0; i < 6; i++)
		func::rotatePoint(crnr[i], center, angle, crnr[i]);

	func::rotatePoint(min, center, angle, min);
	func::rotatePoint(max, center, angle, max);

	vector2 smin, smax, crnr2, crnr3, crnr4, crnr5, crnr6, crnr7;

	float height = 0.0f, width = 0.0f;

	if (func::worldToScreen(min, smin)
		&& func::worldToScreen(max, smax)
		&& func::worldToScreen(crnr[0], crnr2)
		&& func::worldToScreen(crnr[1], crnr3)
		&& func::worldToScreen(crnr[2], crnr4)
		&& func::worldToScreen(crnr[3], crnr5)
		&& func::worldToScreen(crnr[4], crnr6)
		&& func::worldToScreen(crnr[5], crnr7))
	{
		vector2 arr[] = { smin, smax, crnr2, crnr3, crnr4, crnr5, crnr6, crnr7 };
		float left = smin.x;
		float top = smin.y;
		float right = smin.x;
		float bottom = smin.y;

		for (int i = 1; i < 8; i++)
		{
			if (left > arr[i].x)
				left = arr[i].x;
			if (top < arr[i].y)
				top = arr[i].y;
			if (right < arr[i].x)
				right = arr[i].x;
			if (bottom > arr[i].y)
				bottom = arr[i].y;
		}

		height = top - bottom;
		width = right - left;

		switch (boxType)
		{
		case BOX_2D: draw::outline(left, top - height, right - left, height, "white", color, 1.0f);
			break;
		case BOX_3D: 
			// From min to 2, 4 and 6 
			draw::line(smin.x, smin.y, crnr2.x, crnr2.y, color, 1.0f);
			draw::line(smin.x, smin.y, crnr4.x, crnr4.y, color, 1.0f);
			draw::line(smin.x, smin.y, crnr6.x, crnr6.y, color, 1.0f);

			// From max to 5, 7 and 3 
			draw::line(smax.x, smax.y, crnr5.x, crnr5.y, color, 1.0f);
			draw::line(smax.x, smax.y, crnr7.x, crnr7.y, color, 1.0f);
			draw::line(smax.x, smax.y, crnr3.x, crnr3.y, color, 1.0f);

			// From 2 to 7 and 3 
			draw::line(crnr2.x, crnr2.y, crnr7.x, crnr7.y, color, 1.0f);
			draw::line(crnr2.x, crnr2.y, crnr3.x, crnr3.y, color, 1.0f);

			// From 4 to 5 and 3 
			draw::line(crnr4.x, crnr4.y, crnr5.x, crnr5.y, color, 1.0f);
			draw::line(crnr4.x, crnr4.y, crnr3.x, crnr3.y, color, 1.0f);

			// From 6 to 5 and 7 
			draw::line(crnr6.x, crnr6.y, crnr5.x, crnr5.y, color, 1.0f);
			draw::line(crnr6.x, crnr6.y, crnr7.x, crnr7.y, color, 1.0f);
			break;
		case BOX_CORNER: draw::corner(left, top - height, right - left, height, color);
			break;
		case BOX_2DFILLED: draw::outline(left, top - height, right - left, height, "white", color, 1.0f, true, lightBlack);
			break;
		}

		return boundsData(left, top - height, right - left, height);
	}
}

void esp::bones(int clientNum, float *color)
{
	for (int i = 0; i < ARRAYSIZE(Bones) - 1; i++)
	{
		vector2 screen = vector2(), screen2 = vector2();
		vector3 bonePos1 = vector3(), bonePos2 = vector3();

		__int64 bone[2] = { GScr_AllocString(Bones[i]), GScr_AllocString(Bones[i + 1]) };
		if (func::getTagPos(clientNum, bone[0], bonePos1) && func::getTagPos(clientNum, bone[1], bonePos2))
		{
			if (func::worldToScreen(bonePos1, screen) && func::worldToScreen(bonePos2, screen2))
			{
				if(vAimbot.closestClient == clientNum && bone[0] == vAimbot.bestBone[clientNum])
					draw::line(screen.x, screen.y, screen2.x, screen2.y, red, 1);
				else
					draw::line(screen.x, screen.y, screen2.x, screen2.y, color, 1);
			}
		}
	}
}

void esp::player(int client)
{
	if (clientInfo[client].health == 0)
		return;

	float *color = vEsp.friendlyColor;

	if (func::notTeam(client))
		color = vAimbot.visible[client] ? vEsp.visibleColor : vEsp.enemyColor;

	vector2 screen = vector2();
	if (func::worldToScreen(centity[client].origin, screen))
	{
		if (func::notTeam(client))
		{
			boundsData bounds = boundingBox(client, color, vEsp.enemyBoxType);

			if (vEsp.nameEsp == NAME_ENEMY || vEsp.nameEsp == NAME_BOTH)
				draw::text(clientInfo[client].clientName, screen.x, bounds.y - 15.0f, 1, 0.5f, White, 'C', 0, false);

			if (vEsp.healthBar == NAME_ENEMY || vEsp.healthBar == NAME_BOTH)
			{
				float *healthColor = red;
				int pHealth = clientInfo[client].health;
				if (pHealth >= 75)
					healthColor = green;
				else if (pHealth > 30 && pHealth < 75)
					healthColor = yellow;
				else
					healthColor = red;

				float health = ((float)clientInfo[client].health / 100.0f) * bounds.height;
				draw::rect(bounds.x + bounds.width + 2.0f, bounds.y - health + bounds.height, 3, health, "white", healthColor);
			}

			switch (vEsp.enemySnaplines)
			{
			case SNAPLINE_TOP: draw::line(refDef->width / 2.0f, 0, screen.x, screen.y, color, 1.0f);
				break;
			case SNAPLINE_CENTER: draw::line(refDef->width / 2.0f, refDef->height / 2.0f, screen.x, screen.y, color, 1.0f);
				break;
			case SNAPLINE_BOTTOM: draw::line(refDef->width / 2.0f, refDef->height, screen.x, screen.y, color, 1.0f);
				break;
			}

			if (vEsp.bones == NAME_ENEMY || vEsp.bones == NAME_BOTH)
				bones(client, White);
		}
		else
		{
			boundsData bounds = boundingBox(client, color, vEsp.enemyBoxType);

			if (vEsp.nameEsp == NAME_FRIENDLY || vEsp.nameEsp == NAME_BOTH)
				draw::text(clientInfo[client].clientName, screen.x, bounds.y - 15.0f, 1, 0.5f, White, 'C', 0, false);

			if (vEsp.healthBar == NAME_FRIENDLY || vEsp.healthBar == NAME_BOTH)
			{
				float *healthColor = red;
				int pHealth = clientInfo[client].health;
				if (pHealth >= 75)
					healthColor = green;
				else if (pHealth > 30 && pHealth < 75)
					healthColor = yellow;
				else
					healthColor = red;

				float health = ((float)clientInfo[client].health / 100.0f) * bounds.height;
				draw::rect(bounds.x + bounds.width + 2.0f, bounds.y - health + bounds.height, 3, health, "white", healthColor);
			}

			switch (vEsp.friendlySnaplines)
			{
			case SNAPLINE_TOP: draw::line(refDef->width / 2.0f, 0, screen.x, screen.y, color, 1.0f);
				break;
			case SNAPLINE_CENTER: draw::line(refDef->width / 2.0f, refDef->height / 2.0f, screen.x, screen.y, color, 1.0f);
				break;
			case SNAPLINE_BOTTOM: draw::line(refDef->width / 2.0f, refDef->height, screen.x, screen.y, color, 1.0f);
				break;
			}

			if (vEsp.bones == NAME_FRIENDLY || vEsp.bones == NAME_BOTH)
				bones(client, White);
		}
	}
}

void esp::draw()
{
	if (centityAddr && cgAddr && centity && cg && refDef && clientInfo && ca)
	{
		for (int i = 0; i < 1024; i++)
		{
			if (cg->clientNumber == i || !centity[i].isAlive())
				continue;

			switch (centity[i].eType)
			{
			case ET_PLAYER: player(i);
				break;
			case ET_ITEM:
			case ET_MISSILE:
			case ET_HELICOPTER:
			case ET_PLANE:
				if(vEsp.itemEsp)
					boundsData bounds = boundingBox(i, blue, BOX_3D);
				break;
			case ET_ACTOR:
			case ET_ACTOR_CORPSE:
				boundsData bounds = boundingBox(i, pink, vEsp.enemyBoxType);
				break;
			}
		}
	}
}