#pragma once
#include "Figure.h"
class Rect :
	public Figure
{
public:
	Rect(int x1, int y1, int x2, int y2, COLORREF, COLORREF);
	~Rect();
	void draw();
	int getType();
};

