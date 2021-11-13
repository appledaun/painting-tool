#include "stdafx.h"
#include "menu.h"
#include "Misc.h"
#include "component.h"
#include "View.h"
#include <string>
#include "container.h"
#include "menubar.h"

Menu::Menu() {

}

Menu::Menu(int n, View * v) {
	menuNum = n;
	m_view = v;
}


Menu::Menu(std::string s, View * v) : Container(s, v) {

}

//��ư �߰��ϱ�
void Menu::addMenu(MenuItem * m) {
	Container::addComponent(m); //m_CompList.push_back(t);
	m->setLocation(menuNum, menuItemNum);
	menuItemNum++;
}

//�޴� �׸���
void Menu::draw() {
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

//void Menu::draw();
void Menu::tempDraw() {
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


void Menu::openMenus() {
	for (auto b : m_CompList) {
		b->draw();
	}
}

void Menu::setLocation(int n) {
	m_x = n * 48;
	m_y = 0;
	m_sizex = 48;
	m_sizey = 32;
}

void Menu::open_menu(MenuBar * mb) {
	if (open) {	//�̹� �ش�޴��� �����ִٸ� 
		mb->close_menu();	//�޴� �� �ݱ� 
	}
	else {
		mb->close_menu();	//�޴� �� �ݱ� 
		open = 1;		//�ش� �޴��� ���� 
	}
}

void Menu::close_menu() {
	open = 0;
}

bool Menu::is_open() {
	//debugOutput("in\n");
	return open;
}