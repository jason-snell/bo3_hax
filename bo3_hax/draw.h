#pragma once

class draw
{
public:
	static void line(float x1, float y1, float x2, float y2, const float *color, float width);
	static void rect(float x, float y, float w, float h, const char *material, const float *color);
	static void outline(float x, float y, float w, float h, const char *material, const float *color, float outlineWidth, bool filled = false, const float *fillColor = 0);
	static void corner(float x, float y, float w, float h, float *color);
	static void text(const char *text, float x, float y, int font, float fontSize, const float *color, char alignment, int outline, bool background, const float *backgroundColor = 0);
	static void checkBox(float x, float y, bool checked, float *checkColor);
	static void intSlider(int x, int y, int value, int min, int max);
	static void circle(vector2 position, float points, float radius, const float *color);
};