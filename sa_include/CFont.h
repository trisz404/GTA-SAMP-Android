#ifndef __CFONT_H__
#define __CFONT_H__

class CFont
{
public:
	static void PrintString(float, float, unsigned short *);
	static void RenderFontBuffer();
	static float GetHeight(bool);
	
	static void SetFontStyle(unsigned char);
	static void SetBackground(unsigned char, unsigned char);
	static void SetBackgroundColor(CRGBA);
	static void SetWrapx(float);
	static void SetProportional(unsigned char);
	static void SetColor(CRGBA);
	static void SetEdge(signed char);
	static void SetDropColor(CRGBA);
	static void SetScale(float);
	static void SetOrientation(unsigned char);
};

#endif