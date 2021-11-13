#pragma once
#include "string"
#include "component.h"

class View;

class MyButton :public Component
{
public:
	MyButton();
	MyButton(std::string s, View * v);
	~MyButton();
protected:
	//std::string m_title;
	//int m_x, m_y, m_sizex, m_sizey;
	//View *m_view = 0;
	//COLORREF m_normal_bg_color = RGB(230,230,230);
	//COLORREF m_temp_bg_color = RGB(200,200,200);
	//COLORREF m_line_color = RGB(0, 0, 0);
public:
	virtual void draw();
	virtual void tempDraw();
	//bool inside(int x, int y);
	//void action();
};

