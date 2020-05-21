#ifndef RECT_H
#define RECT_H

class Rect{
	float x;
	float y;
	float w;
	float h;
	float r;
	float g;
	float b;

public:
	Rect();
	Rect(float, float, float, float, float r=1, float g=0, float b=0);

	void draw() const;

	void setY(float y);
	float getY() const;
};

#endif
