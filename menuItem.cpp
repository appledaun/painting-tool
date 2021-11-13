#include "stdafx.h"
#include "menuItem.h"

MenuItem::MenuItem() {

}

MenuItem::MenuItem(string s, View * v) : MyButton(s, v) {

}

void MenuItem::draw()
{
	Component::draw();
	/*
	���� Ŭ��������
	m_view->setPenColor(m_normal_bg_color);
	m_view->setFillColor(m_normal_bg_color);
	*/
	m_view->drawRectangle(m_x, m_y, m_x + m_sizex, m_y + m_sizey);
	SIZE s = m_view->textSize(m_title);
	int xoff = (m_sizex - s.cx) / 2;
	int yoff = (m_sizey - s.cy) / 2;
	m_view->setTextBkColor(m_normal_bg_color);
	m_view->drawText(m_title, m_x + xoff, m_y + yoff);

}

// ��ư ���� ���콺�� �ö���� �� �׸� �׸��� �Լ�.
void MenuItem::tempDraw() {

	Component::tempDraw();
	/*
	���� Ŭ��������
	m_view->setPenColor(m_temp_bg_color);
	m_view->setFillColor(m_temp_bg_color);
	*/
	m_view->drawRectangle(m_x, m_y, m_x + m_sizex, m_y + m_sizey);
	SIZE s = m_view->textSize(m_title);
	int xoff = (m_sizex - s.cx) / 2;
	int yoff = (m_sizey - s.cy) / 2;
	m_view->setTextBkColor(m_temp_bg_color);
	m_view->drawText(m_title, m_x + xoff, m_y + yoff);

}

void MenuItem::setLocation(int menuN, int menuItemN) {
	m_x = menuN * 48;
	m_y = menuItemN * 32;
	m_sizex = 48;
	m_sizey = 32;
}