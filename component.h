#pragma once
#include "string"
#include <list>
class View;
class ButtonListener;
class MenuBar;
class Component
{
public:
	Component();
	Component(std::string s, View * v);
	Component(int x, int y, int sizex, int siezy, std::string title);
	~Component();
protected:
	std::string m_title;
	HICON m_icon;
	int m_x, m_y, m_sizex, m_sizey;
	View *m_view = 0;
	COLORREF m_normal_bg_color = RGB(230, 230, 230);
	COLORREF m_temp_bg_color = RGB(200, 200, 200);
	COLORREF m_line_color = RGB(0, 0, 0);
	std::list<ButtonListener *> lList;
public:
	virtual void draw();
	virtual void tempDraw();
	bool inside(int x, int y);
	virtual void action();
	virtual void openMenus();
	virtual void addButtonListener(ButtonListener *);
	virtual void open_menu(MenuBar *);
	
};