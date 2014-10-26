#ifndef __CRGBA_H__
#define __CRGBA_H__

class CRGBA
{
private:
	float r;
	float g;
	float b;
	float a;
	
public:
	CRGBA(unsigned char, unsigned char, unsigned char, unsigned char);
	~CRGBA();
};

#endif