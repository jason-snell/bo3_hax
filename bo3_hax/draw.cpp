#include "main.h"

void draw::line(float x1, float y1, float x2, float y2, const float *color, float width)
{
	float x, y, angle, l1, l2, h1;
	h1 = y2 - y1;
	l1 = x2 - x1;

	l2 = sqrt(l1 * l1 + h1 * h1);
	x = x1 + ((l1 - l2) / 2.0f);
	y = y1 + (h1 / 2.0f);
	angle = atan(h1 / l1) * 57.2957795f;

	CG_DrawRotatedPicW(ScrPlace_GetView(0), x, y, 1.0f, l2, width, 5, 5, angle, color, Material_RegisterHandle("white", 7, 1, -1), 0);
}

void draw::rect(float x, float y, float w, float h, const char *material, const float *color)
{
	R_AddCmdDrawStretchPic(x, y, w, h, 0, 0, 1, 1, color, Material_RegisterHandle(material, 7, 1, -1));
}

void draw::outline(float x, float y, float w, float h, const char *material, const float *color, float outlineWidth, bool filled, const float *fillColor)
{
	if(filled)
		R_AddCmdDrawStretchPic(x + outlineWidth, y + outlineWidth, w - (outlineWidth * 2.0f), h - (outlineWidth * 2.0f), 0.0f, 0.0f, 1.0f, 1.0f, fillColor, Material_RegisterHandle(material, 7, 1, -1)); // LEFT

	R_AddCmdDrawStretchPic(x, y, outlineWidth, h, 0.0f, 0.0f, 1.0f, 1.0f, color, Material_RegisterHandle(material, 7, 1, -1)); // LEFT
	R_AddCmdDrawStretchPic(x + outlineWidth, y, w - outlineWidth, outlineWidth, 0.0f, 0.0f, 1.0f, 1.0f, color, Material_RegisterHandle(material, 7, 1, -1)); // TOP
	R_AddCmdDrawStretchPic(x + outlineWidth, y + h - outlineWidth, w - (outlineWidth * 2.0f), outlineWidth, 0.0f, 0.0f, 1.0f, 1.0f, color, Material_RegisterHandle(material, 7, 1, -1)); // BOTTOM
	R_AddCmdDrawStretchPic(x + w - outlineWidth, y + outlineWidth, outlineWidth, h - outlineWidth, 0.0f, 0.0f, 1.0f, 1.0f, color, Material_RegisterHandle(material, 7, 1, -1)); // RIGHT
}

void draw::corner(float x, float y, float w, float h, float *color)
{
	float lineW = (w / 5.0f);
	float lineH = (h / 6.0f);
	float lineT = 1.0f;

	line(x, y, x, y + lineH, color, 1.0f); // top left
	line(x, y, x + lineW + 1, y, color, 1.0f);
	line(x + w - lineW - 2, y, x + w, y, color, 1.0f); // top right
	line(x + w, y, x + w, y + lineH, color, 1.0f);
	line(x, y + h - lineH, x, y + h, color, 1.0f); // bottom left
	line(x - 1, y + h, x + lineW + 1, y + h, color, 1.0f);
	line(x + w - lineW - 2, y + h, x + w, y + h, color, 1.0f); // bottom right
	line(x + w, y + h - lineH, x + w, y + h, color, 1.0f);
}

void draw::text(const char *text, float x, float y, int font, float fontSize, const float *color, char alignment, int outline, bool background, const float *backgroundColor)
{
	if (!text)
		return;

	void *font_ = R_RegisterFont(0, font);
	float textWidth = (float)R_TextWidth(0, text, 0x7FFFFFFF, font_) * fontSize;
	float textHeight = (float)R_TextHeight(font_) * fontSize;

	switch (alignment)
	{
	default:
	case 'l':
	case 'L':
		if(background)
			rect(x, y, textWidth, textHeight, "white", backgroundColor);

		CL_DrawTextPhysical(text, 0x7FFFFFFF, font_, x, y + textHeight, 1.0f, fontSize, fontSize, White, outline, 0.0f);
		break;
	case 'c':
	case 'C':
		if (background)
			rect(x - (textWidth / 2.0f), y, textWidth, textHeight, "white", backgroundColor);

		CL_DrawTextPhysical(text, 0x7FFFFFFF, font_, x - (textWidth / 2.0f), y + textHeight, 1.0f, fontSize, fontSize, color, outline, 0.0f);
		break;
	case 'r':
	case 'R':
		if (background)
			rect(x - textWidth, y, textWidth, textHeight, "white", backgroundColor);

		CL_DrawTextPhysical(text, 0x7FFFFFFF, font_, x - textWidth, y + textHeight, 1.0f, fontSize, fontSize, color, outline, 0.0f);
		break;
	}
}

void draw::checkBox(float x, float y, bool checked, float *checkColor)
{
	rect(x, y, 15.0f, 15.0f, "white", darkMenuColor);
	outline(x, y, 15.0f, 15.0f, "white", mint, 1.0f);

	if (checked)
	{
		void *scrPlace = ScrPlace_GetView(0);
		if (scrPlace)
		{
			CG_DrawRotatedPicW(scrPlace, x + 5.0f, y + 7.0f, 1.0f, 8.0f, 1.0f, 5, 5, -60.0f, checkColor, Material_RegisterHandle("white", 7, 1, -1), 0);
			CG_DrawRotatedPicW(scrPlace, x + 3.0f, y + 9.0f, 1.0f, 5.0f, 1.0f, 5, 5, 33.0f, checkColor, Material_RegisterHandle("white", 7, 1, -1), 0);
		}
	}
}

void draw::intSlider(int x, int y, int value, int min, int max)
{
	rect(x, y + 4.0f, 100.0f, 2.0f, "white", White);
	rect(x + value, y, 5.0f, 10.0f, "white", White);

	char textBuff[32] = { 0 };
	sprintf_s(textBuff, "<%i/%i>", value, max);
	text(textBuff, x - 2.0f, y - 6.0f, 1, 0.8f, White, 'r', 0, false);
}

void draw::circle(vector2 position, float points, float radius, const float *color)
{
	if (radius == 0)
		return;

	float step = (float)XM_PI * 2.0f / points;

	for (float a = 0; a < (XM_PI * 2.0f); a += step)
	{
		vector2 start(radius * cosf(a) + position.x, radius * sinf(a) + position.y);
		vector2 end(radius * cosf(a + step) + position.x, radius * sinf(a + step) + position.y);
		draw::line(start.x, start.y, end.x, end.y, color, 1.0f);
	}
}