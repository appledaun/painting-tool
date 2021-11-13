#include "stdafx.h"
#include "component.h"
#include "View.h"
#include "ButtonListener.h"

using namespace std;

Component::Component()
{
}

Component::Component(std::string s, View * v) {
	m_title = s;
	m_view = v;
}

Component::Component(int x, int y, int sizex, int sizey, std::string title)
	:m_x(x), m_y(y), m_sizex(sizex), m_sizey(sizey), m_title(title)
{
}


Component::~Component()
{
}

// 평상시 그리는 함수 draw
void Component::draw()
{
	m_view->setPenColor(m_normal_bg_color);
	m_view->setFillColor(m_normal_bg_color);
	/*
	응용
	m_view->drawRectangle(m_x, m_y, m_x + m_sizex, m_y + m_sizey);
	SIZE s = m_view->textSize(m_title);
	int xoff = (m_sizex - s.cx) / 2;
	int yoff = (m_sizey - s.cy) / 2;
	m_view->setTextBkColor(m_normal_bg_color);
	m_view->drawText(m_title, m_x + xoff, m_y + yoff);
	*/
}

// 버튼 위로 마우스가 올라왔을 때 그림 그리는 함수.
void Component::tempDraw() {
	m_view->setPenColor(m_temp_bg_color);
	m_view->setFillColor(m_temp_bg_color);
	/*
	응용
	m_view->drawRectangle(m_x, m_y, m_x + m_sizex, m_y + m_sizey);
	SIZE s = m_view->textSize(m_title);
	int xoff = (m_sizex - s.cx) / 2;
	int yoff = (m_sizey - s.cy) / 2;
	m_view->setTextBkColor(m_temp_bg_color);
	m_view->drawText(m_title, m_x + xoff, m_y + yoff);
	*/
}

// 마우스가 버튼 위치에 있는지 판별하는 함수
bool Component::inside(int x, int y) {
	return (m_x <= x && x <= m_x + m_sizex
		&& m_y <= y && y <= m_y + m_sizey);
}

void Component::action() {
	debugOutput(m_title);
	for (auto i : lList) {
		i->actionPerformed(this);
	}
	//m_view->buttonActions(this);
}

void Component::openMenus() {
	
}

void Component::addButtonListener(ButtonListener * l) {
	lList.push_back(l);
}

void Component::open_menu(MenuBar * mb) {

}

